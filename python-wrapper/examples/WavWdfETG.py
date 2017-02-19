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
Config.read("WDFConfig.ini")

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

######### Starts WDF loop
###parameter for WDF
window = Config.getint("WDF",'window')
overlap = Config.getint("WDF",'overlap')
deltaT =Config.getfloat("WDF",'deltaT')
deltaSNR = Config.getfloat("WDF",'deltaSNR')
thresh=Config.getfloat("WDF",'thresh')
Ncoeff = window
# sigma for the noise
sigma = ADE.GetAR(0)
print ('Estimated sigma= %s' % sigma)
# event class
evP = pytsa.tsa.EventFullFeatured(Ncoeff)
evN = pytsa.tsa.EventFullFeatured(Ncoeff)
ev = pytsa.tsa.EventFullFeatured(Ncoeff)
Cev = pytsa.tsa.ClusterizedEventFullFeatured(Ncoeff)
outdir=Config.get('FileData','outdir')
outfile = outdir + 'WDFTrigger-%s-Win%s-Over%s.csv' % (fn,window,overlap)

f = open(outfile, 'a+')

stringa = 'GPSMax,SNRMax,FreqMax,GPSstart,Duration,WaveletFam'
for i in range(Ncoeff):
    stringa += ',' + 'WavCoeff' + str(i)
stringa += '\n'
f.write(stringa)

#DetectD = pytsa.tsa.WDF2Classify(window, overlap, thresh, sigma, Ncoeff,pytsa.tsa.WaveletThreshold.dohonojohnston)

DetectD = pytsa.tsa.WDF2Classify(window, overlap, thresh, sigma, Ncoeff,pytsa.tsa.WaveletThreshold.cuoco)
###Start detection loop
print ("Starting detection loop")
start_time = time.time()
timeTrigger = 0.0
EventsNumber = 0
ClusterizedEvents = 0
Cmax = np.empty(Ncoeff)
factorF = float(sampFreq) / (2.0 * window);

chunck = Config.getint("WDF",'chunck')
dataw =SV()
sampling=1.0/float(sampFreq)
print  (sampling)
gc.enable()
slice=0
data =SV(float(slice) / float(sampFreq), sampling, chunck)
while slice < (snd.shape[0]-chunck):
    print (slice)
    data.SetStart(float(slice) / float(sampFreq))
    for i in range(chunck):
        data.FillPoint(0,i, float(snd[i + slice]))
    LF(data, dataw)
    DetectD(dataw, sigma)
    while DetectD.GetDataNeeded() > 0:
        DetectD(ev)
        if ev.mTime != evN.mTime:
            if EventsNumber == 0:
                EventsNumber = 1
                evP.EVcopy(ev)
                evN.EVcopy(ev)
                ###inizialite parameter at peak
                SNRmax = ev.mSNR
                for i in range(Ncoeff):
                    Cmax[i] = ev.GetCoeff(i)
                ClevelMax = ev.mlevel
                TimeMax = ev.mTime
                WaveMax = ev.mWave
            EventsNumber += 1
            if np.fabs(ev.mTime - evN.mTime) > deltaT or (np.fabs(ev.mSNR - evN.mSNR) / evN.mSNR) > deltaSNR:
                Cev.mTime = evP.mTime  # starting time
                Cev.mTimeMax = TimeMax  # gps of peak
                Cev.mSNR = SNRmax  # snr of peak
                Cev.mLenght = np.fabs(evN.mTime - evP.mTime)  # duration
                for i in range(0, Ncoeff):
                    Cev.SetCoeff(i, Cmax[i])  # wavelet coefficient at peak

                Cev.mlevel = ClevelMax  # frequency at peak
                Cev.mWave = WaveMax  # wavelet at peak

                frequency = Cev.mlevel * factorF
                stringa = repr(Cev.mTimeMax) + ',' + repr(Cev.mSNR) + ',' + repr(frequency) + ',' \
                          + repr(Cev.mTime) + ',' + repr(Cev.mLenght) + ',' + repr(Cev.mWave)
                for i in range(0, Ncoeff):
                    stringa += ',' + repr(Cev.GetCoeff(i))
                stringa += '\n'
                f.write(stringa)
                f.flush()
                ClusterizedEvents += 1
                del Cev
                Cev = pytsa.tsa.ClusterizedEventFullFeatured(Ncoeff)
                evP.EVcopy(ev)
                evN.EVcopy(ev)
                ##new values to identify next peak
                SNRmax = ev.mSNR
                TimeMax = ev.mTime
                for i in range(0, Ncoeff):
                    Cmax[i] = ev.GetCoeff(i)
                WaveMax = ev.mWave
                ClevelMax = ev.mlevel  # insert triggers into file

            else:
                evN.EVcopy(ev)
                if ev.mSNR > SNRmax:
                    SNRmax = ev.mSNR
                    TimeMax = ev.mTime
                    for i in range(0, Ncoeff):
                        Cmax[i] = ev.GetCoeff(i)
                    WaveMax = ev.mWave
                    ClevelMax = ev.mlevel


    data.Clear()
    slice +=chunck


f.close()
out='passed'
print(out=='passed')
print ('Program terminated. found %s Events and %s Clusterized Events.' % (EventsNumber, ClusterizedEvents))


