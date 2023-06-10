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

// Basic operations on numbers which do not fall into other categories
// For example initialization, copying etc.

ms8x32_err_t ms8x32_set_zero(ms8x32_t* n) {
    if(!n) return MS8X32_ERR_NULL_ARG;

    memset(&(n->digits[0]), 0x0, sizeof(uint32_t) * MS8X32_DIGITS);

    return MS8X32_SUCCESS;
}

ms8x32_err_t ms8x32_set_max(ms8x32_t* n) {
    if(!n) return MS8X32_ERR_NULL_ARG;

    memset(&(n->digits[0]), 0xff, sizeof(uint32_t) * MS8X32_DIGITS);

    return MS8X32_SUCCESS;
}

ms8x32_err_t ms8x32_copy(ms8x32_t* from, ms8x32_t* to) {
    if(!from || !to) return MS8X32_ERR_NULL_ARG;

    memcpy(to, from, sizeof(ms8x32_t));

    return MS8X32_SUCCESS;
}
