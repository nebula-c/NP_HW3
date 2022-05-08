// #include "RootData.h"

// RootData::RootData(){ }

// RootData::RootData(int track_num, int _TrackCharge, int _TrackBayesianPID, float _TrackPt, float _TrackEta, float _TrackPhi, 
// float _TrackDCAXY)
// {
//     TrackCharge[track_num] = _TrackCharge;
//     TrackBayesianPID[track_num] = _TrackBayesianPID;
//     TrackPt[track_num] = _TrackPt;
//     TrackEta[track_num] = _TrackEta;
//     TrackPhi[track_num] = _TrackPhi;
//     TrackDCAXY[track_num] = _TrackDCAXY;
// }

// void RootData::SetBranch(TTree *rootTree)
// {
//     rootTree->SetBranchAddress("IsMB",&IsMB);
//     rootTree->SetBranchAddress("IsHMV0",&IsHMV0);
//     rootTree->SetBranchAddress("VertexZ",&VertexZ);
//     rootTree->SetBranchAddress("nTrack",&nTrack);
//     rootTree->SetBranchAddress("TrackPt",TrackPt);
//     rootTree->SetBranchAddress("TrackEta",TrackEta);
//     rootTree->SetBranchAddress("TrackPhi",TrackPhi);
//     rootTree->SetBranchAddress("TrackCharge",TrackCharge);
//     rootTree->SetBranchAddress("TrackDCAXY",TrackDCAXY);
//     rootTree->SetBranchAddress("Centrality",&Centrality);
//     rootTree->SetBranchAddress("TrackBayesianPID",TrackBayesianPID);
// }

// void RootData::ExportValue(int itrk, KnPData *mydata)
// {
//     mydata->t_Pt = TrackPt[itrk];
//     mydata->t_Eta = TrackEta[itrk];
//     mydata->t_Phi = TrackPhi[itrk];
//     mydata->t_DCA = TrackDCAXY[itrk];
    
//     if(TrackBayesianPID[itrk] == 1)
//     {
//         mydata->t_M = mass_kaon;
//         if(TrackCharge[itrk] == 1)
//             mydata->t_PID = Kaon_p;
//         if(TrackCharge[itrk] == -1)
//             mydata->t_PID = Kaon_n;
//     }

//     else if(TrackBayesianPID[itrk] == 0)
//     {
//         mydata->t_M = mass_kaon;
//         if(TrackCharge[itrk] == 1)
//             mydata->t_PID = Pion_p;
//         if(TrackCharge[itrk] == -1)
//             mydata->t_PID = Pion_n;
//     }
// }

// void RootData::SaveTrack(KnPData *mydata, TTree *myTree, int itrk, Double_t mass)
// {
//     mydata->t_Pt = TrackPt[itrk];
//     mydata->t_Eta = TrackEta[itrk];
//     mydata->t_Phi = TrackPhi[itrk];
//     mydata->t_M = mass;
//     mydata->t_Chr = TrackCharge[itrk];
//     mydata->t_DCA = TrackDCAXY[itrk];
//     cout << mydata->t_Pt <<
//     myTree->Fill();
// }