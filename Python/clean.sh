#!/bin/bash
find ./ \( -type d \( -name "__pycache__" -o -name "build" -o -name "bin" \
                    -o -name dist -o -name *.egg-info \) \
                    -o -type f \( -name "*.spec" \) \) \
-exec rm -rfv {} +
