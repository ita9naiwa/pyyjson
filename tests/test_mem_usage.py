import os
import tracemalloc

import json, pyyjson, orjson
obj_1 = [[{a:10 * ["AKGAKEKAKCASKC", "ASDKAEKAC", 1341341] for (i, a) in
         enumerate("abcdefghijklfaksdfjasejfasjiccabsbkq")}]]
obj_2 = {"text": [[{str(a):a*a for a in range(1000)}] for _ in range(13)]}

str_1 = json.dumps(obj_1)
str_2 = json.dumps(obj_2)

tracemalloc.start()
for i in range(10000):
    str_1 = pyyjson.dumps(obj_1)
    obj_1 = pyyjson.loads(str_1)
snapshot = tracemalloc.take_snapshot()
top_stats = snapshot.statistics('lineno')
print("[ Top 3 ]")
for stat in top_stats[:10]:
    print(stat)
