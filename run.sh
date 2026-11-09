#!/bin/bash

cd ./build || exit 1

MAKE=false
CMAKE=false
SANDBOX=""

print_usage() {
    echo "Usage: ./run.sh [-c] [-m] (-l | -a)"
    echo "  -c: Generate CMake build files"
    echo "  -m: Compile selected sandbox"
    echo "  -l: Run low-level sandbox"
    echo "  -a: Run application sandbox"
}

while getopts "mlac" opt; do
    case $opt in
        m) MAKE=true;;
        c) CMAKE=true;;
        l) SANDBOX="sandbox_lowlevel";;
        a) SANDBOX="sandbox_application";;
        *) print_usage; exit 1;;
    esac
done

if [[ -z "$SANDBOX" ]]; then
    echo "Error: No sandbox specified. (-l or -a must be provided)"
    print_usage
    exit 1
fi

if [[ "$CMAKE" == true ]]; then
    cd .. || exit 1
    cmake . -Bbuild || exit 1
    cd build || exit 1
fi

if [[ "$MAKE" == true ]]; then
    make "$SANDBOX" || exit 1
fi

cd "$SANDBOX" || exit 1
./"$SANDBOX"
