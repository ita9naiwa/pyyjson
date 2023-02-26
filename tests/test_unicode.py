import json, ujson, pyyjson, orjson
msg = {"김밥":"이는고양이"}
print("json lib")
m = json.dumps(msg, ensure_ascii=True)
print(m)
recovered = json.loads(m)
print(recovered)

print("ujson lib")
m = ujson.dumps(msg, ensure_ascii=True)
print(m)
recovered = json.loads(m)
print(recovered)

print("orjson lib")
m = orjson.dumps(msg)
print(m)
recovered = json.loads(m)
print(recovered)

print("myjson lib")
m = pyyjson.dumps(msg, ensure_ascii=True)
print(m)
recovered = json.loads(m)
print(recovered)