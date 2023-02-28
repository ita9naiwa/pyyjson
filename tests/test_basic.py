import pytest
import json, pyyjson

obj_1 = [[{a:10 * ["AKGAKEKAKCASKC", "ASDKAEKAC", 1341341] for (i, a) in
         enumerate("abcdefghijklfaksdfjasejfasjiccabsbkq")}]]
obj_2 = {"text": [[{str(a):a*a for a in range(1000)}] for _ in range(13)]}

str_1 = json.dumps(obj_1)
str_2 = json.dumps(obj_2)

def test1_basic_loads():
    assert json.loads(str_1) == pyyjson.loads(str_1)
    assert json.loads(str_2) == pyyjson.loads(str_2)

def test2_basic_dumps():
    str_1_ = pyyjson.dumps(obj_1)
    assert json.loads(str_1_) == pyyjson.loads(str_1_)
    assert pyyjson.loads(str_1_) == obj_1

    str_2_ = pyyjson.dumps(obj_2)
    assert json.loads(str_2_) == pyyjson.loads(str_2_)
    assert pyyjson.loads(str_2_) == obj_2

def test3_load_bytes_and_strs():
    a = b"[1,2,3,4]"
    b = "[1,2,3,4]"
    assert json.loads(a) == [1,2,3,4]
    assert json.loads(b) == [1,2,3,4]

def test4_unicode_json_compatibility():
    for ensure_ascii in [False, True]:
        msg = {"김밥":"이는고양이", "오뎅": ["그러면", "누가", "멍멍이지?"]}
        d = json.dumps(msg, ensure_ascii=ensure_ascii)
        assert json.loads(d) == pyyjson.loads(d)
        d = pyyjson.dumps(msg, ensure_ascii=ensure_ascii)
        assert json.loads(d) == pyyjson.loads(d)

def test5_bytes():
    msg_bytes = {"ita9naiwa": b"blahblah"}
    msg_nobytes = {"ita9naiwa": "blahblah"}
    assert pyyjson.dumps(msg_bytes) == pyyjson.dumps(msg_nobytes)

def test6_time_example():
    import datetime, time
    now = datetime.datetime.now()
    def default_parser1(obj):
        if isinstance(obj, datetime.datetime):
            return int(time.mktime(obj.timetuple()))
        raise TypeError(f"Type {type(obj)} is not serializable")
    pyyjson.dumps([1,2, now], default=default_parser1)
