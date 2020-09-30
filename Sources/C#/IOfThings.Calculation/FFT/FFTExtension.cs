using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

namespace IOfThings.Calculation.FFT
{
    public static class FFTExtension
    {

        public static double[] ToComplexValues(this double[] input, double[] complexSignal = null)
        {
            int N = input.Length * 2;
            complexSignal = complexSignal ?? new double[N];
            for (int j = 0, i = 0; j < N; j += 2, i++)
            {
                complexSignal[j] = (double)input[i];
                complexSignal[j + 1] = 0;
            }
            return complexSignal;
        }

        public static double[] ToComplexValues(this Complex[] input, double[] complexSignal = null)
        {
            int N = input.Length * 2;
            complexSignal = complexSignal ?? new double[N];
            for (int j = 0, i = 0; j < N; j += 2, i++)
            {
                complexSignal[j] = input[i].Real;
                complexSignal[j + 1] = input[i].Imaginary;
            }
            return complexSignal;
        }

        public static IEnumerable<Complex> ToComplex(this double[] input)
        {
            int N = input.Length;
            for (int j = 0; j < N; j += 2)
            {
                yield return new Complex(input[j], input[j + 1]);
            }
        }
    }
}
