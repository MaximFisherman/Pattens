#pragma once
#include "stdafx.h"
using namespace std;

class Figure
{
public:
	virtual void draw() = 0;
	virtual ~Figure() {};
};

struct PointProps
{
	char type;
	HANDLE hCon;
};


class Point
{
	PointProps pointProps;
	short x, y;
public:
	Point(PointProps _pointProps, short _x, short _y) : x(_x), y(_y), pointProps(_pointProps)
	{
	}

	virtual void draw()
	{
		SetConsoleCursorPosition(pointProps.hCon, COORD{ x, y });
		cout << pointProps.type;
	}
};



class FlyWeightFactory
{
protected: 
	vector<PointProps> vectPropsPoint;
public:
	PointProps getPointProps(HANDLE _hCor, char _type)
	{
		vector<PointProps>::const_iterator it = find_if(vectPropsPoint.begin(), vectPropsPoint.end(), [=](PointProps& p) { return (p.hCon == _hCor && p.type == _type); });
		if (it == vectPropsPoint.end())
		{
			vectPropsPoint.push_back(PointProps{ _type, _hCor});
			return vectPropsPoint[vectPropsPoint.size() - 1];
		}
		else
		{
			return *it;
		}
	}
};

class Circle : public Figure
{
	int R = 6;
	int x = 12, y = 12;
	vector<Point> vectPoint;
public:
	Circle(int _x, int _y, int _r) : x(_x), y(_y), R(_r)
	{
		FlyWeightFactory flyFactory;
		PointProps props = flyFactory.getPointProps(GetStdHandle(STD_OUTPUT_HANDLE), '0');

		for (int i = x - R; i < x + R; i++)
		{
			for (int j = y - R; j < y + R; j++)
			{
				if ((pow((i - x), 2) + pow((j - y), 2) ) < pow(R, 2))
				{
					vectPoint.push_back(Point(props, i, j));
				}
			}
		}
	};

	virtual void draw() override
	{
		for_each(begin(vectPoint), end(vectPoint), [](Point& p) { p.draw(); });
	}
};