#!/bin/bash
astyle --options=./.vscode/.astylerc -n --formatted --recursive src/\*.c,\*.h
astyle --options=./.vscode/.astylerc -n --formatted --recursive test/\*.c,\*.h