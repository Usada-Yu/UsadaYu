#!/bin/bash
find ./ \( -type d \( -name "bin" -o -name "obj" \) \
-o -type f \( -name "*.o" -o -name "*.exe" -o -name "*.gcno" -o -name "*.gcda" \) \) \
-exec rm -rfv {} +
