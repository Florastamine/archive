# Hotland 

[![Build Status](https://travis-ci.org/Florastamine/Hotland.svg?branch=master)](https://travis-ci.org/Florastamine/Hotland)

## Build instructions 
Due to the limtation of the aging [premake4](https://premake.github.io/), currently __Hotland__ only offers ready-to-use solution/project files for __Code::Blocks__, __CodeLite__, __GNU make__, __Xcode__ and __Microsoft Visual Studio 2012__. This limtation will be lifted with the replacement of [premake5](https://premake.github.io/) which will allow exporting build files targeting __Microsoft Visual Studio 2013__ and higher. In the meantime, if you're using Windows, you can just simply upgrade the 2012 project files in your Visual Studio IDE. 

First off, get the source code: 
```bash 
git clone https://github.com/Florastamine/Hotland
```

### Building on Microsoft Windows 
Simply open the solution file (`./Build/Hotland_VS2012.sln`), upgrade the projects to use the newer compiler/toolchain, and hit `F7`. 

The resulting files will be placed inside the `vs2012` folder. 

### Building on Linux and/or Windows with MinGW/Cygwin 
```bash 
cd ./Build 
make clean && make 
```

The resulting files will be placed inside the `gmake` folder. You can either `make` on `./Build` or `./Build/gmake`, building results will always be the same. 





