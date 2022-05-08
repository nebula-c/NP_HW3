#ifndef INTERVAL_H
#define INTERVAL_H

#include "TString.h"

typedef struct Interval
{
    int min, max;
    Double_t Ptk, Ptp;
    bool dcut;
    Double_t DCA;
    TString name;

    TString firstname;
    TString myfilename;

    Interval(int _min, int _max, Double_t _Ptk, Double_t _Ptp, bool _dcut, Double_t _DCA)
    { 
        min = _min; max = _max; Ptk = _Ptk; Ptp = _Ptp; dcut = _dcut; DCA = _DCA;
        if( dcut == 0 )
        {
            name = TString::Itoa(min,10) + "_" + TString::Itoa(max,10);
        }
        if( dcut == 1 )
        {
            name = TString::Itoa(min,10) + "_" + TString::Itoa(max,10) + "_d";
        }



        if(dcut==false)
            firstname = "NoD_";
        else 
            firstname = "DCut_";
        myfilename = "Pair_" + firstname + _min + "_" + _max + ".root";
    }


} Interval;

#endif