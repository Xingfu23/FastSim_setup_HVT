#include <string>

void Draw_Photon_DeltaEta(){
	auto c1 = new TCanvas("c1", "c1", 800, 600);
	auto leg3 = new TLegend(0.58, 0.7, 0.9, 0.9);
	//leg3->SetNColumns(2);

	string s1 = "output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_";
	for(int fileno = 0; fileno < 4; fileno++){
		
		float a = 2.0 + fileno;
		string s2 = Form("%.1fTeV_2.root", a);
		string filename = s1 + s2;
		
		TFile *file = new TFile(filename.c_str());
		TTree *Photontree;
		file->GetObject("Photontree", Photontree);
		
		double DeltaEta_Photons;
		Photontree->SetBranchAddress("DeltaEta_Photons", &DeltaEta_Photons);

		TH1D *P = new TH1D(Form("P%d", fileno)," ", 50, 0., 10.);
		P->SetStats(0);     
		P->SetLineWidth(3);
		P->GetXaxis()->SetTitle("#Delta#eta(#gamma, #gamma)");
		P->GetYaxis()->SetTitle("Entries (Normalized)");
		P->GetYaxis()->SetTitleOffset(1.3);
		
		for(int evt_entry=0; evt_entry<Photontree->GetEntries(); evt_entry++){
			Photontree->GetEntry(evt_entry);
			P->Fill(DeltaEta_Photons);
		}
		double norm = P->GetEntries();
		P->Scale(1./norm);

		if(fileno < 2){
			P->SetLineColor(1 + fileno);
		}
		else if(fileno == 2){
			P->SetLineColor(4);
		}
		else{
			P->SetLineColor(6);
		}
		P->SetMaximum(0.7);
		P->SetMinimum(0.);
		P->Draw("hist, same");
		
		leg3->AddEntry(P, Form("W'= %.1fTeV", a), "f");
	}
	leg3->Draw();
}

