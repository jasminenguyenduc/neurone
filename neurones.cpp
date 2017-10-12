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
		//int_clock += h;
}

bool Neurone::refractory (double t) {
	
	if (V > V_thr) {
		
	return true;	
	}
	if (!spk_time.empty() and (t-spk_time.back()) < r_per and !(V > V_thr)) {
		
	return true;
	}
	else {
		
	return false;	
	}
	
} 
void Neurone::receive (double t, double J)
{
	if (!buffer.empty() and buffer[4] != 0) {
				
		V+= buffer[4];	
	}
	for (size_t i(1); i < 5; ++i){
				
		buffer[i] = buffer[i-1];
	}
		
	if (refractory(t)) {
		buffer[0] = 0;
	}
	if (refractory(t) == false) {
		buffer[0] = J;
	}
			
	
}


vector <Neurone*> Neurone::gettargets() const {
	return targets;
	}


vector<double> Neurone :: get_tab() const	
{
	return spk_time;
}

double Neurone :: get_potential() const
{
	return V;
}
void Neurone::addtarget (Neurone n){
	
	targets.push_back(new Neurone(n));
	}
void Neurone::set_potential(double v) {
	
	V = v;
	}

/*
double Neurone::get_int_clock () const {
	
	return int_clock;
	}
	
void Neurone:: set_clock (double h){
	
	int_clock += h;
	}
	
*/
	
Neurone :: Neurone()
:spikes(0), V(V_ref)
{}
