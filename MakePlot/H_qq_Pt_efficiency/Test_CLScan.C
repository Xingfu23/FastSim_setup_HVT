using namespace RooFit;
TRandom3 rnd;

double CL_scan(double target_ns=5., int ntoys=1000, bool display=false){
	const double nobs = 1227.992+53.75;
	const double nb = 1227.992;

	double L0 = TMath::Poisson(nobs, nb);
	double L1 = TMath::Poisson(nobs, nb+target_ns);
	double Q_obs = -2.*(log(L1)-log(L0)); // observed test statistic

	vector<double> CL = {0.,0.}; //CL[0] is CLb and CL[1] is CLs+b
	vector<double> stat[2];

	for(int hypo=0; hypo<=1; hypo++){
		for(int idx=0; idx<ntoys; idx++){
			int n=0;
			if(hypo==0) n = rnd.Poisson(nb);           //toy sampling b-only
			if(hypo==1) n = rnd.Poisson(nb+target_ns); // toy sampling s+b
			double L0 = TMath::Poisson(n, nb);
			double L1 = TMath::Poisson(n, nb+target_ns);
			double Q  = -2.*(log(L1)-log(L0));         // sampled test statistic
			stat[hypo].push_back(Q);

			if(Q>=Q_obs) CL[hypo] += 1.;
		}
		CL[hypo] /= (double)ntoys;
	}
	double CLs = CL[1]/CL[0];

	if (display){
		TH1D* h_stat0 = new TH1D("h_stat0", "", 50, -50, 40);
		TH1D* h_stat1 = new TH1D("h_stat1", "", 50, -50, 40);

		for(int idx=0; idx<ntoys; idx++){
			h_stat0->Fill(stat[0][idx]);
			h_stat1->Fill(stat[1][idx]);
		}

		TCanvas *c1 = new TCanvas("c1", " ");
		c1->SetMargin(0.14,0.06,0.13,0.07);
		c1->SetLogy();
		h_stat1->Draw();
		h_stat1->SetStats(false);
		h_stat1->SetFillColor(kBlue-10);
		h_stat1->GetXaxis()->SetTitle("-2log(L_{s+b}/L_{b})");
		h_stat1->GetYaxis()->SetTitle("# of toys");
		h_stat1->GetXaxis()->SetTitleSize(0.06);
		h_stat1->GetYaxis()->SetTitleSize(0.06);
		h_stat1->GetYaxis()->SetTitleOffset(1.0);
		h_stat0->SetFillColor(kRed);
		h_stat0->SetFillStyle(3365);
		h_stat0->Draw("same");
		TLine l1;
		l1.SetLineWidth(3);
		l1.DrawLine(Q_obs, 0. ,Q_obs, h_stat1->GetMaximum());
	}
	printf("Target ns=%.1f, CLs+b=%.3f, CLb=%.3f, CLs=%.3f\n", target_ns, CL[1], CL[0], CLs);
	return CLs;
}

void Test_CLScan(){
	vector<double> vec_x, vec_obs;
	double target_ns = 0.;
	while(target_ns<=150.){
		double CLs = CL_scan(target_ns, 50000);
		//if (CLs == 0.1)  printf("Target ns=%.1f, CLs=%.3f", target_ns, CLs);
		//else if (CLs == 0.05) printf("Target ns=%.1f, CLs=%.3f", target_ns, CLs);
		vec_x.push_back(target_ns);
		vec_obs.push_back(CLs);
		target_ns += 1;
	}

	TGraph *gr_obs = new TGraph(vec_x.size(), vec_x.data(), vec_obs.data());
	gr_obs->SetLineWidth(3);
	gr_obs->SetLineColor(66);

	TCanvas *c1 = new TCanvas("c1","",600,600);
	c1->SetMargin(0.14,0.06,0.13,0.07);
	c1->SetGrid();
	c1->SetLogy();

	TH2D *frame = new TH2D("frame","",15, 0.,150.,10,0.01,1.2);
	frame->SetStats(false);
	frame->GetXaxis()->SetTitle("Signal Yield");
	frame->GetYaxis()->SetTitle("CL_{s} = 1-CL");
	frame->GetXaxis()->SetTitleSize(0.06);
	frame->GetYaxis()->SetTitleSize(0.06);
	frame->GetYaxis()->SetTitleOffset(1.0);
	frame->Draw("");

	gr_obs->Draw("same");
    
    TLine lin;
	lin.SetLineColor(kGray+2);
	lin.SetLineStyle(7);
	lin.SetLineWidth(3);
	//lin.DrawLine(50.,0.05,200.,0.05);
	//lin.DrawLine(50.,0.10,200.,0.10);
}




