//
//  minunit.h
//  test
//
//  Created by Daniel Meltzer on 28/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef minunit_h
#define minunit_h

#include <stdio.h>
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
if (message) return message; } while (0)
extern int tests_run;
#endif /* minunit_h */
