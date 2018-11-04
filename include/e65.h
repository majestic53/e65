/**
 * E65
 * Copyright (C) 2018 David Jolly
 *
 * E65 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * E65 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef E65_H_
#define E65_H_

enum {
	E65_BREAKPOINT_CLEAR = 0,
	E65_BREAKPOINT_CLEAR_ALL,
	E65_BREAKPOINT_CONTAINS,
	E65_BREAKPOINT_SET,
	E65_FRAME,
};

typedef struct {
	int type;

	union {
		unsigned short u16;
	} data;
} e65_req_t;

typedef struct {
	int type;

	union {
		unsigned short u16;
		unsigned int u32;
		int i;
	} data;
} e65_rsp_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Runtime routines

extern int e65_run(const char *path, int debug);

extern int e65_step(void);

// Interactive routines

extern int e65_command(const e65_req_t *request, e65_rsp_t *response);

// Helper routines

extern const char *e65_error(void);

extern void e65_version(int *major, int *minor);

extern const char *e65_version_string(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // E65_H_
