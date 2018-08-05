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
  
  if (has_colors() && can_change_color())
    start_color();
}

int fc_deinit()
{
  endwin();
}

static void fc_static_window_sync(fc_window_t *window)
{
  if (NULL != window && !window->manual_sync)
    wrefresh(window->window);
}

static void fc_static_window_draw_border(fc_window_t *window)
{
  box(window->window, 0, 0);
  
  if (NULL != window->title)
    fc_window_draw_string(window, window->title, (fc_window_get_width(window) - strlen(window->title)) / 2, 0);
  
  fc_static_window_sync(window);
}

fc_window_t *fc_window_new(int w, int h, int x, int y, const char *title)
{
  fc_window_t *window = (fc_window_t *) FC_MALLOC(sizeof(fc_window_t));
  window->title       = (char *)        FC_MALLOC(strlen(title) * sizeof(char));
  window->manual_sync = false;
  
  strcpy(window->title, title);
  
  window->window = newwin(h, w, y, x);
  fc_static_window_draw_border(window);
  fc_static_window_sync(window);
  
  return window;
}

void fc_window_free(fc_window_t *window)
{
  if (NULL != window)
  {
    delwin(window->window);
    window->window = NULL;
    
    FC_FREE(window->title);
    window->title = NULL;
    
    FC_FREE(window);
    window = NULL;
  }
}

void fc_window_clear(fc_window_t *window)
{
  if (NULL != window)
  {
    wclear(window->window);
    fc_static_window_draw_border(window);
    fc_static_window_sync(window);
  }
}

void fc_window_set_manual_sync(fc_window_t *window, bool sync)
{
  if (NULL != window)
    window->manual_sync = sync;
}

bool fc_window_get_manual_sync(fc_window_t *window)
{
  return NULL != window ? window->manual_sync : false;
}

void fc_window_sync(fc_window_t *window)
{
  if (NULL != window)
    wrefresh(window->window);
}

void fc_window_draw_string(fc_window_t *window, const char *string, int x, int y)
{
  if (NULL != window && NULL != string)
  {
    mvwaddstr(window->window, y, x, string);
    fc_static_window_sync(window);
  }
}

void fc_window_get_size(fc_window_t *window, unsigned *width, unsigned *height)
{
  unsigned w = -1, h = -1;
  
  if (NULL != window)
    getmaxyx(window->window, h, w);
  
  if (NULL != width)
    *width = w;
  
  if (NULL != height)
    *height = h;
}

unsigned fc_window_get_width(fc_window_t *window)
{
  unsigned width = 0u;
  fc_window_get_size(window, &width, NULL);
  
  return width;
}

unsigned fc_window_get_height(fc_window_t *window)
{
  unsigned height = 0u;
  fc_window_get_size(window, NULL, &height);
  
  return height;
}

void fc_window_get_position(fc_window_t *window, unsigned *xp, unsigned *yp)
{
  unsigned x = -1, y = -1;
  
  if (NULL != window)
    getbegyx(window->window, y, x);
  
  if (NULL != x)
    *xp = x;
  
  if (NULL != y)
    *yp = y;
}

unsigned fc_window_get_x(fc_window_t *window)
{
  unsigned x = 0u;
  fc_window_get_position(window, &x, NULL);
  
  return x;
}

unsigned fc_window_get_y(fc_window_t *window)
{
  unsigned y = 0u;
  fc_window_get_position(window, NULL, &y);
  
  return y;
}

void fc_window_set_color(fc_window_t *window, int index)
{
  if (NULL != window)
  {
    wbkgd(window->window, COLOR_PAIR(index));
    fc_static_window_sync(window);
  }
}

int fc_window_get_color(fc_window_t *window)
{
  if (NULL != window)
    return PAIR_NUMBER(getbkgd(window->window));
  
  return -1;
}

unsigned fc_terminal_get_height()
{
  return LINES;
}

unsigned fc_terminal_get_width()
{
  return COLS;
}

void fc_window_draw_line(fc_window_t *window, int x0, int y0, int x1, int y1, char c)
{
  if (NULL != window)
  {
    int dx = x1 - x0,
        dy = y1 - y0,
        x = x0,
        y = y0,
        p = 2*dy - dx;

    while(x < x1)
    {
      if(p >= 0)
      {
        mvwaddch(window->window, x, y, c);
        y += 1;
        p += 2*dy - 2*dx;
      }
      else
      {
        mvwaddch(window->window, x, y, c);
        p += 2*dy;
      }
      x += 1;
    }
    fc_static_window_sync(window);
  }
}

void fc_window_draw_rectangle(fc_window_t *window, int x1, int y1, int x2, int y2)
{
  if (NULL != window)
  {
    mvwhline(window->window, y1, x1, 0, x2-x1);
    mvwhline(window->window, y2, x1, 0, x2-x1);
    mvwvline(window->window, y1, x1, 0, y2-y1);
    mvwvline(window->window, y1, x2, 0, y2-y1);
    mvwaddch(window->window, y1, x1, ACS_ULCORNER);
    mvwaddch(window->window, y2, x1, ACS_LLCORNER);
    mvwaddch(window->window, y1, x2, ACS_URCORNER);
    mvwaddch(window->window, y2, x2, ACS_LRCORNER);
    
    fc_static_window_sync(window);
  }
}

static void static_fc_draw_8point(fc_window_t *window, int xc, int yc, int x, int y, char c)
{
  mvwaddch(window->window, xc+x, yc+y, c);
  mvwaddch(window->window, xc-x, yc+y, c);
  mvwaddch(window->window, xc+x, yc-y, c);
  mvwaddch(window->window, xc-x, yc-y, c);
  mvwaddch(window->window, xc+y, yc+x, c);
  mvwaddch(window->window, xc-y, yc+x, c);
  mvwaddch(window->window, xc+y, yc-x, c);
  mvwaddch(window->window, xc-y, yc-x, c);
}

void fc_window_draw_circle(fc_window_t *window, int xc, int yc, int r, char c)
{
  int x = 0, y = r;
  int d = 3 - 2 * r;
  while (y >= x)
  {
    static_fc_draw_8point(window, xc, yc, x, y, c);
    x++;
    
    if (d > 0)
    {
      y--; 
      d = d + 4 * (x - y) + 10;
    }
    else
      d = d + 4 * x + 6;
    
    static_fc_draw_8point(window, xc, yc, x, y, c);
  }
  fc_static_window_sync(window);
}
