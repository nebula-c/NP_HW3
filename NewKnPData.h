#ifndef KNPDATA_H
#define KNPDATA_H

#include "Interval.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"


#include "iostream"

using namespace std;;

#define Kaon_p 10
#define Kaon_n 20
#define Pion_p 1
#define Pion_n 2

class KnPData
{
    private:
        

    public:
        Double_t t_Pt, t_Eta, t_Phi, t_M;
        Int_t t_PID;
        Int_t t_Chr;
        Double_t t_DCA;


        KnPData();
};


KnPData::KnPData() { }

#endif