#include <iostream>
#include "neurones.hpp"
#include <cmath>
using namespace std;

bool Neurone :: update(double t,double I,double h)

{	


			
		if (V > V_thr) {
			++spikes;
			spk_time.push_back(t);
			V = 0;	
			return true;
		}
		if (!spk_time.empty() and (t-spk_time.back()) < r_per and !(V > V_thr)){
			V = 0;
			return false;
		}
	
		else {
			
			V = exp(-h/tau)*V + I*R*(1-exp(-h/tau));
			return false;
			
		}
}

void Neurone::receive (double t, double J, double h, double I)
{
	
	/*	if ((V > V_thr) or (!spk_time.empty() and (t-spk_time.back()) < r_per )) {
			V += 0;
		}
		else {
			*/
			V += J;	
		//}
	
	}


vector <Neurone*> Neurone::gettargets() const {
	return targets;
	}


vector<double> Neurone :: get_tab()	
{
	return spk_time;
}

double Neurone :: get_potential()
{
	return V;
}
void Neurone::addtarget (Neurone n){
	
	targets.push_back(new Neurone(n));
	}
void Neurone::set_potential(double v) {
	
	V = v;
	}


Neurone :: Neurone()
:spikes(0), V(V_ref)
{}
