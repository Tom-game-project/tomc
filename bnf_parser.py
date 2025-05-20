# BNF形式で定義された文法構造を表現するのに十分な構造体を生成するためのプログラム
# https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm


# TODO 定義が見つからなかったものについて保存する領域を作る

import re
import pprint

from enum import Enum,auto

class TypeofToken(Enum):
    A = auto() # *   {<>}*
    Q = auto() # ?   {<>}?
    P = auto() # +   {<>}+
    U = auto() # uni <>
    S = auto() #     normal string

# 右辺
class BnfBranch:
    type_of_self: TypeofToken
    tree: "BnfTree"
    #string:str # type -> TypeofToken.S
    def __init__(
            self,
            type_of_self: TypeofToken,
            tree: "BnfTree"
        ) -> "BnfBranch":
        self.type_of_self = type_of_self
        self.tree = tree

    def __repr__(self) -> str:
        match self.type_of_self:
            case TypeofToken.A:
                pass
            case TypeofToken.Q:
                pass
            case TypeofToken.P:
                pass
            case TypeofToken.U:
                pass
            case TypeofToken.S:
                return f"type_of_self {self.type_of_self} {'<' + self.tree.name + '>' if type(self.tree) is BnfTree else '\"' + self.tree + '\"'}"
        return f"type_of_self {self.type_of_self} {'<' + self.tree.name + '>' if type(self.tree) is BnfTree else self.tree}"

    def gen_c_struct(self):
        match self.type_of_self:
            case TypeofToken.A:
                return f"t_void_list *{self.tree.name}_list; // Vec<{self.tree.name}> Repeat more than 0 times(*)";
            case TypeofToken.P:
                return f"t_void_list *{self.tree.name}_list; // Vec<{self.tree.name}> Repeat one or more times(+)";
            case TypeofToken.Q:
                return f"struct s_{self.tree.name} * {self.tree.name}; // ?"
            case TypeofToken.U:
                return f"struct s_{self.tree.name} * {self.tree.name};"
            case TypeofToken.S:
                return f"// \"{self.tree}\" TODO"
        # return f"type_of_self {self.type_of_self} {'<' + self.tree.name + '>' if type(self.tree) is BnfTree else '\"' + self.tree + '\"'}"

    def gen_c_struct_and_set_enum(self, enum_contents_name:list):
        match self.type_of_self:
            case TypeofToken.A | TypeofToken.P | TypeofToken.Q | TypeofToken.U:
                enum_contents_name.append(self.tree.name)
            case _:
                pass
        return self.gen_c_struct()


def create_struct_from_list(lst:list, structure_name: str, structure_type_name:str, depth:int) -> str:
    rstr = "\n" + " " * 4 * depth + f"struct {structure_name} {{\n"
    for i in lst:
        rstr += " " * 8 * depth + f"{i}\n"
    rstr += " " * 4 * depth + f"}} {structure_type_name};\n"
    return rstr


def create_struct_from_list_and_set_enum(enum_contents_name: list, lst:list, structure_name: str, structure_type_name:str, depth:int):
    enum_contents_name.append(structure_type_name)
    return (create_struct_from_list(lst, structure_name, structure_type_name, depth))

def create_union_from_list(lst:list, union_name:str, depth:int) -> str:
    rstr = " " * 4 * depth + "union {\n"
    for i in lst:
        rstr += " " * 8 * depth + f"{i}\n"
    rstr += " " * 4 * depth + f"}} {union_name};\n"
    return rstr

def create_enum_from_list(lst:list, enum_name:str, depth: int) -> str:
    rstr = " " * 4 * depth + "enum {\n"
    rstr += (",\n").join([" " * 8 * depth + i for i in lst]) + "\n"
    #for i in lst:
    #    rstr += " " * 8 * depth + f"{i},\n"
    rstr += " " * 4 * depth + f"}} {enum_name};\n"
    return rstr


# 左辺
class BnfTree:
    name: str
    undef_flag: bool
    branch: list[list[BnfBranch]]
    raw: list[str] # ルール ex) [' <storage_class_specifier>\n', ' <type_specifier>\n', ' <type_qualifier>']
    def __init__(self, name:str, raw:str):
        self.name = name
        self.raw = raw
        self.undef_flag = True

    def show(self):
        #print (f"<{self.name}> at {id(self)} raw[{self.raw}]")
        print (f"<{self.name}> raw[{self.raw}]")
        for i in self.branch:
            print("    ",i)

    def gen_c_struct(self):
        enum_contents_name = []
        lst = [
                [j.gen_c_struct() for j in i] 
                for i in self.branch
        ]


        lst2 = []
        for i, j in enumerate(lst):
            if len(j) == 1:
                enum_contents_name.append(f"case_{i}")
                lst2.append(j[0])
            else:
                lst2.append(create_struct_from_list_and_set_enum(enum_contents_name, j, "", f"case_{i}", 2))
        # 内部のコンテンツを判定するenumを定義する、TODO
        
        enum_code = create_enum_from_list(
                map(lambda a: f"e_{self.name}_{a}", enum_contents_name) , "type_of_contents", 1)

        return create_struct_from_list(
            [enum_code, lst2[0] if len(lst2) == 1 else create_union_from_list(lst2, "contents", 1)],
            f"s_{self.name}",
            "",
            0
        )

# すべての定義名を返す
def get_all_dec_name(bnffile:str):
    rlist:str = []
    regex = re.compile(r"<(.*)> ::= (.*)")

    with open(bnffile, encoding="utf-8", mode='r') as f:
        for i, j in enumerate(f):
            group = regex.match(j)
            if group != None:
                rlist.append(group[1])
    return rlist

# 名前から定義部分を抽出する
def get_dec(bnffile:str, name:str):
    rlist = []
    dec = False

    with open("bnf", encoding="utf-8", mode='r') as f:
        for i, j in enumerate(f):
            if j.startswith(f"<{name}> ::="):
                dec = True
                rlist.append(j[6 + len(name):])
                continue
            if dec:
                if len(j) <= 5 + len(name):
                    continue
                elif j[5 + len(name)] == '|':
                    rlist.append(j[6 + len(name):])
                else:
                    break
            else: continue

    return list(map(lambda a: a[:-1] if a.endswith("\n") else a, rlist))

# 定義された左辺の名前のリストから、名前だけが設定されたBnfTreeのリストを生成する
def set_bnftree_from_dec_name_list(dec_name_list: list[str], raw_list:list[str]) -> list[BnfTree]:
    return [BnfTree(i, j) for i, j in zip(dec_name_list,raw_list)]

# 定義されたBNFtreeのリストから、名前で要素を検索し、該当するもののアドレスを返却する
def find_bnftree_from_bnftree_list_by_name(bnf_tree: list[BnfTree], name: str) -> BnfTree:
    try:
        rv = next(filter(lambda a: a.name == name, bnf_tree))
    except StopIteration:
        bnt = BnfTree(name, "")
        bnf_tree.append(bnt)
        return bnt
    return rv

def interpret_rule(rule:str, bnftree_list: list[BnfTree]) -> list[BnfBranch]:
    pattern = ""
    rlist = []
    regex_a = re.compile(r"\{<(.*)>\}\*")
    regex_q = re.compile(r"\{<(.*)>\}\?")
    regex_p = re.compile(r"\{<(.*)>\}\+")
    regex_uni = re.compile(r"<(.*)>")
    lst = rule.split(' ')
    for i in lst[1:]:
        if (pattern:= regex_a.match(i)) != None:
            rlist.append(
                    BnfBranch(
                        TypeofToken.A, 
                        find_bnftree_from_bnftree_list_by_name(
                            bnftree_list,pattern[1])))
        elif (pattern:= regex_q.match(i)) != None:
            rlist.append(
                    BnfBranch(
                        TypeofToken.Q, 
                        find_bnftree_from_bnftree_list_by_name(
                            bnftree_list,pattern[1])))
        elif (pattern:= regex_p.match(i)) != None:
            rlist.append(
                    BnfBranch(
                        TypeofToken.P, 
                        find_bnftree_from_bnftree_list_by_name(
                            bnftree_list,pattern[1])))
        elif (pattern:= regex_uni.match(i)) != None:
            rlist.append(
                    BnfBranch(
                        TypeofToken.U, 
                        find_bnftree_from_bnftree_list_by_name(
                            bnftree_list,pattern[1])))
        else:
            rlist.append(BnfBranch(TypeofToken.S, i))
    return rlist


# BnfTreeをBNFファイルに基づいて各種設定をする
def set_a_bnftree(bnftree: BnfTree, bnftree_list:list[BnfTree]) -> None:
    bnftree.branch =  [[j for j in interpret_rule(i, bnftree_list)] for i in bnftree.raw]


if __name__ == "__main__":
    BNF_FILE = "bnf"
    name_list = get_all_dec_name(BNF_FILE)
    name_bnftreelist = set_bnftree_from_dec_name_list(
            name_list, 
            map(lambda i:get_dec(BNF_FILE, i), name_list))
    # for i in name_bnftreelist:
    #     print("                " , i.name)
    #pprint.pprint(get_dec(BNF_FILE, "declaration_specifier"))
    #pprint.pprint(get_dec("struct_or_union_specifier"))
    #print(find_bnftree_from_bnftree_list_by_name(name_bnftreelist, "struct_or_union_specifier").name)
    
    for i in name_bnftreelist:
        set_a_bnftree(i, name_bnftreelist)

    for i in name_bnftreelist:
        print(i.gen_c_struct())
    # print(name_bnftreelist[0].gen_c_struct())
