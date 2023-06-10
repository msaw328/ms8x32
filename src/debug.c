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

// TODO: Remove after debugging is removed
#include <stdio.h>

// TODO: remove it or make it debug-only or something
void ms8x32_debug_dump(ms8x32_t* n) {
    if(!n) return;
    uint32_t* nd = &(n->digits[0]);
    for(size_t idx = 0; idx < MS8X32_DIGITS; idx++) {
        printf("%08x%c", nd[8 - idx - 1], (idx == MS8X32_DIGITS - 1) ? ':' : ' ');
    }
    puts("");
}
