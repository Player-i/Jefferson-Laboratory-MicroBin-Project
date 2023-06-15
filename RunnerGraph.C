#include "TBrowser.h"
#include "TH2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TH1F.h>
#include <TMath.h>
#include <fstream>
#include <iostream>

void RunnerGraph(){
    

    // Creating variables in text file
    int i, l, j, k, m;
    float  Npos, Nneg, pTmean, xmean, Q2mean, zetamean, phimean, xFmean, demean;

    float etamean, pT;

    



    // Opening Text File
    

    // Creating Canvas
    TCanvas* canvas = new TCanvas("canvas", "Graph", 800, 600);
    canvas->Divide(1,1);
    // Creating Graph
    TGraph* graph = new TGraph();

    for (int n=1; n <= 10; n++) {

        pT = 0;
        FILE *fp = fopen("microBin.txt","r");
        for(int g=0; g<1350; g++){

            fscanf(fp, " %d %d %d %d %d %f %f %f  ", &l, &j, &i, &k, &m, &pTmean, &Npos, &Nneg );

            fscanf(fp, " %f %f %f %f %f ", &xmean, &Q2mean, &zetamean, &phimean, &xFmean);

            fscanf(fp, " %f %f ", &etamean, &demean);

	
            if (n == l ) {
                 if (pTmean != 0) {

                    pT += pTmean;

                }
            }
  

        };
        pT = pT / 135;
        fclose(fp);
        printf("PT: %f\n", pT);
        graph->SetPoint(n, n, pT);
	

        

    }


    graph->SetTitle("pT"); // Set the title
    graph->SetMarkerStyle(20);  // Set the marker style
    graph->SetMarkerColor(kBlue);  // Set the marker color
    graph->SetLineColor(kRed);
    graph->GetXaxis()->SetTitle("PT Bin #");
    graph->GetYaxis()->SetTitle("PT Value");
    graph->GetXaxis()->SetRangeUser(0.0, 10);     //xF (-0.8, 0.6); Q2 (0.0, 6.0); pT (0.0, 1.3)
    graph->GetYaxis()->SetRangeUser(0, 0.15);


    graph->Draw("APL");
    canvas->Update();
}
