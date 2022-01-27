void draw_fatjet_mass(){
	
	auto c1   = new TCanvas("c1", "c1", 800, 600);
	auto leg3 = new TLegend(0.58, 0.7, 0.9, 0.9); 
	auto leg4 = new TLegend(0.58, 0.67, 0.9, 0.7);

	THStack *hs = new THStack("hs","");

	TFile* s1 = new TFile("output_bb_HVT_QQToWpToNuL2b_4TeV.root", "r");                
	TH1F *fatjetmass_s1 = (TH1F*) s1->Get("fatjetMaiss");            
	TH1F *fatjetmass_signal_s1 = (TH1F*) s1->Get("fatjetMass_signal");

	TFile* s2 = new TFile("output_bb_HVT_QQToWpToNuL2Q_4TeV.root", "r"); 
	TH1F *fatjetmass_s2 = (TH1F*) s2->Get("fatjetMaiss");                     
	TH1F *fatjetmass_signal_s2 = (TH1F*) s2->Get("fatjetMass_signal");

	TFile* b1 = new TFile("output_bb_BKG_ttWJetToLNu_LO_MLM_cut3.root", "r");
	TH1F *fatjetmass_b1 = (TH1F*) b1->Get("fatjetMaiss");                    
	TH1F *fatjetmass_signal_b1 = (TH1F*) b1->Get("fatjetMass_signal"); 

	TFile* b2 = new TFile("output_bb_BKG_WWToLNu2Q_4f_LO_MLM_cut3.root", "r");
	TH1F *fatjetmass_b2 = (TH1F*) b2->Get("fatjetMaiss");             
	TH1F *fatjetmass_signal_b2 = (TH1F*) b2->Get("fatjetMass_signal");

	TFile* b3 = new TFile("output_bb_BKG_WZToL3Nu_LO_MLM_cut3.root", "r");
	TH1F *fatjetmass_b3 = (TH1F*) b3->Get("fatjetMaiss");               
	TH1F *fatjetmass_signal_b3 = (TH1F*) b3->Get("fatjetMass_signal");

	TFile* b4 = new TFile("output_bb_BKG_WWToLNu2Q_4f_LO_MLM_cut3.root", "r"); 
	TH1F *fatjetmass_b4 = (TH1F*) b4->Get("fatjetMaiss");                  
	TH1F *fatjetmass_signal_b4 = (TH1F*) b4->Get("fatjetMass_signal");     

	TFile* b5 = new TFile("output_bb_BKG_WJetsToLNu_LO_MLM_cut3.root", "r");
	TH1F *fatjetmass_b5 = (TH1F*) b5->Get("fatjetMaiss");                         
	TH1F *fatjetmass_signal_b5 = (TH1F*) b5->Get("fatjetMass_signal");           

	TFile* b6 = new TFile("output_bb_BKG_ST_t-channel_4f_inclusiveDecays_LO_cut3.root", "r");  
    TH1F *fatjetmass_b6 = (TH1F*) b6->Get("fatjetMaiss");                     
    TH1F *fatjetmass_signal_b6 = (TH1F*) b6->Get("fatjetMass_signal");        

	TFile* b7 = new TFile("output_bb_BKG_ST_s-channel_4f_leptonDecays_LO_cut3.root", "r");
	TH1F *fatjetmass_b7 = (TH1F*) b7->Get("fatjetMaiss");                                    
	TH1F *fatjetmass_signal_b7 = (TH1F*) b7->Get("fatjetMass_signal");               

	TFile* b8 = new TFile("output_bb_BKG_WH_HToBB_WToLNu.root", "r");
	TH1F *fatjetmass_b8 = (TH1F*) b8->Get("fatjetMaiss");                                    
    TH1F *fatjetmass_signal_b8 = (TH1F*) b8->Get("fatjetMass_signal");                       
	                                                                                             

	//
	
	fatjetmass_s1->SetLineColor(9);
	fatjetmass_s1->SetFillColor(9);
	fatjetmass_s1->SetLineWidth(2);


	fatjetmass_s2->SetLineColor(38);
	fatjetmass_s2->SetFillColor(38);
	fatjetmass_s2->SetLineWidth(2);
	//hs->Add(fatjetmass_s2);
	fatjetmass_b1->SetLineColor(2);
	fatjetmass_b1->SetFillColor(2);
	fatjetmass_b1->SetLineWidth(2);
	//hs->Add(fatjetmass_b1);
	fatjetmass_b2->SetLineColor(8);
	fatjetmass_b2->SetFillColor(8);
	fatjetmass_b2->SetLineWidth(2);
	
	fatjetmass_b3->SetLineColor(28);
	fatjetmass_b3->SetFillColor(28);
	fatjetmass_b3->SetLineWidth(2);

	fatjetmass_b4->SetLineColor(12);
	fatjetmass_b4->SetFillColor(12);
	fatjetmass_b4->SetLineWidth(2);
 
	fatjetmass_b5->SetLineColor(92);
	fatjetmass_b5->SetFillColor(92);
	fatjetmass_b5->SetLineWidth(2);
	//hs->Add(fatjetmass_b5);        
	
	fatjetmass_b6->SetLineColor(87);
	fatjetmass_b6->SetFillColor(87);
	fatjetmass_b6->SetLineWidth(2);

	fatjetmass_b7->SetLineColor(29);
	fatjetmass_b7->SetFillColor(29);
	fatjetmass_b7->SetLineWidth(2);

	fatjetmass_b8->SetLineColor(46);
	fatjetmass_b8->SetFillColor(46);
	fatjetmass_b8->SetLineWidth(2);
	                        
	// Show event
	int N_fatjetmass_s1 = fatjetmass_s1->Integral();
	int N_fatjetmass_signal_s1 = fatjetmass_signal_s1->Integral();

	int N_fatjetmass_s2 = fatjetmass_s2->Integral();
	int N_fatjetmass_signal_s2 = fatjetmass_signal_s2->Integral();

	int N_fatjetmass_b1 = fatjetmass_b1->Integral();              
	int N_fatjetmass_signal_b1 = fatjetmass_signal_b1->Integral();

	int N_fatjetmass_b2 = fatjetmass_b2->Integral();              
	int N_fatjetmass_signal_b2 = fatjetmass_signal_b2->Integral();

	int N_fatjetmass_b3 = fatjetmass_b3->Integral();              
	int N_fatjetmass_signal_b3 = fatjetmass_signal_b3->Integral();

	int N_fatjetmass_b4 = fatjetmass_b4->Integral();              
	int N_fatjetmass_signal_b4 = fatjetmass_signal_b4->Integral();

	int N_fatjetmass_b5 = fatjetmass_b5->Integral();              
	int N_fatjetmass_signal_b5 = fatjetmass_signal_b5->Integral();

	int N_fatjetmass_b6 = fatjetmass_b6->Integral();              
	int N_fatjetmass_signal_b6 = fatjetmass_signal_b6->Integral();

	int N_fatjetmass_b7 = fatjetmass_b7->Integral();              
	int N_fatjetmass_signal_b7 = fatjetmass_signal_b7->Integral();

	int N_fatjetmass_b8 = fatjetmass_b8->Integral();              
	int N_fatjetmass_signal_b8 = fatjetmass_signal_b8->Integral();


	cout << "The event number of s1: " << N_fatjetmass_s1 << endl;
	cout << "The event number in signal region of s1: " << N_fatjetmass_signal_s1 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of s2: " << N_fatjetmass_s2 << endl;                        
	cout << "The event number in signal region of s2: " << N_fatjetmass_signal_s2 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of b1: " << N_fatjetmass_b1 << endl;                        
	cout << "The event number in signal region of b1: " << N_fatjetmass_signal_b1 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of b2: " << N_fatjetmass_b2 << endl;                        
	cout << "The event number in signal region of b2: " << N_fatjetmass_signal_b2 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of b3: " << N_fatjetmass_b3 << endl;                        
	cout << "The event number in signal region of b3: " << N_fatjetmass_signal_b3 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of b4: " << N_fatjetmass_b4 << endl;                        
	cout << "The event number in signal region of b4: " << N_fatjetmass_signal_b4 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of b5: " << N_fatjetmass_b5 << endl;                        
	cout << "The event number in signal region of b5: " << N_fatjetmass_signal_b5 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of b6: " << N_fatjetmass_b6 << endl;                        
	cout << "The event number in signal region of b6: " << N_fatjetmass_signal_b6 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of b7: " << N_fatjetmass_b7 << endl;                        
	cout << "The event number in signal region of b7: " << N_fatjetmass_signal_b7 << endl;
	cout << "===========================================" << endl;
	cout << "The event number of b8: " << N_fatjetmass_b8 << endl;                        
	cout << "The event number in signal region of b8: " << N_fatjetmass_signal_b8 << endl;
	cout << "===========================================" << endl;

	//Normalize
	/*
	fatjetmass_s1->Scale(5.638);
	fatjetmass_s2->Scale(2.702);
	fatjetmass_b1->Scale(502);
	fatjetmass_b2->Scale(6325);
	fatjetmass_b3->Scale(3422);
	fatjetmass_b4->Scale(15955);
	fatjetmass_b5->Scale(316000000);
	fatjetmass_b6->Scale(1019000);
	fatjetmass_b7->Scale(13810000);
	fatjetmass_b8->Scale(1206);
	*/

	// Graph option 
	//c1->SetLogy();
	fatjetmass_s1->Draw();
	fatjetmass_s1->SetTitle(" ");                            
	fatjetmass_s1->GetXaxis()->SetTitle("jet mass(GeV)");    
	fatjetmass_s1->GetXaxis()->SetLabelSize(0.03);           
	//fatjetmass_s1->GetXaxis()->SetLimits(0., 1000.);          
	fatjetmass_s1->GetYaxis()->SetTitle("Eentries");         
	fatjetmass_s1->GetYaxis()->SetTitleOffset(1.4);          
	fatjetmass_s1->GetYaxis()->SetLabelSize(0.03);           
	//fatjetmass_s1->GetYaxis()->SetUserRange(0., 1000.);
	fatjetmass_s1->SetAxisRange(0, 1000, "X");
	fatjetmass_s1->SetAxisRange(0, 2500, "Y");
	//fatjetmass_s1->SetMinimum(1);            
	//fatjetmass_s1->SetMaximum(1000000000000);

	fatjetmass_s1->SetStats(0);
	fatjetmass_s1->Draw();
	fatjetmass_s2->Draw("same");
	fatjetmass_b1->Draw("same");
	fatjetmass_b2->Draw("same");
	fatjetmass_b3->Draw("same");
	fatjetmass_b4->Draw("same");
	fatjetmass_b5->Draw("same");
	fatjetmass_b6->Draw("same");
	fatjetmass_b7->Draw("same");
	fatjetmass_b8->Draw("same");
	//hs->Draw("same");

	// Legend option
	leg3->SetHeader("M_{Z'}/M_{W'}= 3TeV ");      
	leg3->SetNColumns(2);                         
	leg3->AddEntry(fatjetmass_s1, "W'> WH(bb)");    
	leg3->AddEntry(fatjetmass_s2, "W'> WZ(jj)");    
	leg3->AddEntry(fatjetmass_b1, "tt~ > WZj");     
	leg3->AddEntry(fatjetmass_b2, "WZ > LNu2Q");    
	leg3->AddEntry(fatjetmass_b3, "WZ > L3Nu");     
	leg3->AddEntry(fatjetmass_b4, "WW > LNu2Q");    
	leg3->AddEntry(fatjetmass_b5, "Wj > LNu");      
	leg3->AddEntry(fatjetmass_b6, "ST s-channel");  
	leg3->AddEntry(fatjetmass_b7, "ST t-channel");  
	leg3->AddEntry(fatjetmass_b8, "WH > LNubb");    
	                                              
	leg3->SetTextSize(0.03);                      
	leg4->SetHeader("g_{v}=4, c_{H}=-1, c_{F}=1");
	leg4->SetTextSize(0.02);                      
	                                              
	leg3->Draw();                                 
	leg4->Draw();                                 

}
