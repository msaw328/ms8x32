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

#ifndef _MS8X32_H_
#define _MS8X32_H_

#include <stdint.h>

#include "ms8x32/errors.h"

// The 8 is in the name, since i only planned on 256 bits of precision,
// but majority of the code should be easy to adapt if one needs more bits.
// That being said, there is no guarantee about that, and maybe changing this
// value will break compilation. Also im pretty sure tests won't work.
#define MS8X32_DIGITS 8

struct ms8x32_t {
    uint32_t digits[MS8X32_DIGITS];
};
typedef struct ms8x32_t ms8x32_t;

// TODO: Remove it or make it debug-only or something
void ms8x32_debug_dump(ms8x32_t* n);

// Setters and getters of sorts - base.c
ms8x32_err_t ms8x32_set_zero(ms8x32_t* n);
ms8x32_err_t ms8x32_set_max(ms8x32_t* n);
ms8x32_err_t ms8x32_copy(ms8x32_t* from, ms8x32_t* to);

// Conversions - conv.c
ms8x32_err_t ms8x32_from_u32(ms8x32_t* n, uint32_t value);
ms8x32_err_t ms8x32_to_u32(ms8x32_t* n, uint32_t* value);
#define MS8X32_BYTEORDER_LE 0x1
#define MS8X32_BYTEORDER_BE 0x2
#define MS8X32_BYTES_LENGTH (256 / 8)
ms8x32_err_t ms8x32_to_bytes(ms8x32_t* n, uint8_t* bytes_output, int byteorder);
ms8x32_err_t ms8x32_from_bytes(ms8x32_t* n, uint8_t* bytes_input, int byteorder);

// Arithmetic - arithmetic.c
ms8x32_err_t ms8x32_add(ms8x32_t* a, ms8x32_t* b, ms8x32_t* result);
ms8x32_err_t ms8x32_add_u32(ms8x32_t* a, uint32_t b, ms8x32_t* result);
ms8x32_err_t ms8x32_mul(ms8x32_t* a, ms8x32_t* b, ms8x32_t* result);
ms8x32_err_t ms8x32_mul_u32(ms8x32_t* a, uint32_t b, ms8x32_t* result);

// Compare - cmp.c
// This function is not error-checked, since the only error that can occur
// is the NULL_ARG error, and this can be easily checked by the user.
// Returning the result directly allows for cleaner API.
// Returns negative, zero or positive value depending on if a is less than,
// equal or greater than b.
int ms8x32_cmp(ms8x32_t* a, ms8x32_t* b);
#define MS8X32_GT(a, b) (ms8x32_cmp(a, b) > 0)
#define MS8X32_EQ(a, b) (ms8x32_cmp(a, b) == 0)
#define MS8X32_LT(a, b) (ms8x32_cmp(a, b) < 0)

// TODO: implement shifts and rotates and binary ops
// Shifts and rotates
// uint8_t is enough to store all possible rotations, since 2^8 = 256 = 8 * 32
// ms8x32_err_t ms8x32_shr(ms8x32_t* n, uint8_t shift);
// ms8x32_err_t ms8x32_shl(ms8x32_t* n, uint8_t shift);
// ms8x32_err_t ms8x32_ror(ms8x32_t* n, uint8_t shift);
// ms8x32_err_t ms8x32_rol(ms8x32_t* n, uint8_t shift);



#endif
