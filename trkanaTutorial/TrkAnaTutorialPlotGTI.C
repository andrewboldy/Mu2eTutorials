#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <string>
#include <fstream>
#include <iostream>

void TrkAnaTutorialPlotGTI()
{

  TChain* trkana = new TChain("TrkAna/trkana"); //creating a TChain that we can iterate over to plot from various different trk files

  ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBSignal.Tutorial_2024_03.list"); //opening up the file list to pull strings and add to the the filenames
  if (input_filelist.is_open()) //checking to mkae sure the filelist is open
  {
    string filename; //create a string we are calling filename
    while(getline(input_filelist,filename)) //go through each line and assign it a filename
    {
      trkana->Add(filename.c_str()); //add the filename string to the chain we are calling trkana
    }
    input_filelist.close(); //close the filelist to prevent leakage
  }

  //Creating the TCanvas to plot our data onto
  TCanvas* c1 = new TCanvas("c1","c1"); //TCanvas pointer setup to map to a new canvas we are calling c1 TCanvas(name,title)
  c1->SetGridx(true); //giving the canvas an x grid
  c1->SetGridy(true);  //giving the canvas a y grid

  TH1D* hist = new TH1D("hist","hist",100,0,100); //creating a new histogram object (name, binNumber,lowBinEdge,highBinEdge)
  TH1D* hist2 = new TH1D("hist2","hist2",100,0,100); //create the second histogram object that will be utilizing the actives
  trkana->Draw("dem.nhits>>hist","","goff"); //drawing the data from trkana to the canvas
  trkana->Draw("dem.nactive>>hist2", "", "goff"); //draw the second historgram to be the "Active"
  hist->GetXaxis()->SetTitle("Number of Hits"); //setting the x axis label
  hist->GetYaxis()->SetTitle("Number of Tracks"); //setting the y axis label

  hist->Draw("HIST");
  hist2->SetLineColor(kRed);
  hist2->Draw("HIST SAME");

  TLegend* leg = new TLegend();
  leg->AddEntry(hist, "total number of hits", "l");
  leg->AddEntry(hist2, "total number of active hits", "l");
  leg->Draw();

  trkana->Draw("dem.nactive>>hist3", "tcnt.ndem==2", "goff");

  c1->SaveAs("globalOutput.pdf");
}

