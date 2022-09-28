/* USE THIS SCRIPT CREATE THE HISTOGRAMS FROM THE TREES STORED AT THE JLAB CLUSTER  */

/* The output root file that we obtain from here is what we import to our personal computer */

/* root -l -q plot.C */

void plot_zlc_dPhiLab(TString tar,Int_t r,Int_t iMax){

    TString targ;

    if(tar=='F'){
        targ = "Fe";
    }else if(tar=='P'){
        targ = "Pb";
    }else{
        targ = tar;
    };

    TString run;

    if (r<10){
        run = "0"+TString(Form("%i",r));
    };
    
    if (r >= 10){
        run = TString(Form("%i",r));
    };

    /* Constructors */
    TString infile = "/Users/wood5/jlab/clas6/DMS/eg2/proton/Simulations/Proton_Lepto/GST_out/"+targ+"/pruned"+targ+"_"+run+".root";
    TFile *f1 = TFile::Open(infile); /* Open file where the tree is located */
    TTree* ntuple_sim = (TTree*) f1->Get("ntuple_sim"); /* Read tree */

    TString outfile = "plot_zlc_dPhiLab_pruned"+targ+"_"+run+".root";
    TFile *outf = new TFile(outfile,"RECREATE"); /* Save output plots in a root file */

    Int_t nEvts;
    if(iMax<=0){
        nEvts = ntuple_sim->GetEntries();
    }else{
        nEvts = iMax;
    }
    
    //Cuts
    TCut cut1 = "P>0.5";
    TCut cut2 = "P<3";
    TCut cut3 = "pid==2212";
    TCut cut4 = "Q2>1";
    TCut cut5 = "W>2";
    TCut cut6 = "Betta-P/(TMath::Sqrt(P*P+0.938272*0.938272))<(-0.00218+3*0.01002)";
    TCut cut7 = "Betta-P/(TMath::Sqrt(P*P+0.938272*0.938272))>(-0.00218-3*0.01002)";
    TCut cut8 = "Yb<0.85";
    
    TCut total_cut = cut1&&cut2&&cut3&&cut4&&cut5&&cut6&&cut7&&cut8;
    
    TCut cut1_mc = "mc_P>0.5";
    TCut cut2_mc = "mc_P<3";
    TCut cut3_mc = "mc_pid==2212";
    TCut cut4_mc = "mc_Q2>1";
    TCut cut5_mc = "mc_W>2";
    TCut cut6_mc = "mc_Betta-mc_P/(TMath::Sqrt(mc_P*mc_P+0.938272*0.938272))<(-0.00218+3*0.01002)";
    TCut cut7_mc = "mc_Betta-mc_P/(TMath::Sqrt(mc_P*mc_P+0.938272*0.938272))>(-0.00218-3*0.01002)";
    TCut cut8_mc = "mc_Yb<0.85";

    TCut total_cut_mc = cut1_mc&&cut2_mc&&cut3_mc&&cut4_mc&&cut5_mc&&cut6_mc&&cut7_mc&&cut8_mc;

    /* Draw Tree histograms with cuts */
    ntuple_sim->Draw("(mc_Eh+mc_Pz)/(0.938272+2*mc_Nu):TMath::RadToDeg()*(TMath::ATan2(mc_Pey,mc_Pex)-TMath::ATan2(mc_Py,mc_Px))>>Zlc_dPhiLab_Gen(360,-360.0,360.0,100,0,1.0)",total_cut_mc," ",nEvts);

    ntuple_sim->Draw("(Eh+Pz)/(0.938272+2*Nu):TMath::RadToDeg()*(TMath::ATan2(Pey,Pex)-TMath::ATan2(Py,Px))>>Zlc_dPhiLab_Rec(360,-360.0,360.0,100,0,1.0)",total_cut," ",nEvts);

//    TH2D *h2D = (TH2D*)f1->Get("Zlc_dPhiLab_Rec");
//    TH1D *h1D;
//    Int_t binLo = 1;
//    Int_t binHi = -1;
//    h1D = (TH1D*)h2D->ProjectionY("dPhiLab",binLo,binHi,"");
    
    /* Export plots */
    outf->Write();
    outf->Close(); /* (i) root plot_out.root; (ii) new TBrowser */
}
