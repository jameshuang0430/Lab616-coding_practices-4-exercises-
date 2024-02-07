#include <iostream>
using namespace std;
int input;
int sum = 0;
bool isPrime(int number);

int main(void)
{
	cout << "Please enter a positive number." << endl;
	cin >> input;

	if (input > 0)
	{
		for (int i = 2; i <= input; i++)
		{
			if (isPrime(i))
			{
				sum = sum + i;
			}
		}
		cout << "The sum is: " << sum << endl;
	}
	else
	{
		cout << "It is not a positive number." << endl;
	}
	
}

bool isPrime(int number)
{
	for (int k=2; k < number; k++)
	{
		if (number % k == 0)
		{
			return false;
		}
	}
	return true;
}