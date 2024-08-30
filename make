cd ./src
find -name '*.o' -exec rm {} \;
USE_GCC=1 make 
