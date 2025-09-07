from setuptools import setup, Extension

setup(
    name='fast_factorial_module',
    version='0.1',
    description='Fast factorial calculation using C',
    ext_modules=[
        Extension('fast_factorial', ['fast_factorial.c'])
    ]
)