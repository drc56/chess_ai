find src/ -iname *.hpp -o -iname *.cpp | xargs clang-format-10 -i
find test/ -iname *.hpp -o -iname *.cpp | xargs clang-format-10 -i