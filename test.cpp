#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "THStack.h"
#include "TLegend.h"

#include <fstream>
#include <iostream>

using namespace std;

void test()
{

  TString filepath = "/home/share/Class2022NP/Data_pp13TeV_2017/";
  TString filelist = "./file.lst";
  ifstream listfile(filelist);


  string line;
  while(!listfile.eof())
  {
    listfile >> line;
    TString Tline = line;
    
    cout << line.substr(21,13) << endl;
    
  }
  listfile.close();



  // TFile *datafile = new TFile(filepath + rawname,"read");
  // if(!datafile)
  //     cout << "there is no datafile : " << rawname << endl;
  // else
  //     cout << "~~~ OPEN : " << filename << " -> " << rawname << endl;
  // datafile->cd();
}


