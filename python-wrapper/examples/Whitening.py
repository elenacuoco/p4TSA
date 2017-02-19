'''
@author Elena Cuoco
Wavelet Detection scripts offline
It finds the triggers in a data set,clusterized and save the results.md in ascii files
produced only clusterized triggers.  it is tuned for ML classifiers
'''

from scipy.io import wavfile
import pytsa
import time
import numpy as np
import configparser,os
import gc
from pytsa.tsa import SeqView_double_t as SV
Config = configparser.ConfigParser()


Config.read("Whitening.ini")

print (Config.sections())

filename = Config.get("FileData",'filename')
fn=filename.strip('../datawav')
print(fn)
#data fraction for AR estimations in seconds
DataFraction=Config.getfloat("Whitening",'DataFraction')
##read data
sampFreq, snd = wavfile.read(filename)
print (sampFreq,snd.dtype,snd.shape)

n_est=int(DataFraction*sampFreq)
print (n_est)

##Do whitening parameters estimation
learn =SV(0.0, 1.0/sampFreq, n_est)

for i in range(n_est):
    learn.FillPoint( 0, i, float(snd[i]))

ARorder=Config.getint("Whitening",'ARoder')
ADE = pytsa.tsa.ArBurgEstimator(ARorder)
LV = pytsa.tsa.LatticeView(ARorder)
LF = pytsa.tsa.LatticeFilter(LV)
LVfile = "./LVparam-%s.txt" %fn
ARfile = "./ARparam-%s.txt" %fn
estimation=Config.getboolean('Whitening',"estimation")
if estimation==True:
    print('Start whitening parameters estimation')
    ADE(learn)
    ADE.GetLatticeView(LV)
    LV.Save(LVfile, "txt")
    LF.init(LV)
    ADE.Save(ARfile, "txt")
    print('Saved whitening parameters')
else:
    print('Load whitening parameter')
    ADE.Load(ARfile, "txt")
    LV.Load(LVfile, "txt")
    LF.init(LV)

out='passed'
print (out=='passed')


