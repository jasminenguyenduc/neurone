#include "neurone.cpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main() {
	
	vector <double> alpha (0,0);
	Neurone neuron (10, 0 , alpha);
	double t1;
	double t2;
	double input_current;
	double simtime = 0;

	while (simtime < stop) {
		cout << " Input current :" << endl;
		cin >> input_current;
		cout << " Input starting time:" << endl;
		cin >> t1;
		cout << " Input ending time:" << endl;
		cin >> t2;
		if (t1> t2) {
			
			cout << "Erreur" << endl;
			}
		else {
		//neuron.addcurrent (t1,t2,input_current);
		//neuron.setV(); 
		
		//I
		for (int m(t1); m <= t2; ++m) {
				I[m]= input_current;
				} 
	
		// V
		V[0] = neuron.getvo();
		for (int i(1); i < V.size(); ++i) {
			if (V[i-1] < V_thr) {
			V[i] = V[i-1]*exp(-1/tau)+I[i]*R*(1-exp(-1/tau));
				}
			if (V[i-1] >= V_thr) {
				for (int j(1); j < ref_per; ++j) {
				V[i]= 0;
				neuron.addspikes(1);
				neuron.addtimespikes(i-1);
				V[j+i]= V_reset;
				i += j; 
					}
				}
			}
	simtime = t2; 
		
	neuron.file("V", V);
	
		ofstream o ("spikes.txt");
		
		o << "Le nombre de spikes est : " << endl;
			o << neuron.getspikes() << endl;
	
	neuron.file("I", I);
	neuron.file("timespikes", neuron.gettimespikes());
			}
		}
			

	return 0;
	}
