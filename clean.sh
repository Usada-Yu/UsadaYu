#!/bin/bash

pre_dir=$(pwd)

# remove common directory
find ${pre_dir} -type d \( -name "bin" -o -name "obj"                   \
    -o -name "build" -o -name "dist" -o -name "artifact" \)             \
    -exec rm -rfv {} +

# remove python directory
find ${pre_dir} -type d \( -name "__pycache__"                          \
    -o -name "*.egg-info" \)                                            \
    -exec rm -rfv {} +

# remove common file
find ${pre_dir} -type f \( -name "*.o"                                  \
    -o -name "*.gcno" -o -name "*gcda" \)                               \
    -exec rm -rfv {} +

# remove python file
find ${pre_dir} -type f \( -name "*.spec" \)                            \
    -exec rm -rfv {} +
