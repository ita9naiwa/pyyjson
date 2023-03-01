# pyyjson

Yet another Json Parser for Python
- based on yyjson bindings from @TkTech's ([py_yyjson](https://github.com/ibireme/yyjson))
- original c library: [yyjson](https://github.com/ibireme/yyjson)
- benchmarks are based on [ultrajson](https://github.com/ultrajson/ultrajson)

### Installation

1. installation from pypi
```
    pip install pyyjson
```

2. installation from source
```
    git clone https://github.com/ita9naiwa/pyyjson
    cd pyyjson
    pip install .
```

### Supports
it supports standard `json` lib's
- dumps
- loads
- dump
- load

functions


### loads examples
```python
>>> import pyyjson
>>> pyyjson.loads("[1,2,3]")
[1, 2, 3]
>>> pyyjson.loads('[{"a":"b"}, 3, 4]')
[{'a': 'b'}, 3, 4]
```

### dumps example
```python
>>> pyyjson.dumps([{'a': 'b'}, 3, 4])
'[{"a":"b"},3,4]'
```

### load example

`load` take either string or file object. If string is given, it is assumed that it's a path to json file


```python
>>> import pyyjson
>>> pyyjson.load("simple_json.json") # in "tests/" directory
{'a': 1, 'b': 2, 'c': 3}
```

### dump example

`dump` take either string or file object. If string is given, it is assumed that it's a path to save the file

```python
>>> import pyyjson
>>> pyyjson.dump({'a': 1, 'b': 2, 'c': 3}, "simple_json.json")
```

### Benchmarks
each elements in cols denotes "calls/sec". Test suite is adapted from ujson's benchmark format.

|         content         |        |  json | ujson | orjson | pyyjson(mine) |
|:-----------------------:|:------:|:-----:|:-----:|:------:|:-------------:|
|    Arr of 256 doubles   | ENCODE |  10119 | 35361 | 170829 |44925        |
|    Arr of 256 dobules   | DECODE | 28684 | 54593 | 170383 |     155127    |
| Arr of 256 UTF-8 string | ENCODE |  5247 |  7344 |  45684 |      8554     |
| Arr of 256 UTF-8 String | DECODE |  2838 |  5223 |  7248  |      6424     |
|    Arr of 256 strings   | ENCODE | 36624 | 59568 | 216707 |     87624     |
|    Arr of 256 strings   | DECODE | 66842 | 66960 |  100252 |     98242     |
|  Medium complex object  | ENCODE |  9948 | 22344 |  80465 |     30888     |
|  Medium complex object  | DECODE | 17183 | 28733 |  45008 |     29267     |
