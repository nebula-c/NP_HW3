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

int interval_i[6] = {1, 2, 4, 6, 8, 12};
int interval_f[6] = {2, 4, 6, 8, 12, 24};
Double_t ptk[6] = {0.5, 0.7, 0.7, 0.7, 0.7, 0.6};
Double_t ptp[6] = {0.5, 0.7, 0.7, 0.7, 0.7, 0.6};
Double_t dcut[6] = {-0.00002, -0.0002, -0.00005, -0.00005, -0.00005, 10};

void All_Run();
void Run(TString rawname, Interval *interval, TString filename);

void Read()
{   
    // time_t start_time, end_time;
    // start_time=time(NULL);

    
    All_Run();

    // end_time = time(NULL);
    // cout << "========================" << endl;
    // cout << "Runtime : " << (double)(end_time-start_time) << " sec" << endl;
    // cout << "========================" << endl;
}

void All_Run()
{
    TString filepath = "/home/share/Class2022NP/Data_pp13TeV_2017/";
    TString filelist = "./file.lst";
    ifstream listfile(filelist);

    string line;    
    //------------------------------------------------------------
    // file loop
    while(!listfile.eof())
    {
        listfile >> line;
        TString Tline = line;

        //------------------------------------------------------------
        // interval loop
        for(int i=0;i<=6;i++)
        {
            for(int iscut=0;iscut<=1;iscut++)
            {
                Interval *myreg = new Interval(interval_i[i],interval_f[i],ptk[i],ptp[i],iscut,dcut[i]);           // information for cuts

                TString firstname;
                if(myreg->dcut==false)
                    firstname = "NoD_";
                else
                    firstname = "DCut_";

                    TString filename = firstname + interval_i[i] + "_" + interval_f[i] + ".root";

                Run(line,myreg,filename);
            }
        }
        //------------------------------------------------------------
    }
    //------------------------------------------------------------
    listfile.close();

}

void Read_One_File(TString rawname, Interval *interval, TString filename)
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

    TH1F *H_Likesign = (TH1F*)F2->Get("likesign");
    if(!H_Likesign)
    {
        H_Likesign = new TH1F("likesign","likesign",25,1.7,2.2);
    }
    
    TH1F *H_Unikesign = (TH1F*)F2->Get("unlikesign");
    if(!H_Unikesign)
    {
        H_Unikesign = new TH1F("unlikesign","unlikesign",25,1.7,2.2);
    }
    datafile->cd();


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
        myKnPData->Comb_Pair(KaonTree,PionTree,interval,H_Likesign,H_Unikesign);
        
        delete PionTree;
        delete KaonTree;
    }
    // event loop
    //------------------------------------------------------
    F2->cd();
    H_Likesign->Write("",TObject::kOverwrite);
    H_Unikesign->Write("",TObject::kOverwrite);
    delete rootTree;
    F2->Close(); 
    cout << interval->min << "_" << interval->max <<" : F2 closed now!!!" << endl;
    delete F2;

    datafile->cd();
    datafile->Close();
    delete datafile;
    cout << interval->min << "_" << interval->max <<" : datafile closed now!!!" << endl;

    delete myKnPData;
}
