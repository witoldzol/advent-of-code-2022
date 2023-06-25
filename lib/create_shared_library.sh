gcc -fPIC -g -c -Wall stack.cpp
gcc -shared -Wl,-soname,libstack.so.1 \
    -o libstack.so.1 stack.o -lc
