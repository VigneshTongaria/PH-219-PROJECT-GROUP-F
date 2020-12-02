


/*********************************************************************
  ___________________________________________________________
  | DEFINING THE FUNCTIONS FOR MEAN,VARIANCE AND SKEWNESS   |
  |_________________________________________________________|

*********************************************************************/
Double_t mean(Double_t *x, Int_t n)
{
    Double_t sum=0;
    for(int i=0;i<n;i++)
    {
        sum=sum+x[i];
	}
    return sum*1.0/n;
}
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
  Double_t s4[]={0.0,0.0,0.0,0.0,0.0};
  int n=5;

  for(int I=0;I<n;I++)
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
      cout<<"<pT>: "<<q1<<endl;
      cout<<"Intensive Variance of <pT>: "<<TMath::Sqrt(q2)/q1<<endl;
      cout<<"Standardised Skewness of <pT>: "<<q3/TMath::Power(q2,1.5)<<endl;
      cout<<"Intensive Skewness of <pT>: "<<q3*q1/TMath::Power(q2,2)<<endl;


      s1[I]=q1;
      s2[I]=TMath::Sqrt(q2)/q1;
      s3[I]=q3/TMath::Power(q2,1.5);
      s4[I]=q3*q1/TMath::Power(q2,2);

  }


  /*********************************************************************
  _____________________________________________
  |       DRAWING THE GRAPHS                  |
  |___________________________________________|
  
  *********************************************************************/


  TCanvas *c1 = new TCanvas("c1","Mean",200,10,500,300);
  TCanvas *c2 = new TCanvas("c2","Intensive Variance",200,10,500,300);
  TCanvas *c3 = new TCanvas("c3","Standardized Skewness",200,10,500,300);
  TCanvas *c4 = new TCanvas("c4","Intensive Skewness",200,10,500,300);
  TGraph* gr1 = new TGraph(5,B,s1);
  TGraph* gr2 = new TGraph(5,B,s2);
  TGraph* gr3 = new TGraph(5,B,s3);
  TGraph* gr4 = new TGraph(5,B,s4);


  gr1->SetMarkerStyle(20);
  gr1->SetMarkerColor(2);
  gr1->SetMarkerSize(2);
  gr1->SetLineWidth(3);
  gr1->SetLineStyle(1);
  gr1->SetMinimum(0);
  gr1->SetMaximum(TMath::MaxElement(n,gr1->GetY())*1.5);
  gr1->SetTitle("Mean pT");
  gr1->GetXaxis()->SetTitle("Multiplicity");
  gr1->GetYaxis()->SetTitle("<pT> (GeV/c)");


  gr2->SetMarkerStyle(21);
  gr2->SetMarkerColor(3);
  gr2->SetMarkerSize(2);
  gr2->SetLineWidth(3);
  gr2->SetLineStyle(7);
  gr2->SetLineColor(16);
  gr2->SetMinimum(0);
  gr2->SetMaximum(TMath::MaxElement(n,gr2->GetY())*1.5);
  gr2->SetTitle("Intensive Variance of pT");
  gr2->GetXaxis()->SetTitle("Multiplicity");
  gr2->GetYaxis()->SetTitle("Var(pT)");


  gr3->SetMarkerStyle(22);
  gr3->SetMarkerColor(4);
  gr3->SetMarkerSize(2);
  gr3->SetLineWidth(3);
  gr3->SetLineStyle(7);
  gr3->SetLineColor(16);
  gr3->SetMinimum(0);
  gr3->SetMaximum(TMath::MaxElement(n,gr3->GetY())*1.5);
  gr3->SetTitle("Standardized Skewness of pT");
  gr3->GetXaxis()->SetTitle("Multiplicity");
  gr3->GetYaxis()->SetTitle("Skewness(pT) (GeV/c)");
  

  gr4->SetMarkerStyle(29);
  gr4->SetMarkerColor(9);
  gr4->SetMarkerSize(2);
  gr4->SetLineWidth(3);
  gr4->SetLineStyle(7);
  gr4->SetLineColor(16);
  gr4->SetMinimum(0);
  gr4->SetMaximum(TMath::MaxElement(n,gr4->GetY())*1.5);
  gr4->SetTitle("Intensive Skewness of pT");
  gr4->GetXaxis()->SetTitle("Multiplicity");
  gr4->GetYaxis()->SetTitle("Skewness(pT)");



  /*********************************************************************
    _____________________________________________
    |   DEFINING THE LEGEND                     |
    |___________________________________________|

  *********************************************************************/



   TLegend *legend1 = new TLegend(0.6,0.7,0.9,0.9);
   legend1->SetHeader("Legend","C");
   legend1->AddEntry(gr1,"Graph for Mean vs Multiplicity","p");
   legend1->AddEntry(gr1,"Line joining the points","l");
   legend1->SetFillColor(kYellow-10);
   TLegend *legend2 = new TLegend(0.6,0.7,0.9,0.9);
   legend2->SetHeader("Legend","C");
   legend2->AddEntry(gr2,"Graph for Intensive Skewness vs Multiplicity","p");
   legend2->AddEntry(gr2,"Line joining the points","l");
   legend2->SetFillColor(kYellow-10);
   TLegend *legend3 = new TLegend(0.6,0.7,0.9,0.9);
   legend3->SetHeader("Legend","C");
   legend3->AddEntry(gr3,"Graph for Standardized Skewness vs Multiplicity","p");
   legend3->AddEntry(gr3,"Line joining the points","l");
   legend3->SetFillColor(kYellow-10);
   TLegend *legend4 = new TLegend(0.6,0.7,0.9,0.9);
   legend4->SetHeader("Legend","C");
   legend4->AddEntry(gr4,"Graph for Intensive Skewness vs Multiplicity","p");
   legend4->AddEntry(gr4,"Line joining the points","l");
   legend4->SetFillColor(kYellow-10);


  c1->cd();
  gr1->Draw("APL");
  legend1->Draw();
  c2->cd();
  gr2->Draw("APL");
  legend2->Draw();
  c3->cd();
  gr3->Draw("APL");
  legend3->Draw();
  c4->cd();
  gr4->Draw("APL");
  legend4->Draw();

  

}


/*********************************END**********************************/