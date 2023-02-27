# pyyjson

Yet another Json Parser for Python
- based on yyjson bindings from @TkTech([yyjson](https://github.com/ibireme/yyjson))
- benchmarks are based on [ultrajson](https://github.com/ultrajson/ultrajson)
- original c library: [yyjson]: https://github.com/ibireme/yyjson


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
|    Arr of 256 doubles   | ENCODE |  10119 | 35361 | 170829 |124386        |
|    Arr of 256 dobules   | DECODE | 28684 | 54593 | 170383 |     122328    |
| Arr of 256 UTF-8 string | ENCODE |  5247 |  7344 |  45684 |      8797     |
| Arr of 256 UTF-8 String | DECODE |  2838 |  5223 |  7248  |      5516     |
|    Arr of 256 strings   | ENCODE | 36624 | 59568 | 216707 |     136944     |
|    Arr of 256 strings   | DECODE | 66842 | 66960 |  100252 |     105645     |
|  Medium complex object  | ENCODE |  9948 | 22344 |  80465 |     56106     |
|  Medium complex object  | DECODE | 17183 | 28733 |  45008 |     26377     |
