#include <vector>
void Draw_Event_Number_Pt_cut_6(){
	auto c1 = new TCanvas("c1", "c1");
	c1->SetGrid();
	
	vector<double> Pt;
	for(int entry = 0; entry < 21; entry++){
		Pt.push_back(entry*50.);
	}
	
	//background1: WGToLNuG_01Jet_LO_MLM
	vector<double> y1 = {1616.67, 71.527, 43.095, 11.757, 2.8282, 0.5222, 0.522, 0.4409, 0.4409, 0.2242, 0.0616, 0.0616, 0.0244, 0.0244, 0.0151, 0.0040, 0.0040, 0.0040, 0.0040, 0.0040, 0.0040 }; 
	//background2: WGToLNu2G_01Jet_LO_MLM
	vector<double> y2 = {23.371, 7.8368, 0.06964, 0.06121, 0.05436, 0.01215, 0.00169, 0.00128, 0.00117, 0.00108,  0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
	//background3: WH_HToGammagamma_WToLNu
	vector<double> y3 = {5.9882, 4.8717, 2.7923, 1.5438, 0.8397, 0.4625, 0.2953, 0.2367, 0.1225, 0.05484, 0.03895, 0.02491, 0.01689, 0.01122, 0.00792, 0.00541, 0.00375, 0.00265, 0.00191, 0.00138, 0.00101};
	
	int n = Pt.size();
	THStack *hs = new THStack("hs", "The SM background Event left after different dipoton P_{T} cut; DiPhoton P_{T} cut(GeV); Event number");
	TH1* LNu1G = new TH1D("LNu1G", "LNu1G", n, 0., 1000.);
	TH1* LNu2G = new TH1D("LNu2G", "LNu2G", n, 0., 1000.);
	TH1* HTo2G = new TH1D("HTo2G", "HTo2G", n, 0., 1000.);

	for(int point_N=0; point_N<n; point_N++){ 
		LNu1G->Fill(Pt[point_N], y1[point_N]);
		LNu2G->Fill(Pt[point_N], y2[point_N]);
		HTo2G->Fill(Pt[point_N], y3[point_N]);
	}

	LNu1G->SetFillColor(38);
	LNu2G->SetFillColor(2);
	HTo2G->SetFillColor(8);
	hs->Add(LNu2G);
	hs->Add(LNu1G);
	hs->Add(HTo2G);
	


	c1->SetLogy();      
	hs->SetMinimum(0.005);      
	hs->SetMaximum(10000.0);
	hs->Draw("hist");
	hs->GetXaxis()->SetRangeUser(0.,950.);

	auto legend = new TLegend(0.65, 0.7, 0.9, 0.9);
	legend->AddEntry(LNu1G, "W+#gamma+jet", "f");
	legend->AddEntry(LNu2G, "W+2#gamma+jet", "f");
	legend->AddEntry(HTo2G, "W+higgs, H->#gamma#gamma", "f");
	legend->Draw();
	
	c1->Update();
	c1->SaveAs("plot/event_plot_2.pdf");

}
