import pytest
import json, pyyjson

obj_1 = [[{a:10 * ["AKGAKEKAKCASKC", "ASDKAEKAC", 1341341] for (i, a) in
         enumerate("abcdefghijklfaksdfjasejfasjiccabsbkq")}]]
obj_2 = {"text": [[{str(a):a*a for a in range(1000)}] for _ in range(13)]}

str_1 = json.dumps(obj_1)
str_2 = json.dumps(obj_2)

def test_basic_loads():
    assert json.loads(str_1) == pyyjson.loads(str_1)
    assert json.loads(str_2) == pyyjson.loads(str_2)

def test_basic_dumps():
    str_1_ = pyyjson.dumps(obj_1)
    assert json.loads(str_1_) == pyyjson.loads(str_1_)
    assert pyyjson.loads(str_1_) == obj_1

    str_2_ = pyyjson.dumps(obj_2)
    assert json.loads(str_2_) == pyyjson.loads(str_2_)
    assert pyyjson.loads(str_2_) == obj_2
