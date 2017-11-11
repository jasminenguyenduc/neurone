# neurone
This program simulates the electrical activity of 12500 neurons. 10000 of the neurons are excitatory and 2500
are inhibitatory. Each neuron has a membrane potential value that varies throughout the simulation because
of the activity of it's neighbouring neurons. When the membrane potential reaches a certain value, 
it spikes : it will send a certain membrane potential to all the neurons it is connected to, and by doing so,
increases their potential membrane. The potential of the spiking neuron then drops to 0.
For a certain time after the spiking, the neuron cannot react to any incoming membrane potentials.
When an excitatory neuron spikes, it will send a value J to the potentials of it's so called target neurons.
When an inhibitatory neuron spikes, it will send a value of - g * J to the potentials of the targets, thus 
decreasing the potentials.
To send a membrane potential to a target, the neuron will add a certain value to a vector called "buffer", that belongs to the target.
The buffer of each neuron is updated when the neuron itself is updated. The values in the buffer shift towards the end of the vector at each update. When a value reaches the end of the buffer, the target's potential will be increased.
The connections between the neurons are made randomely, but each neuron has (in average) 1000 excitatory targets and
250 inhibitatory targets.
The simulation will run for 1 second, and calculate the values for each neuron at every step (1 step = 0.0001 sec).

To use the program, you must enter the plot you desire to make. 4 different plots are possible (Brunel).
If you wish to make all four of them, you should run the program 4 times for each plot.
