/*	
	Mathematical Theory is coming from :
	A generalized LSTM-like training algorithm for second-order recurrent neural networks
	Derek D. Monner⇤, James A. Reggia
	Department of Computer Science, University of Maryland, College Park, MD 20742, USA
*/

using System;
using System.Collections.Generic;
using System.Linq;

namespace IOfThings.AI.Edge
{
    public delegate float SquashingFn(float x, bool derivate);

    public static class SquashingFunctions
    {
        public static float Logistic(float x, bool derivate)
        {
            float fx = (float)(((float)1) / (((float)1) + Math.Exp(-x)));
            return derivate ? fx * (((float)1) - fx) : fx;

        }
        public static float Tanh(float x, bool derivate)
        {
            return derivate ? ((float)1) - (float)Math.Pow(Math.Tanh(x), 2) : (float)Math.Tanh(x);
        }

        public static float Identity(float x, bool derivate)
        {
            return derivate ? 1 : x;
        }

        public static float Hlim(float x, bool derivate)
        {
            return derivate ? 1 : x > 0 ? 1 : 0;
        }

        public static float Relu(float x, bool derivate)
        {
            return derivate ? (x > 0 ? 1 : 0) : (x > 0 ? x : 0);
        }
    }

    public class Neuron
    {
        internal Connection[] _inputs;
        internal Connection[] _gateds; // for LSTM only
        internal float _old;
        internal float _state;
        internal float _activation;
        internal float _bias;

        public IEnumerable<Connection> Inputs => _inputs;
        public IEnumerable<Connection> Gateds => _gateds;
        public float State => _state;

        public Connection SelfConnection { get; set; }
        public SquashingFn Squash { get; set; }

        public void Activate()
        {
            _old = _state;

            /* eq. 15 - Recurrent Network */
            _state = _bias;
            Connection sc = SelfConnection;
            if (sc._weight != 0)
            {
                _state += sc._gain * sc._weight * State;
            }

            if (_inputs != null)
            {
                for (int i = 0; i != _inputs.Length; i++)
                {
                    Connection c = _inputs[i];
                    _state += c._from._activation * c._weight * c._gain;
                }
            }

            /* eq. 16 */
            _activation = Squash(_state, false);

            /* LSTM update gated connection's gains */
            if (_gateds != null)
            {
                for (int i = 0; i != _gateds.Length; i++)
                {
                    Connection c = _gateds[i];
                    c._gain = _activation;
                }
            }
        }
    }

    public class Connection
    {
        internal Neuron _from;
        internal float _weight;
        internal float _gain;
    }

    public class NNItem
    {
        public string Comment { get; set; }
        public string Description { get; set; }
        public string DisplayName { get; set; }
    }

    public class Layer : NNItem
    {
        protected Neuron[] _n;

        public IEnumerable<Neuron> Neurons => _n;
        public int Size => _n != null ? _n.Length : 0;

        public void Activate()
        {
            for (int i = 0; i != _n.Length; i++)
            {
                _n[i].Activate();
            }
        }
    }

    public class InputLayer : Layer
    {
        public void Activate(float[] inputs)
        {
            for (int i = 0; i != inputs.Length; i++)
            {
                _n[i]._activation = inputs[i];
                _n[i]._bias = default;
            }
        }
    }

    public class NeuralNetwork : NNItem
    {
        public InputLayer Input { get;}
        public ICollection<Layer> Hiddens { get;}
        public Layer Output { get;}

        public void Activate(IEnumerable<float> inputs)
        {
            Input.Activate(inputs.ToArray());
            foreach(Layer l in Hiddens)
            {
                l.Activate();
            }
        }
    }
}
