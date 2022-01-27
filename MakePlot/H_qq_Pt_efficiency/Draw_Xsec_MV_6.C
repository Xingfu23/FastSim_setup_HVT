void Draw_Xsec_MV_6(){
	auto c1 = new TCanvas("c1", "c1");
	c1->SetGrid();
	c1->SetLogy();
	auto legend  = new TLegend(0.6, 0.65, 0.9, 0.9);
	//auto legend2 = new TLegend(0.65, 0.67, 0.9, 0.7);
	TMultiGraph *mg = new TMultiGraph();
	mg->SetTitle(" ; M_{#Lambda_{NP}} (GeV); #sigma#timesBR_{W'->WH} (fb)");
	//mg->GetXaxis()->SetLimits(0.,4000.);
	mg->SetMinimum(0.1);    
	mg->SetMaximum(10000.);


	vector<double> MV       = {1000., 1500., 2000., 2500., 3000., 3500., 4000., 4500., 5000.};
	vector<double> L300_Z2  = {677.14, 25.134, 2.0104, 1.8165, 1.9279, 2.1496, 2.4487, 4.4984, 22.095};
	vector<double> L1000_Z2 = {265.43, 9.8522, 0.78804, 0.71205, 0.75571, 0.84264, 0.95986, 1.7633, 8.6609};
	vector<double> L3000_Z2 = {116.02, 4.3066, 0.3445, 0.3113, 0.3303, 0.3683, 0.4196, 0.7708, 3.7858};
	vector<double> L300_Z3  = {1308.1, 48.553, 3.8836, 3.5091, 3.7242, 4.1526, 4.7303, 8.6899, 42.682};
	vector<double> L1000_Z3 = {498.55, 18.505, 1.4801, 1.3374, 1.4194, 1.5827, 1.8028, 3.3120, 16.26};
	vector<double> L3000_Z3 = {211.59, 7.8538, 0.6282, 0.5676, 0.6024, 0.6717, 0.7652, 1.4057, 6.9041};

	vector<double> HVT = {1252., 211.6, 51.36, 15.04, 4.94, 1.756, 0.6651, 0.2698, 0.1191};

	int n = MV.size();
	auto ge1 = new TGraph(n, &MV[0], &L300_Z2[0]);
	auto ge2 = new TGraph(n, &MV[0], &L1000_Z2[0]);
	auto ge3 = new TGraph(n, &MV[0], &L3000_Z2[0]);
	auto ge4 = new TGraph(n, &MV[0], &L300_Z3[0]); 
	auto ge5 = new TGraph(n, &MV[0], &L1000_Z3[0]); 
	auto ge6 = new TGraph(n, &MV[0], &L3000_Z3[0]); 

	auto ges = new TGraph(n, &MV[0], &HVT[0]);

	for(int point_N=0; point_N<L300_Z2.size(); point_N++){ 
		ge1->SetPoint(point_N, MV[point_N], L300_Z2[point_N]);
	}
	//ge1->Fit("expo");
	//TF1 *f1 = ge1->GetFunction("expo");
	/*
	TF1 *f1 = new TF1("f1", "exp([0]+[1]*x+[2]*x*x)");
	f1 -> SetParameters(500., -0.05, 0.000002);
	ge1->Fit("f1");
	TF1 *f1_r = ge1->GetFunction("f1");
	*/
	ge1->SetMarkerStyle(7);
	ge1->SetMarkerColor(6);
	ge1->SetFillColor(6);
	ge1->SetFillStyle(3004);
	ge1->SetLineColor(6);
	ge1->SetLineWidth(-303);

	//f1->SetLineColor(6);
	
	mg->Add(ge1);

		
	for(int point_N=0; point_N<L300_Z3.size(); point_N++){ 
		ge4->SetPoint(point_N, MV[point_N], L300_Z3[point_N]);
	}
	//ge4->Fit("pol2");
	//TF1 *f4 = ge4->GetFunction("pol2");

	ge4->SetMarkerStyle(7);
	ge4->SetMarkerColor(6);
	ge4->SetFillColor(6);
	ge4->SetFillStyle(3004);
	ge4->SetLineColor(6);   
	ge4->SetLineWidth(603); 
	ge4->SetLineStyle(7);
	//mg->Add(ge4);

	
	for(int point_N=0; point_N<L1000_Z2.size(); point_N++){      
		ge2->SetPoint(point_N, MV[point_N], L1000_Z2[point_N]);
	}                                                             
	//ge2->Fit("pol2");
	//TF1 *f2 = ge2->GetFunction("pol2");
	
	ge2->SetMarkerStyle(7);
	ge2->SetMarkerColor(4);
	ge2->SetFillStyle(3004);
	ge2->SetFillColor(4);
	ge2->SetLineWidth(3); 
	ge2->SetLineColor(4);
	ge2->SetLineWidth(-303);

	mg->Add(ge2);

	for(int point_N=0; point_N<L1000_Z3.size(); point_N++){      
		ge5->SetPoint(point_N, MV[point_N], L1000_Z3[point_N]);
	}                                                           
	//ge5->Fit("pol2");
	//TF1 *f5 = ge5->GetFunction("pol2");
	ge5->SetMarkerStyle(7);
	ge5->SetMarkerColor(4);
	ge5->SetLineWidth(3); 
	ge5->SetLineColor(4);
	ge5->SetLineStyle(7);

	//mg->Add(ge5);


	for(int point_N=0; point_N<L3000_Z2.size(); point_N++){      
		ge3->SetPoint(point_N, MV[point_N], L3000_Z2[point_N]);
	}                                                             
	//ge3->Fit("pol2");                                              
	//TF1 *f3 = ge3->GetFunction("pol2");                            
	ge3->SetMarkerStyle(7);                                        
	ge3->SetMarkerColor(2);
	ge3->SetFillStyle(3004);
	ge3->SetFillColor(2);
	ge3->SetLineWidth(3);                                           
	ge3->SetLineColor(2);
	ge3->SetLineWidth(-303);

	mg->Add(ge3);

	for(int point_N=0; point_N<L3000_Z3.size(); point_N++){      
		ge6->SetPoint(point_N, MV[point_N], L3000_Z3[point_N]);
	}                                                             
	//ge6->Fit("pol2");                                              
	//TF1 *f6 = ge6->GetFunction("pol2");                            
	ge6->SetMarkerStyle(7);                                        
	ge6->SetMarkerColor(2);                                        
	ge6->SetLineWidth(3);                                           
	ge6->SetLineColor(2); 
	ge6->SetLineStyle(7);

	//mg->Add(ge6);

	for(int point_N=0; point_N<HVT.size(); point_N++){    
		ges->SetPoint(point_N, MV[point_N], HVT[point_N]);
	} 

	ges->SetMarkerStyle(7);
	ges->SetMarkerColor(1);
	ges->SetLineWidth(3);  
	ges->SetLineColor(1);  
	//ges->SetLineStyle(7);

	mg->Add(ges);


	mg->Draw("ac");
	c1->Update();
	//f1_r->Draw("same");
	
	
	//legend->SetNColumns(2);
	legend->AddEntry(ge1, "L=300 fb^{-1}, 2#sigma significance", "l");
	legend->AddEntry(ge2, "L=1000 fb^{-1}, 2#sigma significance", "l");
	legend->AddEntry(ge3, "L=3000 fb^{-1}, 2#sigma significance", "l");
	//legend->AddEntry(ge4, "L=300 fb^{-1}, Z=3", "l");
	//legend->AddEntry(ge5, "L=1000 fb^{-1}, Z=3", "l");
	//legend->AddEntry(ge6, "L=3000 fb^{-1}, Z=3", "l");
	legend->AddEntry(ges, "HVT, g_{V}=2, c_{H}=1, c_{F}=1", "l");

	legend->SetTextSize(0.024);
	//legend2->SetTextSize(0.025);
	legend->Draw();

	mg->GetXaxis()->SetLabelSize(0.035);
	mg->GetYaxis()->SetLabelSize(0.035);
	mg->GetYaxis()->SetTitleOffset(1.2);
}
