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

#ifndef _MS8X32_ERRORS_H_
#define _MS8X32_ERRORS_H_

// Error codes for the library

typedef uint32_t ms8x32_err_t;

// If ms8x32_error == MS8X32_SUCCESS it means that operation succeeded and was safe
#define MS8X32_SUCCESS (ms8x32_err_t) 0x0

// If (ms8x32_error & MS8X32_ERR_*) != 0 it means that the appropriate error happened
#define MS8X32_ERR_NULL_ARG (ms8x32_err_t) (1 << 0) // One of arguments is null
#define MS8X32_ERR_OVERFLOW (ms8x32_err_t) (1 << 1) // Overflow happened (bits left bounds to the left) - addition, leftshift, multiplication
#define MS8X32_ERR_UNDERFLOW (ms8x32_err_t) (1 << 2) // Underflow happened (bits left bounds to the right) - subtraction, rightshift
#define MS8X32_ERR_TRUNCATED (ms8x32_err_t) (1 << 3) // Conversion from ms8x32num to smaller type truncated some important bits
#define MS8X32_ERR_INVALID (ms8x32_err_t) (1 << 4) // Invalid value of an argument

#endif
