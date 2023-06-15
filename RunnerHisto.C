#include "TBrowser.h"
#include "TH2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TH1F.h>
#include <TMath.h>
#include <fstream>
#include <iostream>

void RunnerHisto(){
    

    // Creating variables in text file
    int i, l, j, k, m;
    float  Npos, Nneg, pTmean, xmean, Q2mean, zetamean, phimean, xFmean, demean;

    float etamean, pT;

     // Creating Three
    TFile *hfile = hfile = TFile::Open("PKplus2.root","RECREATE");


    TTree *outTree = new TTree("T","kinematics tree");
    outTree->Branch("pTmean", &pTmean, "pTmean/F");




    // Opening Text File
    

    // Creating Canvas
    TCanvas* canvas = new TCanvas("canvas", "Graph", 800, 600);
    FILE *fp = fopen("microBin.txt","r");
   


        for(int g=0; g<1358; g++){

            fscanf(fp, " %d %d %d %d %d %f %f %f  ", &l, &j, &i, &k, &m, &pTmean, &Npos, &Nneg );

            fscanf(fp, " %f %f %f %f %f ", &xmean, &Q2mean, &zetamean, &phimean, &xFmean);

            fscanf(fp, " %f %f ", &etamean, &demean);

	
            

                    outTree->Fill();
            
            }


       
    TH1F* histogram = new TH1F("histogram","",20,-0.5, 2);
    canvas->Divide(1,1);
    histogram->GetXaxis()->SetTitle("pT");
    histogram->GetXaxis()->SetTitleSize(0.1);
    histogram->GetXaxis()->SetLabelSize(0.05);
    histogram->GetXaxis()->SetTitleOffset(0.6);
    histogram->GetYaxis()->SetTitle("Counts");
    histogram->GetYaxis()->SetTitleSize(0.1);
    histogram->GetYaxis()->SetLabelSize(0.05);
    histogram->GetYaxis()->SetTitleOffset(0.6);
    histogram->SetLineWidth(5);
    histogram->SetStats(1);
    outTree->Draw("pTmean>>histogram");
    canvas->Update();
}