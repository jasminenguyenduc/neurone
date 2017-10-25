#ifndef NEURONES_H
#define NEURONES_H
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
using namespace std;

class Neurone 
{
	private :
		
		int spikes;
		vector<double> spk_time;
		double V;
		double int_clock;
		vector <int> spiker;
		vector <int> targets;
		const int V_ref = 10;
		const double D = 1.5;
		const int C = 1;
		const double r_per = 1;
		const double tau = 20; 
		const double R = tau/C;
		const double teta = 20;
		const double J = 0.1;
		const int Ne = 1000;
		const int Ni = 250;
		const int Ce = 100;
		const int Ci = Ce/4;
		const int Cext = Ce;
		const int g = 5;
		const double V_thr = teta/(Ce * J * tau);
		const double Vext = 2*V_thr;
	public :
		Neurone();
		bool update(double t,double h);
		vector<double> get_tab() const;
		double get_potential() const;
		double get_clock() const;
		void set_potential(double v);
		void addneurone (Neurone n);
		vector <double> add_to_buffer (double J);
		bool refractory (double t);
		void set_clock (double h);
		vector <int> get_spiker () const;
		void add_spiker (int value);
		vector<double> buffer;
		vector <double> update_buffer();
		void addTarget (int target);
		vector <int> getTargets () const;
		


};


int time_to_step (double t, double h);
int random_uni (int a1, int a2);
int random_poisson (int a1);







#endif
