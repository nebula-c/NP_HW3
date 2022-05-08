#ifndef ROOTDATA_H
#define ROOTDATA_H

#include "Interval.h"
#include "KnPData.h"

#include "TTree.h"


#define NMAX_TRK 500

class RootData  // class for data in raw file
{
    public:
    // private:
        bool IsHMV0;
        float VertexZ;
        int nTrack;
        float Centrality;
        int n_ev=0;
        
        int event_num;

        float TrackPt[NMAX_TRK];
        float TrackEta[NMAX_TRK];
        float TrackPhi[NMAX_TRK];
        float TrackDCAXY[NMAX_TRK];
        float TrackM[NMAX_TRK];
        int TrackCharge[NMAX_TRK];
        int TrackBayesianPID[NMAX_TRK];

        const Double_t mass_kaon = 0.493677;
        const Double_t mass_pion = 0.139570;
    
    // public:
        RootData();
        void SetBranch(TTree *T);                                                   //
        void ExportValue(int itrk, KnPData *mydata);                                //
        void SaveTrack(KnPData *mydata, TTree *myTree, int itrk, Double_t mass);    //
        bool IsMB;

        bool cond_pion(int itrk, Interval *interval)                                // conditions of Pion : cuts for Eta, PID, Tp
        {
            bool con_eta = TrackEta[itrk] <0.8 && TrackEta[itrk] > -0.8;
            bool ImPion = TrackBayesianPID[itrk] == 0;
            bool Imptp = TrackPt[itrk]>interval->Ptp;

            return con_eta && ImPion && Imptp ;
        }

        bool cond_kaon(int itrk, Interval *interval)                                // conditions of Kaon : cuts for Eta, PID, Tp
        {
            bool con_eta = TrackEta[itrk] <0.8 && TrackEta[itrk] > -0.8;
            bool ImKaon = TrackBayesianPID[itrk] == 1;
            bool Imptk = TrackPt[itrk]>interval->Ptk;

            return con_eta && ImKaon && Imptk ;
        }
};


RootData::RootData(){ }

void RootData::SetBranch(TTree *rootTree)                                           // SetBranAddress for a Tree in raw file
{
    rootTree->SetBranchAddress("IsMB",&IsMB);
    rootTree->SetBranchAddress("IsHMV0",&IsHMV0);
    rootTree->SetBranchAddress("VertexZ",&VertexZ);
    rootTree->SetBranchAddress("nTrack",&nTrack);
    rootTree->SetBranchAddress("TrackPt",TrackPt);
    rootTree->SetBranchAddress("TrackEta",TrackEta);
    rootTree->SetBranchAddress("TrackPhi",TrackPhi);
    rootTree->SetBranchAddress("TrackCharge",TrackCharge);
    rootTree->SetBranchAddress("TrackDCAXY",TrackDCAXY);
    rootTree->SetBranchAddress("Centrality",&Centrality);
    rootTree->SetBranchAddress("TrackBayesianPID",TrackBayesianPID);
}

void RootData::SaveTrack(KnPData *mydata, TTree *myTree, int itrk, Double_t mass)   // save data in other tree
{
    mydata->t_Pt = TrackPt[itrk];
    mydata->t_Eta = TrackEta[itrk];
    mydata->t_Phi = TrackPhi[itrk];
    mydata->t_M = mass;
    mydata->t_Chr = TrackCharge[itrk];
    mydata->t_DCA = TrackDCAXY[itrk];
    myTree->Fill();         // mydata(KnPData) is a set of branchse of myTree
}

#endif