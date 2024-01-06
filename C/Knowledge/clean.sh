#!/bin/bash
find ./ \( -type d \( -name "bin" -o -name "obj" \) \
-type f \( -name "lovely" -o -name "*.o" \) \) \
-exec rm -rfv {} +
