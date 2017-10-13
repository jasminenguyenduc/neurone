#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "neurones.hpp"
#include "neurones.cpp"
using namespace std;

int main()
{
	Neurone n1;
	Neurone n2;
	n1.addtarget(n2);
	n2.addtarget(n1);
	vector<Neurone> neurones;
	neurones.push_back(n1);
	neurones.push_back(n2);
	double t;
	double h = 0.1; 
	double stop = 1000;
	double start = 0;
	double I;
	double t1;
	double t2;
	double J = 0.1;
	vector<double> buffer= {0,0,0,0,0};
	

	string const valeurs_pot("valeurs.txt");
	ofstream sortie(valeurs_pot.c_str());
	
	cout << "Insert start time : ";
	cin >> t1;
	cout << "Insert time of stop : ";
	cin >> t2;
	cout << "Insert external current for n1 : ";
	cin >> I;

	t = t1;
	
	if (t1 >= start and t2 <= stop)
	{
	
		while (t < t2)
		{
			if(sortie){
				sortie << "n1 : " << n1.get_potential() << endl;
				for (auto& target : n1.gettargets()) {
				sortie << "n2 : " << target->get_potential() << endl;
				buffer = update_buffer(target, buffer);
				/*
				sortie << "buffer : ";
				for (auto value : buffer) {
				sortie << value  << "," ;
				}
				sortie << endl;
				* */
				}
			}
			else
			cout << "Erreur";
			
			
			
			if (n1.update(t, I, h)) { // impulse applied to one particular neuron, if spiking = true
			
				for (auto& target : n1.gettargets()){ //all the neighboors n1 has
				sortie << "j'ai spiké" << endl;
				buffer = target->receive(t,J, buffer); // will receive J 
				
				
				}
			}
			
		
		t +=h;

	 }
	sortie.close();
	
	for(auto t_spike : n1.get_tab())
	cout << t_spike << endl;
	}
	

	
	return 0;
	
	
}
