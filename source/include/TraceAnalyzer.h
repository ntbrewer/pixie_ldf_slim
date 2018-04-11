/**   \file TraceAnalyzer.h
 *    \brief Header file for the TraceAnalyzer class
 *
 *    SNL - 7-2-07
 */

#ifndef __TRACEANALYZER_H_
#define __TRACEANALYZER_H_

#include <string>
#include <vector> //is this needed?

#include <sys/times.h>

using std::string;
using std::vector;


/** \brief quick online trace analysis
 *
 * Trace class implements a quick online trapezoidal fiter for the
 * identification of double pulses with relatively little computation.
 */

class TraceAnalyzer {
 private:
    // things associated with timing
    double userTime;          ///< user time used by this class
    double systemTime;        ///< system time used by this class
    double clocksPerSecond;   ///< frequency of system clock

    vector<double> average;   ///< trace average
    //vector<int> fastFilter;   ///< fast filter of trace
    //vector<int> energyFilter; ///< energy filter of trace
    //vector<int> thirdFilter;  ///< third filter of trace, used as a second threshold check 

    vector<int> flt;         ///< vector used in filter function
        
    int t1;                  ///< time of E1 pulse
    int t2;                  ///< time of E2 pulse
    double e1;               ///< energy of E1 pulse
    double e2;               ///< energy of E2 pulse
    
    double phase;            ///< phase of the pulse in ch.
    int rownum850;           ///< rownumber of DAMM spectrum 850
    int rownum870;           ///< rownumber of DAMM spectrum 870

    int fastRise;            ///< rise time of fast filter (in samples)
    int slowRise1;           ///< rise time of energy filter (in samples)
    int slowRise2;           ///< rise time of slow threshold filter (in samples)
    int fastGap;             ///< gap time of fast filter (in samples)
    int slowGap1;            ///< gap time of energy filter (in samples)
    int slowGap2;            ///< gap time of slow threshold filter (in samples)
    int fastThresh;          ///< threshold of fast filter
    int slowThresh;          ///< threshold of slow filter
    int traceDelay;          ///< Trace Delay for this analysis
    double avgBaseline;      ///< Avg. Baseline of the trace for PSA
    double stdDevBaseline;   ///< Variance of Baseline of the trace for PSA
    double avgBaselinePre;      ///< Avg. Baseline of the trace for PSA
    double stdDevBaselinePre;   ///< Variance of Baseline of the trace for PSA
    double avgBaselinePost;      ///< Avg. Post Pulse Baseline of the trace for PSA
    double stdDevBaselinePost;   ///< Avg. Post Pulse Baseline of the trace for PSA    
    int traceMax;            ///< Maximum Value of the trace
    int traceMaxTime;        ///< Time in trace for Maximum Value of the trace
    int traceMin;						 ///< Minimum Value of the trace	
    int traceMinTime;				 ///< Time in trace for Minimum Value of the trace	
    int traceReturnTime;     ///< Time that the trace returns to baseline
    int region;              ///< Region of Trace analysis FOM
    int satLength;           ///< Number of Saturated Channels (NTB)
    double factorPSD;        ///< PSD factor  of L/(L+S) or 1-S/T
    double traceRise;        ///< Trace Rise Time E/t (ADU/ch)
    double traceFall;        ///< Trace Fall Time E/t (ADU/ch)

    /** default filename containing filter parameters
     */
    static const std::string defaultFilterFile;
    
    //traceClassifiers = {avgBaselinePre, stdDevBaselinePre, avgBaselinePost,
    //stdDevBaselinePost, double(traceMaxTime), double(traceMin), double(traceMinTime), avgBaseline, 
    //stdDevBaseline, factorPSD, (traceRise+1)*10, (traceFall+1)*10, (traceRise/traceFall +1)*10};
    
const vector< vector <int> > signalVector = {
 {206220, 2266, 19872606, 215604, 4906, 563087, 
 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {504, 5, 446560, 
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {206763, 7499, 1049428, 1289284, 970808, 25088240,
 238140, 20699, 1259420, 459983, 138338, 1506069, 4094500, 5013, 56810},
 {501, 1864, 3109068, 60449, 89864, 29651513, 293358, 35314, 307296, 
 0, 0, 0, 0, 0, 0},
 {487972, 2889, 5929557, 681581, 27189, 2598626, 
 785368, 20431, 580417, 504700, 8947, 6562256, 542161, 24062, 4828538},
 {204094, 2403, 20602888, 
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {8055, 2594, 2503585, 325694, 9401, 3553920, 
 1615928, 308, 3855, 123724, 97684, 9832970, 
 0, 0, 0},
 {366954, 24684, 1202212, 2809826, 165424, 12027239,
 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {181909, 10695, 742907, 1653052, 16507, 13220778, 228462, 30441, 592049, 
 0, 0, 0, 0, 0, 0},
 {129408, 14252, 887274, 152824, 5005, 945506,
 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {18582, 957, 1233412, 86636, 1864, 9443632, 49907, 17649, 1315636, 
 0, 0, 0, 0, 0, 0},
 {20665, 4300, 2707850, 56147, 18813, 16382699,
 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {33912, 7522, 6250519, 54293, 16900, 2537275, 22948, 4296, 11680971, 
 0, 0, 0, 0, 0, 0}};
 
const vector< vector <int> > noiseVector = {
 {116519, 83356, 36239577, 203613, 1075, 57303864,
 206789, 2332, 61698363, 395228, 31229, 185186,
 0, 0, 0},
 {500, 466, 124164074, 500, 18104, 13371189, 500, 2504, 54682873, 
 0, 0, 0, 0, 0, 0},
 {155664, 58925, 31501881, 204336, 2109, 104206277,
 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {500, 2, 805987, 
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {2000, 2000, 2200000, 513906, 36321, 137592607,
 1128042, 329895, 8380143, 1193911, 3731, 344815,
 0, 0, 0},
 {31838, 77636, 28881436, 201960, 1863, 92467910,
 172883, 45851, 12043891, 2000, 2000, 2400000,
 0, 0, 0},
 {6633, 1963, 5323665, 110713, 53039, 27048493,
 1203688, 131396, 66459434, 1554862, 104271, 31804047,
 0, 0, 0},
 {152244, 60442, 31117041, 217232, 3120, 101803061, 505, 2296849, 53666292, 
 0, 0, 0, 0, 0, 0},
 {47873, 13944, 2608388, 23830, 4399, 68209336, 16210, 1956, 75121076, 
 0, 0, 0, 0, 0, 0},
 {164032, 11461, 1318515, 188989, 3833, 36409030,
 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {11026, 229, 466250478, 
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {11082, 530, 132763752, 
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {24265, 4657, 29742067, 2278, 1739, 7701789,
 46390, 30444, 2255313, 19630, 1073, 92816416,
 0, 0, 0}};
 
 public:
    int Init(const std::string &filterFile=defaultFilterFile);
    void DeclarePlots(void) const;
    int Analyze(const vector<int> &, const string &, const string &);
    vector<int> Filter(vector<int> &, int , int , int , int );
    void FilterFill(const vector<int> &, vector<int> &, int, int, int, int);
    void CalculateTraceMaxAndAvgBaseline(const vector<int> &, int, int, int, int);
    void CalculatePhase( vector<int> &, int, int);
    void TracePlot(const vector<int> &);

    int GetTime(void) const {return t1;}
    int GetSecondTime(void) const {return t2;}
    double GetEnergy(void) const {return e1;}
    double GetAvgBaseline(void) const {return avgBaselinePre;}
    double GetStdDevBaseline(void) const {return stdDevBaselinePre;}
    double GetAvgBaselinePost(void) const {return avgBaselinePost;}
    int GetTraceMax(void) const {return traceMax;}
    int GetTraceMin(void) const {return traceMin;}
    int GetTraceMaxTime(void) const {return traceMaxTime;}
    int GetTraceMinTime(void) const {return traceMinTime;}
    int GetRegion(void) const {return region;}
    double GetSecondEnergy(void) const {return e2;}
    double GetPhase(void) const {return phase;}
    double GetSatLength(void) const {return satLength;}
    
    TraceAnalyzer();
    ~TraceAnalyzer();
};

#endif // __TRACEANALYZER_H_
