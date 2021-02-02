import numpy as np
import pandas as pd

d = pd.read_csv('TECHEDSAT-10-PASSES.txt', delimiter='  ', header=4, engine='python')
d = d.drop(0)
i = 1

while i < len(d["AOS"]):
    t = d["AOS"][i]
    hour = int(t[11:13])
    if not(hour >= 13 and hour < 22):
        d = d.drop(i)
    i += 1

d.to_csv('TECHEDSAT-10-PASSES-FILTERED.txt', sep='&',index=False,quotechar=" ", line_terminator="\\\\\n")