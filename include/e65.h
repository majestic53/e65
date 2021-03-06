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

/**
 * ========================================================
 * DATA TYPES
 * ========================================================
 */

/* Command enumeration */
enum {
	E65_BREAKPOINT_CLEAR = 0,		/* Remove a breakpoint from the current sesion */
	E65_BREAKPOINT_CLEAR_ALL,		/* Remove all breakpoints from the current session */
	E65_BREAKPOINT_LIST,			/* List all breakpoints in the current session (caller must free response) */
	E65_BREAKPOINT_SET,			/* Add a breakpoint to the current session */
	E65_MEMORY_DUMP,			/* Dump memory at a specified address to offset (caller must free response) */
	E65_MEMORY_READ,			/* Read a byte from a specified memory address */
	E65_MEMORY_READ_WORD,			/* Read a word from a specified memory address */
	E65_MEMORY_WRITE,			/* Write a byte to a specified memory address */
	E65_MEMORY_WRITE_WORD,			/* Write a word to a specified memory address */
	E65_PROCESSOR_ACCUMULATOR,		/* Retrieve the processors accumulator register */
	E65_PROCESSOR_ACCUMULATOR_SET,		/* Set the processors accumulator register */
	E65_PROCESSOR_BREAK,			/* Stop an actively running processor */
	E65_PROCESSOR_CORE,			/* Retrieve the processors core information (caller must free response) */
	E65_PROCESSOR_CYCLE,			/* Retrieve the processors cycle count */
	E65_PROCESSOR_DISASSEMBLE,		/* Disassemble processor instructions (caller must free response) */
	E65_PROCESSOR_FLAGS,			/* Retrieve the processors flags */
	E65_PROCESSOR_FLAGS_SET,		/* Set the processors flags */
	E65_PROCESSOR_INDEX_X,			/* Retrieve the processors index-x register */
	E65_PROCESSOR_INDEX_X_SET,		/* Set the processors index-x register */
	E65_PROCESSOR_INDEX_Y,			/* Retrieve the processors index-y register */
	E65_PROCESSOR_INDEX_Y_SET,		/* Set the processors index-y register */
	E65_PROCESSOR_PROGRAM_COUNTER,		/* Retrieve the processors program counter register */
	E65_PROCESSOR_PROGRAM_COUNTER_SET,	/* Set the processors program counter register */
	E65_PROCESSOR_RUN,			/* Run the processor until a breakpoint is hit */
	E65_PROCESSOR_STACK_POINTER,		/* Retrieve the processors stack pointer register */
	E65_PROCESSOR_STACK_POINTER_SET,	/* Set the processors stack pointer register */
	E65_PROCESSOR_STOP,			/* Set the processors stop flag */
	E65_PROCESSOR_STOP_CLEAR,		/* Clear the processors stop flag */
	E65_PROCESSOR_STOPPED,			/* Retrieve the processor stop flag */
	E65_PROCESSOR_WAIT,			/* Set the processors wait flag */
	E65_PROCESSOR_WAIT_CLEAR,		/* Clear the processors wait flag */
	E65_PROCESSOR_WAITING,			/* Retrieve the processor wait flag */
	E65_VIDEO_FRAME,			/* Retrieve the video frame count */
	E65_VIDEO_FRAME_CYCLE,			/* Retrieve the video frame cycle count */
	E65_VIDEO_FREQUENCY,			/* Retrieve the video frequency (Hz) */
	E65_VIDEO_FULLSCREEN,			/* Fullscreen the video display */
	E65_VIDEO_HIDE,				/* Hide the video display */
	E65_VIDEO_PIXEL,			/* Retrieve a video display pixel color */
	E65_VIDEO_PIXEL_SET,			/* Set a video display pixel color */
};

/* Event enumeration */
enum {
	E65_EVENT_BREAK = 0,			/* Encountered processor break command (BRK) */
	E65_EVENT_BREAKPOINT,			/* Encountered breakpoint */
	E65_EVENT_MASKABLE_INTERRUPT,		/* Encountered maskable interrupt (IRQ) */
	E65_EVENT_NON_MASKABLE_INTERRUPT,	/* Encountered non-maskable interrupt (NMI) */
	E65_EVENT_STOP,				/* Encountered processor stop command (STP) */
	E65_EVENT_WAIT,				/* Encountered processor wait command (WAI) */
};

/* State enumeration */
enum {
	E65_STATE_INACTIVE = 0,			/* Library is inactive */
	E65_STATE_ACTIVE,			/* Library is active */
};

/* Command debug struture */
typedef struct {
	unsigned short address;			/* Command debug address */
	int result;				/* Command debug result (EXIT_SUCCESS or EXIT_FAILURE) */

	union {
		unsigned char byte;
		unsigned short word;
		unsigned int dword;
		char *literal;
	} payload;				/* Command debug payload */
} e65_debug_t;

/* Event handler */
typedef void (*e65_event_handler)(int type, unsigned short address);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * ========================================================
 * SETUP ROUTINES
 * ========================================================
 */

/**
 * Initialization routine
 * @brief This routine creates a new library session, and must be called before calling any runtime routines
 * @param None
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_initialize(void);

/**
 * Uninitialization routine
 * @brief This routine destroys an active library session, and must be called after initialization and all runtime routines
 * @param None
 * @return None
 */
extern void e65_uninitialize(void);

/**
 * ========================================================
 * RUNTIME ROUTINES
 * ========================================================
 */

/**
 * Runtime interrupt routine
 * @brief This routine allows the caller to interrupt an active library session
 * @param maskable A flag that defines the interrupt as either maskable=true or non-maskable=false (ie. IRQ=true, NMI=false)
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_interrupt(int maskable);

/**
 * Runtime register handler routine
 * @brief This routine allows the caller to register an event handler for an active library session
 * @param handler A caller defined event handler routine
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_register_handler(e65_event_handler handler);

/**
 * Runtime reset routine
 * @brief This routine allows the caller to reset an active library session
 * @param None
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_reset(void);

/**
 * Runtime run routine
 * @brief This routine allows the caller to run a binary/ihex file in an active library session
 * @param path A pointer to a valid, caller allocated file path (Supports binary (.bin) and Intel Hex (.hex) formats)
 * @param hex A flag that defines whether the file is a binary or ihex file (ie. binary=0, ihex=1)
 * @param debug A flag the defines whether or not the session is run in debug mode (ie. non-debug=0, debug=1)
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_run(const char *path, int hex, int debug);

/**
 * Runtime state routine
 * @brief This routine allows the caller to retrieve a library session state
 * @param state A pointer to a valid integer, which will hold the library state
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_state(int *state);

/**
 * Runtime terminate routine
 * @brief This routine allows the caller to terminate an active library session
 * @param None
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_terminate(void);

/**
 * ========================================================
 * DEBUG ROUTINES
 * ========================================================
 */

/**
 * Debug command routine
 * @brief This routine allows the caller to issue commands to an active library session
 * @param command Caller requested command
 * @param request A pointer to a valid, caller allocated request structure
 * @param response A pointer to a valid, caller allocated response structure
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_debug_command(int command, const e65_debug_t *request, e65_debug_t *response);

/**
 * Debug step routine
 * @brief This routine allows the caller to step an active library session
 * @param offset Number of steps
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_debug_step(int offset);

/**
 * Debug step frame routine
 * @brief This routine allows the caller to step an active library session through a frame
 * @param offset Number of frames
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
extern int e65_debug_step_frame(int offset);

/**
 * ========================================================
 * MISC. ROUTINES
 * ========================================================
 */

/**
 * Error routine
 * @brief This routine returns a string containing the last error
 * @param None
 * @return A string containing the last error
 */
extern const char *e65_error(void);

/**
 * Version routine
 * @brief This routine returns the library version information
 * @param major A pointer to a valid integer, which will hold the library major version
 * @param minor A pointer to a valid integer, which will hold the library minor version
 * @return None
 */
extern void e65_version(int *major, int *minor);

/**
 * Version as string routine
 * @brief This routine returns a string containing the library version
 * @param None
 * @return A string containing the library version
 */
extern const char *e65_version_string(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* E65_H_ */
