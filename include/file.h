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

#ifndef _FILE_H
#define _FILE_H

#include <catype.h>
#include <stream.h>

#define FILE_READ FALSE
#define FILE_WRITE TRUE

ioerr openf(stream *c, string filename, bool out);
stream openfq(string filename, bool out); // panics on error

ioerr openf_unbuf(stream *c, string filename, bool out);
stream openfq_unbuf(string filename, bool out); // panics on error

ioerr removef(string filename);
void removefq(string filename); // panics on error
ioerr renamef(string from, string to);
void renamefq(string from, string to); // panics on error

// referenced from stream.c
stream _libca_openfd(u32 fd, bool out);

#endif
