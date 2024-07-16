
#ifndef __D6T_H
#define __D6T_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "render.h"
#include "communication.h"

typedef enum{
	ABS_MODE = 0,
	REF_MODE = 1,
}DISPLAY_MODE;


void d6t_reading_to_lcd();

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
