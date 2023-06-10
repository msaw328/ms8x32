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

#include "ms8x32/ms8x32.h"

#include "internal.h"

#include <stdint.h>
#include <string.h>
#include <stddef.h>

// Conversion between ms8x32_t and other types

ms8x32_err_t ms8x32_from_u32(ms8x32_t* n, uint32_t value) {
    if(!n) return MS8X32_ERR_NULL_ARG;

    n->digits[0] = value;
    memset(&(n->digits[1]), 0x0, sizeof(uint32_t) * (MS8X32_DIGITS - 1));

    return MS8X32_SUCCESS;
}

ms8x32_err_t ms8x32_to_u32(ms8x32_t* n, uint32_t* value) {
    if(!n || !value) return MS8X32_ERR_NULL_ARG;

    ms8x32_err_t status = MS8X32_SUCCESS;

    for(size_t idx = 1; idx < MS8X32_DIGITS; idx++) {
        if(n->digits[idx] != 0x0) status |= MS8X32_ERR_TRUNCATED;
    }

    *value = n->digits[0];

    return status;
}

ms8x32_err_t ms8x32_to_bytes(ms8x32_t* n, uint8_t* bytes_output, int byteorder) {
    if(!n || !bytes_output) return MS8X32_ERR_NULL_ARG;

    if(byteorder != MS8X32_BYTEORDER_LE && byteorder != MS8X32_BYTEORDER_BE) return MS8X32_ERR_INVALID;

    // Iterate over each digit
    for(size_t digit_idx = 0; digit_idx < MS8X32_DIGITS; digit_idx++) {
        size_t real_digit_idx = digit_idx;
        if(byteorder == MS8X32_BYTEORDER_BE) real_digit_idx = MS8X32_DIGITS - real_digit_idx - 1;

        // Iterate over each byte in a digit
        for(size_t byte_idx = 0; byte_idx < sizeof(uint32_t); byte_idx++) {
            size_t real_byte_idx = byte_idx;
            if(byteorder == MS8X32_BYTEORDER_BE) real_byte_idx = sizeof(uint32_t) - real_byte_idx - 1;

            bytes_output[digit_idx * 4 + byte_idx] = (uint8_t) (n->digits[real_digit_idx] >> (real_byte_idx * 8)) & 0xff;
        }
    }

    return MS8X32_SUCCESS;
}

ms8x32_err_t ms8x32_from_bytes(ms8x32_t* n, uint8_t* bytes_input, int byteorder) {
    if(!n || !bytes_input) return MS8X32_ERR_NULL_ARG;

    if(byteorder != MS8X32_BYTEORDER_LE && byteorder != MS8X32_BYTEORDER_BE) return MS8X32_ERR_INVALID;

    // Iterate over each digit
    for(size_t digit_idx = 0; digit_idx < MS8X32_DIGITS; digit_idx++) {
        size_t real_digit_idx = digit_idx;
        if(byteorder == MS8X32_BYTEORDER_BE) real_digit_idx = MS8X32_DIGITS - real_digit_idx - 1;

        // Iterate over each byte in a digit
        for(size_t byte_idx = 0; byte_idx < sizeof(uint32_t); byte_idx++) {
            size_t real_byte_idx = byte_idx;
            if(byteorder == MS8X32_BYTEORDER_BE) real_byte_idx = sizeof(uint32_t) - real_byte_idx - 1;

            n->digits[real_digit_idx] |= ((uint32_t) bytes_input[digit_idx * 4 + byte_idx]) << (real_byte_idx * 8);
        }
    }

    return MS8X32_SUCCESS;
}
