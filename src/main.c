/*
 ============================================================================
 Name        : main.c
 Author      : Kevin Phillips
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <GL/freeglut.h>
#include "cpu6502.h"
#include "rom.h"

#define CYCLE_TIME_US   1

static cpu6502_st cpu6502;
static mem_st     mem;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void do_clock_cycle(void)
{
	cpu6502_clk();
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}

int
timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

int main(int argc, char** argv)
{
	struct timeval now, last;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("VIC-20");

    InitializeGlutCallbacks();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	mem_init(&mem);
	rom_load(&mem, 0x8000, 0x1000, "rom/vic20/chargen");
	rom_load(&mem, 0xC000, 0x2000, "rom/vic20/basic");
	rom_load(&mem, 0xE000, 0x2000, "rom/vic20/kernal");
	cpu6502_init(&cpu6502, &mem);
	cpu->ofp = fopen("trace", "w");
	cpu6502.trace = 1;

	gettimeofday(&last,NULL);
	while (1) {
		struct timeval elapsed;
		gettimeofday(&now,NULL);
		if (timeval_subtract(&elapsed, &now, &last)) {
			printf ("Error: Negative elapsed time\n");
			break;
		}

		if (elapsed.tv_sec || elapsed.tv_usec >= CYCLE_TIME_US) {
			do_clock_cycle();
			last = now;
		}
		glutMainLoopEvent();
	}

    return 0;
}
