from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension

ext_modules = [
    Pybind11Extension(
        "mymod",
        sorted(glob("src/*.cpp")),  # Sort source files for reproducibility
    ),
]

setup(name="mymod",
       ext_modules=ext_modules)