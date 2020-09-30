#ifndef __NEURAL_NETWORK_H
#define	__NEURAL_NETWORK_H

/*	
	Mathematical Theory is coming from :
	A generalized LSTM-like training algorithm for second-order recurrent neural networks
	Derek D. Monner⇤, James A. Reggia
	Department of Computer Science, University of Maryland, College Park, MD 20742, USA
*/

#include "neural_network_platform.h"
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define DEC_ARRAY(t) struct { t items; uint32_t length; }

	typedef double nnvalue_t;
	typedef double(*squashingFn)(nnvalue_t x, bool derivate);

	nnvalue_t squash_logistic(nnvalue_t x, bool derivate);
	nnvalue_t squash_tanh(nnvalue_t x, bool derivate);
	nnvalue_t squash_identity(nnvalue_t x, bool derivate);
	nnvalue_t squash_hlim(nnvalue_t x, bool derivate);
	nnvalue_t squash_relu(nnvalue_t x, bool derivate);

	/* neural network */
	typedef struct {
		void * from;
		void * to;
		nnvalue_t weight;
		nnvalue_t gain;
	} ConnectionBase_t, *Connection_t;

	typedef struct {
		struct {
			Connection_t* inputs; /* NULL terminated list */
			Connection_t* gated;  /* NULL terminated list - for LSTM only */
		} connections;
		nnvalue_t state;
		nnvalue_t old;
		nnvalue_t activation;
		nnvalue_t bias;
		ConnectionBase_t selfConnection;
		squashingFn squash;
	} NeuronBase_t, * Neuron_t;

	typedef struct {
		DEC_ARRAY(Neuron_t*) neurons;
	} LayerBase_t, *Layer_t;


	typedef struct {
		DEC_ARRAY(Neuron_t) neurons;
		DEC_ARRAY(Connection_t) connections;
		DEC_ARRAY(Layer_t) layers;
		Layer_t input;
		Layer_t output;
		Layer_t * hiddens; /* NULL terminated list */
	} NeuralNetworkBase_t, * NeuralNetwork_t;

	void Neuron_initialize(Neuron_t n);
	void Connection_initialize(Connection_t c);
	void Layer_initialize(Layer_t l);
	void NeuralNetwork_activate(NeuralNetwork_t this, nnvalue_t * input);

#ifdef	__cplusplus
}
#endif

#endif

