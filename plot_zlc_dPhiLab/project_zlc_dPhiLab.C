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

void project_zlc_dPhiLab(TString fAna="plot_zlc_dPhiLab.root", TString targ="C", TString SimType = "Rec")
{
    gROOT->Reset();   // start from scratch

    Float_t Lmar = 0.125;
    Float_t Rmar = 0.125;
    Float_t yoff = 1.5;
    
    const Int_t maxBins = 5;
    Float_t zLC_lo[maxBins] = {0.0,0.0,0.3,0.6,0.9};
    Float_t zLC_hi[maxBins] = {1.0,0.3,0.6,0.9,1.0};
    
    // Canvas to compare IM by each cut
	TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,900);
	c1->SetBorderMode(1);  //Bordermode (-1=down, 0 = no border, 1=up)
	c1->SetBorderSize(5); 
	gStyle->SetOptStat(1111);
	c1->SetFillStyle(4000);
    c1->Divide(3,2);
	// data files contain the trees
	cout << "Analyzing file " << fAna <<endl;
	TFile *fm = new TFile(fAna,"READ");
    
    TString htitle;
    TString hname = "Zlc_dPhiLab_"+SimType;
    cout << hname << endl;
    TH2D *h2D = (TH2D*)fm->Get(hname);
    TH1D *h1Dx[maxBins];

    for(Int_t i=0; i<maxBins; i++){
        c1->cd(i+1);
        gPad->SetLeftMargin(Lmar);
        gPad->SetRightMargin(Rmar);
        gPad->SetFillColor(0);
        
        Int_t binLo = h2D->GetYaxis()->FindBin(zLC_lo[i]);
        Int_t binHi = h2D->GetYaxis()->FindBin(zLC_hi[i]) ;
        TString strname = hname + "_x" + TString(Form("%i",i));
        h1Dx[i] = (TH1D*)h2D->ProjectionX(strname,binLo,binHi,"");
    
        htitle = TString(Form("%5.2f",zLC_lo[i])) + " < zLC < " + TString(Form("%5.2f",zLC_hi[i]));
        h1Dx[i]->SetTitle(htitle);
        h1Dx[i]->SetXTitle("#Delta #phi_{ep} (deg.)");
        h1Dx[i]->GetXaxis()->CenterTitle();
        h1Dx[i]->SetYTitle("Counts");
        h1Dx[i]->GetYaxis()->CenterTitle();
        h1Dx[i]->GetYaxis()->SetTitleOffset(yoff);
        h1Dx[i]->SetLineWidth(2);
        h1Dx[i]->Draw();
    }
    TString OutCan = "project_" + hname + "_" + targ +".gif";
	c1->Print(OutCan);
}

