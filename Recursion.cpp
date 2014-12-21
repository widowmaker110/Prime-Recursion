/*
* This program uses recursion within multi-threading
* to generate the prime factorization of any number up to 
* the max number allowed by long long. On 10/13/2014 the max number
* is 9223372036854775807 in a long long variable in the C++ language.
* 
* By implmenting the developer mode to 'true'
* I computed all of the data below: 
*
* 781859189285709554;
* 782050905290201849;
* 349956174030208996;
* 869723665327180202;
* 
* in about 0.052 seconds on my laptop:
*
* HP pavilion DV7-6b32us 8GB RAM, i7 qaud core processor
*
* Author: Alexander Miller
* Date: 10/13/2014
*/

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<thread> threads;
vector<long long> inputVector;
bool developer = true; 
int numPrimes;

class PrimeNumber
{
	long long initValue;		// the number being prime factored
	vector<long long> factors;  // all of the factor values
public:
	void setInitValue(long long n)
	{
		initValue = n;
	}
	void addToVector(long long m)
	{
		factors.push_back(m);
	}
	void setVector(vector<long long> m)
	{
		factors = m;
	}
	long long getInitValue()
	{
		return initValue;
	}
	vector<long long> getVector()
	{
		return factors;
	}
};

vector<PrimeNumber> primes;

// find primes recursively and have them returned in vectors
vector<long long> getPrimes(long long n, vector<long long> vec)
{
	if (n % 2 == 0)
	{
		return vec.push_back(2), getPrimes(n / 2, vec); //cause recursion
	}

	if (n % 3 == 0)
	{
		return vec.push_back(3), getPrimes(n / 3, vec); //cause recursion
	}

	double sqrt_of_n = sqrt(n);

	for (int i = 5; i <= sqrt_of_n; i = i + 2)
	{	
		if (n % i == 0) 
		{
			return vec.push_back(i), getPrimes(n / i, vec); //cause recursion
		}
	}
	
	// pick up the last prime factorization number
	vec.push_back(n);
	
	//return the finished vector
	return vec;
}

void getUserInput()
{
	long long input = -1;
	cout << "Enter all of the numbers to find their prime factors. Enter 0 to compute" << endl;
	do
	{
		cin >> input;
		if (input >= 9223372036854775807)
		{
			cout << "Sorry but that number is too large. Please try a smaller number" << endl;
			cin >> input;
		}
		
		if (input == 0)
		{
			break;
		}
		
		inputVector.push_back(input);
	} while (input != 0);
}

int main() 
{
	vector<long long> temp1;   // empty vector
	vector<long long> result1; // temp vector
	
	if (developer == false)
	{
		getUserInput();
	}
	else
	{
		cout << "developer mode active" << endl;
		cout << endl;

		long long m1 = 781859189285709554;
		long long m2 = 782050905290201849;
		long long m3 = 349956174030208996;
		long long m4 = 869723665327180202;

		inputVector.push_back(m1);
		inputVector.push_back(m2);
		inputVector.push_back(m3);
		inputVector.push_back(m4);
	}
	
	high_resolution_clock::time_point time1 = high_resolution_clock::now();
	
	if (inputVector.size() % 4 == 0)
	{
		// finding out the points in the array to optimize the run time
		int fourth = inputVector.size() / 4;
		int half = inputVector.size() / 2;
		int threeFourth = half + fourth;

		// give each thread a number to comput within the recursive function
		for (int i = 0; i < fourth; i++)
		{
			threads.push_back(thread([&]{
				PrimeNumber prime;
				prime.setInitValue(inputVector.at(i));
				prime.setVector(result1 = getPrimes(inputVector.at(i), temp1));
				primes.push_back(prime);
			}));
		}

		// give each thread a number to comput within the recursive function
		for (int i = fourth; i < half; i++)
		{
			threads.push_back(thread([&]{
				PrimeNumber prime;
				prime.setInitValue(inputVector.at(i));
				prime.setVector(result1 = getPrimes(inputVector.at(i), temp1));
				primes.push_back(prime);
			}));
		}

		// give each thread a number to comput within the recursive function
		for (int i = half; i < threeFourth; i++)
		{
			threads.push_back(thread([&]{
				PrimeNumber prime;
				prime.setInitValue(inputVector.at(i));
				prime.setVector(result1 = getPrimes(inputVector.at(i), temp1));
				primes.push_back(prime);
			}));
		}

		// give each thread a number to comput within the recursive function
		for (int i = threeFourth; i < inputVector.size(); i++)
		{
			threads.push_back(thread([&]{
				PrimeNumber prime;
				prime.setInitValue(inputVector.at(i));
				prime.setVector(result1 = getPrimes(inputVector.at(i), temp1));
				primes.push_back(prime);
			}));
		}

	}
	else
	{
		// give each thread a number to comput within the recursive function
		for (int i = 0; i < inputVector.size(); i++)
		{
			threads.push_back(thread([&]{
				PrimeNumber prime;
				prime.setInitValue(inputVector.at(i));
				prime.setVector(result1 = getPrimes(inputVector.at(i), temp1));
				primes.push_back(prime);
			}));
		}
	}
	
	
	// allow all of the threads to join back together.
	for (auto& th : threads)
	{
		th.join();
	}

	high_resolution_clock::time_point time2 = high_resolution_clock::now();

	// print all of the information
	for (int i = 0; i < primes.size(); i++)
	{
		cout << "Factorization of: " << primes.at(i).getInitValue() << endl;
		vector<long long> temp = primes.at(i).getVector();
		cout << "Prime: ";
		for (int m = 0; m < temp.size(); m++)
		{
			cout << temp.at(m) << " ";
			numPrimes++;
		}
		cout << endl;
		cout << endl;
	}

	cout << endl;

	cout << "There are " << numPrimes << " Primes" <<  endl;

	cout << endl;

	// so the running time
	auto duration = duration_cast<microseconds>(time2 - time1).count();

	cout << "Duration in seconds: " << (duration / 1000000.0) << endl;
	
	return 0;
}
