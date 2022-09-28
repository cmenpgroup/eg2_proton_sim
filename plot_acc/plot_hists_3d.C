/* USE THIS SCRIPT CREATE THE HISTOGRAMS FROM THE TREES STORED AT THE JLAB CLUSTER  */

/* The output root file that we obtain from here is what we import to our personal computer */

/* root -l -q plot.C */

void plot_hists_3d(TString tar,Int_t r,Int_t iMax, Double_t sigma = 3.0){

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

    TString outfile = "plot_hists_3d_pruned"+targ+"_"+run+".root";
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
    const Int_t Q2bins = 3;
    TCut cuts_Q2_b[Q2bins] = {"1.0<=Q2","1.33<Q2", "1.76<Q2"};
    TCut cuts_Q2_t[Q2bins] = {"Q2<=1.33","Q2<=1.76","Q2<=4.10"};

    TCut cuts_Q2_b_mc[Q2bins] = {"1.0<=mc_Q2","1.33<mc_Q2", "1.76<mc_Q2"};
    TCut cuts_Q2_t_mc[Q2bins] = {"mc_Q2<=1.33","mc_Q2<=1.76","mc_Q2<=4.10"};

    const Int_t Nubins = 3;
    TCut cuts_Nu_b[Nubins] = {"2.20<=Nu","3.20<Nu", "3.73<Nu"};
    TCut cuts_Nu_t[Nubins] = {"Nu<=3.20","Nu<=3.73","Nu<=4.25"};

    TCut cuts_Nu_b_mc[Nubins] = {"2.20<=mc_Nu","3.20<mc_Nu", "3.73<mc_Nu"};
    TCut cuts_Nu_t_mc[Nubins] = {"mc_Nu<=3.20","mc_Nu<=3.73","mc_Nu<=4.25"};

    TH1F *Zh_Gen[Q2bins][Nubins];
    TH1F *Zh_Rec[Q2bins][Nubins];
    TString hname;
    TString varexp;

    /* Draw Tree histograms with cuts */
    for(int i=0; i<Q2bins; i++){
      for(int j=0; j<Nubins; j++){
        hname = "Zh_Gen_" + TString(Form("%i",i)) + TString(Form("%i",j));
        Zh_Gen[i][j] = new TH1F(hname,hname,50,0.0,1.25);
        cout << "Start Zh_Gen_" << i << j << endl;
        TCut final_cut_mc = total_cut_mc&&cuts_Q2_b_mc[i]&&cuts_Q2_t_mc[i]&&cuts_Nu_b_mc[j]&&cuts_Nu_t_mc[j];
        varexp = "mc_Zh>>" + hname;
        ntuple_sim->Draw(varexp,final_cut_mc," ",nEvts);

        hname = "Zh_Rec_" + TString(Form("%i",i)) + TString(Form("%i",j));;
        Zh_Rec[i][j] = new TH1F(hname,hname,50,0.0,1.25);
        cout << "Start Zh_Rec_" << i << j << endl;
        TCut final_cut = total_cut&&cuts_Q2_b[i]&&cuts_Q2_t[i]&&cuts_Nu_b[j]&&cuts_Nu_t[j];
        varexp = "Zh>>" + hname;
        ntuple_sim->Draw(varexp,final_cut," ",nEvts);
      }
    }

    /* Export plots */
    outf->Write();
    outf->Close(); /* (i) root plot_out.root; (ii) new TBrowser */
}
