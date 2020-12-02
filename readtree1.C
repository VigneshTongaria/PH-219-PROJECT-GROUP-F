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






/*
*   VARIABLES USED:
*   
    ╔══════════╤════════════════╤══════════╤═══════════════════════════════════════════════════════════════════════╗
    ║ VARIABLE │   DATA TYPE    │   SIZE   │                              DESCRIPTION                              ║
    ╠══════════╪════════════════╪══════════╪═══════════════════════════════════════════════════════════════════════╣
    ║    A     │   char array   │   5*15   │                       Stores the names of trees                       ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    B     │ Double_t array │    5     │                Stores the x-axis values for the graphs                ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    s1    │                │          │                         Stores the Mean of pT                         ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────────────────╢
    ║    s2    │                │          │                  Stores the Intensive Variance of pT                  ║
    ╟──────────┤ Double_t array │    5     ├───────────────────────────────────────────────────────────────────────╢
    ║    s3    │                │          │                 Stores the Standardized Skewess of pT                 ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────────────────╢
    ║    s4    │                │          │                  Stores the Intensive Skewness of pT                  ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    n     │      int       │    -     │            Stores the number of elements on the x-axis, 5             ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    I     │      int       │    -     │                    Loop index for array A of trees                    ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    f     │     TFile*     │    -     │                 Stores the file name of the ROOT file                 ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║   tree   │     TTree*     │    -     │                        Stores the current tree                        ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║ entries  │     Int_t      │    -     │              Total number of entries in the current tree              ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║ maxTrack │     Int_t      │    -     │       Maximum size of array containing pT for each event, 10000       ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║  ntrack  │     Int_t      │    -     │                  Number of data points in each event                  ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    pT    │ Double_t array │ maxTrack │              Array for Transverse Momentum of each event              ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    NT    │ Double_t array │ entries  │              Array of ntrack corresponding to each event              ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    q1    │    Double_t    │    -     │                  Stores mean of mean of pT (<<pT>>)                   ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    q2    │    Double_t    │    -     │              Stores <del pi del pj> = <(<pT>-<<pT>>)^2>               ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    q3    │    Double_t    │    -     │           Stores <del pi del pj del pk> = <(<pT>-<<pT>>)^3>           ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║  ntrks   │     Int_t      │    -     │            Temporarily stores ntrack for the current event            ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    ii    │      int       │    -     │                         Loop index for events                         ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║    c1    │                │          │         Canvas for Graph of Mean of pT vs Multiplicity Class          ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────────────────╢
    ║    c2    │                │          │  Canvas for Graph of Intensive Variance of pT vs Multiplicity Class   ║
    ╟──────────┤    TCanvas*    │    -     ├───────────────────────────────────────────────────────────────────────╢
    ║    c3    │                │          │ Canvas for Graph of Standardized Skewness of pT vs Multiplicity Class ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────────────────╢
    ║    c4    │                │          │  Canvas for Graph of Intensive Skewness of pT vs Multiplicity Class   ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║   gr1    │                │          │               Graph of Mean of pT vs Multiplicity Class               ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────────────────╢
    ║   gr2    │                │          │        Graph of Intensive Variance of pT vs Multiplicity Class        ║
    ╟──────────┤    TGraph*     │    -     ├───────────────────────────────────────────────────────────────────────╢
    ║   gr3    │                │          │      Graph of Standardized Skewness of pT vs Multiplicity Class       ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────────────────╢
    ║   gr4    │                │          │        Graph of Intensive Skewness of pT vs Multiplicity Class        ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────────────────╢
    ║ legend1  │                │          │                         Legend for Graph gr1                          ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────────────────╢
    ║ legend2  │                │          │                         Legend for Graph gr2                          ║
    ╟──────────┤    TLegend*    │    -     ├───────────────────────────────────────────────────────────────────────╢
    ║ legend3  │                │          │                         Legend for Graph gr3                          ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────────────────╢
    ║ legend4  │                │          │                         Legend for Graph gr4                          ║
    ╚══════════╧════════════════╧══════════╧═══════════════════════════════════════════════════════════════════════╝

*   
*/









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

  TFile *f=new TFile("13TeV_CR0_RHoff.root");
  for(int I=0;I<n;I++)
  {      
      TTree *tree = (TTree*)f->Get(A[I]);
      Int_t entries = tree->GetEntries();

      const Int_t maxTrack=10000;




  /*********************************************************************
    _____________________________________________
    |   INITIALISING THE CORRESPONDING ARRAYS,  |
    |        AND TREES                          |
    |___________________________________________|

  *********************************************************************/
   
  Int_t ntrack = 0;
  Double_t pT[maxTrack];
  Double_t NT[entries];


  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("pT",&pT);


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
  |       DEFINING THE GRAPHS                 |
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


  /*********************************************************************
  _____________________________________________
  |       DRAWING THE GRAPHS                  |
  |___________________________________________|
  
  *********************************************************************/


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