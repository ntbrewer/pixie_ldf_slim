/**    \file TraceAnalyzer.cpp
 *     \brief defines the Trace class.
 *
 *     Implements a quick online trapezoidal filtering mechanism
 *     for the identification of double pulses
 *
 *     - SNL - 7-2-07 - created
 *     - SNL - 2-4-08 - Add plotting spectra
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <signal.h>

#include <cstdlib>

#include "damm_plotids.h"
#include "RandomPool.h"
#include "RawEvent.h"
#include "StatsAccumulator.h"
#include "TraceAnalyzer.h"
//#include <math.h>

using namespace std;

// external pool of random numbers defined in RandomPool.cpp
extern RandomPool randoms;

const string TraceAnalyzer::defaultFilterFile="filter.txt";

/**
 * Initialize the trace analysis class.  Set the row numbers
 * for spectra 850 and 870 to zero and reserve enough memory
 * for the filter vectors. This also reads in the filter parameters from
 * the filter file in the following order:
 *    fast rise, fast gap, fast threshold
 *    energy rise, energy gap
 *    3rd filter rise, 3rd filter gap, 3rd filter threshold
 */
int TraceAnalyzer::Init(const string &filterFile)
{   
    const int maxTraceLength = 6400;

    rownum850 = 0;
    rownum870 = 0;

    // reserves enough space in the vector to contain a reasonable sized trace
    // This improves the performance of the program as a whole since memory
    // does not need to be reallocated every time the size is increased.

    average.reserve(maxTraceLength);
    //fastFilter.reserve(maxTraceLength);
    //energyFilter.reserve(maxTraceLength);
    //thirdFilter.reserve(maxTraceLength);
    flt.reserve(maxTraceLength);

    // read in the filter parameters
    ifstream in(filterFile.c_str());
    if (!in) {
      cout << "failed to open the filter parameter file" << endl;
      cout << "  using default values" << endl;
      return 1;
    }

    while (!in.eof()) {
      if ( isdigit(in.peek()) ) {
	in >> fastRise >> fastGap >> fastThresh;
	in >> slowRise1 >> slowGap1;
	in >> slowRise2 >> slowGap2 >> slowThresh;
	in >> traceDelay;
	cout << "Trace analysis parameters are: "
	     << "  \nFast filter: " << fastRise << " " << fastGap << " " << fastThresh
	     << "  \nEnergy filter: " << slowRise1 << " " << slowGap1
	     << "  \n3rd filter: " << slowRise2 << " " << slowGap2 << slowThresh
	     << "  \nTrace Delay " << traceDelay
	     << endl;
	// scale thresholds by the length of integration (i.e. rise time)
	fastThresh *= fastRise;
	slowThresh *= slowRise2;
	break;
      } else {
	// assume this is a comment
	in.ignore(1000, '\n');
      }
    }
    if (in.fail()) {
      cout << "problem reading filter parameters file" << endl;
      return 1;
    }

    return 0;
}

/**
 * Set default filter parameters
 */
TraceAnalyzer::TraceAnalyzer() : 
    userTime(0.), systemTime(0.)
{
  //  clocksPerSecond = sysconf(_SC_CLK_TCK);
    fastRise = fastGap = 5;
    slowRise1 = slowGap1 = 100;
    //? these are some legacy values, are they appropriate
    slowRise2 = 10; 
    slowGap2 = 20;

    fastThresh = fastRise * 3;
    slowThresh = slowRise2 * 2;
}

/** Output time processing traces */
TraceAnalyzer::~TraceAnalyzer() 
{
    cout << "Trace processor : " 
	 << userTime << " user time, "
	 << systemTime << " system time" << endl;
}

/**
 * Function to quickly analyze a trace online.  Trapezoidal filters
 * are run across the trace with varying parameters to extract E1
 * and E2 values and time differences
 *
 * This routine detects when the fast filter crosses its threshold,
 * verifies that the slower 3rd filter also is above its threshold,
 * and then samples the energy filter during its flattop.
 * detType and detSubtype not currently used
 */
int TraceAnalyzer::Analyze(const vector<int> &trace, 
			   const string &detType, const string &detSubtype)
{
    tms tmsBegin;

    times(&tmsBegin); // begin timing process
    
    average.clear();
    //fastFilter.clear();
    //energyFilter.clear();
    //thirdFilter.clear();

    // quick trace analysis adapted from previous scan versions in
    // the xia_trace99.f file.
    const int baseLow = 1, baseHigh = 350;//caution changing parm from thos for header. ...

      
    StatsAccumulator statsPre = accumulate
	(&trace[baseLow], &trace[baseHigh], StatsAccumulator());
    double basel  = statsPre.GetMean();
    //double sbasel = stats.GetStdDev();
    avgBaselinePre = statsPre.GetMean();
    stdDevBaselinePre = statsPre.GetStdDev();
    // sigma not used

 
    // determine trace filters, these are trapezoidal filters
    // characterized by a risetime and gaptime and a range of
    // the filter from lo to hi.
    // filter(trace, lo, hi, gaptime, risetime);
    int high = trace.size();

    //replacing if (i >= hi-70 && i < hi-20) avgBaselinePost += trace[i]/50 below
    StatsAccumulator statsPost = accumulate
	(&trace[high-70], &trace[high-20], StatsAccumulator());
	avgBaselinePost = statsPost.GetMean();
    stdDevBaselinePost = statsPost.GetStdDev();
	
    StatsAccumulator stats = accumulate
	(&trace[baseLow], &trace[high], StatsAccumulator());
	avgBaseline = stats.GetMean();
    stdDevBaseline = stats.GetStdDev();

    // make a trace of the running average
    const int averageLen = 10;
    // a lot of repeated arithmetic here too
    for(int i = 0; i < (signed)(trace.size()-averageLen); i++) {
      stats = accumulate
	(&trace[i], &trace[i+averageLen], StatsAccumulator());
      average.push_back(stats.GetMean() - basel);
    }
        	
    //int fastSize = 2 * fastRise + fastGap;
    //FilterFill(trace, fastFilter, fastSize, high, fastGap, fastRise);

    int slowSize1 = 2 * slowRise1 + slowGap1;
    //FilterFill(trace, energyFilter, slowSize1, high, slowGap1, slowRise1);
    
    //Calculate Trace Maximum and Average Baseline for PSA
    CalculateTraceMaxAndAvgBaseline(trace, slowSize1, high, slowGap1, slowRise1);
    
    
    //int slowSize2 = 2 * slowRise2 + slowGap2;
    //FilterFill(trace, thirdFilter, slowSize2, high, slowGap2, slowRise2);

    //size_t sample; // point at which to sample the slow trace
    // find the point at which the trace crosses the threshold
    /*
    t1 = -1;
    e1 = 0;
    
    vector<int>::iterator iThr  = fastFilter.begin() + baseHigh - fastSize;
    vector<int>::iterator iHigh = fastFilter.end(); 

    while (iThr < iHigh) {
      iThr = find_if(iThr, iHigh, bind2nd(greater<int>(), fastThresh));
      // check that the correlated energy is sufficiently high
      t1 = iThr - fastFilter.begin();
      sample = t1 + (slowRise2 + slowGap2 / 2) - (fastRise + fastGap / 2);
      if (sample < thirdFilter.size() && thirdFilter[sample] > slowThresh) {
	sample = t1 + (slowRise1 + slowGap1 / 2) - (fastRise + fastGap / 2);
	e1 = energyFilter[sample] + randoms.Get();
	// scale to the integration time
	e1 /= slowRise1; 
      }
      // find the trailing edge
      iThr += fastGap;
      iThr = find_if(iThr, iHigh, bind2nd(less<int>(), fastThresh));
      iThr += fastSize;
    }
    */
    //CalculatePhase(fastFilter, baseHigh, high);
    
    // find a second crossing point
    /*t2 = -1;
    e2 = 0;
  
    if ( t1 != -1 && iThr < fastFilter.end() ) {
      while (iThr != iHigh) {
	iThr = find_if(iThr, iHigh, bind2nd(greater<int>(), fastThresh));
	if (iThr != iHigh) {
	  t2 = iThr - fastFilter.begin();
	  sample = t2 + (slowRise2 + slowGap2 / 2) - (fastRise + fastGap / 2);
	  if (sample < thirdFilter.size() && 
	      thirdFilter[sample] - thirdFilter[t2 - fastSize] > slowThresh) {
	    sample = t2 + (slowRise1 + slowGap1 / 2) - (fastRise + fastGap / 2);
	    e2 = energyFilter[sample] - energyFilter[t2 - fastSize];
	    e2 += randoms.Get();
	    // scale to the integration time
	    e2 /= slowRise1;
	  }
	}
      }
    }*/

  TracePlot(trace);
  
  tms tmsEnd;
  times(&tmsEnd);
  userTime += (tmsEnd.tms_utime - tmsBegin.tms_utime) / clocksPerSecond;
  systemTime += (tmsEnd.tms_stime - tmsBegin.tms_stime) / clocksPerSecond; 

  return(0);
}

/**
 * Defines how to implement a trapezoidal filter characterized by two
 * moving sum windows of width risetime separated by a length gaptime.
 * Filter is calculated from channels lo to hi.
 */
vector<int> TraceAnalyzer::Filter(vector<int> &trace, int lo, int hi, 
			  int gapTime, int riseTime){
  flt.clear();

  if (lo != 0) {
      for(int i = 0; i < lo; i++) {
	  flt.push_back(0); 
      }
  }

  // repeated arithmetic here too
  for(int i = lo; i < hi; i++){
    int leftSum  = 0;
    int rightSum = 0;
    
    for (int j = i - 2*riseTime - gapTime; j < i - riseTime - gapTime; j++) {
	leftSum += trace[j];
    }

    for (int j = i - riseTime; j < i; j++) {
	rightSum += trace[j];
    }

    flt.push_back(rightSum - leftSum);
  }

  return flt;
}

/**
 * same thing as Filter() but fill the storage directly without passing 
 * through the temporary return value
 */
void TraceAnalyzer::FilterFill(const vector<int> &trace, vector<int> &res,
			int lo, int hi, int gapTime, int riseTime){
    res.assign(lo, 0);
    int leftSum = 0;
    int rightSum = 0;
    for (int i = lo; i < hi; i++) {
	    leftSum = accumulate(&trace[i - 2*riseTime - gapTime],
				 &trace[i - riseTime - gapTime], 0);
	    rightSum = accumulate(&trace[i - riseTime], &trace[i], 0);
	res.push_back(rightSum - leftSum);
    }

}

/**
 * same thing as Filter() but fill the storage directly without passing 
 * through the temporary return value
 */
/**void TraceAnalyzer::CalculateTraceMaxAndAvgBaseline(const vector<int> &trace, vector<int> &res,
			int lo, int hi, int gapTime, int riseTime){
    res.assign(lo, 0);
	//avgBaseline = accumulate(&trace[lo - 2*riseTime - gapTime],
	//			 &trace[lo - riseTime - gapTime], 0);
	//avgBaseline /= riseTime; 
    
    traceMax = ( int ) trace[lo];
    traceMaxTime = lo;
    for (int i = lo; i < hi; i++) 
    {
      if (trace[i] > traceMax) 
      {
          traceMax = trace[i];
          traceMaxTime = i;
      }
    }
    
}**/

/**
 * same thing as Filter() but fill the storage directly without passing 
 * through the temporary return value
 */
void TraceAnalyzer::CalculateTraceMaxAndAvgBaseline(const vector<int> &trace, 
			int lo, int hi, int gapTime, int riseTime){
    //res.assign(lo, 0);
	//avgBaseline = accumulate(&trace[lo - 2*riseTime - gapTime],
	//			 &trace[lo - riseTime - gapTime], 0);
	//avgBaseline /= riseTime; 
    lo =1;
    traceMax = trace[lo];
    traceMaxTime = lo;
    traceMin = 4095;
    traceMinTime = lo;
    satLength = 0;
    double traceQ=0., traceQTail=0., norm=4095.;
    
    for (int i = lo; i < hi; i++) 
    {
      if (trace[i] > traceMax) 
      {
          traceMax = trace[i];
          traceMaxTime = i;
      }
      if (trace[i] < traceMin) 
      {
          traceMin = trace[i];
          traceMinTime = i;
      }
      if (trace[i] == 4095) satLength+=1; //Calculate the number of Saturated channels in trace. NTB
      //if (i >= hi-70 && i < hi-20) avgBaselinePost += trace[i]/50.;
      traceQ += trace[i]/norm;
    }
    
    if (traceMaxTime > hi-100) //100 based off of method for taking baselinePost
    {
      traceMax = trace[lo];
      traceMaxTime = lo;
      for (int i = lo; i < hi*2./3.; i++) 
      {
        if (trace[i] > traceMax) 
        {
          traceMax = trace[i];
          traceMaxTime = i;
        }        
      }
    }
    
    int isUnset=1;
    
    for (int i = traceMax; i < hi; i++)
    {
      if (trace[i] < avgBaselinePost + stdDevBaselinePost && isUnset)
      {
        traceReturnTime=i;
        isUnset=0;
      }
      traceQTail += trace[i]/norm;
    }
    factorPSD = (traceQTail/traceQ+1)*100;
    traceRise = double(traceMax - avgBaselinePre)/double(traceMaxTime - lo);
    traceFall = double(traceMax - avgBaselinePost)/double(traceReturnTime - traceMaxTime);
    
}
void TraceAnalyzer::CalculatePhase(vector<int> &res, int lo, int hi)
{
    //res here is the result of the fastFilter I'm not sure it is necessary...
    phase = 0;
    int tMin = lo;
    int min = ( int ) res[lo];
    int tMax = lo;
    int max = ( int ) res[lo];

    for (int i = lo; i < hi; i++)
    {
      if (res[i] > max) 
      {
          max = res[i];
          tMax = i;
      }   
    }
        
    for (int i = tMax; i < hi; i++)
    {
      if (res[i] < min)
      {
          min = res[i];
          tMin = i;
      }
    }
    int test = max;
    
    for (int i = max; i < tMin; i++) 
    {
      if (abs(res[i]-res[phase]) < test ) 
      {
          phase = i;
          test = res[i];
      }
    }  
  // cout << "l,h,t,p " << tMax << " " << tMin << " " << test << " " << phase << endl;   
}

/** declare the damm plots */
void TraceAnalyzer::DeclarePlots() const
{
    using namespace dammIds::trace;

    const int traceBins = SB;
    const int numTraces = S8;
    const int numOther1 = SE;
    const int numOther = S8;
    const int energyBins = SC;
    const int energyBins2 = SA;
    const int timeBins = S8;
    const int numTracePlots = 1;//Matt** Starting at 900 make this number of plots, up to 10
    //Matt** use with caution(Makes Big Files)

    for (int i=0; i<numTracePlots; i++) 
    {
        DeclareHistogram2D(DD_TRACE+i, traceBins, numOther1, "traces data");
    }
    DeclareHistogram2D(DD_FILTER1, traceBins, numOther, "fast filter Offset 2k");    
    DeclareHistogram2D(DD_FILTER2, traceBins, numOther, "energy filter Offset 2k");
    DeclareHistogram2D(DD_FILTER3, traceBins, numOther, "3rd filter Offset 2k");
    DeclareHistogram2D(DD_AVERAGE_TRACE, traceBins, numOther, "trace average");
    
    DeclareHistogram2D(DD_DOUBLE_TRACE, traceBins, numOther, "double traces");
    DeclareHistogram2D(DD_ENERGY2__TDIFF, energyBins2, timeBins, "E2 vs DT", 2);
    DeclareHistogram2D(DD_ENERGY1__TIME, energyBins2,traceBins, "E1 vs T");
    DeclareHistogram2D(DD_ENERGY1__TMAX, energyBins2,traceBins, "E1 vs TMax");
//    DeclareHistogram1D(DD_ENERGY1__TIME, energyBins2, timeBins, "E1 vs T", 2);
    DeclareHistogram2D(DD_ENERGY2__ENERGY1, energyBins2, energyBins2, "E2 vs E1", 2);
    DeclareHistogram2D(DD_TRACEMAX_TQDC, SA, SA, "E1 vs. E1/(TraceMax-<BL>) *100", 2);
    DeclareHistogram2D(DD_RTRACE+1, traceBins, numTraces, "Region 1 Traces");
    DeclareHistogram2D(DD_RTRACE+2, traceBins, numTraces, "Region 2 Traces");
    DeclareHistogram2D(DD_RTRACE+3, traceBins, numTraces, "Region 3 Traces");
    
    DeclareHistogram2D(DD_RTRACE+5, SB, S7, "Energy vs Region");
    //DeclareHistogram2D(DD_RTRACE+4, traceBins, numTraces, "Region 4 Traces");
    DeclareHistogram2D(DD_ENERGY_V_TMAX,SE, SE, "Trace Max vs RAW");
    DeclareHistogram1D(D_ENERGY1, energyBins, "E1 from traces");    
    DeclareHistogram1D(D_ENERGY2, energyBins, "E2 from traces");
    
    DeclareHistogram1D(D_PTRACE, energyBins, "avgBaselinePre");
    DeclareHistogram1D(D_PTRACE+1, energyBins, "avgBaselinePre sigma");
    DeclareHistogram1D(D_PTRACE+2, energyBins, "avgBaseline Post");
    DeclareHistogram1D(D_PTRACE+3, energyBins, "pre - post baseline");
    DeclareHistogram1D(D_PTRACE+4, energyBins, "max Trace");
    DeclareHistogram1D(D_PTRACE+5, energyBins, "time of max Trace");
    DeclareHistogram1D(D_PTRACE+6, energyBins, "min Trace");
    DeclareHistogram1D(D_PTRACE+7, energyBins, "time of min Trace");    
    DeclareHistogram1D(D_PTRACE+8, energyBins, "SatLength");
    DeclareHistogram1D(D_PTRACE+9, energyBins, "avgBaseline");
    DeclareHistogram1D(D_PTRACE+10, energyBins, "avgBaseline sigma");
    DeclareHistogram1D(D_PTRACE+11, energyBins, "PSD Factor");
    DeclareHistogram1D(D_PTRACE+12, energyBins, "Trace Rise Time");
    DeclareHistogram1D(D_PTRACE+13, energyBins, "Trace Fall Time");
//    DeclareHistogram1D(D_PTRACE+14, energyBins, "Trace Return Time");
    DeclareHistogram2D(D_PTRACE+14, energyBins, energyBins, "Trace Rise vs Trace Fall Time");
        
    DeclareHistogram1D(D_PTRACE+15, S8, "Region Pre if NB Signal");
    DeclareHistogram1D(D_PTRACE+16, S8, "Region Pre if NB Noise");

    
//    for (int j=0; j<50; j++ ) DeclareHistogram2D(DD_ENERGY_V_TMAX+j,SB, SC, "Trace Max vs RAW");
    
    //DeclareHistogram2D(DD_TRACEMAX_TQDC2, S9, SA, "E1 vs. 10*(TraceMax-<BL>)/E1 ", 2);
}

/**
 * From the trace analysis plot the damm spectra.
 *   including the first few traces of the analysis
 *   and their associated filters.
 *   as well as  E2 v E1 and E2 v time difference plots with
 *   varying conditions for double pulses.
 */
void TraceAnalyzer::TracePlot(const vector<int> &trace)
			      
{
    using namespace dammIds::trace;
    static int r1Cnt=-1;
    //static int r2Cnt=-1;
    static int r3Cnt=-1;
    //static int r4Cnt=-1;
    //int rCnt=-1;
    
    plot(DD_ENERGY1__TIME, (traceMax-avgBaseline)*4/10 , phase );
    plot(DD_ENERGY1__TMAX, (traceMax-avgBaseline)*4/10 , traceMaxTime );
    
    if (traceMax > avgBaseline) 
    {
        double ratio = (double) (1000*e1 / (traceMax-avgBaseline) );
        plot(DD_TRACEMAX_TQDC, e1 , ratio );
    }
    
    //begin 'region classifier' massive case switch and basis for NB classification
    
    region = 0;
    
    if (traceRise>1)
    {
      region+=0;
    } else
    {
      region+=1; //1
    }
    
    if (factorPSD < 160)// && factorPSD < 300)
    {
      region +=2; //2-3
    } else 
    {
      region +=0; //0-1
    }

    /*if (traceMin > 190 && traceMin < 220)
    {
      region += 0; //0-1
      r2Cnt+=1;
      for(unsigned int i = 0; i < trace.size(); i++)
      {
        plot(DD_RTRACE+2,i,r2Cnt,trace[i]);
      }
    } else
    {
      region += 4; //2-3
    }*/
      
    if (traceMax == 4095) 
    {
      region += 4; //4-7
      r1Cnt+=1;
      for(unsigned int i = 0; i < trace.size(); i++)
      {
        plot(DD_RTRACE+1,i,r1Cnt,trace[i]);
      }
    }
    else
    {
      region += 0; //0-3
      r3Cnt+=1;
      for(unsigned int i = 0; i < trace.size(); i++)
      {
        plot(DD_RTRACE+3,i,r3Cnt,trace[i]);
      }      
    }
    
    /*if (traceMaxTime > 50)
    {
      region +=0; //0-7
    } else
    {
      region +=16; //8-15
    }
    
    if (traceMinTime < 500)
    {
      region +=0; //0-15
    } else
    {
      region +=32; //16-31
    }*/
    
    if (avgBaselinePre >190 && avgBaselinePre < 250)
    {
      region+=0;  //0-7
    } else
    {
      region+=8; //8-15
    }
    
    if (stdDevBaselinePre <6)
    {
      region+=0; //0-15
    } else
    {
      region+=16; //16-31
    }
    
    if (avgBaselinePost >185)
    {
      region+=0; //0-31
    } else
    {
      region+=32; //32-63
    }
    
    plot(DD_RTRACE+5, (traceMax-avgBaselinePre)/4., region);

    if ((traceMax-avgBaselinePre) > 500. )  
    { 
      plot(D_PTRACE  , avgBaselinePre);
      plot(D_PTRACE+1, stdDevBaselinePre);       
      plot(D_PTRACE+2, avgBaselinePost);
      plot(D_PTRACE+3, stdDevBaselinePost);            
      plot(D_PTRACE+4, ((avgBaselinePre - avgBaselinePost)+10)*10);
      plot(D_PTRACE+5, traceMaxTime);
      plot(D_PTRACE+6, traceMin);
      plot(D_PTRACE+7, traceMinTime);
      plot(D_PTRACE+8, satLength);    
      plot(D_PTRACE+9, avgBaseline);
      plot(D_PTRACE+10, stdDevBaseline);
      plot(D_PTRACE+11, factorPSD); 
      plot(D_PTRACE+12, (traceRise+1)*10); 
      plot(D_PTRACE+13, (traceFall+1)*10);
//      plot(D_PTRACE+14, (traceRise/traceFall +1)*10);
    }  
    
    plot(D_PTRACE+14,(traceRise+10)*100, (traceFall+10)*100);
    
    vector<double> traceClassifiers = {avgBaselinePre, stdDevBaselinePre, avgBaselinePost,
    stdDevBaselinePost, double(traceMaxTime), double(traceMin), double(traceMinTime), avgBaseline, 
    stdDevBaseline, factorPSD, (traceRise+1)*10, (traceFall+1)*10, (traceRise/traceFall +1)*10};
    
    double meanSignal=0., sigmaSignal=0., ampSignal =0.;
    double meanNoise=0., sigmaNoise=0., ampNoise =0.;
    double probSignal=.02, probClassifierSignal=1., probNoise=0.98, probClassifierNoise =1.;
    for (int tcIndex =0; tcIndex < 13; tcIndex++) 
    {
             
       if (tcIndex == 1 || tcIndex == 3 || tcIndex == 4 || tcIndex == 6 || //poorly classifying
       tcIndex == 7 || tcIndex == 8 || tcIndex == 12) continue; //not independant
       
       
       //cout << tcIndex << " tci ";
       
       probClassifierSignal = 0.;
       probClassifierNoise = 0.;
       
       for (int pIndex =0; pIndex < 5; pIndex++) 
       {
         double tcValue = double(traceClassifiers[tcIndex]);
         
         meanSignal = signalVector[tcIndex][pIndex*3];

         if (meanSignal != 0.) 
         {
           
           meanSignal /= 1000.;
           meanSignal -= tcValue;
           sigmaSignal = signalVector[tcIndex][pIndex*3+1]/1000.;
           ampSignal = signalVector[tcIndex][pIndex*3+2]/1000.;
           
           double ratioSignal = meanSignal/sigmaSignal;
           probClassifierSignal += exp(-(ratioSignal*ratioSignal)/2.) / 
           (sqrt(6.28*sigmaSignal * sigmaSignal));
               
         //  cout <<  probClassifierSignal << " pCS "; 
         } 
         
         meanNoise = noiseVector[tcIndex][pIndex*3];

         if (meanNoise != 0.) 
         {
           
           meanNoise /= 1000.;
           meanNoise -= tcValue;
           sigmaNoise = noiseVector[tcIndex][pIndex*3+1]/1000.;
           ampNoise = noiseVector[tcIndex][pIndex*3+2]/1000.;
           
           double ratioNoise = meanNoise/sigmaNoise;
           probClassifierNoise += exp(-(ratioNoise*ratioNoise)/2.) /
           (sqrt(6.28*sigmaNoise * sigmaNoise));
           
          // cout <<  probClassifierNoise << " pCN ";            
         }        
         
       }
       //if (probClassifierSignal > 0.1) 
       //{
         probSignal *= probClassifierSignal;
       //} else {
       //  probSignal *= 0.1;
       //}
       
       //if (probClassifierNoise > 0.1) 
       //{
        probNoise *= probClassifierNoise;
       //} else {
       //  probNoise *= 0.1;
       //}
      // cout << probSignal << " pS "; 
      // cout << probNoise << " pN " << endl; 
                         
    }  
    //cout << endl; 
     
    if (probNoise < probSignal) {
      plot(D_PTRACE+15, region);
    //  region = 0;
      //cout << "signal: " << region << endl;
      
    } else {
      plot(D_PTRACE+16, region);
     // region = 1;
      //cout << "noise: " << region << endl;
    }
  
     
        
//APD regions        if (ratio > (7.3 * e1 - 11.17)) //Region I noise
        /*if ( abs(traceMax-850)<2) //specific for MTAS trace //(ratio > (2.37 * e1 + 8.9)) //Region I noise - KSI
        {
            region=1;
            r1Cnt++;
            rCnt=r1Cnt;
        } else if ( abs(traceMax-1600)<2 )//( e1 < 4 && ratio < (2.37 *e1 + 8.9)) //Region II low E cut
        {
            region=2;
            r2Cnt++;
            rCnt=r2Cnt;
        } else if ( abs(traceMax-3200)<2 ) //Region III Xrays and Betas
        {
            region=3;
            r3Cnt++;
            rCnt=r3Cnt;
        } else if ( traceMax>4050 ) //Region III Xrays and Betas
        {
            region=4;
            r4Cnt++;
            rCnt=r4Cnt;
        }*/
        /*if( traceMaxTime > 1000 ) //(traceMax - avgBaseline ) < 50 ) //SDD Noise @ ~30
        {
            region=1;
            r1Cnt++;
            rCnt=r1Cnt;
        } 
        else if( abs(avgBaselinePost - avgBaseline) > 50 && traceMax < 500  )// - avgBaseline) < 500) //K40 in SDD
        //else if ( abs(traceMax-1600)<2 )//( e1 < 4 && ratio < (2.37 *e1 + 8.9)) //Region II low E cut
        {
            region=2;
            r2Cnt++;
            rCnt=r2Cnt;
        }
        // added by Goetz Feb 9, look at traces in low energy peak 
        else if (traceMax >= 4000 && traceMax <= 4094) //if( avgBaseline < 200)
        //else if ( abs(traceMax-3200)<2 ) //Region III Xrays and Betas
        {
            region=3;
            r3Cnt++;
            rCnt=r3Cnt;
        }
        
        // added by Goetz Feb 9, 2018. Look at traces pertaining to ~3 keV with current settings  
        else if (traceMax >= 580 && traceMax <= 1740) //if ((avgBaseline - traceMin) > 30)// ( traceMax>4094 ) //Region III Xrays and Betas
        {
            region=4;
            r4Cnt++;
            rCnt=r4Cnt;
        }*/

    
    // plot trace and associated filters and derived energies
    for(unsigned int i = 0; i < trace.size(); i++){
      if(i < average.size() )
	    plot(DD_AVERAGE_TRACE,i,rownum850,average[i]);
    /*  if(i < thirdFilter.size() ) 
    	plot(DD_FILTER3,i,rownum850,abs(thirdFilter[i]+2000));
      if(i < energyFilter.size() ) 
	    plot(DD_FILTER2,i,rownum850,abs(energyFilter[i]+2000));
      if( i < fastFilter.size() )
    	plot(DD_FILTER1,i,rownum850,abs(fastFilter[i]+2000));
     */
      plot(DD_TRACE+rownum850/16384,i,rownum850,trace[i]);
      /*if (traceMax > avgBaseline) 
      {
        plot(DD_RTRACE+region,i,rCnt,trace[i]);
      }*/
    }
    
   
    plot(DD_TRACE,trace.size()+2,rownum850,e1);
    plot(DD_TRACE,trace.size()+3,rownum850,t1);
    if(e2>0)
      plot(DD_TRACE,trace.size()+4,rownum850,e2);
    if(t2>0)
      plot(DD_TRACE,trace.size()+5,rownum850,t2);
    rownum850++;
    
    // plot double pulse E and T spectra
    plot(D_ENERGY1,e1);
    if(e2 > 0) {
      plot(D_ENERGY2,e2);
      plot(DD_ENERGY2__TDIFF,e2,t2-t1);
      plot(DD_ENERGY2__ENERGY1,e2,e1);

      for (size_t i = 0; i < trace.size(); i++) {
	plot(DD_DOUBLE_TRACE,i,rownum870,trace[i]);
      }
      plot(DD_DOUBLE_TRACE,trace.size()+10,rownum870,e1);
      plot(DD_DOUBLE_TRACE,trace.size()+11,rownum870,t1);
      plot(DD_DOUBLE_TRACE,trace.size()+12,rownum870,e2);
      plot(DD_DOUBLE_TRACE,trace.size()+13,rownum870,t2);
	    
      rownum870++;    
    }
}
