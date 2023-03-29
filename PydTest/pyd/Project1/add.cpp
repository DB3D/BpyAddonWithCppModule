
// Using visual studio 2017 make sure:
//    - Download same version of python as blender, and locate it, default on "C:\Users\USERNAME\AppData\Local\Programs\Python\Python310"
// project properties: 
//    - Top set on "All Configurations" "Active(x64)
//    - "ConfigurationProperties">"C/C++">"General">"AdditionalIncludeDirectories" set on :  ..\Python310\include
//    - "ConfigurationProperties">"Linker">"General">"AdditionalLibraryDirectories" set on : ..\Python310\libs
//    - "ConfigurationProperties">"Linker">"Input">"AdditionalDependencies" set on :         python310.lib

#include <Python.h> // Include the Python C API header, make sure the project properties are correct!

// Define the function that will be exposed to Python
// self: a reference to the module object (not used in this case)
// args: a tuple of arguments passed from Python

static PyObject* simpleadd_add(PyObject* self, PyObject* args) {
    int a, b;

    //In this part of the code, we're trying to convert the input arguments (passed from Python) into C++ variables:
    // Parse the input arguments, expecting two integers (ii)
    // If the parsing fails, return nullptr to indicate an error

    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return nullptr;
    }
    return Py_BuildValue("i", a + b); // Return the result of the addition as a Python integer
}

// The SimpleAddMethods array is a list of functions that will be available in Python when you import the module.
// In this case, we have only one function called add which is implemented by the simpleadd_add function in C++.
// We need this array to tell Python what functions are available in our moduleand how they should be called.

static PyMethodDef SimpleAddMethods[] = {
    {"add", simpleadd_add, METH_VARARGS, "Add two integers."},
    {nullptr, nullptr, 0, nullptr}
};

// Define the module structure
// The PyModuleDef structure holds information about our module, such as its name, documentation, and the list of available functions (methods).

static struct PyModuleDef simpleaddmodule = {
    PyModuleDef_HEAD_INIT, // Required boilerplate code, standard procedure..
    "simpleadd",           // Module name
    nullptr,               // Module documentation, can be nullptr if not provided
    -1,                    // Each Python interpreter has its own memory space and state. The size of the per-interpreter state is the amount of memory needed to store the module's data for each interpreter instance. In this case, we don't need any special memory allocation, so we set it to -1.
    SimpleAddMethods       // Array of module methods, Method definitions are simply the list of functions (methods) that our module provides, in this case, SimpleAddMethods.
};

// Module initialization function
// This is the function that Python calls when importing the module:
// The function returns a pointer to the module object, which means it returns the memory address where the module object is stored. This is how Python gets access to the module and its functions.

// - extern "C" is used to tell the C++ compiler to use the C calling convention, which is required for Python to be able to call the function correctly.
// - __declspec(dllexport) is a Microsoft - specific keyword that tells the compiler to export the function so that it can be used by other programs(in this case, Python).
// - PyMODINIT_FUNC is a macro that defines the proper return type and calling convention for the module initialization function.

extern "C" __declspec(dllexport) PyMODINIT_FUNC PyInit_simpleadd(void) {
    return PyModule_Create(&simpleaddmodule);
}

// Build:
// -Press F7 to compile (Release/x64)
// -Build should be successful, "1 succeeded, 0 failed"
// -New .dll should be available in the "Release folder", rename the extension of this .dll
//  in this project, "Project1.dll" to "simpleadd.pyd" that was moved near the main plugin __init__.py

// IMPORTANT NOTE: This will be built for WindowsOS only