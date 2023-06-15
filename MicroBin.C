#include "TBrowser.h"
#include "TH2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TH1F.h>
#include <TMath.h>
#include <fstream>
#include <iostream>

void MicroBin(){


//void Proton(){
    Float_t runnum, evnum, helicity, e_p, e_theta, e_phi, vz_e, p_p, p_theta, p_phi, vz_p, xF, W, Mx, Mx2, x, y, z, Q2, pT, zeta, eta, phi;
    Float_t da, db, dc, dd, dw, de;
    float mean, binNumber, entriesNumber;
    FILE *fp = fopen("/work/clas12/fatiha/MultiDim/Total-Depol-Eloss-QA.txt","r");
    FILE *fp1;
    fp1 = fopen ("microBin.txt", "w");
    TFile *hfile = hfile = TFile::Open("PKplus2.root","RECREATE");

    TTree *outTree = new TTree("T","kinematics tree");
    outTree->Branch("runnum",&runnum,"runnum/F");
    outTree->Branch("evnum",&evnum,"evnum/F");
    outTree->Branch("helicity", &helicity,"helicity/F");
    outTree->Branch("e_p",&e_p,"e_p/F");
    outTree->Branch("e_theta",&e_theta,"e_theta/F");
    outTree->Branch("e_phi",&e_phi,"e_phi/F");
    outTree->Branch("vz_e",&vz_e,"vz_e/F");
    outTree->Branch("p_p",&p_p,"p_p/F");
    outTree->Branch("p_theta",&p_theta,"p_theta/F");
    outTree->Branch("p_phi",&p_phi,"p_phi/F");
    outTree->Branch("vz_p",&vz_p,"vz_p/F");
    outTree->Branch("xF",&xF,"xF/F");
    outTree->Branch("W",&W,"W/F");
    outTree->Branch("Mx",&Mx,"Mx/F");
    outTree->Branch("Mx2",&Mx2,"Mx2/F");
    outTree->Branch("x",&x,"x/F");
    outTree->Branch("y",&y,"y/F");
    outTree->Branch("z",&z,"z/F");
    outTree->Branch("Q2",&Q2,"Q2/F");
    outTree->Branch("pT",&pT,"pT/F");
    outTree->Branch("zeta",&zeta,"zeta/F");
    outTree->Branch("eta",&eta,"eta/F");
    outTree->Branch("phi",&phi,"phi/F");
    outTree->Branch("da",&da,"da/F");
    outTree->Branch("db",&db,"db/F");
    outTree->Branch("dc",&dc,"dc/F");
    outTree->Branch("dd",&dd,"dd/F");
    outTree->Branch("dw",&dw,"dw/F");
    outTree->Branch("de",&de,"de/F");


// for(int k=0; k<9777418; k++){
// for(int k=0; k<16372460; k++){
//16372460 total number of events in this file 
// for(int k=0; k<6; k++){

// 10019 has 57938894 events 

for(int k=0; k<59019; k++){

    fscanf(fp, "%f %f %f %f %f %f %f ", &runnum, &evnum, &helicity, &e_p, &e_theta, &e_phi, &vz_e);

    fscanf(fp, " %f %f %f %f %f %f %f %f ", &p_p, &p_theta, &p_phi, &vz_p, &Q2, &W, &Mx, &Mx2);

    fscanf(fp, " %f %f %f %f %f %f %f %f  ", &x, &y, &z, &xF, &pT, &zeta, &eta, &phi );

    fscanf(fp, " %f %f %f %f %f ", &da, &db, &dc, &dd, &dw);
    
    de = dw/da;

    outTree->Fill();

    }

outTree->Write();
fclose(fp);
hfile->Write();


///////////////////////////////////////////////////////////////
TCut NegHeli = ("helicity == -1");
TCut PosHeli = ("helicity == 1");

char cut_pT[30];
strcpy(cut_pT, "0<pT&&pT<0.14");
float start_pT = 0.14;
float add_pT = 0.14;


char cut_Q2[30];
strcpy(cut_Q2, "1<Q2&&Q2<1.8");
float start_Q2 = 1.8;
float add_Q2 = 0.8;

char cut_x[30];
strcpy(cut_x, "0.06<x&&x<0.13");
float start_x = 0.13;
float add_x = 0.07;

char cut_zeta[30];
strcpy(cut_zeta, "0.3<zeta&&zeta<0.35");
float start_zeta = 0.35;
float add_zeta = 0.05;

char cut_phi[30];
strcpy(cut_phi, "0<phi&&phi<36");
float start_phi = 36;
float add_phi = 36;




//////////////////////////////////////////////////////////////////
    for (int m = 1; m <= 10; m++) {
        TCut PHI1 = (cut_phi);

        for (int k = 1; k <= 10;  k++) {
            TCut ZETA1 = (cut_zeta);

            for (int i = 1; i <= 10;  i++) {
                TCut X1 = (cut_x);

                for (int j = 1; j <= 10;  j++) {
                    TCut Q21 = (cut_Q2);

                    for (int l = 1; l <= 10;  l++) {

                        TCut pT1 = (cut_pT);
                        
                        fprintf(fp1, "%i %i %i %i %i ", l , j , i , k, m);

                        TH1F*h0 = new TH1F("h0","h0",500, 0, 1.4);
                        outTree->Draw("pT>>h0", pT1 && Q21 && X1 && ZETA1 && PHI1);
                        mean = h0->GetMean();
                        fprintf(fp1, "%f ", mean);

                        TH1F*h1 = new TH1F("h1","h1",500, 0, 1.4);
                        outTree->Draw("pT>>h1", PosHeli && pT1 && Q21 && X1 && ZETA1 && PHI1);
                        entriesNumber = h1->GetEntries();
                        fprintf(fp1, "%f ",entriesNumber);

                        TH1F*h2 = new TH1F("h2","h2",500, 0, 1.4);
                        outTree->Draw("pT>>h2", NegHeli && pT1 && Q21 && X1 && ZETA1 && PHI1);
                        entriesNumber = h2->GetEntries();
                        fprintf(fp1, "%f ", entriesNumber);

                        TH1F*h3 = new TH1F("h3","h3",500, 0.06, 0.76);
                        outTree->Draw("x>>h3", pT1 && Q21 && X1 && ZETA1 && PHI1);
                        mean = h3->GetMean();
                        fprintf(fp1, "%f ", mean);

                        TH1F*h4 = new TH1F("h4","h4",500, 1, 8);
                        outTree->Draw("Q2>>h4", pT1 && Q21 && X1 && ZETA1 && PHI1);
                        mean = h4->GetMean();
                        fprintf(fp1, "%f ", mean);

                        TH1F*h5 = new TH1F("h5","h5",500, 0.3, 0.8);
                        outTree->Draw("zeta>>h5", pT1 && Q21 && X1 && ZETA1 && PHI1);
                        mean = h5->GetMean();
                        fprintf(fp1, "%f ", mean);

                        TH1F*h6 = new TH1F("h6","h6",500, 0, 360);
                        outTree->Draw("phi>>h6", NegHeli && pT1 && Q21 && X1 && ZETA1 && PHI1);
                        entriesNumber = h6->GetEntries();
                        fprintf(fp1, "%f ", entriesNumber);

                        TH1F*h7 = new TH1F("h7","h7",500, -1, 1);
                        outTree->Draw("xF>>h7", pT1 && Q21 && X1 && ZETA1 && PHI1);
                        mean = h7->GetMean();
                        fprintf(fp1, "%f ", mean);

                        TH1F*h8 = new TH1F("h8","h8",500, -1.5, 3);
                        outTree->Draw("eta>>h8", pT1 && Q21 && X1 && ZETA1 && PHI1);
                        mean = h8->GetMean();
                        fprintf(fp1, "%f ", mean);

                        TH1F*h9 = new TH1F("h9","h9",500, -3, 3);
                        outTree->Draw("de>>h9", pT1 && Q21 && X1 && ZETA1 && PHI1);
                        mean = h5->GetMean();
                        fprintf(fp1, "%f \n", mean);
                        
                        
                        
                                                h0->Delete();
                        delete h0;

                        h1->Delete();
                        delete h1;

                        h2->Delete();
                        delete h2;

                        h3->Delete();
                        delete h3;

                        h4->Delete();
                        delete h4;

                        h5->Delete();
                        delete h5;

                        h6->Delete();
                        delete h6;

                        h7->Delete();
                        delete h7;

                        h8->Delete();
                        delete h8;

                        h9->Delete();
                        delete h9;


                        

                        sprintf(cut_pT, "%f<pT&&pT<%f", start_pT + (l * add_pT - add_pT) , start_pT + (l * add_pT));
                    }

                    sprintf(cut_Q2, "%f<Q2&&Q2<%f", start_Q2 + (j * add_Q2  - add_Q2) , start_Q2 + (j * add_Q2));



                }
                sprintf(cut_x, "%f<x&&x<%f", start_x + (i * add_x  - add_x) , start_x + (i * add_x));


            }

            sprintf(cut_zeta, "%f<zeta&&zeta<%f", start_zeta + (k * add_zeta  - add_zeta), start_zeta + (k * add_zeta));



        }

        sprintf(cut_phi, "%f<phi&&phi<%f", start_phi + (m * add_phi  - add_phi), start_phi + (m * add_phi));
    }




}
