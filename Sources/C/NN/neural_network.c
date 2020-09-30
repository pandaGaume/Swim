#include "neural_network.h"

void _InputLayer_activate(Layer_t this, nnvalue_t * input);
void _Layer_activate(Layer_t this);


nnvalue_t squash_logistic(nnvalue_t x, bool derivate)
{
	nnvalue_t fx = (nnvalue_t) (((double)1) / (((double)1) + nn_exp(-x)));
	return derivate ? fx * (((double)1) - fx) : fx;
}

nnvalue_t squash_tanh(nnvalue_t x, bool derivate)
{
	return derivate ? ((double)1) - nn_pow(nn_tanh(x), 2) : nn_tanh(x);
}

nnvalue_t squash_identity(nnvalue_t x, bool derivate)
{
	return derivate ? 1 : x;
}

nnvalue_t squash_hlim(nnvalue_t x, bool derivate)
{
	return derivate ? 1 : x > 0 ? 1 : 0;
}

nnvalue_t squash_relu(nnvalue_t x, bool derivate)
{
	return derivate ? (x > 0 ? 1 : 0) : (x > 0 ? x : 0);
}

void NeuralNetwork_activate(NeuralNetwork_t this, nnvalue_t * input) {
	_InputLayer_activate(this->input, input);
	Layer_t * a = this->hiddens;
	if (a && *a) {
		do {
			_Layer_activate(*a);
		} while (*(++a));
	}
	_Layer_activate(this->output);
}

void Neuron_initialize(Neuron_t n) {
	memset(n, 0, sizeof(NeuronBase_t));
	n->squash = squash_logistic;
	n->bias = nn_rand() * .2 - .1;
	Connection_initialize(&n->selfConnection);
	n->selfConnection.weight = 0;
	n->selfConnection.from = n;
	n->selfConnection.to = n;
}

void Connection_initialize(Connection_t c) {
	memset(c, 0, sizeof(ConnectionBase_t));
	c->weight = nn_rand() * .2 - .1;
	c->gain = 1;
}

void Layer_initialize(Layer_t l) {
	memset(l, 0, sizeof(LayerBase_t));
}


/* private */


void _Neuron_activate(Neuron_t this)
{
	this->old = this->state;
	/* eq. 15 - Recurrent Network */
	this->state =  this->selfConnection.weight ? this->selfConnection.gain * this->selfConnection.weight * this->state + this->bias : this->bias ;

	Connection_t * a = this->connections.inputs;
	if (a && *a) {
		do {
			this->state += ((Neuron_t)(*a)->from)->activation * (*a)->weight * (*a)->gain;
		} while (*(++a));
	}

	/* eq. 16 */
	this->activation = this->squash(this->state, false);
	// printf("activation %f\r\n", this->activation);

	/* LSTM update gated connection's gains */
	a = this->connections.gated;
	if (a && *a) {
		do {
			(*a)->gain = this->activation;
		} while (*(++a));
	}

}

void _InputLayer_activate(Layer_t this, nnvalue_t * input) {

	Neuron_t * a = this->neurons.items;
	if (*a) {
		do {
			(*a)->activation = *input;
			(*a)->bias = 0;
			// printf("activation %f\r\n", (*a)->activation);
			a++; input++;
		} while (*a);
	}
}

void _Layer_activate(Layer_t this) {

	Neuron_t * a = this->neurons.items;
	if (*a) {
		do {
			_Neuron_activate(*a++);
		} while (*a);
	}
}
