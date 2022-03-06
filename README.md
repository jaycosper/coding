
# Coding

General coding techniques and algorithms for C and other languages, targeting various platforms.

## Build Process
This process was designed with a Linux-based flow in mind. It uses CMake to create the build environment. Testing is done through CTest and CuTest.

Most of these examples were built and tested using Ubuntu.
```bash
~$ git clone <repo>
~$ cd coding
~$ mkdir build
~$ cd build
~$ cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=clang-toolchain.cmake ..
~$ ninja
~$ cp ../averager/test/input.txt averager/test/
~$ ctest
```
The examples should build cleanly and all tests should pass. The copy of the averager input data is needed to address the relative path.

## Descriptions
Each folder contains a description of the example.

## Directory Structure
- *library_name*
    - inc
        - publically exposed files, typically only library header with types/apis.
        - *library_name*.h
    - test
        - CMakeLists.txt
            - CMake file for creating test executable
        - *library_name*_tests.c
            - Unit tests for this library
        - main.c
            - Generic CuTest main entry point
    - CMakeLists.txt
        - CMake file for library
    - *library_name*.c
        - library implementation code
## CMake
The CMake build process allows for sharing of libraries without full exposure of the library. Each library builds itself and the unit test. Minimal modification of the CMakeLists.txt files should be necessary.
## Creating A New Library
1. Copy *template* directory and replace all instances of *template* with your library name
1. Create library code in ./*library_name*.c and add public APIs to ./inc/*library_name*.h
1. Add your library c code to sourcefiles in ./CMakeLists.txt
1. Create tests for your library in ./test/*library_name*_test.c
    * if required, add other libraries that your library uses to this CMake file
    * target_link_libraries
1. Add your test code to ./CMakeLists.txt
1. Add your test c code to sourcefiles in ./test/CMakeLists.txt
1. Modify top-level CMakeLists.txt file to inlcude your library in the build
    * add_subdirectory(*library_name*)
1. run CMake build flow
### Troubleshooting
- Look for errors in the CMake installation (when running "cmake .."). This will indicate there is a problem with a CMakeLists.txt file.
- Use "make VERBOSE=1" to print out the build command. Flags and linked libraries (appearing as "-I\<path\>") are displayed in the output.
## TODO:
* Real linked list
* FIFO
* sorting algos / styles
* buffer manager
* CPP learnings
* FPGA

## VSCode VIM Bindings
Configured in settings.json
```json
{
   "vim.insertModeKeyBindingsNonRecursive": [
        {
        "before": ["j", "j"],
        "after": ["<ESC>"]
        }
    ],
    "vim.normalModeKeyBindingsNonRecursive": [
        {
        "before": [";"],
        "after": [":"]
        },
        {
        "before": ["leader", "w"],
        "after": [],
        "commands": [{
            "command": "editor.action.trimTrailingWhitespace",
            "args": []
            }]
        }
    ],
    "files.trimTrailingWhitespace": true,
    "files.trimFinalNewlines": true,
    "workbench.editor.enablePreview": false,
    "workbench.editor.enablePreviewFromQuickOpen": false,
    "editor.lineNumbers": "relative",
    "editor.renderWhitespace": "all",
    "workbench.editorAssociations": {
        "*.ipynb": "jupyter-notebook"
    },
    "workbench.editor.untitled.hint": "hidden",
    "terminal.integrated.tabs.enabled": true,
    "explorer.confirmDelete": false,
    "extensions.ignoreRecommendations": true,
    "notebook.cellToolbarLocation": {
        "default": "right",
        "jupyter-notebook": "left"
    }
}
```