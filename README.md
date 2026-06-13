# seedfinding

A minimal Minecraft seedfinding setup that uses [Xpple's fork of Cubiomes](https://github.com/xpple/cubiomes).

To compile both Cubiomes and you own programs stored in the `src` folder, enter the following command.
```
make
```
To run the specific program `src/filename.c`, enter the following command. Notice that `filename` does not include the extension.
```
make run TARGET=filename
```

To clean the repository, meaning deleting the `build` and `cubiomes/build` folder, enter the following command.
```
make clean
```