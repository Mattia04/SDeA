#include <iostream>
#include "common/timing.hpp"

using namespace std;

int main()
{
	common::StopWatch sw;

	for (int i = 0; i < 1000; ++i)
	{
		sw.start();
		sw.stop();
	}

	cout << sw.elapsed_average() << endl;
	cout << sw.elapsed_stddev() << endl;

	return 0;
}
