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

int simple_multiplication(void) {
    ms8x32_t a = {
        .digits = { 0xffffffff, 0x24, 0, 0, 0, 0, 0, 0 }
    };

    ms8x32_t b = {
        .digits = { 0xffff4567, 0x9999, 0, 0, 0, 0, 0, 0 }
    };

    ms8x32_t expected_result = {
        .digits = { 0x0000ba99, 0xffe46e49, 0x163341, 0, 0, 0, 0, 0 }
    };

    ms8x32_t result = { 0 };

    ms8x32_err_t status = ms8x32_mul(&a, &b, &result);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;
}

int simple_overflow(void) {
    ms8x32_t a = {
        .digits = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xefffffff }
    };

    ms8x32_t b = {
        .digits = { 0xf8765232, 0x1245, 0, 0, 0, 0, 0, 0xff88112f }
    };

    ms8x32_t expected_result = {
        .digits = { 0x0789adce, 0xffffedba, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xe077eed0 }
    };

    ms8x32_t result = { 0 };

    ms8x32_err_t status = ms8x32_mul(&a, &b, &result);

    if((status & MS8X32_ERR_OVERFLOW) == 0) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;

}

int simple_multiplication_u32(void) {
    ms8x32_t a = {
        .digits = { 0xffffffff, 0x24, 0, 0, 0, 0, 0, 0 }
    };

    uint32_t b = 0xf89f123d;

    ms8x32_t expected_result = {
        .digits = { 0x0760edc3, 0xeefda2d0, 0x23, 0, 0, 0, 0, 0 }
    };

    ms8x32_t result = { 0 };

    ms8x32_err_t status = ms8x32_mul_u32(&a, b, &result);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;
}

int simple_overflow_u32(void) {
    ms8x32_t a = {
        .digits = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xefffffff }
    };

    uint32_t b = 0x7;

    ms8x32_t expected_result = {
        .digits = { 0xfffffff9, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x8fffffff }
    };

    ms8x32_t result = { 0 };

    ms8x32_err_t status = ms8x32_mul_u32(&a, b, &result);

    if((status & MS8X32_ERR_OVERFLOW) == 0) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;

}

int main(void) {
    runtest(1, simple_multiplication);
    runtest(2, simple_overflow);
    runtest(3, simple_multiplication_u32);
    runtest(4, simple_overflow_u32);

    return 0;
}
