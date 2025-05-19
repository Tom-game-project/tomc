# BNF形式で定義された文法構造を表現するのに十分な構造体を生成するためのプログラム
# https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm

import re
import pprint

from enum import Enum,auto

class TypeofToken(Enum):
    A = auto() # *   {<>}*
    Q = auto() # ?   {<>}?
    P = auto() # +   {<>}+
    U = auto() # uni <>
    S = auto() #     +


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
        return f"type_of_self {self.type_of_self}"

# 左辺
class BnfTree:
    name: str
    branch: list[list[BnfBranch]]
    raw: list[str] # ルール ex) [' <storage_class_specifier>\n', ' <type_specifier>\n', ' <type_qualifier>']
    def __init__(self, name:str, raw:str):
        self.name = name
        self.raw = raw

    def show(self):
        print (f"{id(self)}")
        for i in self.branch:
            print("    ",i)

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

# 定義された名前のリストから、名前だけが設定されたBnfTreeのリストを生成する
def set_bnftree_from_dec_name_list(dec_name_list: list[str], raw_list:list[str]) -> list[BnfTree]:
    return [BnfTree(i, j) for i, j in zip(dec_name_list,raw_list)]

# 定義されたBNFtreeのリストから、名前で要素を検索し、該当するもののアドレスを返却する
def find_bnftree_from_bnftree_list_by_name(bnf_tree: list[BnfTree], name: str) -> BnfTree:
    try:
        rv = next(filter(lambda a: a.name == name, bnf_tree))
    except StopIteration:
        return None
        #raise BaseException(f"name \"{name}\" not found")
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
# TODO 
def set_a_bnftree(bnftree: BnfTree, bnftree_list:list[BnfTree]) -> None:
    # bnftree.branch.append(BnfBranch(type_of_self, tree))
    # 
    bnftree.branch =  [[j for j in interpret_rule(i, bnftree_list)] for i in bnftree.raw]
    


if __name__ == "__main__":
    BNF_FILE = "bnf"
    name_list = get_all_dec_name(BNF_FILE)
    name_bnftreelist = set_bnftree_from_dec_name_list(
            name_list, 
            map(lambda i:get_dec(BNF_FILE, i), name_list))
    for i in name_bnftreelist:
        print("                " , i.name)
    #pprint.pprint(get_dec(BNF_FILE, "declaration_specifier"))
    #pprint.pprint(get_dec("struct_or_union_specifier"))
    #print(find_bnftree_from_bnftree_list_by_name(name_bnftreelist, "struct_or_union_specifier").name)
    
    for i in name_bnftreelist:
        set_a_bnftree(i, name_bnftreelist)

    for i in name_bnftreelist:
        i.show()
