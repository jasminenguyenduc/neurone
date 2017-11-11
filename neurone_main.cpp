#include <fstream>
#include <string>
#include "neurones.hpp"
#include <iostream>
#include <random>
#include <map>
using namespace std;
 
int main()
{
	
vector<Neurone*> neurones; /*! all neurons in system */

static constexpr const double h = 0.1; 

double t; /*! time  */
static constexpr double start = 0;
static constexpr double stop = 1000;

static constexpr double J = 0.1; /*! membrane potential transmitted by an excitatory neuron */

static constexpr int Ne = 10000; /*! amount of excitatory neurons in the system */
static constexpr int Ni = 2500; /*! amount of inhibitatory neurons in the system */
static constexpr int Ce = Ne*0.1; /*! amount of connections to excitatory neurons */
static constexpr int Ci = Ce/4; /*! amount of connections to inhibitatory neurons */

/*! The parameters that change from one plot to the other are: nu_ext/nu_threshold = eta and g */
int plot;
double g = 0; /*! contant used to calculate the membrane ptotential received from an inhibitatory neuron */
double eta = 0;
int neuron_counter;

static constexpr int gA = 3;
static constexpr int gB = 6;
static constexpr int gC = 5;
static constexpr double gD = 4.5;
static constexpr double V_thr = 20;
static constexpr double tau = 20;
static constexpr int etaA = 2;
static constexpr int etaB = 4;
static constexpr int etaC = 2;
static constexpr double etaD = 0.9;
double nu_threshold = V_thr/(J*tau);
double nu_ext = eta * nu_threshold; 
static random_device rd;	
static mt19937 gen(rd());
static uniform_int_distribution<> dis_i(Ne,(Ni+Ne-1));

static uniform_int_distribution<> dis_e(0, Ne -1);



string const Spikes ("Spikes.txt");
ofstream say (Spikes.c_str());

	cout << dis_i(gen) << endl;
	cout << dis_e(gen) << endl;
	
	for (int i(0) ; i < Ne+Ni; ++i) { /*! Creation of 12500 neurons */
		Neurone n;
		neurones.push_back(new Neurone (n));
	
	}


	for (size_t n(0); n < neurones.size(); ++n) {
	
		for (int c(0); c < Ci; ++ c) /*! each neuron has Ci inhibitatory neurons*/
		{	
			neurones[n]->addTarget(dis_i(gen));
		}

		for (int c(0); c < Ce; ++ c) /*! each neuron has Ce excitatory targets */
		{
			neurones[n]->addTarget(dis_e(gen));
		}
}
/*! The plot studied in class is C (reference to Brunel article). To generate two plots, you must run the program twice with the plot of your choosing. */
/*! D will be the fastest plot to create because less neurons will spike due to the small value of the corresponding eta */

	cout << "Which plot would you like ? (if A press 0, B press 1, C press 2, D press 3)" << endl;
	cin >> plot;
	
		if (plot == 0 ) {
		g = gA;
		eta = etaA;
		}
		if (plot == 1) {
		g = gB;
		eta = etaB;
		}
		if (plot == 2) {
		g = gC;
		eta = etaC;
		}
		if (plot == 3) {
		g = gD;
		eta = etaD;
		}
		
	nu_ext = eta * nu_threshold; 
	
	double p(nu_ext*h);
	static poisson_distribution<> dis_p(p);
	cout << dis_p(gen) << endl;
	t = start;
		

		while (t <= stop) /*! while the simulation is running */
		{
			neuron_counter = 0; /*! counts neuron */
			
			for (auto& neurone : neurones){ /*! for all neurons in system */
			
				
			 /*! poisson is generated for each neuron because otherwise it will always be the same value for all neurons */
				
				
				if (neurone->update(t/h,h, dis_p(gen)*J)) {
				
				
					say << t/h << "	" << neuron_counter + 1<< endl; /*! Spike.txt is generated */
					
					for (auto& target : neurone->getTargets()) { 
						if (neuron_counter < Ne) { /*! excitatory neurons will send J to all their targets */
							neurones[target]->add_to_buffer(J);
						}
						if (neuron_counter >= Ne) {/*! inhibitatory neurons will send -J*g to all their targets */
							neurones[target]->add_to_buffer(-J*g);
						}
						
					}
				}
			
				
				neuron_counter += 1;
				
			}
			
				
		
		t +=h; /*! time evolves */

		}
		
		/*! Vitesse d'execution : 100 step/second */

	return 0;
	
	
}

