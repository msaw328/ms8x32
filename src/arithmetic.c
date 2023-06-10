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
#include <stddef.h>

// Regular arithmetic operations on numbers

ms8x32_err_t ms8x32_add(ms8x32_t* a, ms8x32_t* b, ms8x32_t* result) {
    if(!a || !b || !result) return MS8X32_ERR_NULL_ARG;

    // Data pointers
    uint32_t* rd = &(result->digits[0]);
    uint32_t* ad = &(a->digits[0]);
    uint32_t* bd = &(b->digits[0]);

    ms8x32_set_zero(result);

    ms8x32_err_t status = MS8X32_SUCCESS;

    uint32_t carry = 0;
    for(size_t idx = 0; idx < MS8X32_DIGITS; idx++) {
        rd[idx] = ad[idx] + bd[idx] + carry;
        carry = _u32_add_carry(ad[idx], bd[idx], carry);
    }

    if(carry != 0) status |= MS8X32_ERR_OVERFLOW;

    return status;
}

ms8x32_err_t ms8x32_add_u32(ms8x32_t* a, uint32_t b, ms8x32_t* result) {
    if(!a || !b || !result) return MS8X32_ERR_NULL_ARG;

    // Data pointers
    uint32_t* rd = &(result->digits[0]);
    uint32_t* ad = &(a->digits[0]);

    ms8x32_set_zero(result);

    ms8x32_err_t status = MS8X32_SUCCESS;

    uint32_t carry = 0;
    for(size_t idx = 0; idx < MS8X32_DIGITS; idx++) {
        rd[idx] = ad[idx] + b + carry;
        carry = _u32_add_carry(ad[idx], b, carry);
        
        b = 0; // b only really impacts the bottom digit, skip it in higher digits
    }

    if(carry != 0) status |= MS8X32_ERR_OVERFLOW;

    return status;
}

ms8x32_err_t ms8x32_mul(ms8x32_t* a, ms8x32_t* b, ms8x32_t* result) {
    if(!a || !b || !result) return MS8X32_ERR_NULL_ARG;

    // Data pointers
    uint32_t* rd = &(result->digits[0]);
    uint32_t* ad = &(a->digits[0]);
    uint32_t* bd = &(b->digits[0]);

    ms8x32_set_zero(result);

    ms8x32_err_t status = MS8X32_SUCCESS;

    for(size_t b_idx = 0; b_idx < MS8X32_DIGITS; b_idx++) {
        uint32_t mul_carry = 0, add_carry = 0;
        for(size_t a_idx = 0; a_idx + b_idx < MS8X32_DIGITS; a_idx++) {
            uint32_t tmp = rd[a_idx + b_idx] + (ad[a_idx] * bd[b_idx]) + mul_carry + add_carry;
            add_carry = _u32_add_carry(rd[a_idx + b_idx], ad[a_idx] * bd[b_idx] + mul_carry, add_carry);
            mul_carry = _u32_mul_carry(ad[a_idx], bd[b_idx], mul_carry);
            rd[a_idx + b_idx] = tmp;
        }

        if(mul_carry != 0 || add_carry != 0) status |= MS8X32_ERR_OVERFLOW;
    }

    return status;
}

ms8x32_err_t ms8x32_mul_u32(ms8x32_t* a, uint32_t b, ms8x32_t* result) {
    if(!a || !result) return MS8X32_ERR_NULL_ARG;

    // Data pointers
    uint32_t* rd = &(result->digits[0]);
    uint32_t* ad = &(a->digits[0]);

    ms8x32_set_zero(result);

    ms8x32_err_t status = MS8X32_SUCCESS;

    uint32_t mul_carry = 0, add_carry = 0;
    for(size_t a_idx = 0; a_idx < MS8X32_DIGITS; a_idx++) {
        uint32_t tmp = rd[a_idx] + (ad[a_idx] * b) + mul_carry + add_carry;
        add_carry = _u32_add_carry(rd[a_idx], ad[a_idx] * b + mul_carry, add_carry);
        mul_carry = _u32_mul_carry(ad[a_idx], b, mul_carry);
        rd[a_idx] = tmp;
    }

    if(mul_carry != 0 || add_carry != 0) status |= MS8X32_ERR_OVERFLOW;

    return status;
}
