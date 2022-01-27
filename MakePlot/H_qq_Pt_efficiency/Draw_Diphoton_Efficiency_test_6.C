double Pt[]  = {0., 50., 100., 150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 650., 700., 750., 800., 850., 900., 950., 1000.};
double eff[] = {0.9619, 0.7101, 0.3767, 0.1891, 0.0932, 0.0492, 0.0254, 0.0151, 0.0085, 0.0029, 0.0012, 0.0005, 0.0003, 0., 0., 0., 0., 0., 0., 0., 0.};
double err[] = {0.0011, 0.0027, 0.0028, 0.0023, 0.0017, 0.0013, 0.0009, 0.0007, 0.0005, 0.0003, 0.0002, 0.0001, 0.0001, 0., 0., 0., 0., 0., 0., 0., 0.};

int Pt_arr_size  = sizeof(Pt)/sizeof(*Pt);  
int eff_arr_size = sizeof(eff)/sizeof(*eff);

// Fitting function
double func(double x, double *par){
	double value = par[0]/pow(x, par[2]) + par[1]/pow(x, par[3]);
	return value;
}


void fcn(int &npar, double *gin, double &f, double *par, int iflag){
	const int nbins = 10;

	// Calculating chisquare
	double chisq = 0;
	double delta;
	for(int entry=0; entry<nbins; entry++){
		//double test_error = sqrt(eff[entry]);
		delta = (eff[entry]-func(Pt[entry], par))/err[entry];
		chisq += delta*delta;
	}
	f = chisq;
}

void Draw_Diphoton_Efficiency_test_6(){
	auto c1 = new TCanvas("c1", "c1");
	c1->SetGrid();
	//double Pt[] = {0., 50., 100., 150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 650., 700., 750., 800., 850., 900., 950., 1000.};
	//double eff[] = {0.9619, 0.7101, 0.3767, 0.1891, 0.0932, 0.0492, 0.0254, 0.0151, 0.0085, 0.0029, 0.0012, 0.0005, 0.0003, 0., 0., 0., 0., 0., 0., 0., 0.};
	//double err[] = {0.0011, 0.0027, 0.0028, 0.0023, 0.0017, 0.0013, 0.0009, 0.0007, 0.0005, 0.0003, 0.0002, 0.0001, 0.0001, 0., 0., 0., 0., 0., 0., 0., 0.};

	//int Pt_arr_size  = sizeof(Pt)/sizeof(*Pt);
	//int eff_arr_size = sizeof(eff)/sizeof(*eff);
	
	TMinuit *gMinuit = new TMinuit(3);
	gMinuit->SetFCN(fcn);

	gMinuit->DefineParameter(0, "p0", 1., 0.01, -10., 10.);
	gMinuit->DefineParameter(1, "p1", 1., 0.01, -10., 10.);
	gMinuit->DefineParameter(2, "p2", 1, 0.1, 0., -10.);
	gMinuit->DefineParameter(3, "p3", 1, 0.1, 0., -100.);

	gMinuit->Command("MIGRAD");
	//gMinuit->Command("MINOS");

	double par[3], error[3];
	for(int entry=0; entry<3; entry++){
		gMinuit->GetParameter(entry,par[entry],error[entry]); 
	}

	vector<double> Pt_V,eff_V;
	Pt_V.assign(Pt, Pt+Pt_arr_size);
	eff_V.assign(eff, eff+eff_arr_size);

	// Drawing data and fitting function
	TH1F *curve = new TH1F("curve", "curve", Pt_arr_size*5, 0., 1000.);
	for(int point_N=0; point_N<Pt_arr_size; point_N++){
		double x = 50.*point_N;
		double f = func(x, par);
		curve->SetBinContent(point_N, f);
	}

	auto ge = new TGraphErrors(Pt_arr_size, Pt, eff, 0, err);
	for(int point_N=0; point_N<Pt_V.size(); point_N++){ 
		ge->SetPoint(point_N, Pt_V[point_N], eff_V[point_N]);
	}

	ge->SetMarkerStyle(7);
	ge->SetMarkerColor(99);
	curve->SetLineWidth(3);
	ge->SetTitle("SM Higgs decay;Pt_cut(GeV);efficiency");
	ge->GetYaxis()->SetTitleOffset(1.2);                                      
	ge->SetMinimum(0.0);
	ge->SetMaximum(1.0);

	ge->Draw("AP");
	curve->Draw("csame");

}
