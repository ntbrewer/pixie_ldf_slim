/**   \file TraceAnalyzer.h
 *    \brief Header file for the TraceAnalyzer class
 *
 *    SNL - 7-2-07
 */

#ifndef __TRACEANALYZER_H_
#define __TRACEANALYZER_H_

#include <string>
#include <vector>

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
