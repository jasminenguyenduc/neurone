#ifndef neurone_H
#define neurone_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Neurone {
	private:
	double vo ;
	double spikes;
	vector <double> timespikes;
	
	public:
	Neurone ( double vo, double spikes, vector <double >timespikes);
	/*
	Neurone ( const Neurone& copy);
	~Neurone ();
	Neurone& operator= (Neurone n);
	*/
	//double h ; //lenght of each step
	double tau;
	double ref_per; // duration of refractory period
	double R; // resistance
	double V_thr; //membrane potential threshold
	double stop;
	double start;
	double V_reset;
	double getvo() const;
	double getspikes() const;
	vector <double> gettimespikes () const;
	void addspikes (double s); 
	void addtimespikes (double t); // adds a value in timespikes with the time at which the spike occured
	void addcurrent(double t1, double t2, double i); // changes values in I_time from t1 to t2 with the given intensity
	void setV(); // reads I_times and changes the values in V_times with the equation given
	void file( string name, vector <double> v);
	vector<double> V; // vector where position is time (ms) and double is membrane potential
	vector <double> I; 

	};
	
	
#endif
