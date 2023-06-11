#!/bin/bash
lcov -d . -o build/app.info -b . -c --exclude '*/test/*' --exclude '*/src/main/*'
genhtml build/app.info -o build/lcov
