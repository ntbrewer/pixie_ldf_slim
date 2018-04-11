
e=Experiment('Mar08Run.his')
e=Experiment('noise.his')
from Pyspectr.pydamm import *
e=Experiment('noise.his')
e1=Experiment('signal.his')
e.list('2d')
e.list()
e.d(920)
e1.d(920)
e.d(920,clear=False)
e.d(920)
e1.d(920,clear=False)
for i in range(920,935):
    e.d(i)
    e1.d(i,clear=False)
    
for i in range(920,935):
    e.d(i)
    e1.d(i,clear=False)
    input('ok')
    
e.file_name
for i in range(920,935):
    e1.d(i)
    e.d(i,clear=False)
    input('ok')
    
for i in range(920,935):
    e1.d(i)
    peaks = [ginput('peaks')]
    print(peaks)
    
import ginput
for i in range(920,935):
    e1.d(i)
    peaks = [plt.ginput('peaks')]
    print(peaks)
    
for i in range(920,935):
    e1.d(i)
    num = numarrayS[920-i]
    peaks = [plt.ginput(num)]
    print(peaks)
    
numarrayS=[2,1,3,4,4,1,3,2,3,2,2,2,2]
len(numarrayS)
for i in range(920,935):
    e1.d(i)
    num = numarrayS[920-i]
    peaks = [plt.ginput(num)]
    print(peaks)
    
for i in range(920,935):
    e1.d(i)
    num = numarrayS[920-i]
    print(num)
    peaks = [plt.ginput(num)]
    print(peaks)
    
for i in range(920,935):
    e1.d(i)
    num = numarrayS[i-920]
    print(num)
    peaks = [plt.ginput(num)]
    print(peaks)
    
for i in [920,921,922,923,925,926,927,929,930,931,932,933,934]:
    e1.d(i)
    num = numarrayS[i-920]
    print(num)
    peaks = [plt.ginput(num)]
    print(peaks)
    
hislist= [920,921,922,923,925,926,927,929,930,931,932,933,934]
for i in range(0,14):
    e1.d(histlist[i])
    e1.show()
    num = numarrayS[i]
    print(num)
    peaks.append([plt.ginput(num)])
    
peaks=[]
for i in range(0,14):
    e1.d(hislist[i])
    e1.show()
    num = numarrayS[i]
    print(num)
    peaks.append([plt.ginput(num)])
    
for i in range(0,14):
    e1.d(hislist[i])
    plt.show()
    num = numarrayS[i]
    print(num)
    peaks.append([plt.ginput(num)])
    
len(hislist)
for i in range(0,13):
    e1.d(hislist[i])
    plt.show()
    num = numarrayN[i]
    print(num)
    peaks.append([plt.ginput(num)])
    
numarrayN=[4,2,3,1,4,4,4,3,1,1,2,1,3]
peakn = []
for i in range(0,13):
    e1.d(hislist[i])
    plt.show()
    num = numarrayN[i]
    print(num)
    peakn.append([plt.ginput(num)])
    
    
peakn = []
for i in range(0,13):
    e.d(hislist[i])
    plt.show()
    num = numarrayN[i]
    print(num)
    peakn.append([plt.ginput(num)])
    
    
for i in range(0,13):
   e1.pzot()
   e1.pk(list(x[0] for x in peakn[i]))
   e1.fit_peaks(hislist[i])
   plt.show()
   input('ok') 
   
for i in range(0,13):
   e1.pzot()
   e1.pk(list(x[0] for x in peakn[i]))
   e1.fit_peaks(hislist[i])
   plt.show()
   input('ok') 
   
hislist[0]
for i in range(0,13):
   e1.pzot()
   e1.pk(list(x[0] for x in peakn[i]))
   e1.fit_peaks(hislist[i],rx=(0,4000))
   plt.show()
   input('ok') 
   
for i in range(0,13):
   e1.pzot()
   e1.pk(list(x[0] for x in peakn[i]))
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his)
   plt.show()
   input('ok') 
   
list(x[0] for x in peaks[0])
peaks
peaks[0]
peaks[0][0]
peaks[1][0]
peaks[2][0]
peaks[3][0]
for i in range(0,13):
   e1.pzot()
   e1.pk(list(x[0] for x in peaks[i][0]))
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his)
   plt.show()
   input('ok') 
   
list(x[0] for x in peaks[2][0])
e1.pk(list(x[0] for x in peaks[2][0]))
e1.peaks
e1.pk(x[0] for x in peaks[2][0])
e1.peaks
x[0] for x in peaks[2][0]
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his)
   plt.show()
   input('ok') 
   
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4000))
   plt.show()
   input('ok') 
   
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4000))
   plt.show()
   input('ok') 
   
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4000))
   e1.log()
   plt.show()
   input('ok') 
   
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4000))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[0]
peaks[0][0][0]
peaks[0][1][0]
peaks[0][0][1][0]
peaks[0][0][1][0]=300
peaks[0][0][1]=(300,376)
peaks[0]
peaks[0][0][1]=(300,163)
peaks[0]
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4000))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[2]
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4200))
   e1.log()
   plt.show()
   input('ok') 
   
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4000))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[2]
peaks[2][0][2]
peaks[2][0][2]=(4094,64)
peaks[2]
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[2][0][2]=(4093,64)
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[2][0][2]=(393,64)
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[2]
peaks[2][0][2]=(300,64)
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[2][0].append((350,64))
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[2][0].append((4090,64))
for i in range(2,3):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
hislist
hislist = [920, 921, 923, 925, 926, 927, 929, 930, 931, 932, 933, 934]
hislist= [920,921,922,923,925,926,927,929,930,931,932,933,934]
peaks[2]
peaks[2][0]
peaks[2][0]=[(1682.3711644374512, 10.72812015230577)]
peaks[2]
for i in range(4,5):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[4][0]
peaks[4][0][3]
peaks[4][0][3]=(577,24)
for i in range(4,5):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[4][0].appned((600,24))
peaks[4][0].append((600,24))
for i in range(4,5):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
for i in range(6,7):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[6][0].append(100,30)
peaks[6][0].append((100,30))
for i in range(6,7):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
for i in range(8,9):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[8][0]
peaks[8][0][2]=(469,40)
for i in range(8,9):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[8][0].append((300,40))
for i in range(8,9):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[8][0]
peaks[8][0]=[(203.31687647521653, 22.663531236779221),
 (1658.7440991345397, 145.54746862219736),
 (469, 40)]
 
for i in range(8,9):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
for i in range(10,11):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[10][0]
peaks[10][0][1]=(85,192)
for i in range(10,11):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[10][0].append((50,192))
for i in range(10,11):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[12]
peaks[12][0][0]=(1,261)
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[12][0].append((100,26))
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[12][0].append((20,126))
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[12][0].append((50,126))
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[12][0][-1]=(60,126))
peaks[12][0][-1]=(60,126)
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[12][0][0]=(.5,126)
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
e.d(934,clear=False)
e1.d(934,clear=False)
peaks[12][0]
peaks[12][0]=[(32.722265814708578, 257.43926990990593),
 (100, 26),
 (20, 126)]
 
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[2]
peaks[2]=[[(198.59146341463429, 45.309984487378401),
  (1682.3711644374512, 10.72812015230577),
  (300, 64),
  (350, 64),
  (4090, 64)]]
  
for i in range(12,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   e1.fit_peaks(his,rx=(0,4095))
   e1.log()
   plt.show()
   input('ok') 
   
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   fs.append(e1.fit_peaks(his,rx=(0,4095)))
   e1.log()
   plt.show()
   input('ok') 
   
fs=[]
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   fs.append(e1.fit_peaks(his,rx=(0,4095)))
   e1.log()
   plt.show()
   input('ok') 
   
peaks[0]
peaks[0][0][1]=(230,163)
peaks[0]
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   fs.append(e1.fit_peaks(his,rx=(0,4095)))
   e1.log()
   plt.show()
   input('ok') 
   
fs=[]
for i in range(0,13):
   e1.pzot()
   for x in peaks[i][0]:
       e1.pk(x[0])
   his = hislist[i]
   print(his,e1.peaks)
   fs.append(e1.fit_peaks(his,rx=(0,4095)))
   e1.log()
   plt.show()
   input('ok') 
   
fs[0]
fs[0][-1]
fs[0][-1].message()
fs[0][-1].message
ouf = open('Results.txt','a')
ouf.write(fs[0][0])
ouf.write(str(fs[0][0]))
ouf.close()
ouf = open('Results.txt','a')
ouf.write(str(hislist[0]))
ouf.write(str(fs[0][1].covar))
ouf.write(str(fs[0][1].chisqr))
ouf.write(str(fs[0][1].redchi))
ouf.close()
ouf = open('Results.txt','a')
ouf.write('\n'+str(fs[0][1].redchi))
ouf.close()
fs[0][1].errorbars
fs[0][1].params
fs[0][1].flatchain
get_ipython().set_next_input('fs[0][1].flatchain');get_ipython().run_line_magic('pinfo', 'flatchain')
fs[0][1].ndata
fs[0][1].nfev
fs[0][1].nvarys
fs[0][1].lmdif_message
fs[1][1].lmdif_message
fs[2][1].lmdif_message
fs[3][1].lmdif_message
fs[3][1].message
fs[2][1].message
ouf = open('Results.txt','a')
for i in range(0,13):
    ouf.write(str(hislist[i])+':\n')
    ouf.write(str(fs[i][0])+'\n')
    ouf.write(str(fs[i][1].chisqr)+' '+str(fs[i][1].redchi) + '\n')
    ouf.write(fs[i][1].message + '\n')
    
ouf.close()
ouf = open('Results.txt','a')
for i in range(0,13):
    ouf.write(str(hislist[i])+':\n')
    ouf.write(str(fs[i][0])+'\n')
    ouf.write(str(fs[i][1].chisqr)+' '+str(fs[i][1].redchi) + '\n')
    ouf.write(fs[i][1].message + '\n')
    
ouf.close()
peakn
for i in range(0,13):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
for i in range(1,2):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[1]
peakn[1][0][1]=(30,300)
for i in range(1,2):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[1][0][1]=(50,300)
for i in range(1,2):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[1][0].append((20,300))
for i in range(1,2):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[8][0]
peakn[8][0][0]
peakn[8][0][0]=(85,550)
peakn[9][0][0]
peakn[9][0][0]=(150,2500)
peakn[10][0]
peakn[10][0]=[(10,200)]
peakn[12][0]
peakn[12][0]=[(42.652832415421017, 3009.2805105062816),(10,2850),(300,183)]
for i in range(8,13):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[12][0]=[(42.652832415421017, 3009.2805105062816),(10,2850),(100,183)]
peakn[8][0]
peakn[8][0].append((37.927419354838776, 573.17042730221692))
peakn[8][0]
peakn[9][0].append((193.86605035405205, 2499.242377661838))
peakn
for i in range(8,13):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[8][0].append((15,100))
for i in range(8,9):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[12][0]
peakn[12][0][1]=(20,200)
peakn[12][0][2]=(150,200)
for i in range(12,13):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[12][0][1]=(2,200)
for i in range(12,13):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
peakn[12][0]
peakn[12][0].append((20,200))
for i in range(12,13):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   e.fit_peaks(his,rx=(0,4094))
   e.log()
   plt.show()
   input('ok') 
   
fn=[]
for i in range(0,13):
   e.pzot()
   for x in peakn[i][0]:
       e.pk(x[0])
   his = hislist[i]
   print(his,e.peaks)
   fn.append(e.fit_peaks(his,rx=(0,4094)))
   e.log()
   plt.show()
   input('ok') 
   
e.d(925)
e.d(926)
for i in range(0,13):
    nouf.write(str(hislist[i])+':\n')
    ouf.write(str(fs[i][0])+'\n')
    ouf.write(str(fs[i][1].chisqr)+' '+str(fs[i][1].redchi) + '\n')
    ouf.write(fs[i][1].message + '\n')
    
ouf = open('Results.txt','a')
for i in range(0,13):
    ouf.write(str(hislist[i])+':\n')
    ouf.write(str(fn[i][0])+'\n')
    ouf.write(str(fn[i][1].chisqr)+' '+str(fn[i][1].redchi) + '\n')
    ouf.write(fn[i][1].message + '\n')
    
    
ouf.close()
for i in range(0,13):
    ouf.write(str(hislist[i])+':\n')
    ouf.write(str(fn[i][0])+'\n')
    ouf.write(str(fn[i][1].chisqr)+' '+str(fn[i][1].redchi) + '\n')
    ouf.write(fn[i][1].message + '\n\n')
    
    
ouf = open('Results.txt','a')
for i in range(0,13):
    ouf.write(str(hislist[i])+':\n')
    ouf.write(str(fn[i][0])+'\n')
    ouf.write(str(fn[i][1].chisqr)+' '+str(fn[i][1].redchi) + '\n')
    ouf.write(fn[i][1].message + '\n\n')
    
    
ouf.close()
ouf = open('Results.txt','a')
ouf.write(str(peaks)+'\n\n\n')
ouf.write(str(peakn)+'\n\n\n')
out.close()
ouf.close()
ouf = open('Results.txt','a')
ouf.write(hislist)
ouf.write(str(hislist))
ouf.close()
