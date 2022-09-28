// project_zlc_dPhiLab.C
//
//      Project onto the dPhiLab axis with cuts in zLC
// 
// Michael H. Wood, Canisius College
//
//--------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void draw_zlc_dPhiLab(TString fAna="plot_zlc_dPhiLab.root", TString targ="C")
{
    gROOT->Reset();   // start from scratch

    Float_t Lmar = 0.125;
    Float_t Rmar = 0.125;
    Float_t yoff = 1.5;
    
    // Canvas to compare IM by each cut
	TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);
	c1->SetBorderMode(1);  //Bordermode (-1=down, 0 = no border, 1=up)
	c1->SetBorderSize(5); 
	gStyle->SetOptStat(1111);
	c1->SetFillStyle(4000);
    c1->Divide(2,1);
	// data files contain the trees
	cout << "Analyzing file " << fAna <<endl;
	TFile *fm = new TFile(fAna,"READ");
    
    const Int_t nSim = 2;
    TString hname[nSim];
    TString SimType[nSim] = {"Gen","Rec"};
    TString htitle[nSim] = {"Generated","Reconstructed"};
    TH2D *h2D[nSim];

    for(Int_t i=0; i<nSim; i++){
        hname[i] = "Zlc_dPhiLab_"+SimType[i];
        cout << hname[i] << endl;
        h2D[i] = (TH2D*)fm->Get(hname[i]);

        c1->cd(i+1);
        gPad->SetLeftMargin(Lmar);
        gPad->SetRightMargin(Rmar);
        gPad->SetFillColor(0);
    
        h2D[i]->SetTitle(htitle[i]);
        h2D[i]->SetXTitle("#Delta #phi_{ep} (deg.)");
        h2D[i]->GetXaxis()->CenterTitle();
        h2D[i]->SetYTitle("z_{LC}");
        h2D[i]->GetYaxis()->CenterTitle();
        h2D[i]->GetYaxis()->SetTitleOffset(yoff);
        h2D[i]->Draw("colz");
    }
    TString OutCan = "draw_Zlc_dPhiLab_" + targ +".gif";
	c1->Print(OutCan);
}

