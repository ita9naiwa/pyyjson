import os
import os.path

from setuptools import setup, find_packages, Extension


root = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(root, 'README.md'), 'rb') as readme:
    long_description = readme.read().decode('utf-8')

setup(
    name='pyyjson',
    packages=find_packages(),
    version='0.1.0',
    description='yet another json libs using yyjson',
    long_description=long_description,
    long_description_content_type='text/markdown',
    author='Hyunsung Lee',
    author_email='ita9naiwa@gmail.com',
    url='http://github.com/ita9naiwa/pyyjson',
    keywords=['json', 'yyjson', 'pyyjson'],
    zip_safe=False,
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Development Status :: 3 - Alpha'
    ],
    python_requires='>3.4',
    extras_require={
        'test': [
            'pytest'
        ]
    },
    ext_modules=[
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
