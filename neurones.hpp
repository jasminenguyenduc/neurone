#ifndef NEURONES_H
#define NEURONES_H
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <random>
using namespace std;

class Neurone 
{
	private :
		
		int spikes; /*! The amount of spikes before a certain time */
		vector<double> spk_time; /*! the time at which a spike occured */
		double V; /*! membrane potential */
		const double h = 0.1; /*! the length of a step */
		vector <int> targets; /*! vector of neurons that are targeted */
		const double D = 1.5; /*! delay time after which a neuronmake
		make receives J */
		const double r_per = 20; /*! amount of stepsfor refractory time = refractory period*/
		const double tau = 20; /*! time constant */
		const double R = tau; 
		const double V_thr = 20; /*! membrane potential threshold, a spike occurs if the potential > threshold */
		const int Cext = 1000; /*! amount of connections from external neurons that are excitatory */
		double I = 0; /*! external input set at 0, but is used in the TESTs */

		
		
	public :
		Neurone();
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


int random_uni (int a1, int a2);
int random_uni2 (int a1, int a2);







#endif
