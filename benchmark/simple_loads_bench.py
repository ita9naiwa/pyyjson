import json, orjson, ujson, pyyjson
import time

N = 5000

obj_1 = [[{a:10 * ["하하하하하하하하하", 3.14159, 1341341] for (i, a) in
         enumerate("abcdefghijklfaksdfjasejfasjiccabsbkq")}]]
obj_2 = {"text": [[{str(a):a*a for a in range(1000)}] for _ in range(5)]}

str_1 = json.dumps(obj_1)
str_2 = json.dumps(obj_2)
print("simple loads test")
for lib, name in [(json,"json"), (ujson, "ujson"), (orjson, "orjson"), (pyyjson, "pyyjson")]:
    prev = time.time()
    for i in range(N):
        lib.dumps(obj_1)
        lib.dumps(obj_2)
    now = time.time()
    print(f"[lib {name}]:", now - prev, "secs")
