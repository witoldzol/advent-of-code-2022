gcc -fPIC -g -c -Wall stack.cpp
gcc -shared -Wl,-soname,libstack.so.1 \
    -o libstack.so.1.0.0 stack.o -lc
