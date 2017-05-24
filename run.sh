#!/usr/bin/env bash

for script in tests/*.cc; do

    ${CXX:=g++} -o /tmp/test -std=c++1z -O3 -Itools "$script"
    { ulimit -s 16384; timeout 0.5s /tmp/test; } >& /dev/null

    if [[ $? -eq 124 ]]; then
        printf "  \e[32m✓\e[39m $script\n"
    else
        printf "  \e[31m✗\e[39m $script\n"
    fi

done
