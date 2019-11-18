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
#include <string.h>
#include <sys/time.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "cpu6502.h"
#include "rom.h"
#include "vic.h"

#define CYCLE_TIME_US   1
#define WIN_WIDTH       800
#define WIN_HEIGHT      640
#define X_SCALE         4
#define Y_SCALE         3

/* Set to 1 to load 6502 functional test; 0 for VIC-20 */
#define DO_FUNCTIONAL_TEST  0

static cpu6502_st cpu6502;
static mem_st     mem;
static uint8_t   *pixels;
static uint16_t   width, height;

void do_clock_cycle(void)
{
	static uint32_t irq_clk = 0;

	cpu6502_clk();
	vic_clk();
	irq_clk++;
	if (irq_clk >= 1000) {
		irq_clk = 0;

		/* Finish current instruction */
//		while (cpu->wait_cycles) {
//			cpu6502_clk();
//		}

		/* Signal interrupt */
		//cpu6502_irq(CPU6502_NMI);
	}
}

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    vic_get_rgbu8_screen(width, height, pixels);
    glPixelZoom(X_SCALE, Y_SCALE);
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glutSwapBuffers();
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
	static uint16_t render = 60;
	struct timeval now, last;
	if (DO_FUNCTIONAL_TEST) {
		mem_init_functional_test(&mem);
		rom_init_functional_test(&mem);
		vic_init(&mem);
		cpu6502_init_functional_test(&cpu6502, &mem);
	} else {
		mem_init(&mem);
		rom_init(&mem);
		vic_init(&mem);
		cpu6502_init(&cpu6502, &mem);
	}
	vic_get_screen_sz(&width, &height);

	pixels = malloc(width * height * 3);
	if (!pixels) {
		printf ("Failed to allocated screen buffer\n");
		exit(-1);
	}
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(width * X_SCALE, height * Y_SCALE);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("VIC-20");

    InitializeGlutCallbacks();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	gettimeofday(&last,NULL);
	while (!cpu6502.halt) {
		if (!DO_FUNCTIONAL_TEST) {
			struct timeval elapsed;
			gettimeofday(&now,NULL);
			if (timeval_subtract(&elapsed, &now, &last)) {
				printf ("Error: Negative elapsed time\n");
				break;
			}

			if (elapsed.tv_sec || elapsed.tv_usec >= CYCLE_TIME_US) {
				do_clock_cycle();
				last = now;
				if (--render == 0) {
					RenderSceneCB();
                                        render = 600;
				}
			}
		} else {
			do_clock_cycle();
		}

		glutMainLoopEvent();
	}

    return 0;
}
