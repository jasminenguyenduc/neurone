#include <iostream>
#include "neurones.hpp"
#include "neurones_const.cpp"
#include <cmath>
#include <cassert>
#include <random>
#include <map>

using namespace std;



bool Neurone :: update(double t,double h)

{	
		
		buffer = update_buffer();	
		
		if (V > V_thr) {
			++spikes;
			spk_time.push_back(t);
			V = 0;	
			return true;
		}
		if (!spk_time.empty() and ((t-spk_time.back())/h < r_per and !(V > V_thr))){
			V = 0;
			return false;
		}
	
		else {
			
			V = exp(-h/tau)*V + 1*R*(1-exp(-h/tau))+ random_poisson(Cext*Vext*h*0.1) + buffer[buffer.size()-1];
			
			return false;
		}
		
		int_clock +=h;
		
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
vector <double> Neurone::add_to_buffer (double J)
{

	buffer[0] = J;
	
	
	return buffer;
	
}

vector<double> Neurone :: get_tab() const	
{
	return spk_time;
}

double Neurone :: get_potential() const
{
	return V;
}

void Neurone::set_potential(double v) {
	
	V = v;
	}


vector <double> Neurone::update_buffer(){
	
		
		for (size_t i(0); i < buffer.size(); ++i){ // starts at 0 => buffer[5] = buffer[4], ... , buffer[1] = buffer[0]
				
			buffer[buffer.size()-i] = buffer[buffer.size()-i-1];
		} 
		/*
		buffer[4] = buffer[3];
		buffer[3] = buffer[2];
		buffer[2] = buffer[1];
		buffer[1] = buffer[0];
		* */
		buffer[0] = 0;       
		
		return buffer;
	
}

double Neurone::get_clock() const {
	
		return int_clock;
	
}
void Neurone::set_clock (double h) {
	
	int_clock += h;
}

int time_to_step (double t, double h) {
	return static_cast<unsigned long>(std::ceil(t/h));
	
}

vector <int> Neurone::get_spiker () const {
	
	
	return spiker;
}

void Neurone::add_spiker (int value) {
	
	spiker.push_back(value);
}


int random_uni (int a1, int a2) {
	
	random_device rd;	
	mt19937 gen(rd());
	uniform_int_distribution<> dis(a1,a2);
	return dis(gen);
}

int random_poisson (int a1){
	
	random_device rd;
	mt19937 gen(rd());
	poisson_distribution<> dis(a1);
	return dis(gen);
	
}

void Neurone::addTarget (int target) {
	
	targets.push_back(target);
}
	
vector <int> Neurone::getTargets () const {
	
	return targets;
}

Neurone :: Neurone()
:spikes(0), V(V_ref), buffer(vector<double> (D/h))
{}
