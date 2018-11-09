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
	E65_BREAKPOINT_SET,
	E65_MEMORY_READ,
	E65_MEMORY_WRITE,
	E65_PROCESSOR_ACCUMULATOR,
	E65_PROCESSOR_ACCUMULATOR_SET,
	E65_PROCESSOR_CYCLE,
	E65_PROCESSOR_FLAGS,
	E65_PROCESSOR_FLAGS_SET,
	E65_PROCESSOR_HALT,
	E65_PROCESSOR_HALT_CLEAR,
	E65_PROCESSOR_INDEX_X,
	E65_PROCESSOR_INDEX_X_SET,
	E65_PROCESSOR_INDEX_Y,
	E65_PROCESSOR_INDEX_Y_SET,
	E65_PROCESSOR_PROGRAM_COUNTER,
	E65_PROCESSOR_PROGRAM_COUNTER_SET,
	E65_PROCESSOR_STACK_POINTER,
	E65_PROCESSOR_STACK_POINTER_SET,
	E65_PROCESSOR_STOP,
	E65_PROCESSOR_STOP_CLEAR,
	E65_VIDEO_FRAME,
};

typedef struct {
	int type;
	unsigned short address;

	union {
		unsigned char u8;
		unsigned short u16;
	} payload;
} e65_req_t;

typedef struct {
	int type;

	union {
		unsigned char u8;
		unsigned short u16;
		unsigned int u32;
		int i;
	} payload;
} e65_rsp_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern int e65_command(const e65_req_t *request, e65_rsp_t *response);

extern const char *e65_error(void);

extern int e65_initialize(void);

extern int e65_interrupt(int maskable);

extern void e65_uninitialize(void);

extern int e65_run(const char *path, int hex, int debug);

extern int e65_step(void);

extern void e65_version(int *major, int *minor);

extern const char *e65_version_string(void);

extern int e65_wait(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // E65_H_
