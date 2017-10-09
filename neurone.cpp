#include "neurone.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
	
   // double h (1); //lenght of each step
	double tau (20); 
	double ref_per (2); // duration of refractory period
	double R(20); // resistance
	double V_thr(20); //membrane potential threshold
	double stop (1000);
	double start (0);
	double V_reset(10);
	vector<double> V(stop+1); // vector where position is time (ms) and double is membrane potential
	vector <double> I(stop+1); 
	
	Neurone :: Neurone ( double v, double s, vector<double> t): //construstor
	 vo(v), spikes(s),timespikes (t) {}
	/*
	Neurone::Neurone ( const Neurone& copy) // copy constructor
	{};
	Neurone::~Neurone () // destructor
	{};
	Neurone& Neurone::operator= (Neurone c) // allows to equalize each component of the neurones
	{
		swap(*this,c);
		return *this;
		};
		
	*/
	double Neurone::getvo() const // necessary to obtain real value from external methods
	{ return vo; }
	double Neurone::getspikes() const
	{ return spikes; }
	vector <double> Neurone::gettimespikes() const
	{ 
		return timespikes;
		}

	void Neurone::addspikes (double s)
	{ spikes += s;}
	void Neurone::addtimespikes (double t)
	{ 
		timespikes.push_back(t);
		}

	void Neurone::addcurrent(double t1, double t2, double i){
		
			for (int m(t1); m <= t2; ++m) {
				I[m]= i;
				}
		}

	void Neurone::setV(){ // the recursive equation has been transformed into a linear one, including a sum
		
		V[0] = vo;
		for (int i(1); i < V.size(); ++i) {
			if (V[i-1] < V_thr) {
			V[i] = V[i-1]*exp(-1/tau)+I[i]*R*(1-exp(-1/tau));
				}
			if (V[i-1] >= V_thr) {
				for (int j(1); j < ref_per; ++j) {
				V[i]= 0;
				spikes += 1;
				addtimespikes(i-1);
				V[j+i]= V_reset;
				i += j; 
					}
				}
		}
	}
		


	void Neurone::file (string name, vector <double> v) {
		
		ofstream outfile (name + ".txt");
		
		outfile << "Les valeurs sont : " << endl;
		for (size_t i(0); i < v.size(); ++i) {
			
			outfile << v[i] << endl;
			}
		
		}
