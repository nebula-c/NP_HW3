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
        Int_t t_File;
        Int_t t_Chr;
        Double_t t_DCA;


        KnPData();
        void MakeBranch(TTree *KnPTree);
        void ConnectBranch(TTree *myTree);
        void Comb_Pair(TTree *TKaon, TTree *TPion, Interval *interval, TTree *TRes);
};


void KnPData::Comb_Pair(TTree *TKaon, TTree *TPion, Interval *interval, TTree *TRes)            // make pair
{
    if(!TKaon || !TPion)
    {
        cout << "there is no tree in Comb_like" << endl;
        return ;
    }
    TLorentzVector lvec_pair, lvec_K, lvec_P;

    Double_t  K_Pt, K_Eta, K_Phi, K_M, K_DCA;
    Double_t  P_Pt, P_Eta, P_Phi, P_M, P_DCA;

    Int_t K_Chr, P_Chr;

    TKaon->SetBranchAddress("Pt",   &K_Pt);
    TKaon->SetBranchAddress("Eta",  &K_Eta);
    TKaon->SetBranchAddress("Phi",  &K_Phi);
    TKaon->SetBranchAddress("M",    &K_M);
    TKaon->SetBranchAddress("Chr",  &K_Chr);
    TKaon->SetBranchAddress("DCA",  &K_DCA);

    TPion->SetBranchAddress("Pt",   &P_Pt);
    TPion->SetBranchAddress("Eta",  &P_Eta);
    TPion->SetBranchAddress("Phi",  &P_Phi);
    TPion->SetBranchAddress("M",    &P_M);
    TPion->SetBranchAddress("Chr",  &P_Chr);
    TPion->SetBranchAddress("DCA",  &P_DCA);


    Double_t R_M;
    bool same_sign;
    TRes->SetBranchAddress("M", &R_M);
    TRes->SetBranchAddress("IsSame",  &same_sign);

    for(int i_k=0;i_k<TKaon->GetEntries();i_k++)
    {
        TKaon->GetEntry(i_k);
        lvec_K.SetPtEtaPhiM(K_Pt,K_Eta,K_Phi,K_M);
        for(int i_p=0; i_p<TPion->GetEntries();i_p++)
        {
            TPion->GetEntry(i_p);
            lvec_P.SetPtEtaPhiM(P_Pt,P_Eta,P_Phi,P_M);
            
            lvec_pair=lvec_K+lvec_P;
            if(K_Chr == P_Chr)
            {
                same_sign=true;
            }
            if(K_Chr != P_Chr)
            {
                same_sign=false;
            }
            
            if(lvec_pair.Pt() < interval->max && lvec_pair.Pt() > interval->min)
            {
                if(lvec_pair.M()>1.7 && lvec_pair.M()<2.2)
                {
                    if(lvec_pair.Rapidity() < 0.8 && lvec_pair.Rapidity() > -0.8)
                    {
                        if( (!(interval->dcut)) || (K_DCA*P_DCA < interval->DCA))
                        {
                            R_M = lvec_pair.M();
                            TRes->Fill();
                        }
                    }
                }
            }            
        }
    }
}



KnPData::KnPData() { }

void KnPData::MakeBranch(TTree *KnPTree)                                            // make branck for TTree
{
    KnPTree->Branch("Pt",&t_Pt);
    KnPTree->Branch("Eta",&t_Eta);
    KnPTree->Branch("Phi",&t_Phi);
    KnPTree->Branch("M",&t_M);
    KnPTree->Branch("Chr",&t_Chr);
    KnPTree->Branch("DCA",&t_DCA);
}

#endif