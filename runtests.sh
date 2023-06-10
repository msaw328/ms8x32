#!/bin/bash

# ms8x32 - 256-bit integers, grouped as eight 32-bit words.
# Copyright (C) 2023  Maciej Sawka <maciejsawka@gmail.com> <msaw328@kretes.xyz>
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

# Make sure tests are built
make test

test_files=$(cd ./build/test && find . -executable -type f 2>/dev/null | sed 's/^.\///')
num_files=$(echo "$test_files" | wc -l)

export LD_LIBRARY_PATH="./build/lib/:$LD_LIBRARY_PATH"

# https://unix.stackexchange.com/a/10059
if [ -t 1 ]; then
    RED=$(tput setaf 1 2>/dev/null || echo -n "")
    GREEN=$(tput setaf 2 2>/dev/null || echo -n "")
    NC=$(tput sgr0 2>/dev/null || echo -n "")
else
    RED=""
    GREEN=""
    NC=""
fi

echo -e "Running tests:"
i="1"
for test_file in $test_files; do

    test_result="$GREEN[PASS]$NC"
    ./build/test/"$test_file"
    code="$?"
    if [ "$code" -ne "0" ]; then
        test_result="$RED[FAIL]$NC"
    fi

    # https://stackoverflow.com/a/4411098/5457426
    line="--------------------------------------------------------------------"
    printf "\tTest %03d/%03d ::: %s %s %s {%02x}\n" "$i" "$num_files" "$test_file" "${line:${#test_file}}" "$test_result" "$code"
    i=$((i + 1))
done
