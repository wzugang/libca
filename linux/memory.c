/*
    Copyright 2015 Colby Skeggs

    This file is part of libca. See LICENSE.txt for details.

    libca is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libca is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with libca.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <memory.h>
#include <panic.h>

void *memset(void *buf, u8 chr, ulen count) {
	u8 *u8b = (u8*) buf;
	for (ulen i = 0; i < count; i++) {
		u8b[i] = chr;
	}
	return buf;
}
void *memset_c(void *dest, ulen max, u8 chr, ulen count) {
	if (dest == NULL) {
		panic_static("memset_c destination pointer is NULL");
	}
	if (count > max) {
		panic_static("memset_c caught overflow");
	}
	return memset(dest, chr, count);
}

void *memcpy(void *restrict dst, const void *restrict src, ulen count) {
	const u8 *u8s = (const u8*) src;
	u8 *u8d = (u8*) dst;
	for (ulen i = 0; i < count; i++) {
		u8d[i] = u8s[i];
	}
	return u8d;
}
void *memcpy_c(void *restrict dst, ulen bufsize, const void *restrict src, ulen count) {
	if (dst == NULL) {
		panic_static("memcpy_c destination pointer is NULL");
	}
	if (src == NULL) {
		panic_static("memcpy_c source pointer is NULL");
	}
	if (count > bufsize) {
		panic_static("memcpy_c caught overflow");
	}
	if (dst + bufsize > src && dst < src + count) {
		panic_static("memcpy_c attempted to use overlapping regions");
	}
	return memcpy(dst, src, count);
}

void *memmove(void *dst, const void *src, ulen count) { // similar to memcpy, but can handle overlapping ranges.
	const u8 *u8s = (const u8*) src;
	u8 *u8d = (u8*) dst;
	if (src < dst) { // we need to go in reverse to avoid the possibility of clobbering our source data.
		for (ulen i = count; i > 0;) {
			--i;
			u8d[i] = u8s[i];
		}
	} else {
		for (ulen i = 0; i < count; i++) {
			u8d[i] = u8s[i];
		}
	}
	return u8d;
}
void *memmove_c(void *dst, ulen bufsize, const void *src, ulen count) {
	if (dst == NULL) {
		panic_static("memmove_c destination pointer is NULL");
	}
	if (src == NULL) {
		panic_static("memmove_c source pointer is NULL");
	}
	if (count > bufsize) {
		panic_static("memmove_c caught overflow");
	}
	return memmove(dst, src, count);
}

i16 memcmp(const void *lhs, const void *rhs, ulen count) {
	const u8 *lh8 = (const u8 *) lhs, *rh8 = (const u8 *) rhs;
	while (count--) {
		if (*lh8 != *rh8) {
			return *lh8 - *rh8;
		}
		lh8++;
		rh8++;
	}
	return 0;
}
bool memeq(const void *lhs, const void *rhs, ulen count) {
	return memcmp(lhs, rhs, count) == 0;
}

const void *memchr(const void *ptrr, u8 chr, ulen count) {
	const u8 *ptr = (const u8*) ptrr;
	const u8 *max = ptr + count;
	while (ptr < max && *ptr != chr) {
		ptr++;
	}
	return ptr == max ? NULL : ptr;
}
