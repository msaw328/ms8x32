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

int from_bytes_little_endian(void) {
    uint8_t source_bytes[] = {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88,
        0x99, 0xaa, 0xbb, 0xcc,
        0xdd, 0xee, 0xff, 0x00,

        0xf1, 0xe2, 0xd3, 0xc4,
        0xb5, 0xa6, 0x97, 0x88,
        0x79, 0x6a, 0x5b, 0x4c,
        0x3d, 0x2e, 0x1f, 0x00
    };

    ms8x32_t expected_result = {
        .digits = { 0x44332211, 0x88776655, 0xccbbaa99, 0x00ffeedd, 0xc4d3e2f1, 0x8897a6b5, 0x4c5b6a79, 0x001f2e3d }
    };

    ms8x32_t result = { 0 };

    ms8x32_err_t status = ms8x32_from_bytes(&result, &source_bytes[0], MS8X32_BYTEORDER_LE);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;
}

int from_bytes_big_endian(void) {
    uint8_t source_bytes[] = {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88,
        0x99, 0xaa, 0xbb, 0xcc,
        0xdd, 0xee, 0xff, 0x00,

        0xf1, 0xe2, 0xd3, 0xc4,
        0xb5, 0xa6, 0x97, 0x88,
        0x79, 0x6a, 0x5b, 0x4c,
        0x3d, 0x2e, 0x1f, 0x00
    };

    ms8x32_t expected_result = {
        .digits = { 0x3d2e1f00, 0x796a5b4c, 0xb5a69788, 0xf1e2d3c4, 0xddeeff00, 0x99aabbcc, 0x55667788, 0x11223344 }
    };

    ms8x32_t result = { 0 };

    ms8x32_err_t status = ms8x32_from_bytes(&result, &source_bytes[0], MS8X32_BYTEORDER_BE);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&result, &expected_result, sizeof(ms8x32_t)) != 0) return 2;

    return 0;
}

int to_bytes_little_endian(void) {
    uint8_t expected_bytes[] = {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88,
        0x99, 0xaa, 0xbb, 0xcc,
        0xdd, 0xee, 0xff, 0x00,

        0xf1, 0xe2, 0xd3, 0xc4,
        0xb5, 0xa6, 0x97, 0x88,
        0x79, 0x6a, 0x5b, 0x4c,
        0x3d, 0x2e, 0x1f, 0x00
    };

    ms8x32_t a = {
        .digits = { 0x44332211, 0x88776655, 0xccbbaa99, 0x00ffeedd, 0xc4d3e2f1, 0x8897a6b5, 0x4c5b6a79, 0x001f2e3d }
    };

    uint8_t bytes[MS8X32_BYTES_LENGTH] = { 0 };

    ms8x32_err_t status = ms8x32_to_bytes(&a, &bytes[0], MS8X32_BYTEORDER_LE);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&bytes[0], &expected_bytes[0], sizeof(uint8_t) * MS8X32_BYTES_LENGTH) != 0) return 2;

    return 0;
}

int to_bytes_big_endian(void) {
    uint8_t expected_bytes[] = {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88,
        0x99, 0xaa, 0xbb, 0xcc,
        0xdd, 0xee, 0xff, 0x00,

        0xf1, 0xe2, 0xd3, 0xc4,
        0xb5, 0xa6, 0x97, 0x88,
        0x79, 0x6a, 0x5b, 0x4c,
        0x3d, 0x2e, 0x1f, 0x00
    };

    ms8x32_t a = {
        .digits = { 0x3d2e1f00, 0x796a5b4c, 0xb5a69788, 0xf1e2d3c4, 0xddeeff00, 0x99aabbcc, 0x55667788, 0x11223344 }
    };

    uint8_t bytes[MS8X32_BYTES_LENGTH] = { 0 };

    ms8x32_err_t status = ms8x32_to_bytes(&a, &bytes[0], MS8X32_BYTEORDER_BE);

    if(status != MS8X32_SUCCESS) return 1;

    if(memcmp(&bytes[0], &expected_bytes[0], sizeof(uint8_t) * MS8X32_BYTES_LENGTH) != 0) return 2;

    return 0;
}

int main(void) {
    runtest(1, from_bytes_little_endian);
    runtest(2, from_bytes_big_endian);
    runtest(3, to_bytes_little_endian);
    runtest(4, to_bytes_big_endian);

    return 0;
}
