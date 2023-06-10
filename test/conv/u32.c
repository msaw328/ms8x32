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

int from_u32(void) {
    uint32_t from = 0xff8899aa;

    ms8x32_t expected_result = {
        .digits = { 0xff8899aa, 0, 0, 0, 0, 0, 0, 0 }
    };

    ms8x32_t result = { 0 };

    ms8x32_err_t status = ms8x32_from_u32(&result, from);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;
}

int to_u32(void) {
    uint32_t expected_result = 0xff8899aa;

    ms8x32_t a = {
        .digits = { 0xff8899aa, 0, 0, 0, 0, 0, 0, 0 }
    };

    uint32_t result = 0;

    ms8x32_err_t status = ms8x32_to_u32(&a, &result);

    if(status != MS8X32_SUCCESS) return 1;

    if(expected_result != result) return 2;

    return 0;
}

int to_u32_check_trunc(void) {
    uint32_t expected_result = 0xff8899aa;

    ms8x32_t a = {
        .digits = { 0xff8899aa, 0, 0, 0, 0, 0, 0, 0x1 }
    };

    uint32_t result = 0;

    ms8x32_err_t status = ms8x32_to_u32(&a, &result);

    if((status & MS8X32_ERR_TRUNCATED) == 0) return 1;

    if(expected_result != result) return 2;

    return 0;
}

int main(void) {
    runtest(1, from_u32);
    runtest(2, to_u32);
    runtest(3, to_u32_check_trunc);

    return 0;
}
