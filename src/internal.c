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
#include <stdio.h>

// Some procedures used internally by the library, not to be exposed
// to the end-user. Those may in the future be moved into other source files.

// Input:
//  - a, b = 32 bit unsigned numbers which we want to add
//  - prev_carry = carry from a previous addition
//
// Returns: The topmost 32 bits from the operation of a + b + prev_carry (its addition, so it will be either 1 or 0)
uint32_t _u32_add_carry(uint32_t a, uint32_t b, uint32_t prev_carry) {
    return (U32_MAX - b >= a && U32_MAX - a - b >= prev_carry) ? 0 : 1;
}

// Input:
//  - a, b = 32 bit unsigned numbers which we want to multiply
//  - prev_carry = carry from a previous multiplication
//
// Returns: The topmost 32 bits from the operation of a * b + prev_carry
uint32_t _u32_mul_carry(uint32_t a, uint32_t b, uint32_t prev_carry) {
    uint32_t a_hi16 = a >> 16;
    uint32_t b_hi16 = b >> 16;
    a &= 0xffff;
    b &= 0xffff;

    // Summing each of 16-bit "digits" in order from lowest
    uint32_t carry = (a * b) + (prev_carry & 0xffff);
    carry = (carry >> 16) + ((a_hi16 * b) & 0xffff) + ((b_hi16 * a) & 0xffff) + (prev_carry >> 16);
    carry = (carry >> 16) + (a_hi16 * b_hi16) + ((a_hi16 * b) >> 16) + ((b_hi16 * a) >> 16);

    return carry;
}


