#include "KnPData.h"


// void KnPData::CombTree(TTree *TKnP, TFile *F2, TTree *resTree,Interval *interval)
// {
//     int startpoint=0;
//     TLorentzVector lvec_pair, lvec_K, lvec_P;
//     Double_t d_k, d_p;

//     TKnP->SetBranchAddress("Pt",&t_Pt);
//     TKnP->SetBranchAddress("Eta",&t_Eta);
//     TKnP->SetBranchAddress("Phi",&t_Phi);
//     TKnP->SetBranchAddress("M",&t_M);
//     TKnP->SetBranchAddress("PID",&t_PID);
//     TKnP->SetBranchAddress("DCA",&t_DCA);

//     // TKnP->GetEntry(1);
//     // TKnP->Show();
    
//     for(Int_t sign_K=Kaon_p;sign_K<=Kaon_n;sign_K=sign_K+10)
//     {
//         for(Int_t sign_P=Pion_p;sign_P<=Pion_n;sign_P=sign_P+1)
//         {
//             for(int ien=startpoint;ien<TKnP->GetEntries();ien++)
//             {            
//                 TKnP->GetEntry(ien);
                
//                 if(t_PID==sign_K)
//                 {
//                     lvec_K.SetPtEtaPhiM(t_Pt,t_Eta,t_Phi,t_M);
//                     d_k = t_DCA;
//                     for(int jen=startpoint;jen<TKnP->GetEntries();jen++)
//                     {
//                         TKnP->GetEntry(jen);
//                         if(t_PID==sign_P)
//                         {
//                             lvec_P.SetPtEtaPhiM(t_Pt,t_Eta,t_Phi,t_M);
//                             d_p = t_DCA;
//                             lvec_pair=lvec_K+lvec_P;
//                             if(lvec_pair.M()>1.7 && lvec_pair.M()<2.2)
//                             {
//                                 if(lvec_pair.Rapidity() < 0.8 && lvec_pair.Rapidity() > -0.8)
//                                 {                           
//                                     if(d_k*d_p < interval->DCA)
//                                     {
//                                         F2->cd();
//                                         t_Pt = lvec_pair.Pt();
//                                         t_Eta = lvec_pair.Eta();
//                                         t_Phi = lvec_pair.Phi();
//                                         t_M = lvec_pair.M();
//                                         t_PID = sign_K + sign_P;
//                                         resTree->Fill();
//                                     }                    
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// void KnPData::Comb_like(TTree *TKaon, TTree *TPion, Interval *interval, TTree *TRes)
// {
//     if(!TKaon || !TPion)
//     {
//         cout << "there is no tree in Comb_like" << endl;
//         return ;
//     }
//     TLorentzVector lvec_pair, lvec_K, lvec_P;

//     Double_t  K_Pt, K_Eta, K_Phi, K_M, K_DCA;
//     Double_t  P_Pt, P_Eta, P_Phi, P_M, P_DCA;

//     Int_t K_Chr, P_Chr;

//     TKaon->SetBranchAddress("Pt",   &K_Pt);
//     TKaon->SetBranchAddress("Eta",  &K_Eta);
//     TKaon->SetBranchAddress("Phi",  &K_Phi);
//     TKaon->SetBranchAddress("M",    &K_M);
//     TKaon->SetBranchAddress("Chr",  &K_Chr);
//     TKaon->SetBranchAddress("DCA",  &K_DCA);

//     TPion->SetBranchAddress("Pt",   &P_Pt);
//     TPion->SetBranchAddress("Eta",  &P_Eta);
//     TPion->SetBranchAddress("Phi",  &P_Phi);
//     TPion->SetBranchAddress("M",    &P_M);
//     TPion->SetBranchAddress("Chr",  &P_Chr);
//     TPion->SetBranchAddress("DCA",  &P_DCA);


//     Double_t R_M;
//     TRes->SetBranchAddress("M",  &R_M);

//     for(int i_k=0;i_k<TKaon->GetEntries();i_k++)
//     {
//         TKaon->GetEntry(i_k);
//         lvec_K.SetPtEtaPhiM(K_Pt,K_Eta,K_Phi,K_M);
//         cout << "pt : " << K_Pt << ", P_Eta : " << K_Eta << ", P_phi : " << K_Phi << ", P_M : " << K_M << endl;
//         for(int i_p=0; i_p<TPion->GetEntries();i_p++)
//         {
//             TPion->GetEntry(i_p);
//             lvec_P.SetPtEtaPhiM(P_Pt,P_Eta,P_Phi,P_M);
            
//             lvec_pair=lvec_K+lvec_P;
//             // cout << "K : " << K_Chr << ", P : " << P_Chr << endl;
//             // cout << "-----------------" << endl;
//             if(K_Chr == P_Chr)
//             {
//                 // cout << "section 1" << endl;
//                 if(lvec_pair.Pt() < interval->max && lvec_pair.Pt() > interval->min)
//                 {
//                     // cout << "section 2" << endl;
//                     cout << "lvec pair m : " << lvec_pair.M() << endl;
//                     if(lvec_pair.M()>1.7 && lvec_pair.M()<2.2)
//                     {
//                         cout << "section 3" << endl;
//                         if(lvec_pair.Rapidity() < 0.8 && lvec_pair.Rapidity() > -0.8)
//                         {
//                             cout << "section 4" << endl;
//                             if( !(interval->dcut) || K_DCA*P_DCA < interval->DCA)
//                             {
//                                 R_M = lvec_pair.M();
//                                 TRes->GetCurrentFile()->cd();
//                                 TRes->Fill();
//                                 cout << "It works!!!!" << endl;
//                             }
//                         }
//                     }
//                 }
//             }            
//         }
//     }
// }

// void KnPData::Comb_unlike(TTree *TKaon, TTree *TPion, Interval *interval, TTree *TRes)
// {
//     TLorentzVector lvec_pair, lvec_K, lvec_P;

//     Double_t  K_Pt, K_Eta, K_Phi, K_M, K_Chr, K_DCA;
//     Double_t  P_Pt, P_Eta, P_Phi, P_M, P_Chr, P_DCA;

//     TKaon->SetBranchAddress("Pt",   &K_Pt);
//     TKaon->SetBranchAddress("Eta",  &K_Eta);
//     TKaon->SetBranchAddress("Phi",  &K_Phi);
//     TKaon->SetBranchAddress("M",    &K_M);
//     TKaon->SetBranchAddress("PID",  &K_Chr);
//     TKaon->SetBranchAddress("DCA",  &K_DCA);

//     TPion->SetBranchAddress("Pt",   &P_Pt);
//     TPion->SetBranchAddress("Eta",  &P_Eta);
//     TPion->SetBranchAddress("Phi",  &P_Phi);
//     TPion->SetBranchAddress("M",    &P_M);
//     TPion->SetBranchAddress("PID",  &P_Chr);
//     TPion->SetBranchAddress("DCA",  &P_DCA);


//     Double_t R_M;
//     TRes->SetBranchAddress("M",  &R_M);

//     for(int i_k=0;i_k<TKaon->GetEntries();i_k++)
//     {
//         TKaon->GetEntry(i_k);
//         lvec_K.SetPtEtaPhiM(K_Pt,K_Eta,K_Phi,K_M);

//         for(int i_p=0; i_p<TPion->GetEntries();i_p++)
//         {
//             TPion->GetEntry(i_p);
//             lvec_P.SetPtEtaPhiM(P_Pt,P_Eta,P_Phi,P_M);
//             lvec_pair=lvec_K+lvec_P;
//             if(K_Chr != P_Chr)
//             {
//                 if(lvec_pair.Pt() < interval->max && lvec_pair.Pt() > interval->min)
//                 {
//                     if(lvec_pair.M()>1.7 && lvec_pair.M()<2.2)
//                     {
//                         if(lvec_pair.Rapidity() < 0.8 && lvec_pair.Rapidity() > -0.8)
//                         {
//                             if( !(interval->dcut) || K_DCA*P_DCA < interval->DCA)
//                             {
//                                 R_M = lvec_pair.M();
//                                 TRes->GetCurrentFile()->cd();
//                                 TRes->Fill();
//                             }
//                         }
//                     }
//                 }
//             }            
//         }
//     }
// }


// KnPData::KnPData() { }

// void KnPData::MakeBranch2(TTree *KnPTree)
// {
//     KnPTree->Branch("Pt",&t_Pt);
//     KnPTree->Branch("Eta",&t_Eta);
//     KnPTree->Branch("Phi",&t_Phi);
//     KnPTree->Branch("M",&t_M);
//     KnPTree->Branch("Chr",&t_Chr);
//     KnPTree->Branch("DCA",&t_DCA);
// }

// void KnPData::MakeBranch(TTree *KnPTree)
// {
//     KnPTree->Branch("Pt",&t_Pt);
//     KnPTree->Branch("Eta",&t_Eta);
//     KnPTree->Branch("Phi",&t_Phi);
//     KnPTree->Branch("M",&t_M);
//     KnPTree->Branch("Chr",&t_Chr);
//     KnPTree->Branch("DCA",&t_DCA);
// }

// void KnPData::ConnectBranch(TTree *myTree)
// {
//     myTree->GetBranch("Pt")->SetAddress(&t_Pt);
//     myTree->GetBranch("Eta")->SetAddress(&t_Eta);
//     myTree->GetBranch("Phi")->SetAddress(&t_Phi);
//     myTree->GetBranch("M")->SetAddress(&t_M);
//     myTree->GetBranch("PID")->SetAddress(&t_PID);
//     myTree->GetBranch("DCA")->SetAddress(&t_DCA);
// }
