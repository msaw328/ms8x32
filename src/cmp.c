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

// Comparision between two numbers

// Returns positive value, 0 or negative value if a is greater than, equal to or less than b
// NOT constant time!
int ms8x32_cmp(ms8x32_t* a, ms8x32_t* b) {
    uint32_t* ad = &(a->digits[0]);
    uint32_t* bd = &(b->digits[0]);

    for(size_t idx = 0; idx < MS8X32_DIGITS; idx++) {
        size_t i = MS8X32_DIGITS - idx - 1;
        if(ad[i] > bd[i]) return 1;
        if(ad[i] < bd[i]) return -1;
    }
    
    return 0;
}
