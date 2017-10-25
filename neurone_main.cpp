#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include "neurones.hpp"
#include "neurones.cpp"
// #include "neurones_const.cpp"
#include <random>
#include <map>
using namespace std;

int main()
{
	
	vector<Neurone*> neurones;
	double t;
const double h = 0.1; 
const double stop = 1000;
const double start = 0;
const double J = 0.1;
const int Ne = 1000;
const int Ni = 250;
const int Ce = 100;
const int Ci = Ce/4;
const int g = 5;

string const aff_neurons ("aff_neurons.txt");
ofstream say (aff_neurons.c_str());
	
	
	
	for (int i(0) ; i < Ne+Ni; ++i) { //initialise 12500 neurons
		Neurone n;
		neurones.push_back(new Neurone (n));
	
	}
vector <vector<int>> connections (neurones.size(), vector <int> (neurones.size()));
cout << " 12500 neurons are born " << endl;


	// make random spiker vector for all neurons
	for (int n(0); n < neurones.size(); ++n) {
		
		for (int c(0); c < Ce; ++ c) //spikers from Ne
		{
			neurones[n]->add_spiker(random_uni (0, Ne-1));
			
		}
	
		for (int c(0); c < Ci; ++ c) //spikers from Ni
		{
			neurones[n]->add_spiker(random_uni(Ne,(Ni+Ne-1)));
			
		}
		
	
cout << "12500 spikers randomely made" << endl;

	 //n receives from spiker, we add each spiker to the connection table
		for (int i (0); i < neurones[n]->get_spiker().size(); ++i) {
			connections[n][neurones[n]->get_spiker()[i]] += 1;
		}
cout << "connections randomely made" << endl;

		for (int i (0); i < neurones.size(); ++ i){
		
				if (connections[n][i] != 0) {
					neurones[n]->addTarget(i);
				}
		}
cout << "targets made" << endl;
	}
	


				

//now each neuron has 2 vectors with the information : spikers, targets

	t = start;
	
	
		while (t < stop)
		{
			int neuron_counter(0);
			
			for (auto& neurone : neurones){
				
				if (neurone->update(t,h)) {
					cout << neuron_counter<<  ":  I'm spiking" << endl;
					for (auto target : neurone->getTargets()) {
						if (neuron_counter < Ne) {
							neurones[target]->add_to_buffer(J);
						}
						if (neuron_counter >= Ne) {
							neurones[target]->add_to_buffer(-J*g);
						}
					}
				}
				
				neuron_counter += 1;
				
				if (neurone->get_potential() < 0) {
					neurone->set_potential(0);
				}
			}
			
				
		if (say) {
		
				say << t << " : "  << "n(" << 1 << ") : " << neurones[0]->get_potential() << endl;
				say << t << " : "  << "n( target ) : " << neurones[neurones[0]->getTargets()[0]]->get_potential() << endl;
			}
	
		else 
		say << "Erreur";	
			
			
			
		t +=h;

		}
	
	return 0;
	
	
}

//CREATION
// first we create so many neurons
// then we give them so many spikers in a vector of int (as given in class)
// we make a huge matrix with all the information about the connections
// we make them a vector of targets withthe help of the matrix

//WORKING
// while time hasn't run out
// for all neurons (one after the other)
//neuron will be updated -> return true if spiking, does equation to change potential, updates the buffer
// if it spikes (update = true) -> a value will be given to the buffers of the targeting neurons, once the value gets to the end of buffers all targets will receive that value in potential
//
