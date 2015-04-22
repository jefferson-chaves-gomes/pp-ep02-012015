Instruções de compilação:

** MacOS:
    1 - g++ -I/usr/local/Cellar/gcc49/4.9.2_1/lib/gcc/4.9/gcc/x86_64-apple-darwin14.1.0/4.9.2/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/main.d" -MT"src/main.d" -o "src/main.o" "../src/main.cpp"
    2 - g++ -L/usr/local/Cellar/gcc49/4.9.2_1/lib/gcc/4.9 -o "prog" ./src/main.o