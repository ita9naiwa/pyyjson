from setuptools import setup, Extension

setup(ext_modules=[
        Extension(
            'pyyjson.cserde',
            [
                'pyyjson/binding.c',
                'pyyjson/memory.c',
                'pyyjson/yyjson.c',
            ],
            language='c'
        )
    ]
)
