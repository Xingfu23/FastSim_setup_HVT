/*
double fcn(double *x, double *par){
	
	return par[0]+exp(par[1]*x[0]);

}
*/
void Draw_Event_Number_6(){
	auto c1 = new TCanvas("c1", "c1");
	c1->SetGrid();
	//c1->Divide(2,2);
	auto legend = new TLegend(0.65, 0.7, 0.9, 0.9);
	//TMultiGraph *mg = new TMultiGraph();
	//mg->SetTitle(" Background event left under different P_{T} filter; P_{T} filter(GeV); Event Number");

	vector<double> Pt = {0., 200., 500., 600., 800.};
	vector<double> y1 = {84.034, 8.555, 0.678, 0.483, 0.326};
	//vector<double> y2 = {27.89, 15.23, 2.807, 0.398, 0.094, 0.076, 0.031, 0.024, 0.005, 0.002, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
	//vector<double> y3 = {13.35, 9.737, 5.099, 2.651, 1.410, 0.779, 0.441, 0.262, 0.165, 0.104, 0.065, 0.042, 0.029, 0.022, 0.015, 0.007, 0.005, 0.004, 0.003, 0.001, 0.};
	//vector<double> y4 = {17.556, 17.556, 10.53, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
	/*
	vector<double> Pt_V, y1_V, y2_V, y3_V, y4_V;
	//Pt_V.assign(Pt, Pt+(sizeof(Pt)/sizeof(*Pt)));
	//eff_V.assign(eff, eff+(sizeof(Pt)/sizeof(*Pt)));
	Pt_V.assign(Pt, Pt+21);
	y1_V.assign(y1, y1+21);
	y2_V.assign(y2, y2+21);
	y3_V.assign(y3, y3+21);
	y4_V.assign(y3, y4+21);
	*/
	
	int n = Pt.size();
	auto ge1 = new TGraph(n, &Pt[0], &y1[0]);
	//auto ge2 = new TGraph(n, &Pt[0], &y1[0]);
	//auto ge3 = new TGraph(n, &Pt[0], &y1[0]);
	//auto ge4 = new TGraph(n, &Pt[0], &y1[0]);

	for(int point_N=0; point_N<n; point_N++){ 
		ge1->SetPoint(point_N, Pt[point_N], y1[point_N]);
	}
	ge1->SetMarkerStyle(7);
	ge1->SetMarkerColor(99);
	ge1->SetTitle(" ;Pt_cut(GeV); #sigma#timesBR_{W'#rightarrowWH}");
	ge1->GetYaxis()->SetTitleOffset(1.2); 
	ge1->SetMinimum(0.0);
	ge1->SetMaximum(100.0); 
	ge1->Draw("AP");

	//TF1 *f1 = new TF1("fl", fcn, 0., 1000., 2);
	//f1->SetParameters(0, 0);
	ge1->Fit("expo");                  
	TF1 *f1 = ge1->GetFunction("expo");
	f1->SetLineWidth(3);
	f1->SetLineColor(4);
	
	/*
	for(int point_N=0; point_N<21; point_N++){ 
		ge2->SetPoint(point_N, Pt[point_N], y2[point_N]);
	}
	ge2->SetMarkerStyle(20);
	ge2->SetMarkerColor(4);
	ge2->SetTitle("WGToLNu2G_01Jet_LO_MLM ;Pt_cut(GeV);Event Number");
	ge2->GetYaxis()->SetTitleOffset(1.2);                                      
	ge2->SetMinimum(0.0);
	ge2->SetMaximum(30.0);
    c1->cd(3); 
	ge2->Draw("AP");
	
	for(int point_N=0; point_N<21; point_N++){ 
		ge3->SetPoint(point_N, Pt[point_N], y3[point_N]);
	}
	ge3->SetMarkerStyle(20);
	ge3->SetMarkerColor(6);
	ge3->SetTitle("WH_HToGammagamma_WToLNu;Pt_cut(GeV);Event Number");
	ge3->GetYaxis()->SetTitleOffset(1.2);                                      
	ge3->SetMinimum(0.0);
	ge3->SetMaximum(30.0);
    c1->cd(4); 
	ge3->Draw("AP");

	for(int point_N=0; point_N<21; point_N++){ 
		ge4->SetPoint(point_N, Pt[point_N], y4[point_N]);
	}
	ge4->SetMarkerStyle(20);
	ge4->SetMarkerColor(8);
	ge4->SetTitle("DiPhotonJets_LO_MLM ;Pt_cut(GeV);Event Number");
	ge4->GetYaxis()->SetTitleOffset(1.2);                                      
	ge4->SetMinimum(0.0);
	ge4->SetMaximum(30.0);
    c1->cd(2); 
	ge4->Draw("AP");
	*/
	//c1->SetLogy();
	legend->SetHeader("W'=4TeV, HVT model B");
	legend->AddEntry(f1, "2#sigma significance, L=3000^{-1}", "l");
	legend->SetTextSize(0.025);
	legend->Draw();
}
