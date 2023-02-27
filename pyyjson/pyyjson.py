import enum
from serde import _loads, _dumps
import os

class ReaderFlags(enum.IntFlag):
    """
    Flags that can be passed into JSON reading functions to control parsing
    behaviour.
    """
    #: Stop when done instead of issues an error if there's additional content
    #: after a JSON document. This option may be used to parse small pieces of
    # JSON in larger data, such as NDJSON.
    STOP_WHEN_DONE = 0x02
    #: Allow single trailing comma at the end of an object or array, such as
    #: [1,2,3,] {"a":1,"b":2,}.
    ALLOW_TRAILING_COMMAS = 0x04
    #: Allow C-style single line and multiple line comments.
    ALLOW_COMMENTS = 0x08
    #: Allow inf/nan number and literal, case-insensitive, such as 1e999, NaN,
    #: inf, -Infinity
    ALLOW_INF_AND_NAN = 0x10
    #: Read number as raw string. inf/nan
    #: literal is also read as raw with `ALLOW_INF_AND_NAN` flag.
    NUMBERS_AS_RAW = 0x20


class WriterFlags(enum.IntFlag):
    """
    Flags that can be passed into JSON writing functions to control writing
    behaviour.
    """
    #: Write the JSON with 4-space indents and newlines.
    PRETTY = 0x01
    #: Escapes unicode as \uXXXXX so that all output is ASCII.
    ESCAPE_UNICODE = 0x02
    #: Escapes / as \/.
    ESCAPE_SLASHES = 0x04
    #: Writes Infinity and NaN.
    ALLOW_INF_AND_NAN = 0x08
    #: Writes Infinity and NaN as `null` instead of raising an error.
    INF_AND_NAN_AS_NULL = 0x10


def load(path, flags=0x00):
    if os.path.exists(path):
        pass
    else:
        raise FileNotFoundError(f"{path} not found!")
    with open(path, 'r') as f:
        txt = f.read()

    return loads(txt, flags)

def loads(doc, flags=0x00):
    return _loads(doc, flags)

def dumps(obj, ensure_ascii=False, escape_slash=False, flags=0x00):
    _flags = 0x00
    if ensure_ascii:
        _flags |= WriterFlags.ESCAPE_UNICODE
    if escape_slash:
        _flags |= WriterFlags.ESCAPE_SLASHES
    _flags |= flags
    return _dumps(obj, flags)

def dump(obj, fp, ensure_ascii=False, escape_slash=False, flags=0x00):
    _flags = 0x00
    if ensure_ascii:
        _flags |= WriterFlags.ESCAPE_UNICODE
    if escape_slash:
        _flags |= WriterFlags.ESCAPE_SLASHES
    _flags |= flags
    ret_str = _dumps(obj, _flags)
    return fp.write(ret_str)
