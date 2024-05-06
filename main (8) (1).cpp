#include <iostream>
#include <cassert>
using namespace std;
// euclidean algorithm to find GCD
int EuclidAlgGCD (int a, int b)
{
  while (b != 0)
    {
      int temp = b;
      b = a % b;
      a = temp;
    }
  return a;
}

// extended euclidean algorithm function
int ExtendedEuclidAlgGCD (int a, int b, int &s, int &t)
{
  if (b == 0)
    {
      s = 1;
      t = 0;
      return a;
    }
  int s1, t1;
  int d = ExtendedEuclidAlgGCD (b, a % b, s1, t1);
  s = t1;
  t = s1 - (a / b) * t1;
  return d;
}

int mod (int a, int n)
{
  int z = a % n;
  if (z < 0)
    {
      z += n;
    }
  return z;
}

int RelativelyPrime (int n)
{
  for (int i = 2; i < n; i++)
    {
      if (EuclidAlgGCD (i, n) == 1)
	{
	  return i;
	}
    }
  return -1;			// if there will be no prime relative number found
}

int inverse (int a, int n)
{
  int s, t;
  int d = ExtendedEuclidAlgGCD (n, a, s, t);
  if (d == 1)
    {
      return mod (t, n);
    }
  else
    {
      cout << "a and n are not relatively prime" << endl;
      return 0;
    }
}

int Encode (int M, int e, int PQ)
{
  int encoded = 1;
  for (int i = 0; i < e; i++)
    {
      encoded = (encoded * M) % PQ;
    }
  return encoded;
}

int Decode (int C, int d, int PQ)
{
  int decoded = 1;
  for (int i = 0; i < d; i++)
    {
      decoded = (decoded * C) % PQ;
    }
  return decoded;
}

int main ()
{
  // choosing two prime numbers, P & Q
  const int P = 11;
  const int Q = 29;
  int phi = (P - 1) * (Q - 1);
  int PQ = P * Q;
  // e is equivalent to the relative prime of phi: (p-1)*(q-1)
  int e = RelativelyPrime (phi);
  // d is equal to inverse modular of e and phi
  int d = inverse (e, phi);
  // input for message
  int M;
  cout << "Enter an integer that is smaller than PQ = " << PQ << " ";
  cin >> M;
  // calling the encoding function
  int C = Encode (M, e, PQ);
  // calling the decoding function
  int M1 = Decode (C, d, PQ);
  cout << "P: " << P << endl;
  cout << "Q: " << Q << endl;
  cout << "Phi: " << phi << endl;
  cout << "E:  " << e << endl;
  cout << "D: " << d << endl;
  // output of encrypted message
  cout << "Encrypted Message: " << C << endl;
  // output of decrypted message
  cout << "Decrypted Message: " << M1 << endl;
  // test to see if the new message is the same as the inputted message
  assert (M == M1);
}
