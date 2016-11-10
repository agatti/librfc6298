/*
 * Copyright (c) 2016 Alessandro Gatti - frob.it
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "rfc6298.h"

#define TIMER_GRANULARITY 1000
#define K_FACTOR 4
#define ALPHA_FACTOR 125
#define BETA_FACTOR 250

static uint32_t g_srtt = 0;
static uint32_t g_rtt = 0;
static uint32_t g_rto = 1000;

uint32_t rfc6298_update_rto(uint32_t measurement) {
  if ((g_srtt == 0) || (g_rtt == 0)) {
    g_srtt = measurement;
    g_rtt = measurement / 2;
  } else {
    g_rtt =
        (((1000 - BETA_FACTOR) * g_rtt) / 1000) +
        ((BETA_FACTOR * (uint32_t)abs((int32_t)g_srtt - (int32_t)measurement)) /
         1000);
    g_srtt = (((1000 - ALPHA_FACTOR) * g_srtt) / 1000) +
             ((ALPHA_FACTOR * measurement) / 1000);
  }
  g_rto =
      g_srtt + ((TIMER_GRANULARITY > (K_FACTOR * g_rtt)) ? TIMER_GRANULARITY
                                                         : (K_FACTOR * g_rtt));
  if (g_rto < 1000) {
    /*
     * (2.4) Whenever RTO is computed, if it is less than 1 second, then the
     * RTO SHOULD be rounded up to 1 second.
     */
    g_rto = 1000;
  }

  return g_rto;
}

uint32_t rfc6298_get_rto(void) { return g_rto; }

void rfc6298_reset_rto(bool syn_ack_lost) {
  g_srtt = 0;
  g_rtt = 0;
  g_rto = syn_ack_lost ? 3000 : 1000;
}

/*
vim:sts=2:ts=2:sw=2:et:syn=c:fdm=marker:ff=unix:number:fenc=utf-8:cc=80
*/
