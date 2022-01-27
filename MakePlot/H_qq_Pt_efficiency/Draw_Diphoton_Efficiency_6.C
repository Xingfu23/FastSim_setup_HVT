void Draw_Diphoton_Efficiency_6(){
	auto c1 = new TCanvas("c1", "c1");
	c1->SetGrid();
	double Pt[] = {0., 50., 100., 150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 650., 700., 750., 800., 850., 900., 950., 1000.};
	double eff[] = {0.9619, 0.7101, 0.3767, 0.1891, 0.0932, 0.0492, 0.0254, 0.0151, 0.0085, 0.0029, 0.0012, 0.0005, 0.0003, 0., 0., 0., 0., 0., 0., 0., 0.};
	double err[] = {0.0011, 0.0027, 0.0028, 0.0023, 0.0017, 0.0013, 0.0009, 0.0007, 0.0005, 0.0003, 0.0002, 0.0001, 0.0001, 0., 0., 0., 0., 0., 0., 0., 0.};

	vector<double> Pt_V, eff_V;
	//Pt_V.assign(Pt, Pt+(sizeof(Pt)/sizeof(*Pt)));
	//eff_V.assign(eff, eff+(sizeof(Pt)/sizeof(*Pt)));
	Pt_V.assign(Pt, Pt+21);
	eff_V.assign(eff, eff+21);
	
	auto ge     = new TGraphErrors(21, Pt, eff, 0, err);
	auto ge_fit = new TGraphErrors(12, Pt, eff, 0, err);

	for(int point_N=0; point_N<Pt_V.size(); point_N++){ 
		ge->SetPoint(point_N, Pt_V[point_N], eff_V[point_N]);
	}

	for(int point_N=0; point_N<13; point_N++){
		ge_fit->SetPoint(point_N, Pt_V[point_N], eff_V[point_N]);
	}
	
	TF1 *f1 = new TF1("f1", "[0]+exp([1]+[2]*x)", 0., 1000.);
	//f1->SetParameters(10., 10., 10.);
	ge_fit->Fit(f1);

	ge->SetMarkerStyle(7);
	ge->SetMarkerColor(99);

	ge->SetTitle("SM Higgs decay;Pt_cut(GeV);efficiency");
	ge->GetYaxis()->SetTitleOffset(1.2);                                      
	ge->SetMinimum(0.0);
	ge->SetMaximum(1.0);
	ge->Draw("AP");
	f1->Draw("same");
	

}
