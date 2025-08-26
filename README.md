This is a simple code example to demonstrate Python and C++ interoperability using the `pybind11` library.

## Outline

Note: these instructions are for MacOS

### 1. Install pybind11

Create a Python virtual environment for this project and activate it.

```bash
python -m venv .venv
source .venv/bin/activate
```

Install Pybind11 https://github.com/pybind/pybind11

```bash
pip install pybind11
```

### 2. Set the path to pybind11.h includes folder

Locate the pybind11 `includes` folder

```bash
python -m pybind11 --includes
```

You should get something like: 
`-I/opt/homebrew/opt/python@3.13/Frameworks/Python.framework/Versions/3.13/include/python3.13 -I/Users/<your-username>/<path-to-project>/python-cpp-test/.venv/lib/python3.13/site-packages/pybind11/include`

Note: the first path should correspond to your Python installation. My Python was installed with homebrew. The path to yours may differ.

### 3. Both the compiler and the IDE require the path to the pybind11.h file

Impt: I used **VSCode** and git ignored / excluded the `.vscode` folder. 
You must update the `c_cpp_properties.json` because the paths for my machine won't work on yours. 😃

- Open the Command Palette: Press Ctrl+Shift+P (or Cmd+Shift+P on macOS).
- Search for C/C++ Edit Configurations: Type "C/C++: Edit Configurations (JSON)" and select it. This will open a file named `c_cpp_properties.json`
- Edit the includePath: Inside the "configurations" array, you'll find an object with an "includePath" array. Add the paths to your pybind11 and Python include directories to this array.

```json
"includePath": [
                "${workspaceFolder}/**",
                "/Users/<your-username>/<path-to-project>/python-cpp-test/.venv/lib/python3.13/site-packages/pybind11/include",
                "/opt/homebrew/opt/python@3.13/Frameworks/Python.framework/Versions/3.13/include/python3.13",
            ],
```

### 4. Compile `sumInt.cpp` into a shared library that Python can import

```bash
clang++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` sumInt.cpp -o sumInt`python3-config --extension-suffix` -undefined dynamic_lookup
```

#### Notes: 

`-shared` 
tells compiler to create a shared file. 

`-std=c++11`
 compile the code according to the C++11 standard

`-fPIC`
Position-Independent Code -  code cannot rely on absolute memory addresses

`-I` flag tells the compiler where to search for #include files.

"-o sumInt`python3-config --extension-suffix`" 
returns `-o sumInt.cpython-313-darwin.so` (if you are on Apple Silicon)

`-undefined dynamic_lookup`
tells the compiler to ignore missing symbols

### 5. Run Python code

```bash
python test.py
```