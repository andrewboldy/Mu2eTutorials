#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>
#include <Math/Vector3D.h>
#include <string>
#include <fstream>
#include <iostream>


void TrkAnaTutorialPlotTrkMomentum()
{
  TChain* trkana = new TChain("TrkAna/trkana");

  ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBSignal.Tutorial_2024_03.list");
  if (input_filelist.is_open())
  {
    string filename;
    while(getline(input_filelist,filename))
    {
      trkana->Add(filename.c_str());
    }
    input_filelist.close();
  }

  cout << "Number of entries: " << trkana->GetEntries() << endl;

  TCanvas* c1 = new TCanvas("c1","c1");
  c1->SetGridx(true);
  c1->SetGridy(true);

  TH1D* hist = new TH1D("hist","",100,100,110);
  trkana->Draw("demfit.mom.R()>>hist","","HIST"); //utilizing the R() functions. Unsure wha this is, but will come back with more information; plot the magnitude of the momentum vector

  TH1D* hist2 = new TH1D("hist2","",100,100,110);
  trkana->Draw("demfit.mom.R()>>hist2", "demfit.sid==0", "HIST SAME"); //again utilizing R() function. now tracking only at one intersection by establishing a cut using the center argument; sid = surface id, sid=0 denotes the entrance to the tracker
  hist2->SetLineColor(kRed);

  TH1D* hist3= new TH1D("hist3","",100,100,110);
  trkana->Draw("demfit.mom.R()>>hist3","demfit.sid==0 && demlh.t0>=700", "HIST SAME"); //utilizing R() to make cuts at the entrance of the tracker and also at the time greater than 700 (ms?)
  hist3->SetLineColor(kGreen);

  TLegend* leg = new TLegend();
  leg->AddEntry(hist, "momentum  magnitude", "l");
  leg->AddEntry(hist2, "momentum magnitude at entrance", "l");
  leg->AddEntry(hist3, "momentum magnitude at entrance with t>700 (ms?)","l");
  leg->Draw();

  c1->Update();
  cout << "Saving canvas as trkMomentum.pdf" << endl;
  c1->SaveAs("trkMomentum.pdf");

  delete c1;
  delete hist;
  delete hist2;
  delete hist3;
}

