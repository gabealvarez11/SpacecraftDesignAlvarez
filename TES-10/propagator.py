# -*- coding: utf-8 -*-
"""
Created on Wed Feb  3 16:46:25 2021

@author: alvar
"""

# Basic functions copied from https://pypi.org/project/sgp4/

from sgp4.api import Satrec
from sgp4.api import jday
import numpy as np
import matplotlib.pyplot as plt

jd0, fr = jday(2021, 2, 3, 0, 0, 0)
n = 1000
r_e = 6371

jd = np.linspace(jd0,jd0+130,n)
alt = []

# TECHEDSAT-10 TLE from http://celestrak.com/NORAD/elements/active.txt
s = "1 45917U 98067RQ  21034.37979832  .00127436  00000-0  84252-3 0  9991"
#s = "1 45917U 98067RQ  21034.37979832  .00127436  00000-0  10252-2 0  9991"
t = "2 45917  51.6328 270.7093 0007181 161.6030 198.5231 15.74631340 31934"

satellite = Satrec.twoline2rv(s, t)

for i in jd:
    e, r, v = satellite.sgp4(i, 0.0)

    alt.append(np.linalg.norm(r) - r_e)
    
# https://www.geeksforgeeks.org/python-get-the-index-of-first-element-greater-than-k/
ind350 = next(x for x, val in enumerate(alt) if val < 350)
ind300 = next(x for x, val in enumerate(alt) if val < 300)
ind100 = next(x for x, val in enumerate(alt) if val < 100)

daysto350 = jd[ind350] - jd0
daysto300 = jd[ind300] - jd0
daysto100 = jd[ind100] - jd0

plt.figure()
plt.plot(jd-jd0, alt,label="BSTAR=.84e-3")
plt.plot(daysto350, alt[ind350], "r*")
plt.plot(daysto300, alt[ind300], "r*")
plt.plot(daysto100, alt[ind100], "r*")

plt.xlabel("Days After 2/3/21")
plt.ylabel("Altitude (km)")
plt.title("Orbital Decay of TES-10")
plt.legend()

