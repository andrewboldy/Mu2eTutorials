//ParticleInfoPrinterRooUtilTest
//Spring 2025
//Written by Andrew Boldy
//University of South Carolina

//my inclusions
#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <string>
#include <fstream>
#include <iostream>

//Include RooUtil
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

//Include SimInfo //did not change the error message that occured without it, but still think it could be useful to have this inclusion
//#include "EventNtuple/inc/SimInfo.hh"


void ParticleInfoPrinterRooUtilTest(string filename)
{
  //Initialize RooUtil which takes in a filename
  RooUtil util(filename);

  //Print out expectation of events to console
  int eventNumber = util.GetNEvents(); //create the number of events from the file
  cout << filename << " has " << eventNumber << " events." << endl; //Print out number of events to console

    //Attempt number 3: attampt to follow the example more closely
  for (int i_event=0; i_event < eventNumber;i_event++)
  {
  const auto& event = util.GetEvent(i_event);
  if (event.trkmcsim != nullptr)
  {
    for (const auto& trkmcsim : *(event.trkmcsim))
    {
      cout << "New Track!" << endl;
      for (const auto& sim : trkmcsim)
      {
	//if (sim.nhits >=0 && sim.pdg != 11 && sim.pdg !=2212 && sim.pdg != 1000010020 && sim.pdg != -11)
	//{	
        cout << "Entry Number: " << i_event
             << " PDG Number: " << sim.pdg
             << " Tracker Hits: " << sim.nhits
             << " Process Code: " << sim.startCode
             << " Rank: " << sim.rank << endl;
          //if want to manually print these out in the console, open the file in root, then enter the tree and use the scan feature-> ntuple->Scan("trkmcsim.pdg:trkmcsim.nhits:trkmcsim.startCode:trkmcsim.rank"
	//}
	}
    }
  }
  }
}
