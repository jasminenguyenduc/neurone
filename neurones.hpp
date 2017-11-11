#ifndef NEURONES_H
#define NEURONES_H
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <random>
#include <cmath>
#include <math.h>
using namespace std;

class Neurone 
{
	private :
		
		int spikes; /*! The amount of spikes before a certain time */
		vector<double> spk_time; /*! the time at which a spike occured */
		double V; /*! membrane potential */
		static constexpr double h = 0.1; /*! the length of a step */
		vector <int> targets; /*! vector of neurons that are targeted */
		static constexpr int D = 15; /*! delay time after which a neuronmake
		make receives J */
		static constexpr double r_per = 20; /*! amount of stepsfor refractory time = refractory period*/
		static constexpr double tau = 20; /*! time constant */
		static constexpr double R = tau; 
		static constexpr double V_thr = 20; /*! membrane potential threshold, a spike occurs if the potential > threshold */
		double I = 0; /*! external input set at 0, but is used in the TESTs */
		double C = exp(-h/tau);
		
		
	public :
		Neurone();
		~Neurone();
		bool update(double step, double h, double poisson);
		double getPotential() const;
		void setPotential (double v);
		vector <double> add_to_buffer (double J);
		vector<double> buffer; /*! buffer receives a certain J and delivers it to neuron after D steps */
		vector <double> update_buffer();
		void addTarget (int target);
		vector <int> getTargets () const;
		double getSpikes() const;
		void set_i_ext(double i);
		vector <double> get_spk_time() const;


};






#endif
