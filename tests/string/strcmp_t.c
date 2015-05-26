/*
    This file is part of libca/tests. See LICENSE.txt for details.

    libca/tests is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libca/tests is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libca/tests.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <system.h>
#include <assert.h>
#include <string.h>

/* Tests for strcmp, streq */

void checkeq(string a, string b);
void checkeqr(string a, string b);
void checklt(string a, string b);
void checkltr(string a, string b);

void checkeq(string a, string b) {
	mutable_string ad = strdup(a);
	mutable_string bd = strdup(b);
	// check all pairs
#define C4(x) checkeqr(x,a); checkeqr(x,b); checkeqr(x,ad); checkeqr(x,bd);
	C4(a);
	C4(b);
	C4(ad);
	C4(bd);
#undef C4
}

void checkeqr(string a, string b) {
	assert(streq(a, b));
	assert(strcmp(a, b) == 0);
	if (*a) {
		assert(*b);
		checkeq(a + 1, b + 1);
		checklt(a + 1, b);
		checklt(b + 1, a);
	} else {
		assert(!*b);
	}
}

void checklt(string a, string b) {
	mutable_string ad = strdup(a);
	mutable_string bd = strdup(b);
	// check all pairs
#define C4(x) checkltr(x,a); checkltr(x,b); checkltr(x,ad); checkltr(x,bd);
	C4(a);
	C4(b);
	C4(ad);
	C4(bd);
#undef C4
}

void checkltr(string a, string b) {
	assert(!streq(a, b));
	assert(strcmp(a, b) < 0);
	if (*a == *b) {
		assert(*a && *b);
		checklt(a + 1, b + 1);
	}
}

CAMAIN0() {
	// basics and at same addresses
	char extra[] = "extra";
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress"
	assert(extra != "extra");
#pragma GCC diagnostic pop
	assert(streq("extra", extra));
	assert(streq("extra", "extra"));
	assert(strcmp("extra", extra) == 0);
	assert(strcmp("extra", "extra") == 0);

	// basic
	checkeq("", "");
	checkeq("hello", "hello");
	// differences in first character
	checklt("0ello", "hello");
	checklt("hello", "Hello");
	// differences in middle character
	checklt("bbbabb", "bbbbbb");
	checklt("bbbabb", "bbbAbb");
	checklt("bbbbbb", "bbbAbb");
	checklt("bbbabb", "bbbBbb");
	checklt("bbbbbb", "bbbBbb");
	checklt("bbbAbb", "bbbBbb");
	// differences in last character
	checkeq("ahahaA", "ahahaA");
	checklt("ahaha ", "ahahaA");
	checklt("ahahaA", "ahahaB");
	checklt("ahaha ", "ahahaB");
	// differences in more than one character
	checklt("a_0_0", "a_a_a");
	checklt("a_a_a", "b_0_0");
	checklt("x_a_0", "x_a_a");
	checklt("b_a_a", "b_b_0");

	return 0;
}