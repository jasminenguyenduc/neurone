#ifndef NEURONES_H
#define NEURONES_H
#include <iostream>
#include <vector>
using namespace std;

class Neurone 
{
	private :
		
		int spikes;
		vector<double> spk_time;
		const int V_ref = 10;
		const double V_thr = 20;
		const double tau = 20; 
		const int C = 1;
		const double r_per = 0.5;
		const double R = tau/C;
		vector <Neurone*> targets;
		double J;

	
		double V;
	public :
		Neurone();
		bool update(double t,double I,double h);
		vector<double> get_tab();
		double get_potential();
		void set_potential(double v);
		void addtarget (Neurone n);
		void addneurone (Neurone n);
		void receive (double t, double J, double h, double I);
		vector <Neurone*> gettargets() const;
	
	
	
	
};














#endif
