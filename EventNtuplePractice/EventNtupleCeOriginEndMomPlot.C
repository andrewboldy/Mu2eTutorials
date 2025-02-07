//EventNtuple Plotting Origin and End Conversion Electron Momenta (eventually with Varying cuts)
//Written by Andrew Boldy University of South Carolina
//Spring 2025

//All of my Inclusions
#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>
#include <Math/Vector3D.h>
#include <string>
#include <fstream>
#include <iostream>

bool DO_ELECTRON_ORIGIN_MOMENTUM = false;
bool DO_ELECTRON_END_MOMENTUM = true;

using namespace std;

void EventNtupleCeOriginEndMomPlot()
{
  if (DO_ELECTRON_ORIGIN_MOMENTUM==true)
  {
    TChain* ntuple = new TChain("EventNtuple/ntuple");

    ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBTriggered.MDC2020an_v06_01_01_best_v1_3.list");
    if (input_filelist.is_open())
    {
      string filename;
      while(getline(input_filelist,filename))
      {
        ntuple->Add(filename.c_str());
      }
      input_filelist.close();
    }

    cout << "Number of entries: " << ntuple->GetEntries() << endl;
    TCanvas* c1 = new TCanvas("c1","c1");
    c1->SetGridx(true);
    c1->SetGridy(true);

    TH1D* hist = new TH1D("hist","",100,100,110);
    ntuple->Draw("trkmcsim.mom.R()>>hist","","HIST"); //utilizing the R() functions. Unsure wha this is, but will come back with more information; plot the magnitude of the momentum vector

    TLegend* leg = new TLegend();
    leg->AddEntry(hist, "origin momentum of the SimParticle [MeV/c]", "l");
    leg->Draw();

    c1->Update();
    cout << "Saving canvas as originCeMomentum.pdf" << endl;
    c1->SaveAs("originCeMomentum.pdf");

    delete c1;
    delete hist;
  }

  if (DO_ELECTRON_END_MOMENTUM==true)
  {
    TChain* ntuple = new TChain("EventNtuple/ntuple");

    ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBTriggered.MDC2020an_v06_01_01_best_v1_3.list");
    if (input_filelist.is_open())
    {
      string filename;
      while(getline(input_filelist,filename))
      {
        ntuple->Add(filename.c_str());
      }
      input_filelist.close();
    }

    cout << "Number of entries: " << ntuple->GetEntries() << endl;
    TCanvas* c1 = new TCanvas("c1","c1");
    c1->SetGridx(true);
    c1->SetGridy(true);

    TH1D* hist = new TH1D("hist","",170,30,200);
    ntuple->Draw("trkmcsim.endmom.R()>>hist","","HIST"); //utilizing the R() functions. Unsure wha this is, but will come back with more information; plot the magnitude of the momentum vector

    TLegend* leg = new TLegend();
    leg->AddEntry(hist, "end momentumof the SimParticle [MeV/c]", "l");
    leg->Draw();

    c1->Update();
    cout << "Saving canvas as endCeMomentum.pdf" << endl;
    c1->SaveAs("endCeMomentum.pdf");

    delete c1;
    delete hist;
  }
}

