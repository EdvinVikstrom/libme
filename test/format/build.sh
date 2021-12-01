#clang++ format_test.cpp -std=c++20 -g -O3 -lfmt
#clang++ -DNO_TIMER format_test.cpp -std=c++20 -g -O3
#clang++ -S -DNO_TIMER format_test.cpp -std=c++20 -O3
clang++ -o me meformat.cpp -std=c++20 -g -O3 -lfmt
