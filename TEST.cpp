#include <iostream>
#include "neurones.hpp"
#include <gtest/gtest.h>



TEST (NeuronTest, SpikeTimes) {
	Neurone neuron;

	neuron.set_i_ext(1.01);
	for (int i(0); i < 924; ++ i) {
			neuron.update(i,0.1,0);
		}

	EXPECT_EQ (0, neuron.getSpikes());
	
	for (int i(0); i < 1; ++ i) {
			neuron.update(i,0.1,0);
		}
	EXPECT_EQ (1, neuron.getSpikes());
	EXPECT_EQ(0.0 , neuron.getPotential());

}

TEST (NeuronTest, StandaloneSimulation) {
	Neurone neuron;

	neuron.set_i_ext(1.01);
	for (int i(0); i < 4000; ++ i) {
			neuron.update(i,0.1,0);
		}
	EXPECT_EQ (4, neuron.getSpikes());

}


TEST (NeuronTest, PositiveInput) {
	Neurone neuron;

	neuron.set_i_ext(1.0);
	for (int i(0); i < 1; ++ i) {
			neuron.update(i,0.1,0);
		}

	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)) , neuron.getPotential());
	for (int i(0); i < 1000; ++ i) {
			neuron.update(i,0.1,0);
		}

	EXPECT_EQ (0, neuron.getSpikes());
	EXPECT_GT(1, std::fabs(19.999- neuron.getPotential()));
	
	neuron.set_i_ext(0.0);
	for (int i(0); i < 2000; ++ i) {
			neuron.update(i,0.1,0);
		}
	
	EXPECT_NEAR (0, neuron.getPotential(), 1E-3);
}

TEST (NeuronTest, MembranePotential) {
		Neurone neuron;
		neuron.set_i_ext(1.0);
		for (int i(0); i < 1; ++ i) {
			neuron.update(i,0.1,0);
		}
		
		EXPECT_EQ (20.0*(1.0 - std::exp(-0.1/20.0)), neuron.getPotential());
}



TEST (NeuronTest, Buffer) {
		
		Neurone neuron;
		neuron.buffer = neuron.add_to_buffer(0.1);
		for (int i(0); i < 14; ++ i) {
			neuron.update(i,0.1,0);
		}
		EXPECT_EQ (0.1, neuron.getPotential());
	
}


int main (int argc, char **argv) {
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
}

