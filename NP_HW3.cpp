// #include "KnPData.h"
#include "RootData.h"

#include <string.h>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"
#include "TRandom3.h"

#include "iostream"
#include "fstream"
#include "math.h"
#include "time.h"

using namespace std;

const Double_t mass_kaon = 0.493677;
const Double_t mass_pion = 0.139570;

void Run(TString rawname, Interval *interval, TString filename);
void ProgressBar(int ien, int nentries);

void NP_HW3(TString rawname, int input_min, int input_max, Double_t input_Ptk, Double_t input_Ptp, bool input_dcut, Double_t input_DCA)
{   
    time_t start_time, end_time;
    start_time=time(NULL);

    Interval *myreg = new Interval(input_min,input_max,input_Ptk,input_Ptp,input_dcut,input_DCA);           // information for cuts

    
    TString firstname;
    if(myreg->dcut==false)
        firstname = "NoD_";
    else 
        firstname = "DCut_";

    TString filename = firstname + input_min + "_" + input_max + ".root";

    
    Run(rawname,myreg,filename);

    delete myreg;

    // end_time = time(NULL);
    // cout << "========================" << endl;
    // cout << "Runtime : " << (double)(end_time-start_time) << " sec" << endl;
    // cout << "========================" << endl;
}

void Run(TString rawname, Interval *interval, TString filename)
{
    RootData *myrootdata = new RootData();
    KnPData *myKnPData = new KnPData();

    //------------------------------------------------------
    // Read file
    TString filepath="/home/share/Class2022NP/Data_pp13TeV_2017/";
    

    TFile *datafile = new TFile(filepath + rawname,"read");
    if(!datafile)
        cout << "there is no datafile : " << rawname << endl;
    else
        cout << "~~~ OPEN : " << filename << " -> " << rawname << endl;
    datafile->cd();

    //------------------------------------------------------
    // Read tree
    TTree *rootTree = (TTree*)datafile->Get("tree");
    if(!rootTree)
    {
        cout << "there is no tree!!!" << endl;
        datafile->Close();
        delete datafile;
    }

    myrootdata->SetBranch(rootTree);
    
    TLorentzVector lvec_pair, lvec_1, lvec_2;
    int nentries = rootTree->GetEntries();
    
    // new ------------------------------------------------------
    // Pion & Kaon Tree + Result Tree
    TFile *F2 = new TFile("./Trees/Pair_"+ filename,"update");

    Double_t pair_M;
    bool pair_sign;

    TTree *PairTree = (TTree*)F2->Get("Pair");
    if(!PairTree)
    {
        PairTree = new TTree("Pair","Pair");
        PairTree->Branch("M",&pair_M);
        PairTree->Branch("IsSame",&pair_sign);
    }
    else
    {
        PairTree->GetBranch("M")->SetAddress(&pair_M);
        PairTree->GetBranch("IsSame")->SetAddress(&pair_sign);
    }
    datafile->cd();

    // int progress_check = -1;

    // time_t e_start, e_end;
    // e_start = time(NULL);
    //------------------------------------------------------
    // event loop
    for(int ien=0; ien<nentries;ien++)
    {   
        TTree *PionTree =  new TTree();
        TTree *KaonTree =  new TTree();
        myKnPData->MakeBranch(PionTree);
        myKnPData->MakeBranch(KaonTree);

        datafile->cd();
        rootTree->GetEntry(ien);
        //------------------------------------------------------
        // triggered
        if(myrootdata->IsMB==1)
        {   
            //------------------------------------------------------
            // track loop
            for(int itrk=0;itrk<myrootdata->nTrack;itrk++)
            { 
                //----------------------------------
                if(myrootdata->cond_kaon(itrk,interval))
                {
                    myrootdata->SaveTrack(myKnPData,KaonTree,itrk,mass_kaon);
                }
                if(myrootdata->cond_pion(itrk,interval))
                {
                    myrootdata->SaveTrack(myKnPData,PionTree,itrk,mass_pion);
                }
            } 
            //track loop
            //------------------------------------------------------
        }    
        //triggered
        //------------------------------------------------------
        
        //------------------------------------------------------
        //Make Comb tree
        F2->cd();
        myKnPData->Comb_Pair(KaonTree,PionTree,interval,PairTree);
        
        // //------------------------------------------------------
        // // progress bar
        // int progress = int(float(ien)/float(nentries)*100);
        // if( progress % 10 == 0 && progress_check != progress)
        // {
        //     cout << "progress in a file : " << ien << " / " << nentries << " -> " << int(float(ien)/float(nentries)*100) << "%" << endl;
        //     progress_check = progress;
        // }
        delete PionTree;
        delete KaonTree;
    }
    // event loop
    //------------------------------------------------------
    F2->cd();
    PairTree->Write("",TObject::kOverwrite);
    delete rootTree;
    F2->Close(); 
    cout << interval->min << "_" << interval->max <<" : F2 closed now!!!" << endl;
    delete F2;

    datafile->cd();
    datafile->Close();
    delete datafile;
    cout << interval->min << "_" << interval->max <<" : datafile closed now!!!" << endl;

    delete myKnPData;
    

    //  e_end = time(NULL);
     // cout << "time(1 file) : " << (double)(e_end-e_start) << " sec" <<endl;
     // cout << "------ ------ ----- ----- ----- -----" << endl;
}
