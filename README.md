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
