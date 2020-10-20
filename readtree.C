
/*Double_t mean(Double_t *x, Int_t n)
{
    Double_t sum=0;
    for(int i=0;i<n;i++)
    {
        sum=sum+x[i];
	}
    return sum*1.0/n;
}
Double_t var(Double_t *x, Int_t n)
{
    Double_t mu=mean(x,n);
    Double_t sum=0;
    for(int i=0;i<n;i++)
    {
        sum=sum+(x[i]-mu)*(x[i]-mu);
	}
    return sum*1.0/n;
}
Double_t skew(Double_t *x, Int_t n)
{
    Double_t mu=mean(x,n);
    Double_t sigma=TMath::Sqrt(var(x,n));
    Double_t sum=0;
    for(int i=0;i<n;i++)
    {
        sum=sum+(x[i]-mu)*(x[i]-mu)*(x[i]-mu);
	}
    return sum*1.0/(n*TMath::Power(sigma,1.5));
}
*/
void readtree()
{
  
  /*********************************************************************
    _____________________________________________
    |   READING THE TREE                        |
    |   CHANGE TREE NAME AS PER CONVENIENCE     |
    |   entries = NUMBER OF ENTRIES             |
    |___________________________________________|

  ***********************************************************************/

  /*********************************************************************

  TREES AVAILABLE:

  pytree;100
  pytree;99
  pytree2040;28
  pytree2040;27
  pytree4060;24
  pytree4060;23
  pytree020;24
  pytree020;23
  pytree6080;16
  pytree6080;15
  pytree80100;7
  pytree80100;6
  pytree100;3
  pytree100;2

  *********************************************************************/

  TFile *f=new TFile("13TeV_CR0_RHoff.root");
  TTree *tree = (TTree*)f->Get("pytree2040");
  Int_t entries = tree->GetEntries();
  //cout<<entries<<endl;

  const Int_t maxTrack=10000;





  /*********************************************************************
    _____________________________________________
    |   DEFINING THE CANVASES                   |
    |   CANVAS c1: MULTIPLICITY                 |
    |   CANVAS c2: TRANSVERSE MOMENTUM          |
    |   CANVAS c3: PHI                          |
    |   CANVAS c4: RAPIDITY                     |
    |   CANVAS c5: RAP                          |
    |___________________________________________|

  *********************************************************************/

  //TCanvas *c1=new TCanvas("c1","Multiplicity",200,10,800,600);
  TCanvas *c2=new TCanvas("c2","Transverse Momentum",200,10,800,600);
  //TCanvas *c3=new TCanvas("c3","Phi",200,10,800,600);
  //TCanvas *c4=new TCanvas("c4","Rapidity",200,10,800,600);
  //TCanvas *c5=new TCanvas("c5","Rap",200,10,800,600);

  //cout<<sum(3,4)<<endl;





  /*********************************************************************
    _____________________________________________
    |   INITIALISING THE CORRESPONDING ARRAYS,  |
    |   TREES AND HISTOGRAMS                    |
    |___________________________________________|

  *********************************************************************/
   
  Int_t ntrack = 0;
  Double_t pT[maxTrack];
  Double_t eta[maxTrack];
  Double_t rap[maxTrack];
  Double_t phi[maxTrack];
  Double_t NT[entries];


  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("eta",&eta);
  tree->SetBranchAddress("rap",&rap);
 


  TH1D *hmult  = new TH1D("hmult","Multiplicity",100,0,100.0);
  TH1D *hpT   =  new TH1D("hpT","Transverse Momentum", 100,0,3.0);
  TH1D *hphi  =  new TH1D("hphi","Phi",100,-5.0,5.0);
  TH1D *heta  =  new TH1D("heta","Rapidity",100,-5.0,5.0);
  TH1D *hrap  =  new TH1D("hrap","Rap",100,-5.0,5.0);




  /*********************************************************************
    _____________________________________________
    |   FILLING THE HISTOGRAMS                  |
    |___________________________________________|

  *********************************************************************/

  for(Int_t ii=0; ii<entries; ii++)  
  {//Event loop starts here
        tree->GetEntry(ii);
        Int_t ntrks = ntrack;
        NT[ii]=ntrks;
        //cout<<ntrks<<endl;
        hmult->Fill(ntrks);
        for(int i=0; i<ntrks; i++) 
        {            
            //Double_t pT1 = pT[i];
            //hpT->Fill(pT1);
            //Double_t phi1 = phi[i];
            //hphi->Fill(phi1);
            //Double_t eta1 = eta[i];
            //heta->Fill(eta1);
            //Double_t rap1 = rap[i];
            //hrap->Fill(rap1);
        }
        hpT->Fill(TMath::Mean(pT,pT+ntrks));
  }

  //cout<<skew(NT,entries)<<endl;
  cout<<"Skewness of <pT>: "<<hpT->GetSkewness()<<endl;
  cout<<"Standard Skewness of <pT>: "<<hpT->GetSkewness()*1.0*hpT->GetMean()/hpT->GetStdDev()<<endl;


  /*********************************************************************
    _____________________________________________
    |   DRAWING THE HISTOGRAMS                  |
    |___________________________________________|

  *********************************************************************/

  //c1->cd();
  //hmult->Draw();
  c2->cd();
  hpT->Draw();
  //c3->cd();
  //hphi->Draw();
  //c4->cd();
  //heta->Draw();
  //c5->cd();
  //hrap->Draw();

}


/*********************************END**********************************/
