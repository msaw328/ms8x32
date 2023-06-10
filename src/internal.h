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

#ifndef _MS8X32_INTERNAL_H_
#define _MS8X32_INTERNAL_H_

#include <stdint.h>

// Some procedures used internally by the library, not to be exposed
// to the end-user. Those may in the future be moved into other source files.

#define U32_MAX (uint32_t) (0xffffffff)

// Input:
//  - a, b = 32 bit unsigned numbers which we want to add
//  - prev_carry = carry from a previous addition
//
// Returns: The topmost 32 bits from the operation of a + b + prev_carry (its addition, so it will be either 1 or 0)
uint32_t _u32_add_carry(uint32_t a, uint32_t b, uint32_t prev_carry);

// Input:
//  - a, b = 32 bit unsigned numbers which we want to multiply
//  - prev_carry = carry from a previous multiplication
//
// Returns: The topmost 32 bits from the operation of a * b + prev_carry
uint32_t _u32_mul_carry(uint32_t a, uint32_t b, uint32_t prev_carry);

#endif
