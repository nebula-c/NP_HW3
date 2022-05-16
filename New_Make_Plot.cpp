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
#include "TF1.h"
#include "TFitResultPtr.h"

#include "iostream"
#include "time.h"
using namespace std;

void LoadPlots(TString filename, TH1F **hist1, TH1F **hist2);
void SavePlot(TH1F *hist1, TH1F *hist2, TString filename, Int_t min, Int_t max);
TH1F *SubHisto(TH1F *hist1, TH1F *hist2, TString filename, Int_t min, Int_t max);
void FitHisto(TH1F *subhist);

Double_t pair_M;
bool IsSame;

void New_Make_Plot(TString filename, Int_t min, Int_t max)
{
    time_t start_time, end_time;
    start_time=time(NULL);
    TString histname;
    
    TCanvas *c1 = new TCanvas();

    TH1F *h1 = new TH1F("h1","like-sign",50,1.7,2.2);
    TH1F *h2 = new TH1F("h2","unlike-sign",50,1.7,2.2);

    LoadPlots(filename,&h1,&h2);
    h1->Rebin(0.01);
    h2->Rebin(0.01);
    // SavePlot(h1,h2,filename,min,max);
    TH1F *subhist = SubHisto(h1,h2,filename,min,max);
    subhist->Rebin(0.01);
    FitHisto(subhist);
    



    end_time = time(NULL);
    cout << "========================" << endl;
    cout << "Runtime : " << (double)(end_time-start_time) << " sec" << endl;
    cout << "========================" << endl;
}   

void LoadPlots(TString filename, TH1F **hist1, TH1F **hist2)
{
    // TString dir = "./result_all/";
    TString dir = "./";
    cout << dir+filename << endl;
    TFile *myFile = new TFile(dir+filename);

    *hist1 = (TH1F*)myFile->Get("likesign");
    *hist2 = (TH1F*)myFile->Get("unlikesign");
    
}

void SavePlot(TH1F *hist1, TH1F *hist2, TString filename, Int_t min, Int_t max)
{
    TCanvas *c1 = new TCanvas("c1");
    THStack *hs1 = new THStack();

    hist1->SetMarkerStyle(8);
    hist1->SetMarkerColor(kBlue);
    
    TLegend *l1 = new TLegend(0.2,0.2,0.4,0.4);
    l1->AddEntry(hist1,"like-sign");
    l1->AddEntry(hist2,"unlike-sign");

    hs1->Add(hist1);
    hs1->Add(hist2);
    hs1->Draw("ple nostack");
    l1->Draw();
    
    TString title = TString::Itoa(min,10) + " <  p_{T} < " + TString::Itoa(max,10) + " GeV/c";
    hs1->SetTitle(title);
    c1->SaveAs("./Plots/" + filename + ".png");
}

TH1F *SubHisto(TH1F *hist1, TH1F *hist2, TString filename, Int_t min, Int_t max)
{
    TCanvas *c1 = new TCanvas("c1");
    TH1F *subhist = new TH1F();
    *subhist = *hist2 - *hist1;
    // subhist->Draw();
    // c1->SaveAs("./Plots/Sub_" + filename + ".png");
    return subhist;
}

void FitHisto(TH1F *subhist)
{
    TF1 *f1 = new TF1("f1","gaus(0) + pol2(3)",1.7,2.2);
    f1->SetParameter(0,subhist->GetMaximum());
    f1->SetParameter(1,1.87);
    f1->SetParameter(2,0.01);

    subhist->SetMarkerStyle(8);
    subhist->SetMarkerColor(kBlue);
    subhist->Fit(f1,"R0");
    subhist->Draw("ple");

    
    
    f1->Draw("same");
}