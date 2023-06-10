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

int test_set_zero(void) {
    ms8x32_t expected_result = {
        .digits = { 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    ms8x32_t result = {
        .digits = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8 }
    };

    ms8x32_err_t status = ms8x32_set_zero(&result);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;
}

int test_set_max(void) {
    ms8x32_t expected_result = {
        .digits = {
            0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
            0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
        }
    };

    ms8x32_t result = {
        .digits = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8 }
    };

    ms8x32_err_t status = ms8x32_set_max(&result);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;
}

int test_copy(void) {
    ms8x32_t from = {
        .digits = {
            0x1, 0x2, 0x3, 0x4,
            0x5, 0x6, 0x7, 0x8
        }
    };

    ms8x32_t to = {
        .digits = {
            0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff
        }
    };

    ms8x32_err_t status = ms8x32_copy(&from, &to);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&from, &to, sizeof(ms8x32_t)) != 0) return 2;

    return 0;
}

int main(void) {
    runtest(1, test_set_zero);
    runtest(2, test_set_max);
    runtest(3, test_copy);

    return 0;
}
