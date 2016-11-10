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

#ifndef RFC6298_H
#define RFC6298_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Obtains the currently calculated RTO, in milliseconds.
 *
 * @return the currently calculated RTO, in milliseconds.
 */
uint32_t rfc6298_get_rto(void);

/**
 * Updates the RTO with the new measurement information.
 *
 * @param[in] measurement the new measurement, in milliseconds.
 *
 * @return the currently calculated RTO, in milliseconds.
 */
uint32_t rfc6298_update_rto(uint32_t measurement);

/**
 * Resets the calculated RTO value to an appropriate default.
 *
 * @param[in] syn_ack_lost true if a SYN or ACK packet was lost in the SYN
 *                         phase of the measurement, false otherwise.  See
 *                         also RFC6298 section 7.
 */
void rfc6298_reset_rto(bool syn_ack_lost);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RFC6298_H */

/*
vim:sts=2:ts=2:sw=2:et:syn=c:fdm=marker:ff=unix:number:fenc=utf-8:cc=80
*/
