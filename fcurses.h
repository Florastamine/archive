/*
 * BSD 3-Clause License
 * 
 * Copyright (c) 2018, Florastamine
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>

#if !defined(FC_MALLOC)
#define FC_MALLOC(x) malloc(x)
#endif

#if !defined(FC_FREE)
#define FC_FREE(x) free(x)
#endif

typedef enum { FC_A_DEFAULT, FC_A_LEFT, FC_A_RIGHT } alignment_t;

typedef struct {
  char       *title;
  alignment_t title_alignment;

  bool manual_sync;

  WINDOW *window;
} fc_window_t;

int fc_init();
int fc_deinit();

void fc_terminal_flash();

unsigned fc_terminal_get_width();
unsigned fc_terminal_get_height();

fc_window_t *fc_window_new(int w, int h, int x, int y, const char *title);
void fc_window_free(fc_window_t *window);
void fc_window_sync(fc_window_t *window);
void fc_window_clear(fc_window_t *window);
void fc_window_set_manual_sync(fc_window_t *window, bool sync);
bool fc_window_get_manual_sync(fc_window_t *window);
void fc_window_set_title_alignment(fc_window_t *window, alignment_t alignment);
const char *fc_window_get_title_alignment(fc_window_t *window);

void fc_window_draw_string(fc_window_t *window, const char *string, int x, int y);
void fc_window_draw_line(fc_window_t *window, int x0, int y0, int x1, int y1, char c);
void fc_window_draw_rectangle(fc_window_t *window, int x1, int y1, int x2, int y2);
void fc_window_draw_circle(fc_window_t *window, int x, int y, int radius, char c);
void fc_window_draw_triangle(fc_window_t *window, int x0, int y0, int x1, int y1, int x2, int y2, char c);

void fc_window_set_color(fc_window_t *window, int index);
int fc_window_get_color(fc_window_t *window);

unsigned fc_window_get_width(fc_window_t *window);
unsigned fc_window_get_height(fc_window_t *window);

unsigned fc_window_get_x(fc_window_t *window);
unsigned fc_window_get_y(fc_window_t *window);
