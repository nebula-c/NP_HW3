#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <fstream>

using namespace std;

void test()
{
  int val;
  
  TFile *F1 = new TFile("testfile.root","update");
  TFile *F2 = new TFile("testfile.root","update");

  F1->Close();
  TTree *T1 = (TTree*)F2->Get("Tree");
  F2->Close();  
  
}
