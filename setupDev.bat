SET buildPath=%~dp0
if not exist %buildPath%\build mkdir %buildPath%\build
cd %buildPath%\build
conan install .. --build=missing -s cppstd=23 -s build_type=Debug
cmake .. -G "Visual Studio 17"
@pause