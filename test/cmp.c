// ms8x32 - 256-bit integers, grouped as eight 32-bit words.
// Copyright (C) 2023  Maciej Sawka <maciejsawka@gmail.com> <msaw328@kretes.xyz>
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <stdint.h>
#include <string.h>

#include "ms8x32/ms8x32.h"

#include "runtests.h"

int simple_greater_than() {
    ms8x32_t a = {
        .digits = { 0xf8765232, 0x1245, 0, 0, 0, 0, 0x1, 0 }
    };

    ms8x32_t b = {
        .digits = { 0xffffffff, 0, 0, 0, 0, 0, 0x1, 0 }
    };

    if(ms8x32_cmp(&a, &b) <= 0) return 1;

    if(!MS8X32_GT(&a, &b)) return 2;

    return 0;
}

int simple_equal() {
    ms8x32_t a = {
        .digits = { 0xffffffff, 0, 0, 0, 0, 0, 0x1, 0 }
    };

    ms8x32_t b = {
        .digits = { 0xffffffff, 0, 0, 0, 0, 0, 0x1, 0 }
    };

    if(ms8x32_cmp(&a, &b) != 0) return 1;

    if(!MS8X32_EQ(&a, &b)) return 2;

    return 0;
}

int simple_less_than() {
    ms8x32_t a = {
        .digits = { 0xf8765232, 0, 0, 0, 0, 0, 0, 0x2 }
    };

    ms8x32_t b = {
        .digits = { 0xffffffff, 0, 0, 0, 0, 0, 0, 0x2 }
    };

    if(ms8x32_cmp(&a, &b) >= 0) return 1;

    if(!MS8X32_LT(&a, &b)) return 2;

    return 0;
}

int main() {
    runtest(1, simple_less_than);
    runtest(2, simple_equal);
    runtest(3, simple_greater_than);
}
