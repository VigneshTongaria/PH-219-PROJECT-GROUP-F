
Double_t mean(Double_t *x, Int_t n)
{
    Double_t sum=0;
    for(int i=0;i<n;i++)
    {
        sum=sum+x[i];
	}
    return sum*1.0/n;
}


  /*********************************************************************
    ___________________________________________________________
    |   DEFINING THE FUNCTIONS FOR VARIANCE AND SKEWNESS      |
    |_________________________________________________________|

  *********************************************************************/


Double_t Q2(Double_t *x, Int_t n, Double_t mu)
{
    return TMath::Power((TMath::Mean(x,x+n)-mu),2);
}
Double_t Q3(Double_t *x, Int_t n, Double_t mu)
{
    return TMath::Power((TMath::Mean(x,x+n)-mu),3);
}


void readtree1()
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

  char A[5][15]={"pytree2040","pytree4060","pytree6080","pytree80100","pytree100"};
  Double_t B[]={20,40,60,80,100};
  Double_t s1[]={0.0,0.0,0.0,0.0,0.0};
  Double_t s2[]={0.0,0.0,0.0,0.0,0.0};
  Double_t s3[]={0.0,0.0,0.0,0.0,0.0};
  for(int I=0;I<5;I++)
  {
      TFile *f=new TFile("13TeV_CR0_RHoff.root");
      TTree *tree = (TTree*)f->Get(A[I]);
      Int_t entries = tree->GetEntries();
      //cout<<entries<<endl;

      const Int_t maxTrack=10000;




  /*********************************************************************
    _____________________________________________
    |   INITIALISING THE CORRESPONDING ARRAYS,  |
    |        AND TREES                          |
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


      /*********************************************************************
        _____________________________________________
        |   FINDING THE VARIANCE AND SKEWNESS       |
        |___________________________________________|

      *********************************************************************/


      Double_t q1=0.0;
      Double_t q2=0.0;
      Double_t q3=0.0;

      for(Int_t ii=0; ii<entries; ii++)  
      {
            tree->GetEntry(ii);
            Int_t ntrks = ntrack;
            NT[ii]=ntrks;
            q1+=TMath::Mean(pT,pT+ntrks);
      }
      q1=q1*1.0/entries;
      for(Int_t ii=0; ii<entries; ii++)  
      {
            tree->GetEntry(ii);
            Int_t ntrks = ntrack;
            NT[ii]=ntrks;
            q2+=Q2(pT,ntrks,q1);
            q3+=Q3(pT,ntrks,q1);
      }
      q2=q2*1.0/entries;
      q3=q3*1.0/entries;

      cout<<"\n\n"<<A[I]<<"\n\n"<<endl;
      cout<<"Standardised Skewness of <pT>: "<<q3/TMath::Power(q2,1.5)<<endl;
      cout<<"Intensive Skewness of <pT>: "<<q3*q1/TMath::Power(q2,2)<<endl;


      s1[I]=q1;
      s2[I]=TMath::Sqrt(q2)/q1;
      s3[I]=q3*q1/TMath::Power(q2,2);

  }


  /*********************************************************************
  _____________________________________________
  |       DRAWING THE GRAPHS                  |
  |___________________________________________|
  
  *********************************************************************/


  TCanvas *c7 = new TCanvas("c7","Mean",200,10,500,300);
  TCanvas *c8 = new TCanvas("c8","Variance",200,10,500,300);
  TCanvas *c9 = new TCanvas("c9","Skewness",200,10,500,300);
  TGraph* gr1 = new TGraph(5,B,s1);
  TGraph* gr2 = new TGraph(5,B,s2);
  TGraph* gr3 = new TGraph(5,B,s3);
  c7->cd();
  gr1->Draw();
  c8->cd();
  gr2->Draw();
  c9->cd();
  gr3->Draw();

  

}


/*********************************END**********************************/