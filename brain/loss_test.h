#ifndef LOSS_TEST_H
#define LOSS_TEST_H

#include <Arduino.h>
#include "move.h"
#include "definitions.h"
#include "pins.h"

#define NUM_TESTS 5

void loss_test(void);

void testX(void);
void testY(void);
void testZ(void);

#endif
