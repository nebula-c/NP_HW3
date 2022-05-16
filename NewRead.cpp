// #include "KnPData.h"
#include "../../NewRootData.h"


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
#include "TLorentzVector.h"

#include <iostream>
#include <string>
#include "fstream"
#include "math.h"
#include "time.h"

using namespace std;



int interval_i[6] = {1, 2, 4, 6, 8, 12};
int interval_f[6] = {2, 4, 6, 8, 12, 24};
Double_t ptk[6] = {0.5, 0.7, 0.7, 0.7, 0.7, 0.6};
Double_t ptp[6] = {0.5, 0.7, 0.7, 0.7, 0.7, 0.6};
Double_t dcut[6] = {-0.00002, -0.0002, -0.00005, -0.00005, -0.00005, 10};

void All_Run(int iwrk);
void Read_One_File(TString rawname, Interval *interval, TString filename, int ifile);

void NewRead(int iwrk)
{   
    time_t start_time, end_time;
    start_time=time(NULL);

    All_Run(iwrk);

    end_time = time(NULL);
    ofstream mylogfile("/alice/home/suchoi/NP_HW3/mylog.txt",std::ios::app);
    TString mylog = "wrk_" + to_string(iwrk) + " is done, it takes " + to_string((double)(end_time-start_time)) + "sec\n";
    mylogfile << mylog;
    mylogfile.close();

    // end_time = time(NULL);
    // cout << "========================" << endl;
    // cout << "Runtime : " << (double)(end_time-start_time) << " sec" << endl;
    // cout << "========================" << endl;
}

void All_Run(int iwrk)
{
    cout << "run" << endl;
    TString filepath = "/alice/data/shlim/ALICE/Class2022/Data_pp13TeV_2017_v2/";
    TString filelist = "./file.lst";
    // TString filelist = "./list_allfile.lst";
    ifstream listfile(filelist);

    string line;    
    
    //------------------------------------------------------------
    // count line
    int iline=0;
    while(!listfile.eof())
    {
        listfile >> line;
        iline++;
    }
    
    listfile.clear();
    listfile.seekg(0,ios::beg);
    //------------------------------------------------------------


    //------------------------------------------------------------
    // file loop
    int ifile=0;
    while(!listfile.eof())
    {
        listfile >> line;
        if(listfile.eof())
            break;
        TString Tline = line;

        //------------------------------------------------------------
        // interval loop
        for(int i=0;i<6;i++)
        {
            for(int iscut=0;iscut<=1;iscut++)
            {
                Interval *myreg = new Interval(interval_i[i],interval_f[i],ptk[i],ptp[i],iscut,dcut[i]);           // information for cuts

                TString firstname;
                if(myreg->dcut==false)
                    firstname = "NoD_";
                else
                    firstname = "DCut_";

                    TString filename = firstname + to_string(interval_i[i]) + "_" + to_string(interval_f[i]) + "__" + to_string(iwrk)+ ".root";
                Read_One_File(line,myreg,filename,ifile);
            }
        }
        //------------------------------------------------------------
        ifile++;
        cout << "==================================" << endl;
        cout << "progress : " << ifile << "/" << iline-1 << endl;
        cout << "==================================" << endl;
    }
    //------------------------------------------------------------
    listfile.close();

}

void Read_One_File(TString rawname, Interval *interval, TString filename, int ifile)
{
    RootData *myrootdata = new RootData();

    //------------------------------------------------------
    // Read file
    TString filepath = "/alice/data/shlim/ALICE/Class2022/Data_pp13TeV_2017_v2/";
    

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
    
    int nentries = rootTree->GetEntries();
    
    // new ------------------------------------------------------
    // Pion & Kaon Tree + Result Tree
    TFile *F2 = new TFile("/alice/home/suchoi/NP_HW3/Histo/Pair_"+ filename,"update");

    Double_t pair_M;
    bool pair_sign;

    // TH1F *H_Likesign = new TH1F("likesign","likesign",25,1.7,2.2);
    // TH1F *H_Unlikesign = new TH1F("unlikesign","unlikesign",25,1.7,2.2);

    TH1F *H_Likesign = (TH1F*)F2->Get("likesign");
    if(!H_Likesign)
    {
        H_Likesign = new TH1F("likesign","likesign",25,1.7,2.2);
    }
    
    TH1F *H_Unlikesign = (TH1F*)F2->Get("unlikesign");
    if(!H_Unlikesign)
    {
        H_Unlikesign = new TH1F("unlikesign","unlikesign",25,1.7,2.2);
    }
    datafile->cd();


    //------------------------------------------------------
    // event loop
    for(int ien=0; ien<nentries;ien++)
    {   
        datafile->cd();
        rootTree->GetEntry(ien);
        
        // triggered
        if(myrootdata->IsMB==1)
        {   
            myrootdata->InspectTrack(ien,interval,H_Likesign,H_Unlikesign);
        }    
    }
    // event loop
    //------------------------------------------------------

    F2->cd();
    H_Likesign->Write("",TObject::kOverwrite);
    H_Unlikesign->Write("",TObject::kOverwrite);
    delete rootTree;
    F2->Close(); 
    cout << interval->min << "_" << interval->max <<" : F2 closed now!!!" << endl;
    delete F2;

    datafile->cd();
    datafile->Close();
    delete datafile;
    cout << interval->min << "_" << interval->max <<" : datafile closed now!!!" << endl;
}
