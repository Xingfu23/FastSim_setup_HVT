 void Draw_Photon_DeltaR(){
	
	auto c1 = new TCanvas("c1","c1",800,600);    
	auto leg3 = new TLegend(0.58, 0.7, 0.9, 0.9);

	TFile* b1 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_1.0TeV_2.root");
	TH1F* h1 = (TH1F*) b1->Get("DeltaR_DiPhoton");                            

	TFile* b2 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_1.5TeV_2.root");
	TH1F* h2 = (TH1F*) b2->Get("DeltaR_DiPhoton");                            

	TFile* b3 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_2.0TeV_2.root");
	TH1F* h3 = (TH1F*) b3->Get("DeltaR_DiPhoton"); 

	TFile* b4 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_2.5TeV_2.root");
	TH1F* h4 = (TH1F*) b4->Get("DeltaR_DiPhoton");                       

	TFile* b5 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_3.0TeV_2.root");
	TH1F* h5 = (TH1F*) b5->Get("DeltaR_DiPhoton");

	TFile* b6 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_3.5TeV_2.root");
	TH1F* h6 = (TH1F*) b6->Get("DeltaR_DiPhoton");                       

	TFile* b7 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_4.0TeV_2.root");
	TH1F* h7 = (TH1F*) b7->Get("DeltaR_DiPhoton");

	TFile* b8 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_4.5TeV_2.root");
	TH1F* h8 = (TH1F*) b8->Get("DeltaR_DiPhoton");                            

	TFile* b9 = new TFile("output_deltaR_HVT_QQToWpToNuL2gamma_Wprime_5.0TeV_2.root");
	TH1F* h9 = (TH1F*) b9->Get("DeltaR_DiPhoton");                            
	
	double norm1 = h1->GetEntries();
	h1->SetLineWidth(3);
	h1->SetLineColor(2);
	h1->Scale(1./norm1);
	h1->SetStats(0);                                    
	h1->SetTitle(" ");                                  
	h1->GetXaxis()->SetTitle("#DeltaR(#gamma, #gamma)");
	h1->GetXaxis()->SetRangeUser(0., 4.);               
	h1->GetYaxis()->SetTitle("Entries");                
	h1->GetYaxis()->SetTitleOffset(1.3);
	h1->SetMaximum(1.);
	h1->SetMinimum(0.);
	h1->Draw();
	
	double norm2 = h2->GetEntries();
	h2->SetLineWidth(3);
	h2->SetLineColor(97);
	h2->Scale(1./norm2);
	//h2->Draw("same");

	double norm3 = h3->GetEntries();
	h3->SetLineWidth(3);
	h3->SetLineColor(94);
	h3->Scale(1./norm3);
	h3->Draw("same");
	
	double norm4 = h4->GetEntries();
	h4->SetLineWidth(3);
	h4->SetLineColor(91);
	h4->Scale(1./norm4);
	//h4->Draw("same");

	double norm5 = h5->GetEntries();
	h5->SetLineWidth(3);
	h5->SetLineColor(86);
	h5->Scale(1./norm5);
	h5->Draw("same");

	double norm6 = h6->GetEntries();
	h6->SetLineWidth(3);
	h6->SetLineColor(81);
	h6->Scale(1./norm6);
	//h6->Draw("same");

	double norm7 = h7->GetEntries();
	h7->SetLineWidth(3);
	h7->SetLineColor(76);
	h7->Scale(1./norm7);
	h7->Draw("same");

	double norm8 = h8->GetEntries();
	h8->SetLineWidth(3);
	h8->SetLineColor(65);
	h8->Scale(1./norm8);
	//h8->Draw("same");
	
	double norm9 = h9->GetEntries();
	h9->SetLineWidth(3);
	h9->SetLineColor(61);
	h9->Scale(1./norm9);
	h9->Draw("same");

	leg3->SetNColumns(2);
	leg3->AddEntry(h1, "W= 1.0TeV", "f");
	//leg3->AddEntry(h2, "W= 1.5TeV", "f");
	leg3->AddEntry(h3, "W= 2.0TeV", "f");
	//leg3->AddEntry(h4, "W= 2.5TeV", "f");
	leg3->AddEntry(h5, "W= 3.0TeV", "f");
	//leg3->AddEntry(h6, "W= 3.5TeV", "f");
	leg3->AddEntry(h7, "W= 4.0TeV", "f");
	//leg3->AddEntry(h8, "W= 4.5TeV", "f");
	leg3->AddEntry(h9, "W= 5.0TeV", "f");
	leg3->Draw();
}
