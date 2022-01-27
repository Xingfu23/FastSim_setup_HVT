#include <iostream>
#include <TCanvas.h>
#include <TObject.h>
#include <TROOT.h>
#include <TPaveText.h>
#include <TLatex.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <THStack.h>
#include <TLegend.h>
#include <string>
#include "Math/GenVector/PtEtaPhiE4D.h"
#include "Math/GenVector/LorentzVector.h"
//#include <TLorentzVector.h>
#include <vector>
#include <math.h>

using Position4_t = ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double>>;
using namespace std;

double DeltaR(Position4_t a, Position4_t b){
	double delta_phi = abs(a.Phi()-b.Phi());
	if (delta_phi > M_PI) delta_phi = 2*M_PI - delta_phi;
	double delta_eta = abs(a.Eta()-b.Eta());
	return sqrt(pow(delta_phi, 2)+pow(delta_eta, 2));
}


int main(){
// Reading all output file from different type of background.
// Booking vector to store cross section and event number inside the signal region.
//-------------------------------------------------------------------------------------------------------------
	vector<string> Background_list ={
		"output_Delphes_BKG_WH_HToGammagamma_WToLNu_",
		"output_Delphes_BKG_WGToLNu2G_01Jet_",
		"output_Delphes_BKG_WGToLNuG_01Jet_"
	};
	string Extension = ".root";
	vector<string> Background_SMHiggs_bin = {"0_20", "20_50", "50_100", "100_200", "200_300", "300_500", "500_700", "700_1000", "1000_1500", "1500_2000", "2000_Inf"};
	vector<double> X_section_background_SMHiggs = {17.712, 66.322, 90.714, 53.4, 8.8248, 2.6878, 0.32276, 0.072596, 0.011496, 0.00075278, 0.000070368};
	//vector<double> X_section_background_Wplus2G = {0.31574, 1.304, 2.3416, 1.9512, 0.52676, 0.24438, 0.041682, 0.011466, 0.0021374, 0.00015578, 0.000015414};
	//vector<double> X_section_background_WplusG  = {2045500, 20835, 2086.6, 579.82, 88.574, 30.282, 4.1138, 0.99372, 0.16674, 0.01128, 0.0010616};
	vector<double> X_section_background_Wplus2G = {216.746577, 322.769745, 82.313722, 26.020894, 4.518776, 1.695359, 0.256877, 0.065357, 0.011846, 0.000801, 0.000046};
	vector<double> X_section_background_WplusG  = {88161.0579, 95526.2998, 6949.6529, 1412.5587, 182.8000, 58.0493, 7.5072, 1.7777, 0.2925, 0.0020, 0.0018};
	vector<double> WPrimeMass_V = {2000., 3000., 4000., 5000.};
	vector<vector<double> > X_section;
	X_section.push_back(X_section_background_SMHiggs);
	X_section.push_back(X_section_background_Wplus2G);
	X_section.push_back(X_section_background_WplusG);
	vector<double> Event_left_SR_SMHiggs;
	vector<double> Event_left_SR_Wplus2G;
	vector<double> Event_left_SR_WplusG;
	double Total_input_entry = 50000.;
	double Luminosity = 1.;
	double Higgs_decay_BR = 0.00227;
	double Scale_factor_Higgs = 1.853364092;
//-------------------------------------------------------------------------------------------------------------
// Finding How many events left in signal region after putting photon pair Pt cut, here we define siganl region is diphoton mass between 120 and 130GeV.
//------------------------------------------------------------------------------------------------------------- 
	// Reading input file
	double signal_region_L = 120.;
	double signal_region_U = 130.;
	int vectorsize_Background_SMHiggs_bin = Background_SMHiggs_bin.size();
	int Entry_No_Inside_SR;
	double Event_No_Inside_SR;
	double Offline_DiPhoton_Pt_cut;
	// Select Background file and reading file name, next we setting up offline diphoton Pt cut for each bin of background file
	for (int file_type = 0; file_type < Background_list.size(); file_type++){
	//for (int file_type = 0; file_type < 1; file_type++){
		string bkg_type = Background_list[file_type];
		for (int cut_no = 0; cut_no < WPrimeMass_V.size(); cut_no++){
			
			Offline_DiPhoton_Pt_cut = WPrimeMass_V[cut_no]/3;
			cout << "The offline diphoton pt cut is: " << Offline_DiPhoton_Pt_cut << endl;
			
			for (int fileno = 0; fileno < Background_SMHiggs_bin.size(); fileno++){
				string filename = bkg_type + Background_SMHiggs_bin[fileno] + Extension;
				TFile *file     = new TFile(filename.c_str());
				TTree *Tree_Photon;
				file->GetObject("Tree_Photon", Tree_Photon);
				
				int PhotonNumber;
				int LeptonNumber;
				double LeadingPhotonPt;
				double LeadingPhotonEta;
				double LeadingPhotonPhi;
				double LeadingPhotonEnergy;
				double SubleadingPhotonPt;
				double SubleadingPhotonEta;
				double SubleadingPhotonPhi;
				double SubleadingPhotonEnergy;
				Tree_Photon->SetBranchAddress("PhotonNumber", &PhotonNumber);
				Tree_Photon->SetBranchAddress("LeptonNumber", &LeptonNumber);
				Tree_Photon->SetBranchAddress("LeadingPhotonPt", &LeadingPhotonPt);
				Tree_Photon->SetBranchAddress("LeadingPhotonEta", &LeadingPhotonEta);
				Tree_Photon->SetBranchAddress("LeadingPhotonPhi", &LeadingPhotonPhi);
				Tree_Photon->SetBranchAddress("LeadingPhotonEnergy", &LeadingPhotonEnergy);
				Tree_Photon->SetBranchAddress("SubleadingPhotonPt", &SubleadingPhotonPt);
				Tree_Photon->SetBranchAddress("SubleadingPhotonEta", &SubleadingPhotonEta);
				Tree_Photon->SetBranchAddress("SubleadingPhotonPhi", &SubleadingPhotonPhi);
				Tree_Photon->SetBranchAddress("SubleadingPhotonEnergy", &SubleadingPhotonEnergy);
				
				// Finding the the event number inside the signal region under specific photon pair Pt restriction
				// Loop all over events
				for (int evt_entry = 0; evt_entry<Tree_Photon->GetEntries(); evt_entry++){
					Tree_Photon->GetEntry(evt_entry);
					Position4_t a1, a2;
					a1.SetCoordinates(LeadingPhotonPt , LeadingPhotonEta , LeadingPhotonPhi , LeadingPhotonEnergy);
					a2.SetCoordinates(SubleadingPhotonPt , SubleadingPhotonEta , SubleadingPhotonPhi , SubleadingPhotonEnergy);
					if ((a1+a2).Pt() < Offline_DiPhoton_Pt_cut) continue;
					double DiPhoton_Mass = (a1+a2).M();
					double DiPhoton_DeltaR = DeltaR(a1, a2);
					if (DiPhoton_Mass > signal_region_L && DiPhoton_Mass < signal_region_U && DiPhoton_DeltaR>=0.15){
						Entry_No_Inside_SR += 1;
					}
				}
				// Calculating and store event number in signal region
				cout << "Total entry left in " << filename << " is: " << Entry_No_Inside_SR << endl;
				double Efficiency = Entry_No_Inside_SR/Total_input_entry;
				double Weighted_Event_No_Left;
				if (file_type == 0){
					Weighted_Event_No_Left = X_section[file_type][fileno]*Higgs_decay_BR*Efficiency*Scale_factor_Higgs*Luminosity;
				}
				else{
					Weighted_Event_No_Left = X_section[file_type][fileno]*Efficiency*Luminosity;
				}
				
				Event_No_Inside_SR += Weighted_Event_No_Left;
				Entry_No_Inside_SR = 0.;
				Weighted_Event_No_Left = 0.;
			}
			// Fill the event number left inside the signal region
			// File Type number is represent different background: 
			// 0 means SMHiggs VH process
			// 1 means ZPlus2Gamma
			// 2 means ZPlusGamma
			if (file_type == 0) Event_left_SR_SMHiggs.push_back(Event_No_Inside_SR);
			else if (file_type == 1) Event_left_SR_Wplus2G.push_back(Event_No_Inside_SR);
			else if (file_type == 2) Event_left_SR_WplusG.push_back(Event_No_Inside_SR);
			
			cout << "Total Event Number in SR: " << Event_No_Inside_SR << endl;
			cout << "==============================================================" << endl;
			Event_No_Inside_SR = 0.;
		}
	}
//-------------------------------------------------------------------------------------------------------------
// Booking Stack histogram for each SM background
//------------------------------------------------------------------------------------------------------------- 
	auto c1 = new TCanvas("c1", "c1");
	c1->SetLogy();
	THStack *hs = new THStack("hs", " ;p_{t}^{#gamma#gamma} cut(GeV); #sigma [fb]");
	vector<double> Offline_DiPhoton_Pt_cut_bin = {0., 100., 200., 300., 400., 500., 600., 700., 800., 900., 1000.};
	int Offline_DiPhoton_Pt_cut_bin_binsize = Offline_DiPhoton_Pt_cut_bin.size();
	
	TH1* SMHiggs_histo = new TH1D("SMHiggs_histo", "SMHiggs_histo", Offline_DiPhoton_Pt_cut_bin_binsize, 0., 1100.);
	TH1* Wplus2G_histo = new TH1D("Wplus2G_histo", "Wplus2G_histo", Offline_DiPhoton_Pt_cut_bin_binsize, 0., 1100.);
	TH1* WplusG_histo  = new TH1D("WplusG_histo" , "WplusG_histo" , Offline_DiPhoton_Pt_cut_bin_binsize, 0., 1100.);
	for (int entry = 0; entry < Offline_DiPhoton_Pt_cut_bin_binsize; entry++){
		SMHiggs_histo->Fill(Offline_DiPhoton_Pt_cut_bin[entry], Event_left_SR_SMHiggs[entry]);
		Wplus2G_histo->Fill(Offline_DiPhoton_Pt_cut_bin[entry], Event_left_SR_Wplus2G[entry]);
		WplusG_histo ->Fill(Offline_DiPhoton_Pt_cut_bin[entry], Event_left_SR_WplusG[entry]);
	}
	
	SMHiggs_histo->SetFillColor(kYellow);
	Wplus2G_histo->SetFillColor(kGreen+2);
	WplusG_histo->SetFillColor(kAzure-2);
	hs->Add(WplusG_histo);
	hs->Add(Wplus2G_histo);
	hs->Add(SMHiggs_histo);
	hs->SetHistogram(new TH1D("hstot"," ", Offline_DiPhoton_Pt_cut_bin_binsize, 0., 1100.));
	hs->GetHistogram()->SetStats(0);
	hs->GetHistogram()->GetXaxis()->SetLabelSize(0.035);
	hs->GetHistogram()->GetXaxis()->SetTitleOffset(1.1);
	hs->GetHistogram()->GetYaxis()->SetLabelSize(0.035);
	hs->GetHistogram()->GetYaxis()->SetTitleSize(0.04);
	hs->GetHistogram()->GetYaxis()->SetTitleOffset(1.05);
	hs->SetMinimum(0.001);
	hs->SetMaximum(100);
	hs->Draw("hist");
	
	auto legend  = new TLegend(0.6, 0.6, 0.85, 0.8);
	legend->AddEntry(SMHiggs_histo, "SM Higgs, H#rightarrow#gamma#gamma", "f");
	legend->AddEntry(WplusG_histo, "W + #gamma + jet", "f");
	legend->AddEntry(Wplus2G_histo, "W + 2#gamma + jet" , "f");
	legend->SetTextSize(0.035);
	legend->SetBorderSize(0);
	legend->Draw();
	TLatex latex1;
	latex1.SetNDC(true);
	latex1.SetTextSize(0.035);
	latex1.DrawLatex(.10, .91, "MadGraph+Pythia+Delphes");
	latex1.SetTextSize(0.03);
	latex1.DrawLatex(.13, .86, "Event left in 120 GeV < M_{#gamma#gamma} < 130 GeV");
	c1->SaveAs("EventNo_inSR_T.pdf");
	/*
	// Checking Vector contents
	for (auto i = Event_left_SR_Zplus2G.begin(); i != Event_left_SR_Zplus2G.end(); i++){
		cout << "Event inside SR, Zplus2G: " << *i << " " << endl;
	}
	*/
}
