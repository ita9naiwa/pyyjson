import json
import orjson
import ujson
import pyyjson
import time

N = 10000

obj_1 = [[{a: 10 * ["하하하하하하하하하", 3.14159, 1341341] for (i, a) in
         enumerate("abcdefghijklfaksdfjasejfasjiccabsbkq")}]]
obj_2 = {"text": [[{str(a): a * a for a in range(1000)}] for _ in range(5)]}

str_1 = json.dumps(obj_1)
str_2 = json.dumps(obj_2)
print("simple dumps test")
for lib, name in [(json, "json"), (ujson, "ujson"), (orjson, "orjson"), (pyyjson, "pyyjson")]:
    prev = time.time()
    for i in range(N):
        lib.dumps(str_1)
        lib.dumps(str_2)
    now = time.time()
    print(f"[lib {name}]:", now - prev, "secs")
