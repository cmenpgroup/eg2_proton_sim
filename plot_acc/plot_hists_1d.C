/* USE THIS SCRIPT CREATE THE HISTOGRAMS FROM THE TREES STORED AT THE JLAB CLUSTER  */

/* The output root file that we obtain from here is what we import to our personal computer */

/* root -l -q plot.C */

void plot_hists_1d(TString tar,Int_t r,Int_t iMax, Double_t sigma = 3.0){

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

    TString outfile = "plot_hists_1d_pruned"+targ+"_"+run+".root";
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
    TString cut6_str = "Betta-P/(TMath::Sqrt(P*P+0.938272*0.938272))<(-0.00218+" + TString(Form("%f",sigma)) + "*0.01002)";
    TString cut7_str = "Betta-P/(TMath::Sqrt(P*P+0.938272*0.938272))>(-0.00218-" + TString(Form("%f",sigma)) + "*0.01002)";
    TCut cut6 = (TCut)cut6_str;
    TCut cut7 = (TCut)cut7_str;
    TCut cut8 = "Yb<0.85";

    cout<<"cut 6 " << cut6 << endl;
    cout<<"cut 7 " << cut7 << endl;

    TCut total_cut = cut1&&cut2&&cut3&&cut4&&cut5&&cut6&&cut7&&cut8;

    TCut cut1_mc = "mc_P>0.5";
    TCut cut2_mc = "mc_P<3";
    TCut cut3_mc = "mc_pid==2212";
    TCut cut4_mc = "mc_Q2>1";
    TCut cut5_mc = "mc_W>2";
    TString cut6_mc_str = "mc_Betta-mc_P/(TMath::Sqrt(mc_P*mc_P+0.938272*0.938272))<(-0.00218+" + TString(Form("%f",sigma)) + "*0.01002)";
    TString cut7_mc_str = "mc_Betta-mc_P/(TMath::Sqrt(mc_P*mc_P+0.938272*0.938272))>(-0.00218-" + TString(Form("%f",sigma)) + "*0.01002)";
    TCut cut6_mc = (TCut)cut6_mc_str;
    TCut cut7_mc = (TCut)cut7_mc_str;
    TCut cut8_mc = "mc_Yb<0.85";

    cout<<"cut 6 mc " << cut6_mc << endl;
    cout<<"cut 7 mc " << cut7_mc << endl;
    
    TCut total_cut_mc = cut1_mc&&cut2_mc&&cut3_mc&&cut4_mc&&cut5_mc&&cut6_mc&&cut7_mc&&cut8_mc;

    /* Draw Tree histograms with cuts */
    cout<<"Start P_Gen"<<endl;
    ntuple_sim->Draw("mc_P>>P_Gen(100,0,5)",total_cut_mc," ",nEvts);
    cout<<"Start P_Rec"<<endl;
    ntuple_sim->Draw("P>>P_Rec(100,0,5)",total_cut," ",nEvts);
    cout<<"Start Zh_Gen"<<endl;
    ntuple_sim->Draw("mc_Zh>>Zh_Gen(50,0,1.25)",total_cut_mc," ",nEvts);
    cout<<"Start Zh_Rec"<<endl;
    ntuple_sim->Draw("Zh>>Zh_Rec(50,0,1.25)",total_cut," ",nEvts);
    cout<<"Start Zlc_lo_Gen"<<endl;
    ntuple_sim->Draw("(mc_Eh+mc_Pz)/(0.938272+2*mc_Nu)>>Zlc_lo_Gen(30,0,0.3)",total_cut_mc," ",nEvts);
    cout<<"Start Zlc_lo_Rec"<<endl;
    ntuple_sim->Draw("(Eh+Pz)/(0.938272+2*Nu)>>Zlc_lo_Rec(30,0,0.3)",total_cut," ",nEvts);
    cout<<"Start Zlc_hi_Gen"<<endl;
    ntuple_sim->Draw("(mc_Eh+mc_Pz)/(0.938272+2*mc_Nu)>>Zlc_hi_Gen(50,0.3,1.2)",total_cut_mc," ",nEvts);
    cout<<"Start Zlc_hi_Rec"<<endl;
    ntuple_sim->Draw("(Eh+Pz)/(0.938272+2*Nu)>>Zlc_hi_Rec(50,0.3,1.2)",total_cut," ",nEvts);
    cout<<"Start Q2_Gen"<<endl;
    ntuple_sim->Draw("mc_Q2>>Q2_Gen(50,1.0,4.1)",total_cut_mc," ",nEvts);
    cout<<"Start Q2_Rec"<<endl;
    ntuple_sim->Draw("Q2>>Q2_Rec(50,1.0,4.1)",total_cut," ",nEvts);
    cout<<"Start Nu_Gen"<<endl;
    ntuple_sim->Draw("mc_Nu>>Nu_Gen(50,2.2,4.2)",total_cut_mc," ",nEvts);
    cout<<"Start Nu_Rec"<<endl;
    ntuple_sim->Draw("Nu>>Nu_Rec(50,2.2,4.2)",total_cut," ",nEvts);
    cout<<"Start Pt2_Gen"<<endl;
    ntuple_sim->Draw("mc_Pt2>>Pt2_Gen(30,0,2.0)",total_cut_mc," ",nEvts);
    cout<<"Start Pt2_Rec"<<endl;
    ntuple_sim->Draw("Pt2>>Pt2_Rec(30,0,2.0)",total_cut," ",nEvts);
    cout<<"Start PhiPQ_Gen"<<endl;
    ntuple_sim->Draw("mc_PhiPQ>>PhiPQ_Gen(60,-180.0,180.0)",total_cut_mc," ",nEvts);
    cout<<"Start PhiPQ_Rec"<<endl;
    ntuple_sim->Draw("PhiPQ>>PhiPQ_Rec(60,-180.0,180.0)",total_cut," ",nEvts);
    cout<<"Start W_Gen"<<endl;
    ntuple_sim->Draw("mc_W>>W_Gen(100,1.5,3.5)",total_cut_mc," ",nEvts);
    cout<<"Start W_Rec"<<endl;
    ntuple_sim->Draw("W>>W_Rec(100,1.5,3.5)",total_cut," ",nEvts);
    cout<<"Start Yb_Gen"<<endl;
    ntuple_sim->Draw("mc_Yb>>Yb_Gen(100,0.0,1.0)",total_cut_mc," ",nEvts);
    cout<<"Start Yb_Rec"<<endl;
    ntuple_sim->Draw("Yb>>Yb_Rec(100,0.0,1.0)",total_cut," ",nEvts);
    cout<<"Start PhiLab_Gen"<<endl;
    ntuple_sim->Draw("mc_PhiLab>>PhiLab_Gen(360,-30.0,330.0)",total_cut_mc," ",nEvts);
    cout<<"Start PhiLab_Rec"<<endl;
    ntuple_sim->Draw("PhiLab>>PhiLab_Rec(360,-30.0,330.0)",total_cut," ",nEvts);

    /* Export plots */
    outf->Write();
    outf->Close(); /* (i) root plot_out.root; (ii) new TBrowser */
}
