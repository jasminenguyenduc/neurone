#include "neurones.hpp"

using namespace std;



bool Neurone :: update(double step, double h, double poisson) /*! updates neuron by moving the buffer, incrementing the potential if it isn't refractory  */

{	
		buffer = update_buffer(); /*! updates buffer */
		if (V > V_thr) { /*! if spiking -> membrane potential becomes 0 */
			++spikes;
			spk_time.push_back(step*h-h);
			V = 0;	
			return true;
		}
		if (!spk_time.empty() and ((step-spk_time.back()/h) < r_per and !(V > V_thr))){ /*! while refractory -> membrane potential is 0 */
		
			V = 0;
			return false;
		}

	
		else { /*! uses formula, buffer and poisson to increment V if neuron is neither spiking or refractory*/
			
			V = exp(-h/tau)*V+ I*(1-exp(-h/tau))*R + poisson + buffer[buffer.size()-1];
		
			return false;
		}
		
		
}

	
vector <double> Neurone::add_to_buffer (double J) /*! the first square in buffer will receive J, this is used for targets to receive J */
{

	buffer[0] += J;
	
	return buffer;
	
}



double Neurone :: getPotential() const /*! allows acces to potential */
{
	return V;
}

void Neurone::setPotential(double v) { /*! allows modification of potential  */
	
	V = v;
	}


vector <double> Neurone::update_buffer(){ /*! shifts the buffer vector one step thus deleting the last value, the first value becomes 0. */
	
		
		for (size_t i(0); i < buffer.size(); ++i){ 
				
			buffer[buffer.size()-i] = buffer[buffer.size()-i-1];
		} 
		/*!
		 * ...
		buffer[4] = buffer[3];
		buffer[3] = buffer[2];
		buffer[2] = buffer[1];
		buffer[1] = buffer[0];
		* buffer[0] = 0;
		* */
		buffer[0] = 0;       
		
		return buffer;
	
}



int random_uni (int a1, int a2) { /*! gives a random number between a1 and a2 */
	
	static random_device rd;	
	static mt19937 gen(rd());
	static uniform_int_distribution<> dis(a1,a2);
	return dis(gen);
}

int random_uni2 (int a1, int a2) { /*! A second identical function was weirdly necessary. Otherwise, if I use this function twice, it will only take account of the first one */
	
	static random_device rd;	
	static mt19937 gen(rd());
	static uniform_int_distribution<> dis(a1,a2);
	return dis(gen);
}
void Neurone::addTarget (int target) { /*! Adds a target, which is a neuron that our neuron is connected to, so that it will receive J from our neuron */
	
	targets.push_back(target);
}
	
vector <int> Neurone::getTargets () const { /*! allows acces to target */
	
	return targets;
}

void Neurone::set_i_ext(double i) { /*! allows modification of external input */
		I = i;
}
double Neurone::getSpikes() const { /*! allows access to spikes */
	
	return spikes;
	}
	
vector <double> Neurone::get_spk_time() const { /*! allows acces to spike times */
	
	return spk_time;
	}
Neurone :: Neurone() /*! constructor */
:spikes(0), V(0), buffer(vector<double> ((D)/h))
{}
