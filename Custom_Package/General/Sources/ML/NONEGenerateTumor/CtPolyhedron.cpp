// includes
#include "CtPolyhedron.h"

#include <map>
#include <set>

#include <fstream>

#include <iostream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <random>

using namespace std;



//! Constructor
CtPolyhedron::CtPolyhedron(int maxDiameter, int precision, int neighbors)
{

	_maxDiameter = maxDiameter;
	_precision = precision;
	_neighbors = neighbors;

	if (maxDiameter < 0)
		_precision = 0;

	if (_precision < 0)
		_precision = 0;

	if (_precision > 6)
		_precision = 7;

	if (_neighbors < 0)
		_neighbors = -1;

	_neighbors = 0;

	createRefineMeshes();
}


//! Destructor
CtPolyhedron::~CtPolyhedron()
{
	icos12.clear();
	icos32.clear();
	icos92.clear();
	icos272.clear();
	icos812.clear();
	icos2432.clear();
	icos7296.clear();
	icos21876.clear();
}


//-----------------------------------------------------------------------------------------------//
//! check ico
//-----------------------------------------------------------------------------------------------//
bool CtPolyhedron::checkIco(int refineIco, std::vector<SbVec3f> &icos)
{
	if (refineIco == 12)
	{
		if (icos12.size() != 12)
			return false;

		icos = icos12;
	}

	else if (refineIco == 32)
	{
		if (icos32.size() != 32)
			return false;

		icos = icos32;
	}

	else if (refineIco == 92)
	{
		if (icos92.size() != 92)
			return false;

		icos = icos92;
	}

	else if (refineIco == 272)
	{
		if (icos272.size() != 272)
			return false;

		icos = icos272;
	}

	else if (refineIco == 812)
	{
		if (icos812.size() != 812)
			return false;

		icos = icos812;
	}

	else if (refineIco == 2432)
	{
		if (icos2432.size() != 2432)
			return false;

		icos = icos2432;
	}

	else if (refineIco == 7296)
	{
		if (icos7296.size() != 7296)
			return false;

		icos = icos7296;
	}

	else if (refineIco == 21876)
	{
		if (icos21876.size() != 21876)
			return false;

		icos = icos21876;
	}

	else
	{
		return false;
	}

	return true;
}


//-----------------------------------------------------------------------------------------------//
// Create the meshes for the icosahedrons
//-----------------------------------------------------------------------------------------------//
void CtPolyhedron::createRefineMeshes()
{
	icos12.clear();
	icos32.clear();
	icos92.clear();
	icos272.clear();
	icos812.clear();
	icos2432.clear();
	icos7296.clear();
	icos21876.clear();

	// set up the facePoints vector
	const int facePoints[4 * 20] = {
		0, 8, 4, -1,   //  0
		0, 5, 10, -1,  //  1
		2, 4, 9, -1,   //  2
		2, 11, 5, -1,  //  3
		1, 6, 8, -1,   //  4
		1, 10, 7, -1,  //  5
		3, 9, 6, -1,   //  6
		3, 7, 11, -1,  //  7
		0, 10, 8, -1,  //  8
		1, 8, 10, -1,  //  9
		2, 9, 11, -1,  // 10
		3, 11, 9, -1,  // 11
		4, 2, 0, -1,   // 12
		5, 0, 2, -1,   // 13
		6, 1, 3, -1,   // 14
		7, 3, 1, -1,   // 15
		8, 6, 4, -1,   // 16
		9, 4, 6, -1,   // 17
		10, 5, 7, -1,  // 18
		11, 7, 5, -1   // 19
	};

	_vecFacePoints.clear();
	_vecFacePoints.assign(&(facePoints[0]), &(facePoints[4 * 20]));

	// calculate the parameters for the coordinates
	float phi = 0.5 * (sqrt(5.0) + 1.0);
	float b = 1.0 / sqrt(1.0 + phi * phi) * _maxDiameter;
	float a = phi * b;
	float z = 0.0;

	// set up the pointCoords vector
	float pointCoords[3 * 12] = {
		a,  b,  z,    //  0
		-a,  b,  z,    //  1
		a, -b,  z,    //  2
		-a, -b,  z,    //  3
		b,  z,  a,    //  4
		b,  z, -a,    //  5
		-b,  z,  a,    //  6
		-b,  z, -a,    //  7
		z,  a,  b,    //  8
		z, -a,  b,    //  9
		z,  a, -b,    // 10
		z, -a, -b     // 11
	};

	_vecPointCoords.clear();
	_vecPointCoords.assign(&(pointCoords[0]), &(pointCoords[3 * 12]));

	// fill icos12
	icosFill(_vecPointCoords);

	for (int i = 0; i<_precision; i++)
	{
		// refine
		createRefineMeshes2(_vecFacePoints, _vecPointCoords, _maxDiameter);
		// fill icos32
		icosFill(_vecPointCoords);

	}

	if (_vecPointCoords.size() == 36) // 3*12
	{
		std::cout << "Generation of synthetic tumor succeeded" << std::endl;
	}

	else if (_vecPointCoords.size() == 96) // 3*32
	{
		std::cout << "Generation of synthetic tumor succeeded" << std::endl;
	}
	else if (_vecPointCoords.size() == 276) // 3*92
	{
		std::cout << "Generation of synthetic tumor succeeded" << std::endl;
	}

	else if (_vecPointCoords.size() == 816) // 3*272
	{
		std::cout << "Generation of synthetic tumor succeeded" << std::endl;
	}

	else if (_vecPointCoords.size() == 2436) // 3*812
	{
		std::cout << "Generation of synthetic tumor succeeded" << std::endl;
	}

	else if (_vecPointCoords.size() == 7296) // 3*2432
	{
		std::cout << "Generation of synthetic tumor succeeded" << std::endl;
	}
	else if (_vecPointCoords.size() == 21876) // 3*7292
	{
		std::cout << "Generation of synthetic tumor succeeded" << std::endl;
	}
	else if (_vecPointCoords.size() == 65616) // 3*21872
	{
		std::cout << "Generation of synthetic tumor succeeded" << std::endl;
	}
	else
		std::cout << "unknown ico size " << std::endl;


	// set color
	_rgbas.clear();
	uint32_t color = SbColor(0.95f, 0.95f, 0.95f).getPackedValue();
	uint32_t nColor = SbColor(1.0f, 0.f, 0.f).getPackedValue();


	for (int c = 0; c<(int)_vecPointCoords.size() / 3; c++)
	{
		_rgbas.push_back(color);
	}

	set<int>::iterator it;
	std::set<int> all_neighbours;

	float d;
	float mult;
	float m = 0.97;
	uint32_t newColor;
	std::vector<int> _tempVec;
	std::vector<int> _newNeighbours;

	float upper;
	float lower;

	upper = 2.5;
	lower = 1.0;

	//choose 7 vertices randomly and displace vertices
	for (int count = 0; count < 7; count++)
	{

		// randomly choose strength of displacement
		std::random_device rd1; // obtain a random number from hardware
		std::mt19937 eng1(rd1()); // seed the generator
		std::uniform_real_distribution<> distr1(lower, upper); // define the range


		d = distr1(eng1);  // displacement
		mult = 1 + d;	   // displacement factor

		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, 2432); // define the range

		_neighbors = distr(eng); // randomly choose vertex to displace

		all_neighbours.insert(_neighbors);

		// displace randomly chosen vertex accordingly
		_vecPointCoords[_neighbors * 3] *= mult;
		_vecPointCoords[_neighbors * 3 + 1] *= mult;
		_vecPointCoords[_neighbors * 3 + 2] *= mult;


		//reduce displacement factor for subsequent displacement of remaining vertices
		d *= m;
		mult = 1 + d;

		calcNeighbors();
		std::copy(_neighborsVec.begin(), _neighborsVec.end(), std::inserter(all_neighbours, all_neighbours.end()));

		//displace vertices
		for (int i = 0; i < _neighborsVec.size(); i++)
		{
			_vecPointCoords[_neighborsVec[i] * 3] *= mult;
			_vecPointCoords[_neighborsVec[i] * 3 + 1] *= mult;
			_vecPointCoords[_neighborsVec[i] * 3 + 2] *= mult;
		}


		//reduce displacement factor for subsequent displacement of remaining vertices
		d *= pow(m, 2);
		mult = 1 + d;

		_tempVec = _neighborsVec;

		for (int k = 0; k <45; k++)
		{

			mult = 1 + d;


			for (int j = 0; j < _tempVec.size(); j++)
			{
				_neighbors = _tempVec[j];
				calcNeighbors();

				for (int point = 0; point < (int)_neighborsVec.size(); point++)
				{

					if (all_neighbours.find(_neighborsVec[point]) == all_neighbours.end())
					{
						_newNeighbours.push_back(_neighborsVec[point]);
						all_neighbours.insert(_neighborsVec[point]);
					}
				}
			}

			for (int i = 0; i < _newNeighbours.size(); i++)
			{
				//displace vertices (subsequent displacement)
				_vecPointCoords[_newNeighbours[i] * 3] *= mult;
				_vecPointCoords[_newNeighbours[i] * 3 + 1] *= mult;
				_vecPointCoords[_newNeighbours[i] * 3 + 2] *= mult;
			}

			//save current neighbours in _tempVec
			_tempVec = _newNeighbours;

			// clear _newNeighbours
			_newNeighbours.clear();

			//reduce displacement factor
			d *= pow(m, 2);

		}

		//clear all vectors and lists
		_newNeighbours.clear();
		_tempVec.clear();
		all_neighbours.clear();
		_neighborsVec.clear();

	}

}


//-----------------------------------------------------------------------------------------------//
// Fill an icos vector
//-----------------------------------------------------------------------------------------------//
void CtPolyhedron::icosFill(std::vector<float> &_vecPointCoords)
{
	for (int i = 0; i < (int)_vecPointCoords.size(); i = i + 3)
	{
		SbVec3f tmp(_vecPointCoords[i], _vecPointCoords[i + 1], _vecPointCoords[i + 2]);

		if (_vecPointCoords.size() == 36) // 3*12
		{
			icos12.push_back(tmp);
		}
		else if (_vecPointCoords.size() == 96) // 3*32
		{
			icos32.push_back(tmp);
		}
		else if (_vecPointCoords.size() == 276) // 3*92
		{
			icos92.push_back(tmp);
		}
		else if (_vecPointCoords.size() == 816) // 3*272
		{
			icos272.push_back(tmp);
		}
		else if (_vecPointCoords.size() == 2436) // 3*812
		{
			icos812.push_back(tmp);
		}
		else if (_vecPointCoords.size() == 7296) // 3*2432
		{
			icos2432.push_back(tmp);
		}
		else if (_vecPointCoords.size() == 21876) // 3*7292
		{
			icos7296.push_back(tmp);
		}
		else if (_vecPointCoords.size() == 65616) // 3*21872
		{
			icos21876.push_back(tmp);
		}
	}
}


//-----------------------------------------------------------------------------------------------//
// Create the meshes for the icosahedrons 2
//-----------------------------------------------------------------------------------------------//
void CtPolyhedron::createRefineMeshes2(std::vector<int> &_vecFacePoints,
	std::vector<float> &_vecPointCoords,
	int maxDiameter)
{
	_neighborsVec.clear();

	// create the new center points
	int vecPointCoordsSize3 = _vecPointCoords.size() / 3; // get number of coords (/3 because of x, y, z)
	std::multimap<int, int> mapPointTriangle;
	SbVec3f center(0., 0., 0.);
	std::vector<int>::iterator it;
	int triNum = 0;
	for (it = _vecFacePoints.begin(); it != _vecFacePoints.end(); it++) // loop over indices of triangles
	{
		if (*it != -1)
		{
			center += SbVec3f(_vecPointCoords[*it * 3 + 0],
				_vecPointCoords[*it * 3 + 1],
				_vecPointCoords[*it * 3 + 2]);

			mapPointTriangle.insert(std::pair<int, int>(*it, triNum)); // map a point to a triangle
		}
		else // end of triangle (-1) reached
		{
			center *= maxDiameter / center.length();

			// push bach new coord (center of one existing traingle)
			_vecPointCoords.push_back(center[0]);
			_vecPointCoords.push_back(center[1]);
			_vecPointCoords.push_back(center[2]);

			center = SbVec3f(0., 0., 0.);
			triNum++;
		}
	}

	// create new triangles including all new points
	std::vector<int> vecNewFacePoints;
	for (int i = 0; i < vecPointCoordsSize3; i++) // loop over coords
	{
		SbVec3f point(_vecPointCoords[i * 3], _vecPointCoords[i * 3 + 1], _vecPointCoords[i * 3 + 2]); // get coord
		std::multimap<int, int>::iterator itBegin = mapPointTriangle.lower_bound(i);
		std::multimap<int, int>::iterator itEnd = mapPointTriangle.upper_bound(i);

		// create a sorted triangles list at current point
		std::list<int> triangles;
		{
			std::list<int> tmpTriangles;
			std::multimap<int, int>::iterator it;
			for (it = itBegin; it != itEnd; it++)
			{
				tmpTriangles.push_back(it->second);
			}
			
			triangles.push_back(tmpTriangles.front());
			tmpTriangles.pop_front();
			while (!tmpTriangles.empty())
			{
				int lastTriangle[] = {
					_vecFacePoints[triangles.back() * 4],
					_vecFacePoints[triangles.back() * 4 + 1],
					_vecFacePoints[triangles.back() * 4 + 2],
					-1
				};
				std::list<int>::iterator it;

				for (it = tmpTriangles.begin(); it != tmpTriangles.end(); it++)
				{
					std::set<int> setUnion(&(lastTriangle[0]), &(lastTriangle[3]));
					setUnion.insert(_vecFacePoints[*it * 4]);
					setUnion.insert(_vecFacePoints[*it * 4 + 1]);
					setUnion.insert(_vecFacePoints[*it * 4 + 2]);

					if (setUnion.size() == 4)
					{
						triangles.push_back(*it);
						tmpTriangles.erase(it);
						break;
					}
				} 
			} 
		} 

		  // create new triangles for current point
		int centerPointIndexPrev = triangles.back() + vecPointCoordsSize3;
		std::list<int>::iterator it;
		for (it = triangles.begin(); it != triangles.end(); it++)
		{
			int centerPointIndex = *it + vecPointCoordsSize3;

			SbVec3f diff(point);
			diff -= SbVec3f(_vecPointCoords[centerPointIndex * 3],
				_vecPointCoords[centerPointIndex * 3 + 1],
				_vecPointCoords[centerPointIndex * 3 + 2]);

			SbVec3f diffPrev(point);
			diffPrev -= SbVec3f(_vecPointCoords[centerPointIndexPrev * 3],
				_vecPointCoords[centerPointIndexPrev * 3 + 1],
				_vecPointCoords[centerPointIndexPrev * 3 + 2]);

			if (diff.cross(diffPrev).dot(point) < 0)
			{
				vecNewFacePoints.push_back(i);
				vecNewFacePoints.push_back(centerPointIndexPrev);
				vecNewFacePoints.push_back(centerPointIndex);
				vecNewFacePoints.push_back(-1);
			}
			else
			{
				vecNewFacePoints.push_back(i);
				vecNewFacePoints.push_back(centerPointIndex);
				vecNewFacePoints.push_back(centerPointIndexPrev);
				vecNewFacePoints.push_back(-1);
			}

			centerPointIndexPrev = centerPointIndex;
		} 
	} 

	_vecFacePoints.swap(vecNewFacePoints);
}


void CtPolyhedron::calcNeighbors()
{
	// loop over the facepoints
	for (int jj = 0; jj<(int)_vecFacePoints.size() - 3; jj += 4)
	{
		// check if one of the facepoints (index) belongs to a triangle -> the remaining two points are neighbors

		if (_vecFacePoints[jj] == _neighbors)
		{
			if (insideVector(_neighborsVec, _vecFacePoints[jj + 1]) == false)
				_neighborsVec.push_back(_vecFacePoints[jj + 1]);

			if (insideVector(_neighborsVec, _vecFacePoints[jj + 2]) == false)
				_neighborsVec.push_back(_vecFacePoints[jj + 2]);

		}
		else if (_vecFacePoints[jj + 1] == _neighbors)
		{
			if (insideVector(_neighborsVec, _vecFacePoints[jj]) == false)
				_neighborsVec.push_back(_vecFacePoints[jj]);

			if (insideVector(_neighborsVec, _vecFacePoints[jj + 2]) == false)
				_neighborsVec.push_back(_vecFacePoints[jj + 2]);


		}
		else if (_vecFacePoints[jj + 2] == _neighbors)
		{
			if (insideVector(_neighborsVec, _vecFacePoints[jj]) == false)
				_neighborsVec.push_back(_vecFacePoints[jj]);

			if (insideVector(_neighborsVec, _vecFacePoints[jj + 1]) == false)
				_neighborsVec.push_back(_vecFacePoints[jj + 1]);


		}

	}
}


bool CtPolyhedron::insideVector(std::vector<int> vector, int value)
{
	for (int i = 0; i<(int)vector.size(); i++)
	{
		if (vector[i] == value)
			return true;
	}

	return false;
}

