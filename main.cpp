#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <string>

struct Point
{
	int x;
	int y;

	Point() : x(0), y(0)
	{

	}
};

void Scalar(int _quentityElement)
{
	std::vector<Point> _vecOne(_quentityElement);
	std::vector<Point> _vecSecond(_quentityElement);

	for (int i = 0; i < _quentityElement; i++)
	{
		_vecOne[i].x	= rand() % _quentityElement + 0;
		_vecOne[i].y	= rand() % _quentityElement + 0;
		_vecSecond[i].x = rand() % _quentityElement + 0;
		_vecSecond[i].y = rand() % _quentityElement + 0;
	}

	std::chrono::time_point<std::chrono::system_clock> _start, _end;
	_start = std::chrono::system_clock::now();
#pragma omp parallel
	{
		int _temp;
#pragma omp for
		for (int i = 0; i < _quentityElement; i++)
		{
			std::cout << _vecOne[i].x * _vecSecond[i].x + _vecOne[i].y * _vecSecond[i].y << " thread : ";
			std::cout << omp_get_thread_num() << std::endl;
		}
	}
	_end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = _end - _start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(_end);

	std::cout << "elapsed time element for "<< _quentityElement << " : " << elapsed_seconds.count() << std::endl;
}

double Integral(double(*f)(double x), double a, double b, int n)
{
    double step = (b - a) / n;
    double area = 0.0;  
    for (int i = 0; i < n; i ++) 
	{
        area += f(a + (i + 0.5) * step) * step;
    }

	std::string _str(std::to_string(area));
	
	int _index = 0;
	while (true)
	{
		std::cout << _str[_index];
		if (++_index == 7)
		{
			break;
		}
	}

	std::cout << std::endl;

    return area;
}

double FunctionForIntegral(double _x)
{
	return (_x * _x) / 3;
}

int main()
{
	Scalar(100);
	Scalar(1000);
	Scalar(10000);

	Integral(FunctionForIntegral, 4, 12, 30);

	system("pause");
	return 0;
}