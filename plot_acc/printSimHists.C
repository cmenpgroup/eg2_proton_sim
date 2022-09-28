// printSimHists.C
//
// macro to analyze acceptance histograms
//
// Michael H. Wood, Canisius College
//
//--------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//gROOT->Reset();   // start from scratch

Int_t lcol[10] = {1,2,4,6,7,8,9,10,14,15};
Int_t mkr[10] = {20,21,22,24,23,25,26,27,28,29};

string htitle;
string title;
string cname;
string ctitle;

Float_t Lmar = 0.125;
Float_t Rmar = 0.125;
Float_t yoff = 1.5;

const Int_t nDim = 3; // number of dimensions of analysis (1d, 2d, 3d)

const Int_t nTargets = 4;
string targ[nTargets] = {"D","C","Fe","Pb"};

const Int_t nVars1d = 7;
string Vars1d[nVars1d] = {"Zh","Zlc_lo","Zlc_hi","Q2","Nu","Pt2","PhiPQ"};

const Int_t nSolid = 3;
Double_t norm_factors_data_cor[nSolid]={1.11978,  1.0609,  2.19708}; // the order is C , Fe, Pb

const Int_t nuBin_MR3zh = 3;
const Int_t Q2Bin_MR3zh = 3;
const Int_t maxBin_MR2pT2 = 9;

//
// printSimHists - plot histogram with labels
//
//                  fAna = output file name
//                  hname = histogram name
//
void printSimHists(string fAna="Ana.root", string hname="simHist", string OutFile="printSimHists.txt")
{
    // data files contain the trees
    printf("Analyzing file %s for histogram %s\n",fAna.c_str(),hname.c_str());
    TFile *fm = new TFile(fAna.c_str(),"READ");
    TH1F *hist = (TH1F*)fm->Get(hname.c_str());

    ofstream fout(OutFile.c_str());
    if (fout.is_open()){
        for(Int_t i=1; i<=hist->GetNbinsX(); i++){
            fout << hist->GetBinCenter(i) << "\t" << hist->GetBinContent(i) << "\t" << hist->GetBinError(i) <<endl;
        }
    }
    fout.close();
}

//
// printSimHists3d_single - plot histogram with labels
//
//                  target = target type
//                  hPrefix = variable name
//
void printSimHists3d_single(string target="C", string hPrefix="Zh")
{
    string filePrefix = "plot_hists_3d_pruned" + target + "_all";
    string fAna = target + "/3d/" + filePrefix + ".root";
    string hname;
    string OutFile;
    for(Int_t i=0; i<Q2Bin_MR3zh; i++){
        for(Int_t j=0; j<nuBin_MR3zh; j++){
            hname = hPrefix + "_Gen_" + to_string(i) + to_string(j);
            OutFile = target + "/3d/pruned" + target + "_MR3zh_"+ to_string(i) +  to_string(j) + ".gen";
            printSimHists(fAna,hname,OutFile);

            hname = hPrefix + "_Rec_" + to_string(i) + to_string(j);
            OutFile = target + "/3d/pruned" + target + "_MR3zh_"+ to_string(i) +  to_string(j) + ".rec";
            printSimHists(fAna,hname,OutFile);
        }
    }
}

//
// printSimHists3d - plot histogram with labels
//
//
void printSimHists3d(string target="C")
{
    printSimHists3d_single(target,"Zh");
}

//
// printSimHists2d_single - plot histogram with labels
//
//                  target = target type
//                  hPrefix = variable name
//
void printSimHists2d_single(string target="C", string hPrefix="Pt2")
{
    string filePrefix = "plot_hists_2d_pruned" + target + "_all";
    string fAna = target + "/2d/" + filePrefix + ".root";
    string hname;
    string OutFile;
    for(Int_t i=0; i<maxBin_MR2pT2; i++){
        hname = hPrefix + "_Gen_" + to_string(i);
        OutFile = target + "/2d/pruned" + target + "_MR2pT2_"+ to_string(i) + ".gen";
        printSimHists(fAna,hname,OutFile);

        hname = hPrefix + "_Rec_" + to_string(i);
        OutFile = target + "/2d/pruned" + target + "_MR2pT2_"+ to_string(i) + ".rec";
        printSimHists(fAna,hname,OutFile);
    }
}

//
// printSimHists2d - plot histogram with labels
//
//
void printSimHists2d(string target="C")
{
    printSimHists2d_single(target,"Pt2");
}

//
// printSimHists1d_single - plot histogram with labels
//
//                 target = target type
//                 hPrefix = variable name
//
void printSimHists1d_single(string target="C", string hPrefix = "Zh")
{
    string hname;
    string OutFile;

    string filePrefix = "plot_hists_1d_pruned" + target + "_all";
    string fAna = target + "/1d/" + filePrefix + ".root";
    hname = hPrefix + "_Gen";
    OutFile = target + "/1d/pruned" + target + "_" + hPrefix + ".gen";
    printSimHists(fAna,hname,OutFile);

    hname = hPrefix + "_Rec";
    OutFile = target + "/1d/pruned" + target + "_" + hPrefix + ".rec";
    printSimHists(fAna,hname,OutFile);
}

//
// printSimHists1d - plot histogram with labels
//
//                  target = target type
//
void printSimHists1d(string target="C")
{
    for(Int_t i=0; i<nVars1d; i++){
        printSimHists1d_single(target,Vars1d[i]);
    }
}

//
// printSimHists_allTargets - plot histogram with labels
//
//         dim = dimension of the analysis (1, 2, or 3)
//
void printSimHists_allTargets(Int_t dim=1)
{
    for(Int_t i=0; i<nTargets; i++){
      switch(dim){
        case 1: printSimHists1d(targ[i]); break;
        case 2: printSimHists2d(targ[i]); break;
        case 3: printSimHists3d(targ[i]); break;
        default: cout << "No dimension matching " << dim << endl; exit(0); break;
      }
    }
}

//
// printSimHists_all - plot histogram with labels
//
//
void printSimHists_all()
{

    for(Int_t i=0; i<nDim; i++){
      printSimHists_allTargets(i+1);
    }
}
