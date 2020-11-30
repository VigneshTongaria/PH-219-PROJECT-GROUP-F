
/*Double_t mean(Double_t *x, Int_t n)
{
    Double_t sum=0;
    for(int i=0;i<n;i++)
    {
        sum=sum+x[i];
	}
    return sum*1.0/n;
}
*/


  /*********************************************************************
    ___________________________________________________________
    |   DEFINING THE FUNCTIONS FOR VARIANCE AND SKEWNESS      |
    |_________________________________________________________|

  *********************************************************************/


Double_t Q2(Double_t *x, Int_t n, Double_t mu)
{
    Double_t sum=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i!=j)
            {
                sum+=(x[i]-mu)*(x[j]-mu);    
			}
	    }
	}
    return sum*1.0/(n*(n-1));
}
Double_t Q3(Double_t *x, Int_t n, Double_t mu)
{
    Double_t sum=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                if(i!=j&&j!=k&&k!=i)
                {
                    sum+=(x[i]-mu)*(x[j]-mu)*(x[k]-mu) ;   
			    }
            }
	    }
	}
    return sum*1.0/(n*(n-1)*(n-2));
}


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

  char a[]="pytree2040";
  TFile *f=new TFile("13TeV_CR0_RHoff.root");
  TTree *tree = (TTree*)f->Get(a);
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
  TCanvas *c6=new TCanvas("c6","Mean Transverse Momentum",200,10,800,600);






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
 


  TH1D *hmult =  new TH1D("hmult","Multiplicity",100,0,100.0);
  TH1D *hpT   =  new TH1D("hpT","Transverse Momentum", 100,0,2.0);
  TH1D *hpTm   =  new TH1D("hpTm","Mean Transverse Momentum", 100,0,2.0);
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
        hmult->Fill(ntrks);
        for(int i=0;i<ntrks;i++)
        {
            hpT->Fill(pT[i]);
        }
        Double_t store=TMath::Mean(pT,pT+ntrks);
        hpTm->Fill(store);
  }




  /*********************************************************************
    _____________________________________________
    |   FINDING THE VARIANCE AND SKEWNESS       |
    |___________________________________________|

  *********************************************************************/


  Double_t M=hpTm->GetMean();
  Double_t q2=0.0;
  Double_t q3=0.0;

  for(Int_t ii=0; ii<entries; ii++)  
  {
        tree->GetEntry(ii);
        Int_t ntrks = ntrack;
        NT[ii]=ntrks;
        hmult->Fill(ntrks);
        q2+=Q2(pT,ntrks,M);
        q3+=Q3(pT,ntrks,M);
  }
  q2=q2*1.0/entries;
  q3=q3*1.0/entries;

  cout<<"\n\n"<<a<<"\n\n"<<endl;
  cout<<"Standardised Skewness of <pT>: "<<q3/TMath::Power(q2,1.5)<<endl;
  cout<<"Intensive Skewness of <pT>: "<<q3*M/TMath::Power(q2,2)<<endl;

  
  
  
  
  
  /*********************************************************************
    _____________________________________________
    |   AESTHETICS OF THE HISTOGRAMS            |
    |___________________________________________|

  *********************************************************************/

  hpT->SetTitle(a);
  hpT->GetXaxis()->SetTitle("<pT> (GeV)");
  hpT->GetYaxis()->SetTitle("Count");
  hpTm->SetTitle(a);
  hpTm->GetXaxis()->SetTitle("<pT> (GeV)");
  hpTm->GetYaxis()->SetTitle("Count");





    /*********************************************************************
    _____________________________________________
    |   FITTING THE HISTOGRAMS                  |
    |___________________________________________|

  *********************************************************************/

   TF1 *gaus=new TF1("gaus","gaus",-0.5,0.5);
   gaus->SetParameters(hpTm->GetMaximum(), hpTm->GetMean(), hpTm->GetRMS()); 
   hpTm->Fit("gaus");
   TF1 *expo=new TF1("expo","expo",-0.5,0.5);
   expo->SetParameters(hpT->GetMean(), -hpT->GetMean()); 
   hpT->Fit("expo");




  /*********************************************************************
    _____________________________________________
    |   DRAWING THE HISTOGRAMS                  |
    |___________________________________________|

  *********************************************************************/

  //c1->cd();
  //hmult->Draw();
  c2->cd();
  hpT->Draw();
  c6->cd();
  hpTm->Draw();
  //c3->cd();
  //hphi->Draw();
  //c4->cd();
  //heta->Draw();
  //c5->cd();
  //hrap->Draw();




  /*********************************************************************
    _____________________________________________
    |       DRAWING THE GRAPHS                  |
    |___________________________________________|

  *********************************************************************/


  TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,500,300);
   Double_t x[100], y[100];
   Int_t n = 20;
   for (Int_t i=0;i<n;i++) {
     x[i] = i*0.1;
     y[i] = 10*sin(x[i]+0.2);
   }
   TGraph* gr = new TGraph(n,x,y);
   gr->Draw("AC*");



}


/*********************************END**********************************/