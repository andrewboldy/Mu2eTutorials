//TrkAnaTutorial Plotting Detected Conversion Electron Momenta with Varying cuts
//Written by Andrew Boldy University of South Carolina
//Spring 2025

//all of my inclusions
#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>
#include <Math/Vector3D.h>
#include <string>
#include <fstream>
#include <iostream>

bool DO_ELECTRON_MOMENTUM = true;

using namespace std;

void TrkAnaTutorialPlotTrkMomentum()
{
  if (DO_ELECTRON_MOMENTUM==true)
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
    hist->SetLineColor(kBlue);

    TH1D* hist2 = new TH1D("hist2","",100,100,110);
    trkana->Draw("demfit.mom.R()>>hist2", "demfit.sid==0", "HIST SAME"); //again utilizing R() function. now tracking only at one intersection by establishing a cut using the center argument; sid = surface id, sid=0 denotes the entrance to the tracker
    hist2->SetLineColor(kRed);

    TH1D* hist3= new TH1D("hist3","",100,100,110);
    trkana->Draw("demfit.mom.R()>>hist3","demfit.sid==0 && demlh.t0>=700", "HIST SAME"); //utilizing R() to make cuts at the entrance of the tracker and also at the time greater than 700 (ms?)
    hist2->SetLineColor(kGreen);

    TLegend* leg = new TLegend();
   leg->AddEntry(hist, "e- momentum  magnitude (MeV/c)", "l");
   leg->AddEntry(hist2, "e- momentum magnitude at entrance (MeV/c)", "l");
   leg->AddEntry(hist3, "e- momentum magnitude at entrance (MeV/c) with t>700 (ns)","l"); //selects specifically the data from the entrance and cuts electron momenta that appear before the selection region at 700ns
   leg->Draw();

    c1->Update();
    cout << "Saving canvas as eTrkMomentum.pdf" << endl;
    c1->SaveAs("eTrkMomentum.pdf");

    delete c1;
    delete hist;
    delete hist2;
    delete hist3;
  }
}
