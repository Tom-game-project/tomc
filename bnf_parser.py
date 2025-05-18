# BNF形式で定義された文法構造を表現するのに十分な構造体を生成するためのプログラム
# https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm

import re
import pprint

from enum import Enum,auto

class TypeofToken(Enum):
    A = auto() # *
    Q = auto() # ?
    P = auto() # +

class BnfBranch:
    type_of_self: TypeofToken
    tree: BnfTree
    def __init__(
            self,
            type_of_self: TypeofToken,
            tree: BnfTree
        ) -> BnfBranch:
        self.type_of_self = type_of_self
        self.tree = tree

class BnfTree:
    name: str
    branch: list[BnfBranch]
    def __init__(
        self, 
        name: str,
        branch: list[BnfBranch]
        ) -> BnfTree:
        self.name = name
        self.branch = branch


# すべての定義名を返す
def get_all_dec_name(code: str):
    rlist:str = []
    regex = re.compile(r"<(.*)> ::= (.*)")

    with open("bnf", encoding="utf-8", mode='r') as f:
        for i, j in enumerate(f):
            group = regex.match(j)
            if group != None:
                rlist.append(group[1])
    return rlist

# なまえから定義部分を抽出する
def get_dec(name:str):
    rlist = []
    dec = False

    with open("bnf", encoding="utf-8", mode='r') as f:
        for i, j in enumerate(f):
            if j.startswith(f"<{name}> ::="):
                dec = True
                rlist.append(j[6 + len(name):])
                continue
            if dec:
                if len(j) < 5 + len(name):
                    continue
                elif j[5 + len(name)] == '|':
                    rlist.append(j[6 + len(name):].split(' '))
                else:
                    break
            else: continue
    return rlist


if __name__ == "__main__":
    name_list = get_all_dec_name("hello")
    pprint.pprint(name_list)
    pprint.pprint(get_dec("declaration_specifier"))
    pprint.pprint(get_dec("struct_or_union_specifier"))
    
