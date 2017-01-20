set(SOURCE_FILES
        compactSuffixTree.cpp
        suffixTree.cpp)

set(HEADER_FILES
        compactSuffixTree.hpp
        suffixTree.hpp)

add_library(src STATIC ${HEADER_FILES} ${SOURCE_FILES})