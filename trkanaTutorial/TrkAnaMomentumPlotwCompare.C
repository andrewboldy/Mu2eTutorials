//all of my inclusions
#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>
#include <Math/Vector3D.h>
#include <string>
#include <fstream>
#include <iostream>

bool DO_ELECTRON_MOMENTUM = false;
bool DO_ELECTRON_ORIGIN_MOMENTUM_COMP = true;
bool DO_POSITRON_MOMENTUM = false;
bool DO_POSITRON_ORIGIN_MOMENTUM = false;

using namespace std;

void TrkAnaMomentumPlotwCompare()
{
  if (DO_ELECTRON_MOMENTUM==true)
  {
    TChain* trkana = new TChain("TrkAna/trkana");

    ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BB.MDC2020s_perfect_v1_0_td_v01_01_00.list");
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
  if (DO_POSITRON_MOMENTUM==true)
  {
    TChain* trkana = new TChain("TrkAna/trkana");

    ifstream input_filelist("filelists/nts.mu2e.CePlusEndpointMix1BB.MDC2020s_perfect_v1_0_std_v01_01_00.list");
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
    hist2->SetLineColor(kGreen);

    TLegend* leg = new TLegend();
   leg->AddEntry(hist, "e+ momentum  magnitude (MeV/c)", "l");
   leg->AddEntry(hist2, "e+ momentum magnitude at entrance (MeV/c)", "l");
   leg->AddEntry(hist3, "momentum magnitude at entrance (MeV/c) with t>700 (ns)","l");
   leg->Draw();

    c1->Update();
    cout << "Saving canvas as ePlusTrkMomentum.pdf" << endl;
    c1->SaveAs("ePlusTrkMomentum.pdf");

    delete c1;
    delete hist;
    delete hist2;
    delete hist3;
  }

  if (DO_ELECTRON_ORIGIN_MOMENTUM_COMP==true)
  {
    TChain* trkana = new TChain("EventNtuple/ntuple"); //building a TChain from the directories TrkAnaNeg/trkana for a given file in the filelist
    int fileNumber = 0;
    ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBTriggered.MDC2020an_v06_01_01_best_v1_3.list");
    if (input_filelist.is_open())
    {
      string filename;
      while(getline(input_filelist,filename))
      {
        trkana->Add(filename.c_str());
        fileNumber=fileNumber+1;
      }
      input_filelist.close();
    }
    string fileNumberString = to_string(fileNumber);
    cout << "Number of files analyzed: " << fileNumberString << endl;
    //cout << "Number of total entries: " << trkana->GetEntries() << endl;
    TCanvas* c1 = new TCanvas("c1","c1");
    c1->SetGridx(true);
    c1->SetGridy(true);

    //branch 100 has trkmcsim --> need to determine where the start momentum and momentum are labeled. Says it takes info from SimInfo--> check code maybe
    //Feb 6th, 2025--> Only producing a localization around the 104.9 MeV peak. Need to correct and understand what is happening here.
    TH1D* hist = new TH1D("hist","",100,100,110);
    trkana->Draw("trkmcsim.mom.R()>>hist","","HIST"); //utilizing the R() functions. plots magnitude of momentum vector for detected electrons //

    TH1D* hist2 = new TH1D("hist2","",100,100,110);
    trkana->Draw("trkmcsim.endmom.R()>>hist2", "", "HIST SAME"); //again utilizing R() function. now plotting the thrown
    hist2->SetLineColor(kRed);

    //TH1D* hist3= new TH1D("hist3","",100,100,110);
    //float comparison = demfit.mom.R()/demmcsim.omom.R();
    //trkana->Draw(comparison,"", "HIST SAME"); //utilizing R() to plot the comparison histogram
    //hist3->SetLineColor(kGreen);

    TLegend* leg = new TLegend();
   leg->AddEntry(hist, "origin momentumof the SimParticle [MeV/c]", "l");
   leg->AddEntry(hist2, "end momentumof the SimParticle [MeV/c]", "l");
   //leg->AddEntry(hist3, "measured e- momentum / origin e- momentum","l"); //selects specifically the data from the entrance and cuts electron momenta that appear before the selection region at 700ns
   leg->Draw();

    c1->Update();
    cout << "Saving canvas as eTrkMomOComp.pdf" << endl;
    c1->SaveAs("eTrkMomOComp.pdf");

    delete c1;
    delete hist;
    delete hist2;
    //delete hist3;
  }
}

