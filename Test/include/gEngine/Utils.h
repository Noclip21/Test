#ifndef UTILS_H
#define UTILS_H
#define PI 3.14159265

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;


#include "prologue.h"
namespace utils
{
	struct vector2
	{
		double x,y;

		inline vector2()						{ x = 0; y = 0;										}
		inline vector2(double px,double py)		{ x = px; y = py;									}
		inline vector2 operator = (double n)	{ return vector2(n,n);								}
		inline vector2 operator + (double n)	{ return vector2(x+n,y+n);							}
		inline vector2 operator - (double n)	{ return vector2(x-n,y-n);							}
		inline vector2 operator * (double n)	{ return vector2(x*n,y*n);							}
		inline vector2 operator + (vector2 &v2) { return vector2(x+v2.x,y+v2.y);					}
		inline vector2 operator - (vector2 &v2) { return vector2(x-v2.x,y-v2.y);					}
		inline vector2 operator * (vector2 &v2) { return vector2(x*v2.x,y*v2.y);					}
	};
	struct vector3
	{
		double x,y,z;

		inline vector3()								{ x = y = z = 0;										}
		inline vector3(	double px,double py,double pz)	{ x = px; y = py; z = pz;								}
		inline vector3 operator = (double n)			{ return vector3(n,n,n);								}
		inline vector3 operator + (double n)			{ return vector3(x+n,y+n,z+n);							}
		inline vector3 operator - (double n)			{ return vector3(x-n,y-n,z-n);							}
		inline vector3 operator * (double n)			{ return vector3(x*n,y*n,z*n);							}
		inline vector3 operator + (vector3 &v3)			{ return vector3(x+v3.x,y+v3.y,z+v3.z);					}
		inline vector3 operator - (vector3 &v3)			{ return vector3(x-v3.x,y-v3.y,z-v3.z);					}
		inline vector3 operator * (vector3 &v3)			{ return vector3(x*v3.x,y*v3.y,z*v3.z);					}
	};

	
	static string toStringi(int n)
	{
		stringstream ss;
		ss << n;
		return ss.str();
	}
	static string toStringd(double n)
	{
		stringstream ss;
		ss << n;
		return ss.str();
	}


		// Array methods
	template <class T>
	static int findObject(T &obj,vector<T*> &v)
	{
		for(size_t i=0; i < v.size(); i++)
			if(&obj == v[i]) return i;
		return -1;
	}
	template <class T>
	static int findObject(T &obj,vector<T> &v)
	{
		for(size_t i=0; i < v.size(); i++)
			if(obj == v[i]) return i;
		return -1;
	}


	template <typename T>
	static bool removeObject(T &obj,vector<T*> &v)
	{
		int pos = findObject(obj,v);
		if(pos >= 0)
		{
			v.erase(v.begin()+pos);
			return true;
		}
		return false;
	}
	template <typename T>
	static bool removeObject(T &obj,vector<T> &v)
	{
		int pos = findObject(obj,v);
		if(pos >= 0)
		{
			v.erase(v.begin()+pos);
			return true;
		}
		return false;
	}


		// Math functions
	static double dist(vector2 p1,vector2 p2)
	{
		return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
	}
	static double ang(vector2 p1,vector2 p2)
	{
		double angle = 0;
		if(p1.x-p2.x != 0)
			angle = atan((p1.y-p2.y)/(p1.x-p2.x));

		if(p1.x < p2.x) return angle;
		else			return angle + PI;
	}
	static bool left(vector2 p,vector2 lp1,vector2 lp2)
	{
		if(lp1.y == lp2.y) return (p.y < lp1.y && p.y < lp2.y);
		if(lp1.x == lp2.x) return (p.x < lp1.x);
			
		double a = (lp2.y - lp1.y)/(lp2.x - lp1.x);
		double b = lp1.y - a*lp1.x;
		double x = (p.y - b)/a;
			
		return (p.x < x);
	}
	static bool segIntersec(vector2 l1p1,vector2 l1p2,vector2 l2p1,vector2 l2p2)
	{
		return (left(l1p1,l2p1,l2p2) != left(l1p2,l2p1,l2p2) &&
				left(l2p1,l1p1,l1p2) != left(l2p2,l1p1,l1p2));
	}
}
#include "epilogue.h"

#endif