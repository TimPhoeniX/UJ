#include <iostream>
#include <ctime>

double silnia(double n)
{
	if(n==0.)
		return 1.;
	else
		return n*silnia(n-1.);
}

int main(void)
{
	std::clock_t t = std::clock();
	double s = silnia(500);
	t = std::clock() - t;
	std::cout << double(t)/CLOCKS_PER_SEC << '\n';
}