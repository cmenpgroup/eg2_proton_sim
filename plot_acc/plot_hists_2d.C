/* USE THIS SCRIPT CREATE THE HISTOGRAMS FROM THE TREES STORED AT THE JLAB CLUSTER  */

/* The output root file that we obtain from here is what we import to our personal computer */

/* root -l -q plot.C */

void plot_hists_2d(TString tar,Int_t r,Int_t iMax, Double_t sigma = 3.0){

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

    TString outfile = "plot_hists_2d_pruned"+targ+"_"+run+".root";
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

    /* Bins */
    TCut cuts_Zh_b[9] = {"0.300000<=Zh","0.400000<Zh","0.500000<Zh","0.600000<Zh","0.700000<Zh","0.800000<Zh","0.900000<Zh","1.000000<Zh","1.100000<Zh"};
    TCut cuts_Zh_t[9] = {"Zh<=0.400000","Zh<=0.500000","Zh<=0.600000","Zh<=0.700000","Zh<=0.800000","Zh<=0.900000","Zh<=1.000000","Zh<=1.100000","Zh<=1.200000"};

    TCut cuts_Zh_b_mc[9] = {"0.300000<=mc_Zh","0.400000<mc_Zh","0.500000<mc_Zh","0.600000<mc_Zh","0.700000<mc_Zh","0.800000<mc_Zh","0.900000<mc_Zh","1.000000<mc_Zh","1.100000<mc_Zh"};
    TCut cuts_Zh_t_mc[9] = {"mc_Zh<=0.400000","mc_Zh<=0.500000","mc_Zh<=0.600000","mc_Zh<=0.700000","mc_Zh<=0.800000","mc_Zh<=0.900000","mc_Zh<=1.000000","mc_Zh<=1.100000","mc_Zh<=1.200000"};

    TH1F *Pt2_Gen[9];
    TH1F *Pt2_Rec[9];
    TString hname;
    TString varexp;

    /* Draw Tree histograms with cuts */
    for(int i=0; i<9; i++){
      hname = "Pt2_Gen_" + TString(Form("%i",i));
      Pt2_Gen[i] = new TH1F(hname,hname,30,0.0,2.0);
      cout << "Start Pt2_Gen_" << i << endl;
      TCut final_cut_mc = total_cut_mc&&cuts_Zh_b_mc[i]&&cuts_Zh_t_mc[i];
      varexp = "mc_Pt2>>" + hname;
      ntuple_sim->Draw(varexp,final_cut_mc," ",nEvts);

      hname = "Pt2_Rec_" + TString(Form("%i",i));
      Pt2_Rec[i] = new TH1F(hname,hname,30,0.0,2.0);
      cout << "Start Pt2_Rec_" << i << endl;
      TCut final_cut = total_cut&&cuts_Zh_b[i]&&cuts_Zh_t[i];
      varexp = "Pt2>>" + hname;
      ntuple_sim->Draw(varexp,final_cut," ",nEvts);
    }

    /* Export plots */
    outf->Write();
    outf->Close(); /* (i) root plot_out.root; (ii) new TBrowser */
}
