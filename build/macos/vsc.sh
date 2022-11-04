rm -rf Release
cmake -G Xcode .
xcodebuild -configuration Release -project Lucy.xcodeproj
rm -rf Lucy.build
rm -rf Lucy.xcodeproj
rm -rf EagerLinkingTBDs
rm -rf build
rm -rf CMakeFiles
rm -rf CMakeScripts
rm -rf LTOCache
rm -rf cmake_install.cmake
rm -rf CMakeCache.txt
open Release/Lucy.app