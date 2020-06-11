#!/usr/bin/env python3

import sys

if len(sys.argv) != 3:
    print("Usage: {} a e".format(sys.argv[0]), file=sys.stderr)

a = float(sys.argv[1])
e = float(sys.argv[2])
# b = sqrt (a^2 - (e*a)^2) 

b = float((a**2 - (e*a)**2)**(1/2))
print("{}\n/2 = {}".format(b, float(b/2)))
