#ifndef ROOTDATA_H
#define ROOTDATA_H

#include "Interval.h"
#include "NewKnPData.h"
#include "TLorentzVector.h"
#include "TTree.h"


#define NMAX_TRK 500

const Double_t mass_kaon = 0.493677;
const Double_t mass_pion = 0.139570;

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
        bool cond_pion(int itrk, Interval *interval)                                // conditions of Pion : cuts for Eta, PID, Tp
        {
            bool con_eta = TrackEta[itrk] <0.8 && TrackEta[itrk] > -0.8;
            bool Imptp = TrackPt[itrk]>interval->Ptp;

            return con_eta && Imptp ;
        }

        bool cond_kaon(int itrk, Interval *interval)                                // conditions of Kaon : cuts for Eta, PID, Tp
        {
            bool con_eta = TrackEta[itrk] <0.8 && TrackEta[itrk] > -0.8;
            bool Imptk = TrackPt[itrk]>interval->Ptk;

            return con_eta && Imptk ;
        }
    // public:
        bool IsMB;
        RootData();
        void SetBranch(TTree *T);                                                   //
        void ExportValue(int itrk, KnPData *mydata);                                //
        void SaveTrack(KnPData *mydata, int itrk);
        void SetLvec(TLorentzVector *v1, int trk, Double_t mass);
        void InspectTrack(int ien,Interval *interval, TH1F *likesign, TH1F *unlikesign);
        bool Check_lvec(TLorentzVector* v1, Interval *interval);
        
        bool CheckPID(int itrk, int PID)
        {
            return TrackBayesianPID[itrk] == PID;
        }
        bool ImPion(int itrk)
        {
            return TrackBayesianPID[itrk] == 0;
        }
        bool ImKaon(int itrk)
        {
            return TrackBayesianPID[itrk] == 1;
        }

        bool Check_Cond(int itrk, Interval *interval, int PID)
        {
            if(PID==1)
            {
                return cond_kaon(itrk,interval);
            }
            if(PID==0)
            {
                return cond_pion(itrk,interval);
            }
            return false;
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

void RootData::SaveTrack(KnPData *mydata, int itrk)   // save data in other tree
{
    mydata->t_Pt = TrackPt[itrk];
    mydata->t_Eta = TrackEta[itrk];
    mydata->t_Phi = TrackPhi[itrk];
    if(TrackBayesianPID[itrk]==0)
        mydata->t_M = mass_pion;
    if(TrackBayesianPID[itrk]==1)
        mydata->t_M = mass_kaon;
    mydata->t_Chr = TrackCharge[itrk];
    mydata->t_DCA = TrackDCAXY[itrk];
}

void RootData::SetLvec(TLorentzVector *v1, int trk, Double_t mass)
{
    v1->SetPtEtaPhiM(TrackPt[trk],TrackEta[trk],TrackPhi[trk],mass);
}

void RootData::InspectTrack(int ien,Interval *interval, TH1F *likesign, TH1F *unlikesign)
{
    int firstPID = -1;
    int secondPID = -1;
    
    for(int itrk=0;itrk<nTrack;itrk++)
    {
        if(ImKaon(itrk))
        {
            if(Check_Cond(itrk,interval,TrackBayesianPID[itrk]))
            {
                for(int jtrk=0; jtrk<nTrack; jtrk++)
                {
                    if(ImPion(jtrk))
                    {
                        if(Check_Cond(jtrk,interval,TrackBayesianPID[jtrk]))
                        {
                            if((!(interval->dcut)) || (TrackDCAXY[itrk]*TrackDCAXY[jtrk] < interval->DCA))
                            {
                                TLorentzVector *lvec_pair = new TLorentzVector();
                                TLorentzVector *lvec_1 = new TLorentzVector();
                                TLorentzVector *lvec_2 = new TLorentzVector();

                                SetLvec(lvec_1,itrk,mass_kaon);
                                SetLvec(lvec_2,jtrk,mass_pion);
                                (*lvec_pair) = (*lvec_1)+(*lvec_2);

                                if(Check_lvec(lvec_pair,interval))
                                {
                                    if(TrackCharge[itrk]==TrackCharge[jtrk])
                                    {
                                        likesign->Fill(lvec_pair->M());
                                    }
                                    else
                                        unlikesign->Fill(lvec_pair->M());
                                }
                            }
                        }
                    }
                }
            }
        }
        
        
        
        
        
        
        
        
        
        
        
        // if(ImKaon(itrk) || ImPion(itrk))
        // {
        //     firstPID = TrackBayesianPID[itrk];
        //     if(Check_Cond(itrk,interval,firstPID))
        //     {
        //         KnPData *trk1 = new KnPData();
        //         SaveTrack(trk1,itrk);

        //         secondPID = !(firstPID);
                
        //         for(int jtrk=itrk; jtrk<nTrack; jtrk++)
        //         {
        //             if(CheckPID(jtrk,secondPID))
        //             {
        //                 if(Check_Cond(jtrk,interval,secondPID))
        //                 {
        //                     KnPData *trk2 = new KnPData();
        //                     SaveTrack(trk2,jtrk);
                            
        //                     if((!(interval->dcut)) || (TrackDCAXY[itrk]*TrackDCAXY[jtrk] < interval->DCA))
        //                     {
        //                         TLorentzVector *lvec_pair = new TLorentzVector();
        //                         TLorentzVector *lvec_1 = new TLorentzVector();
        //                         TLorentzVector *lvec_2 = new TLorentzVector();

        //                         SetLvec(lvec_1,itrk);
        //                         SetLvec(lvec_2,jtrk);
        //                         (*lvec_pair) = (*lvec_1)+(*lvec_2);

        //                         if(Check_lvec(lvec_pair,interval))
        //                         {
        //                             if(TrackCharge[itrk]==TrackCharge[jtrk])
        //                             {
        //                                 likesign->Fill(lvec_pair->M());
        //                             }
        //                             else
        //                                 unlikesign->Fill(lvec_pair->M());
        //                         }
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }

        
    }
}

bool RootData::Check_lvec(TLorentzVector* v1, Interval *interval)
{
    Double_t R_M;
    if(v1->Pt() < interval->max && v1->Pt() > interval->min)
    {
        if(v1->M()>1.7 && v1->M()<2.2)
        {
            if(v1->Rapidity() < 0.8 && v1->Rapidity() > -0.8)
            {
                R_M = v1->M();
                return true;
            }
        }
    }

    return false;            
}

#endif