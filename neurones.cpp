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
vector <double> Neurone::receive (double t, double J, vector <double> buffer)
{

	buffer[0] = J;

	return buffer;
	
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
vector <double> update_buffer(Neurone* n,  vector <double> buffer){
	
		if (!buffer.empty() and buffer[4] != 0) {
					n->set_potential(n->get_potential() + buffer[4]);	
				
		}
		/*
		for (size_t i(0); i < 5; ++i){ // starts at 0 => buffer[5] = buffer[4], ... , buffer[1] = buffer[0]
				
			buffer[5-i] = buffer[5-i-1];
		} */
		
		buffer[4] = buffer[3];
		buffer[3] = buffer[2];
		buffer[2] = buffer[1];
		buffer[1] = buffer[0];
		buffer[0] = 0;       
		
		return buffer;
	
}
	
Neurone :: Neurone()
:spikes(0), V(V_ref)
{}
