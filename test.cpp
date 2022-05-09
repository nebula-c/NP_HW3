#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "THStack.h"
#include <iostream>
#include <fstream>
#include "TLegend.h"
using namespace std;

void Watch(TFile *f)
{
  TH1D *myhist = (TH1D*)f->Get("h1");
  if(! myhist) 
  {
    cout << "no histo" << endl;
    return ;
  }
  // myhist->GetXaxis()->SetLimits(0,10);
  myhist->Draw();
}

void Fill(TH1D *myhist, int i)
{
  
  myhist->Fill(i);
  myhist->Write();
}

void test()
{

  
  // TFile *F1 = new TFile("testfile.root","update");
  // TH1D *h1 = new TH1D("h1","h1",10,0,10);
  // TH1D *h2 = new TH1D("h2","h2",10,0,10);
  // TH1D *h3 = new TH1D("h3","h3",10,0,10);

  // h1->Fill(1);
  // h1->Fill(1);
  // h1->Fill(1);
  // h1->Fill(3);
  // h1->Fill(2);
  // h1->Fill(2);


  // h2->Fill(5);
  // h2->Fill(5);
  // h2->Fill(6);
  // h2->Fill(4);
  // h2->Fill(5);
  // h2->Fill(5);



  // h3->Fill(8);
  // h3->Fill(9);
  // h3->Fill(9);
  // h3->Fill(8);
  // h3->Fill(7);
  // h3->Fill(9);
  // // h1->Draw();
  // h1->Write();
  // h2->Write();

  // TFile *F2 = new TFile("testfile2.root","update");
  // F2->cd();
  // h3->Write();
  
  // F1->ReOpen("read");
  // Watch(F1);


  TFile *F1 = new TFile("merge.root","read");
  TH1D *h1 = (TH1D*)F1->Get("h1");
  TH1D *h2 = (TH1D*)F1->Get("h2");
  TH1D *h3 = (TH1D*)F1->Get("h3");

  h1->SetMarkerSize(1);
  h2->SetMarkerSize(1);
  h3->SetMarkerSize(1);

  h1->SetMarkerStyle(8);
  h2->SetMarkerStyle(8);
  h3->SetMarkerStyle(8);

  THStack *total = new THStack("total","total");
  total->Add(h1);
  total->Add(h2);
  total->Add(h3);

  total->Draw("p nostack");
  TLegend *l1 = new TLegend();
  l1->AddEntry(total,"like-sign");
  l1->Draw();
}


