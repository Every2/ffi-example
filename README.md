# FFI EXAMPLE

A simple example of FFI in cpp using the `extern C` keyword with the simple function `add` that doesn't use any lib or anything in cpp just a simple fuction and the py module file called `addTwoIntegers.c` that use CPython api.

# How run this code

Is suposed to everything run fine in PythonFFI folder, so u just need to run:

```bash
python ffi.py
```

but you can build your own addTwoIntegers module with CMameLists.txt via Visual Studio 2022 Cmake project. 

### For windows users

I try use VSCODE, but it never find `Python.h` file even I including in the Path, so I used VS2022 and everything worked. So I believe that is not possible run with vscode.

# How the CPython api code works?

`static PyObject* py_add`: Wrap the C++ integer data type and convert to Python (long long) integer data type into tuple notation the () notation.

`static PyMethodDef MyMethods[]`: Define the add method.

`static struct PyModuleDef addTwoIntegers`:  Define the module convention and make ready to use in Python.

`PyMODINIT_FUNC PyInit_addTwoIntegers`: Use a Python macro to help with specific plataform generation, in windows is DLL and crate and return a Python object.

# FAQ

### Why you used a .pyd file instead a DLL?

I wanted to call the ffi module like a native libraby. e.g:

```Python
import addTwoIntegers 
```

And not using the DLL method that not look like a native. For show what i'm trying to say, I will show the code snipet in DLL way:

```Python
import ctypes

addmodule = ctypes.CDLL('addTwoIntegers.dll')

result = addmodule.add(2, 3)
print(result)  
```

### I wanna build like a dll not .pyd

Idk why you wanted to do this, but you just need remove the `set_target_properties(addTwoIntegers PROPERTIES SUFFIX ".pyd")` line and vs should generate a .dll for you

### Is possible convert a dll to .pyd?

No, but you can generate .pyd file via Python build with .c source file.

Create a python file like this:

```Python
from distutils.core import setup, Extension

module = Extension('addTwoIntegers', sources=['addTwoIntegers.c'])

setup(name='addTwoIntegers',
      version='1.0',
      description='Add two integers',
      ext_modules=[module])
```

and run those commands:

```bash
python setup.py build
python setup.py install
```

### Why not use something like pybind?

I wanted to learn about ffi process from scratch, the CPython api is already an abstraction so I avoided more abstractions, but pybind can be really useful. 

# References

https://en.wikipedia.org/wiki/Foreign_function_interface

https://docs.python.org/3/c-api/index.html

https://learn.microsoft.com/en-us/cpp/cpp/extern-cpp?view=msvc-170
