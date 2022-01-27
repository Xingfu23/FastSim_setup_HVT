void Guess_total_counting_6(){
	auto c1 = new TCanvas("c1", "c1");
	c1->SetGrid();
	double Pt[] = {0., 50., 100., 150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 650., 700., 750., 800., 850., 900., 950., 1000.};
	//double eff[] = {0.9619, 0.7101, 0.3767, 0.1891, 0.0932, 0.0492, 0.0254, 0.0151, 0.0085, 0.0029, 0.0012, 0.0005, 0.0003, 0., 0., 0., 0., 0., 0., 0., 0.};
	//double err[] = {0.0011, 0.0027, 0.0028, 0.0023, 0.0017, 0.0013, 0.0009, 0.0007, 0.0005, 0.0003, 0.0002, 0.0001, 0.0001, 0., 0., 0., 0., 0., 0., 0., 0.};
	double Total_count[] = {1960000, 401000., 80900, 14200, 6100, 2030, 2030};

	vector<double> Pt_V, Total_count_V, Pt_Full_V;
	Pt_V.assign(Pt, Pt+7);
	Pt_Full_V.assign(Pt, Pt+(sizeof(Pt)/sizeof(*Pt)));
	Total_count_V.assign(Total_count, Total_count+7);

	//eff_V.assign(eff, eff+(sizeof(Pt)/sizeof(*Pt)));
	//Pt_V.assign(Pt, Pt+21);
	//eff_V.assign(eff, eff+21);
	
	auto ge = new TGraph(7, Pt, Total_count);
	//auto ge_fit = new TGraph(21, Pt, Total_count);

	for(int point_N=0; point_N<Pt_V.size(); point_N++){ 
		ge->SetPoint(point_N, Pt_V[point_N], Total_count_V[point_N]);
	}
	
	TF1 *f1 = new TF1("f1", "[0]+exp([1]+[2]*x)", 0., 2000.);
	ge->Fit(f1);
	for(int entry1=0; entry1<Pt_Full_V.size(); entry1++){
		cout << "====================" << endl;
		cout << "Pt-value: " << Pt_Full_V[entry1] << endl;
		cout << "Guess events: " << f1->Eval(Pt_Full_V[entry1]) << endl;
		cout << "====================" << endl;
	}

	ge->SetMarkerStyle(20);
	ge->SetMarkerColor(1);

	//ge->SetTitle("SM Higgs decay;Pt_cut(GeV);efficiency");
	ge->GetYaxis()->SetTitleOffset(1.2); 
	ge->GetXaxis()->SetLimits(0., 1000.);
	ge->SetMinimum(0.0);
	ge->SetMaximum(2000000.);
	ge->Draw("AP");
	f1->Draw("same");
	

}
