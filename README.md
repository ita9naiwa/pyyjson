![PyPI - License](https://img.shields.io/pypi/l/yyjson.svg?style=flat-square)
![Tests](https://github.com/TkTech/py_yyjson/workflows/Run%20tests/badge.svg)

# py_yyjson

Python bindings for the excellent [yyjson][] project.

## Documentation

[yyjson]: https://github.com/ibireme/yyjson
[py_yyjson]: http://github.com/TkTech/py_yyjson

Yet another Json Parser for Python
- based on yyjson bindings from @TkTech([yyjson](https://github.com/ibireme/yyjson))
- benchmarks are based on [ultrajson](https://github.com/ultrajson/ultrajson)

### Supports
it supports standard libraries
- dump
- dumps
- load
- loads

functionalities.

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

### Benchmarks
each elements in cols denotes "calls/sec". Test suite is adapted from ujson's benchmark format.

|         content         |        |  json | ujson | orjson | pyyjson(mine) |
|:-----------------------:|:------:|:-----:|:-----:|:------:|:-------------:|
|    Arr of 256 doubles   | ENCODE |  6201 | 27092 | 118710 |     67580     |
|    Arr of 256 dobules   | DECODE | 16252 | 38300 | 111293 |     73448     |
| Arr of 256 UTF-8 string | ENCODE |  3670 |  7516 |  33068 |      3815     |
| Arr of 256 UTF-8 String | DECODE |  2211 |  1636 |  4369  |      3162     |
|    Arr of 256 strings   | ENCODE | 28677 | 49102 | 171134 |     51165     |
|    Arr of 256 strings   | DECODE | 46222 | 30076 |  87968 |     50892     |
|  Medium complex object  | ENCODE |  8171 | 14272 |  63878 |     27021     |
|  Medium complex object  | DECODE | 16055 | 11789 |  32374 |     15795     |
