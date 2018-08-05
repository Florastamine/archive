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

#include "fcurses.h"

#include <string.h>

int fc_init()
{
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  
  if (has_colors())
    start_color();
}

int fc_deinit()
{
  endwin();
}

WINDOW *fc_window_new(int w, int h, int x, int y, const char *title)
{
  WINDOW *window = newwin(h, w, y, x);
  
  box(window, 0, 0);
  wrefresh(window);
  
  if (NULL != title)
    fc_window_draw_string(window, title, (fc_window_get_width(window) - strlen(title)) / 2, 0);
  
  return window;
}

void fc_window_free(WINDOW *window)
{
  if (NULL != window)
    delwin(window);
}

void fc_window_draw_string(WINDOW *window, const char *string, int x, int y)
{
  if (NULL != window && NULL != string)
  {
    mvwaddstr(window, y, x, string);
    wrefresh(window);
  }
}

void window_get_size(WINDOW *window, unsigned *width, unsigned *height)
{
  unsigned w = -1, h = -1;
  
  if (NULL != window)
    getmaxyx(window, h, w);
  
  if (NULL != width)
    *width = w;
  
  if (NULL != height)
    *height = h;
}

unsigned fc_window_get_width(WINDOW *window)
{
  unsigned width = 0u;
  window_get_size(window, &width, NULL);
  
  return width;
}

unsigned fc_window_get_height(WINDOW *window)
{
  unsigned height = 0u;
  window_get_size(window, NULL, &height);
  
  return height;
}

void fc_window_set_color(WINDOW *window, int index)
{
  if (NULL != window)
  {
    wbkgd(window, COLOR_PAIR(index));
    wrefresh(window);
  }
}

unsigned fc_terminal_get_height()
{
  return LINES;
}

unsigned fc_terminal_get_width()
{
  return COLS;
}

void fc_window_draw_rectangle(WINDOW *window, int x1, int y1, int x2, int y2)
{
  if (NULL != window)
  {
    mvwhline(window, y1, x1, 0, x2-x1);
    mvwhline(window, y2, x1, 0, x2-x1);
    mvwvline(window, y1, x1, 0, y2-y1);
    mvwvline(window, y1, x2, 0, y2-y1);
    mvwaddch(window, y1, x1, ACS_ULCORNER);
    mvwaddch(window, y2, x1, ACS_LLCORNER);
    mvwaddch(window, y1, x2, ACS_URCORNER);
    mvwaddch(window, y2, x2, ACS_LRCORNER);
    
    wrefresh(window);
  }
}

static void static_fc_draw_8point(WINDOW *window, int xc, int yc, int x, int y, const char *filler)
{
  mvwaddstr(window, xc+x, yc+y, filler);
  mvwaddstr(window, xc-x, yc+y, filler);
  mvwaddstr(window, xc+x, yc-y, filler);
  mvwaddstr(window, xc-x, yc-y, filler);
  mvwaddstr(window, xc+y, yc+x, filler);
  mvwaddstr(window, xc-y, yc+x, filler);
  mvwaddstr(window, xc+y, yc-x, filler);
  mvwaddstr(window, xc-y, yc-x, filler);
}

void fc_window_draw_circle(WINDOW *window, int xc, int yc, int r, const char *filler)
{
  int x = 0, y = r;
  int d = 3 - 2 * r;
  while (y >= x)
  {
    static_fc_draw_8point(window, xc, yc, x, y, filler);
    x++;
    
    if (d > 0)
    {
      y--; 
      d = d + 4 * (x - y) + 10;
    }
    else
      d = d + 4 * x + 6;
    
    static_fc_draw_8point(window, xc, yc, x, y, filler);
  }
  wrefresh(window);
}
