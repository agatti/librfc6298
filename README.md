# librfc6298 v0.1

This C library is meant to be used to calculate the RTO (retransmission
timeout) according to the method described in
[RFC 6298](https://tools.ietf.org/html/rfc6298).  The API is made up of just
three function, whose usage is pretty much self-explanatory: call
`rfc6298_reset_rto` before measuring RTT (round trip) times, then pass them to
`rfc6298_update_rto` to recalculate the RTO value, and finally retrieve the RTO
value with `rfc6298_get_rto`.  Multiple measurement can sent over at any time,
and make the calculated RTO more accurate.  All times are defined in
milliseconds.

## Caveats

Given that one second is measured as 1000 milliseconds, this code contains
several division operations to normalise pseudo-fixed-point calculations and
therefore might not be suitable for embedded targets.  A potential improvement
would be to assume that a second is made up of 1024 milliseconds instead to use
right shift operations rather than plain arithmetic divisions.  However, given
that RTT times can be smaller than 24 milliseconds this might end up lowering
precision down to unacceptable values.

## Licence

This library is licensed under the MIT licence, whose text can be found in the
LICENCE file in the repository.

Copyright (C) 2016 Alessandro Gatti
