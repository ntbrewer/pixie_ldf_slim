# coding: utf-8


from Pyspectr.pydamm import *
import pandas as pd
from sklearn import naive_bayes as nbca


e=Experiment('SignalNoise.his')
e1=Experiment('Unclassified.his')
labels = ['avgBLpre','sigBLpre','avgBLpost','sigBLpost','traceMaxTime','traceMin',
'traceMinTime','factorPSDx10','traceRise','traceFall','traceReturnTime','signalNoise']
UDF = pd.read_pickle('UnclassifiedDataAll.pkl')
classesu = UDF["signalNoise"] 
for i in range(0,65536):
    if abs( (UDF.iloc[i])['avgBLpre']-194.3 ) < 194.3/2:
        (UDF.iloc[i])['signalNoise']=1
        
classesu = UDF["signalNoise"] 
gnb = nbca.GaussianNB()

gnb.fit(
UDF[[labels[0]]].values,
classesu
)

gnb.theta_
gnb.sigma_

for lab in labels[1:-1]:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
for i in range(0,65536):
    if (UDF.iloc[i])['signalNoise']==1 and abs( (UDF.iloc[i])['traceRise']-1.1e06 ) < 90*3:
        (UDF.iloc[i])['signalNoise']=2
    else if (UDF.iloc[i])['signalNoise']==0 and abs( (UDF.iloc[i])['traceRise']-361 ) < 12*3:
        (UDF.iloc[i])['signalNoise']=3
for i in range(0,65536):
    if (UDF.iloc[i])['signalNoise']==1 and abs( (UDF.iloc[i])['traceRise']-1.1e06 ) < 90*3:
        (UDF.iloc[i])['signalNoise']=2
    elif (UDF.iloc[i])['signalNoise']==0 and abs( (UDF.iloc[i])['traceRise']-361 ) < 12*3:
        (UDF.iloc[i])['signalNoise']=3
        
used_lab = []
labels[8]
used_lab.append(labels[1])
used_lab.append(labels[2])
used_lab.append(labels[3])
used_lab.append(labels[4])
used_lab.append(labels[5])
used_lab.append(labels[6])
 used_lab.append(labels[7])
used_lab.append(labels[1])
used_lab.append(labels[2])
used_lab.append(labels[3])
used_lab.append(labels[4])
used_lab.append(labels[5])
used_lab.append(labels[6])
used_lab.append(labels[7])
used_lab.append(labels[9])
used_lab.append(labels[10])
used_lab
for lab in labels[1:-1]:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[used_lab], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
for lab in used_lab:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
    
for lab in used_lab:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
for i in range(0,65536):
    if (UDF.iloc[i])['signalNoise']==1 and abs( (UDF.iloc[i])['traceRise']-1.1e06 ) < 90:
        (UDF.iloc[i])['signalNoise']=2
    elif (UDF.iloc[i])['signalNoise']==0 and abs( (UDF.iloc[i])['traceRise']-361 ) < 12:
        (UDF.iloc[i])['signalNoise']=3
        
any(UDF['signalNoise']==3)
any(UDF['signalNoise']==2)
for i in range(0,65536):
    if (UDF.iloc[i])['signalNoise']==1 and abs( (UDF.iloc[i])['traceRise']-1.1e06 ) < 90:
        (UDF.iloc[i])['signalNoise']=2
    elif (UDF.iloc[i])['signalNoise']==0 and abs( (UDF.iloc[i])['traceRise']-361 ) < 12*5:
        (UDF.iloc[i])['signalNoise']=3
        
any(UDF['signalNoise']==3)
for lab in used_lab:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
any(UDF['signalNoise']==2)
any(UDF['signalNoise']==1)
any(UDF['signalNoise']==0)
for i in range(0,65536):
    if abs( (UDF.iloc[i])['sigBLpost']-97 ) < 14.5*3:
        (UDF.iloc[i])['signalNoise']=4
    elif abs( (UDF.iloc[i])['traceRise']-361 ) < 12*5:
        (UDF.iloc[i])['signalNoise']=3
    elif abs( (UDF.iloc[i])['sigBLpost']-1.2e5 ) < 170*3:
        (UDF.iloc[i])['signalNoise']=5
        
        
used_lab = []
#used_lab.append(labels[1])
used_lab.append(labels[2])
used_lab.append(labels[3])
used_lab.append(labels[4])
used_lab.append(labels[5])
used_lab.append(labels[6])
used_lab.append(labels[7])
used_lab.append(labels[9])
used_lab.append(labels[10])
for lab in used_lab:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
#used_lab.append(labels[1])
used_lab.append(labels[2])
#used_lab.append(labels[3])
used_lab.append(labels[4])
used_lab.append(labels[5])
used_lab.append(labels[6])
used_lab.append(labels[7])
used_lab.append(labels[9])
used_lab.append(labels[10])
used_lab=[]
#used_lab.append(labels[1])
used_lab.append(labels[2])
#used_lab.append(labels[3])
used_lab.append(labels[4])
used_lab.append(labels[5])
used_lab.append(labels[6])
used_lab.append(labels[7])
used_lab.append(labels[9])
used_lab.append(labels[10])
used_lab=[]
used_lab.append(labels[1])
used_lab.append(labels[2])
#used_lab.append(labels[3])
used_lab.append(labels[4])
used_lab.append(labels[5])
used_lab.append(labels[6])
used_lab.append(labels[7])
used_lab.append(labels[9])
used_lab.append(labels[10])
for lab in used_lab:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
used_lab=[]
#used_lab.append(labels[1])
used_lab.append(labels[2])
#used_lab.append(labels[3])
used_lab.append(labels[4])
#used_lab.append(labels[5])
used_lab.append(labels[6])
used_lab.append(labels[7])
used_lab.append(labels[9])
used_lab.append(labels[10])
for i in range(0,65536):
    if abs( (UDF.iloc[i])['sigBLpre']-27 ) < 79*3:
        (UDF.iloc[i])['signalNoise']=6
    elif abs( (UDF.iloc[i])['traceMin']-194 ) < 194/2:
        (UDF.iloc[i])['signalNoise']=7
    elif abs( (UDF.iloc[i])['traceMin']-199 ) < 199/2:
        (UDF.iloc[i])['signalNoise']=8
        
        
        
for lab in used_lab:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
for lab in labels:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
for lab in labels[:-1]
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
for lab in labels[:-1]:
    classesu =  UDF["signalNoise"]
    gnb.fit( UDF[[lab]], classesu)
    print(gnb.theta_,gnb.sigma_,lab)
    
gnb.fit(
UDF[labels[:-1]].values,
classesu
)
gnb.sigma_
gnb.theta_
get_ipython().run_line_magic('save', '"adaptiveNB.session" "0-50"')
for i in range(0,200):
    setRegion=[0,0,0,0,0]
    if (UDF.iloc[i])['signalNoise']==1
for i in range(0,200):
    setRegion=[0,0,0,0,0]
    if (UDF.iloc[i])['signalNoise']==1 and setRegion[0]==0:
        e1.gy(900,(i,i),clear=False)
        print(1,UDF.iloc[i])
        setRegion[0]+=1
    if (UDF.iloc[i])['signalNoise']==2 and setRegion[1]==0:
        e1.gy(900,(i,i),clear=False)
        print(2,UDF.iloc[i])
        setRegion[1]+=1
    if (UDF.iloc[i])['signalNoise']==4 and setRegion[2]==0:
        e1.gy(900,(i,i),clear=False)
        print(4,UDF.iloc[i])
        setRegion[2]+=1
    if (UDF.iloc[i])['signalNoise']==6 and setRegion[3]==0:
        e1.gy(900,(i,i),clear=False)
        print(6,UDF.iloc[i])
        setRegion[3]+=1
    if (UDF.iloc[i])['signalNoise']==7 and setRegion[4]==0:
        e1.gy(900,(i,i),clear=False)
        print(7,UDF.iloc[i])
        setRegion[4]+=1
        


        
setRegion=[0,0,0,0,0]
plt.cla()
e.gy(911,(14,14))
for i in range(0,200):
    if (UDF.iloc[i])['signalNoise']==1 and setRegion[0]==0:
        e1.gy(900,(i,i),clear=False)
        print(1,UDF.iloc[i])
        setRegion[0]+=1
    if (UDF.iloc[i])['signalNoise']==2 and setRegion[1]==0:
        e1.gy(900,(i,i),clear=False)
        print(2,UDF.iloc[i])
        setRegion[1]+=1
    if (UDF.iloc[i])['signalNoise']==4 and setRegion[2]==0:
        e1.gy(900,(i,i),clear=False)
        print(4,UDF.iloc[i])
        setRegion[2]+=1
    if (UDF.iloc[i])['signalNoise']==6 and setRegion[3]==0:
        e1.gy(900,(i,i),clear=False)
        print(6,UDF.iloc[i])
        setRegion[3]+=1
    if (UDF.iloc[i])['signalNoise']==7 and setRegion[4]==0:
        e1.gy(900,(i,i),clear=False)
        print(7,UDF.iloc[i])
        setRegion[4]+=1
        


        
for i in range(200,1000):
    if (UDF.iloc[i])['signalNoise']==1 and setRegion[0]==0:
        e1.gy(900,(i,i),clear=False)
        print(1,UDF.iloc[i])
        setRegion[0]+=1
    if (UDF.iloc[i])['signalNoise']==2 and setRegion[1]==0:
        e1.gy(900,(i,i),clear=False)
        print(2,UDF.iloc[i])
        setRegion[1]+=1
    if (UDF.iloc[i])['signalNoise']==4 and setRegion[2]==0:
        e1.gy(900,(i,i),clear=False)
        print(4,UDF.iloc[i])
        setRegion[2]+=1
    if (UDF.iloc[i])['signalNoise']==6 and setRegion[3]==0:
        e1.gy(900,(i,i),clear=False)
        print(6,UDF.iloc[i])
        setRegion[3]+=1
    if (UDF.iloc[i])['signalNoise']==7 and setRegion[4]==0:
        e1.gy(900,(i,i),clear=False)
        print(7,UDF.iloc[i])
        setRegion[4]+=1
        


        
for i in range(1000,10000):
    if (UDF.iloc[i])['signalNoise']==1 and setRegion[0]==0:
        e1.gy(900,(i,i),clear=False)
        print(1,UDF.iloc[i])
        setRegion[0]+=1
    if (UDF.iloc[i])['signalNoise']==2 and setRegion[1]==0:
        e1.gy(900,(i,i),clear=False)
        print(2,UDF.iloc[i])
        setRegion[1]+=1
    if (UDF.iloc[i])['signalNoise']==4 and setRegion[2]==0:
        e1.gy(900,(i,i),clear=False)
        print(4,UDF.iloc[i])
        setRegion[2]+=1
    if (UDF.iloc[i])['signalNoise']==6 and setRegion[3]==0:
        e1.gy(900,(i,i),clear=False)
        print(6,UDF.iloc[i])
        setRegion[3]+=1
    if (UDF.iloc[i])['signalNoise']==7 and setRegion[4]==0:
        e1.gy(900,(i,i),clear=False)
        print(7,UDF.iloc[i])
        setRegion[4]+=1
        


        
for i in range(0,3000):
    if (UDF.iloc[i])['signalNoise']==1 and setRegion[0]==0:
        e1.gy(900,(i,i),clear=False)
        print(1,UDF.iloc[i])
        setRegion[0]+=1
    if (UDF.iloc[i])['signalNoise']==2 and setRegion[1]==0:
        e1.gy(900,(i,i),clear=False)
        print(2,UDF.iloc[i])
        setRegion[1]+=1
    if (UDF.iloc[i])['signalNoise']==4 and setRegion[2]==0:
        e1.gy(900,(i,i),clear=False)
        print(4,UDF.iloc[i])
        setRegion[2]+=1
    if (UDF.iloc[i])['signalNoise']==6 and setRegion[3]==0:
        e1.gy(900,(i,i),clear=False)
        print(6,UDF.iloc[i])
        setRegion[3]+=1
    if (UDF.iloc[i])['signalNoise']==7 and setRegion[4]==0:
        e1.gy(900,(i,i),clear=False)
        print(7,UDF.iloc[i])
        setRegion[4]+=1
        


        
setRegion=[0,0,0,0,0]
for i in range(0,3000):
    if (UDF.iloc[i])['signalNoise']==1 and setRegion[0]==0:
        e1.gy(900,(i,i),clear=False)
        print(1,UDF.iloc[i])
        setRegion[0]+=1
    if (UDF.iloc[i])['signalNoise']==2 and setRegion[1]==0:
        e1.gy(900,(i,i),clear=False)
        print(2,UDF.iloc[i])
        setRegion[1]+=1
    if (UDF.iloc[i])['signalNoise']==4 and setRegion[2]==0:
        e1.gy(900,(i,i),clear=False)
        print(4,UDF.iloc[i])
        setRegion[2]+=1
    if (UDF.iloc[i])['signalNoise']==6 and setRegion[3]==0:
        e1.gy(900,(i,i),clear=False)
        print(6,UDF.iloc[i])
        setRegion[3]+=1
    if (UDF.iloc[i])['signalNoise']==7 and setRegion[4]==0:
        e1.gy(900,(i,i),clear=False)
        print(7,UDF.iloc[i])
        setRegion[4]+=1
        


        
plt.cla()
e.d(-5,-4,-3,-2,-1)
setRegion=[0,0,0,0,0]
for i in range(2100,6000):
    if (UDF.iloc[i])['signalNoise']==1 and setRegion[0]==0:
        e1.gy(900,(i,i),clear=False)
        print(1,UDF.iloc[i])
        setRegion[0]+=1
    if (UDF.iloc[i])['signalNoise']==2 and setRegion[1]==0:
        e1.gy(900,(i,i),clear=False)
        print(2,UDF.iloc[i])
        setRegion[1]+=1
    if (UDF.iloc[i])['signalNoise']==4 and setRegion[2]==0:
        e1.gy(900,(i,i),clear=False)
        print(4,UDF.iloc[i])
        setRegion[2]+=1
    if (UDF.iloc[i])['signalNoise']==6 and setRegion[3]==0:
        e1.gy(900,(i,i),clear=False)
        print(6,UDF.iloc[i])
        setRegion[3]+=1
    if (UDF.iloc[i])['signalNoise']==7 and setRegion[4]==0:
        e1.gy(900,(i,i),clear=False)
        print(7,UDF.iloc[i])
        setRegion[4]+=1
        


        
plt.subplots(2,5)
plt.subplots(5,2)
plt.subplot(5,2,0)
plt.subplot(5,2,1)
e.d(-10,clear=False)
e.d(-10)
plt.subplot(5,2,1)
e.d(-10,clear=False)
gnb.class_count_
gnb.class_prior__
gnb.class_prior_
