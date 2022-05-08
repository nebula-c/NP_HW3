#define KpPp 11
#define KpPn 12
#define KnPp 21
#define KnPn 22

#include "TH1F.h"
#include "TCanvas.h"
#include "TH2I.h"
#include "TTree.h"
#include "TFile.h"
#include "THStack.h"
#include "TLegend.h"
#include "TStyle.h"

#include "iostream"
#include "time.h"
using namespace std;

bool checksign(int mysigns);

Double_t pair_M;
bool IsSame;

void Make_Plot(TString filename, Int_t min, Int_t max)
{
    time_t start_time, end_time;
    start_time=time(NULL);
    TString histname;
    TCanvas *c1 = new TCanvas("c1");
    
    
    THStack *hs1 = new THStack();
    TH1F *h1 = new TH1F("h1","like-sign",25,1.7,2.2);
    TH1F *h2 = new TH1F("h2","unlike-sign",25,1.7,2.2);
    
    TString dir = "./Trees/";

    TFile *myFile = new TFile(dir+filename);
    TTree *myTree = (TTree*)myFile->Get("Pair");

    if(!myTree)
    {
        cout << "There is no TTree" << endl;
    }
    
    
    myTree->SetBranchAddress("M",&pair_M);
    myTree->SetBranchAddress("IsSame",&IsSame);

    cout << myTree->GetEntries() << endl;
    for(int i=0;i<myTree->GetEntries();i++)
    {
        myTree->GetEntry(i);
        if(IsSame==true)
            h1->Fill(pair_M);
        else
            h2->Fill(pair_M);
    }
    

    h1->SetMarkerStyle(8);
    h1->SetMarkerColor(kBlue);
    
    TLegend *l1 = new TLegend();
    l1->AddEntry(h1,"like-sign");
    l1->AddEntry(h2,"unlike-sign");
    
    hs1->Add(h1);
    hs1->Add(h2);
    hs1->Draw("ple nostack");
    l1->Draw();
    
    TString title = TString::Itoa(min,10) + " <  p_{T} < " + TString::Itoa(max,10) + " GeV/c";
    hs1->SetTitle(title);
    c1->SaveAs("./Plots/" + filename + ".png");

    end_time = time(NULL);
    cout << "========================" << endl;
    cout << "Runtime : " << (double)(end_time-start_time) << " sec" << endl;
    cout << "========================" << endl;
}   