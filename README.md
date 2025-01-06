# fsystem : Lua File System Module

This repository provides a simple Lua module to access system file features using C. The module includes functionality to read the contents of a directory.
This is mainly a didactic project and for a personal need, but it can be useful! Do not hesitate...

## Features

- `readdirFile(path)` : Reads file names from the specified directory and returns a Lua table with the names of regular files.

## Compilation

To compile the C source code into a shared library (`fsystem.so`), use the following command:

```bash
gcc -shared -fPIC -o ./fsystem.so ./fsystem.c -I/usr/include/lua5.4 -llua5.4
```

This command will generate the fsystem.so shared object, which can be loaded into Lua.

## Testing

To test the module, you can use the main.lua script. Here’s an example of how to run it:

```bash
lua main.lua
```

Make sure that fsystem.so is in the same directory or in your package.cpath.

The main.lua script will require the module, call readdirFile to list files in the specified directory (/home/johndoe in the example), and print each file name.

## License

This project is licensed under the MIT License.

## Feedback

I am open to any feedback or suggestions for improvements. Feel free to open an issue or submit a pull request.