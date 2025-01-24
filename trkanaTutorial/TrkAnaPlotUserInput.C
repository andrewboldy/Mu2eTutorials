//TrkAnaPlotUserInput by Andrew Boldy
//Attempt at having user input to change and modify the output files for given data.

//all of my inclusions
#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>
#include <Math/Vector3D.h>
#include <string>
#include <fstream>
#include <iostream>

void TrkAnaPlotUserInput()
{
  string particleName;
  int secondCutoff;
  int surfaceID;
  string YorN;
  bool namePass = false;
  cout << "Welcome to the TrkAna Plotter!" << endl;
  while (namePass == false)
  {
    bool responsePass = false;
    cout << "What type of particle are you looking to see a plot for?";
    cin >> particleName;
    while (responsePass == false)
    {
      cout << "You wrote: " << particleName << ". Is this correct? Type y or n." << endl;
      cin >> YorN;
      if (YorN == "y")
      {
        namePass = true;
        responsePass = true;
      }
      else if (YorN == "n")
      {
        cout << "Try again.";
        namePass = false;
	responsePass = true;
      }
      else
      {
        cerr << "Invalid response.";
        responsePass = false;
      }
    }
    cout << "Complete" << endl;
  }
}
