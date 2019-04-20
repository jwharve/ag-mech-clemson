#ifndef GLOBALS_H
#define GLOBALS_H

// use volatile ints to ensure they are accurate

// global variables for size of each dimension
extern volatile int x_range;
extern volatile int y_range;
extern volatile int z_range;

// global variables for current position
extern volatile int x_pos;
extern volatile int y_pos;
extern volatile int z_pos;

#endif
