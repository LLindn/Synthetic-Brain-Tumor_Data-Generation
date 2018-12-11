#ifndef __CTPOLYHEDRON_H
#define __CTPOLYHEDRON_H


// includes
#include <inventor/nodes/SoSeparator.h>
#include <inventor/nodes/SoVertexProperty.h>
#include <inventor/nodes/SoIndexedFaceSet.h>


#include <vector>
#include <list>
#include <inventor/SbLinear.h>

#include <iostream>


class CtPolyhedron
{
  
public:

	//! Constructor
	CtPolyhedron(int maxDiameter, int precision, int neighbors);
	
	//! Destructor
	virtual ~CtPolyhedron();

	inline int getMaxDiameter()
	{
		return _maxDiameter;
	}

	inline void setMaxDiameter(int maxDiameter)
	{
		_maxDiameter = maxDiameter;

		createRefineMeshes();
	}

	inline std::vector<int> getVecFacePoints()
	{
		return _vecFacePoints;
	};

	inline std::vector<float> getVecPointCoords()
	{
		return _vecPointCoords;
	};

	inline std::vector<uint32_t> getVecRgbas()
	{
		return _rgbas;
	};

protected:


private:

	std::vector<int> _vecFacePoints;
	std::vector<float> _vecPointCoords;
	std::vector<uint32_t> _rgbas;

	std::vector<SbVec3f> icos12;
	std::vector<SbVec3f> icos32;
	std::vector<SbVec3f> icos92;
	std::vector<SbVec3f> icos272;
	std::vector<SbVec3f> icos812;
	std::vector<SbVec3f> icos2432;
	std::vector<SbVec3f> icos7296;
	std::vector<SbVec3f> icos21876;

	void createRefineMeshes();

	void createRefineMeshes2(std::vector<int> &_vecFacePoints,
							 std::vector<float> &_vecPointCoords,
							 int maxDiameter);

	void icosFill(std::vector<float> &_vecPointCoords);

	bool checkIco(int refineIco, std::vector<SbVec3f> &icos);

	void calcNeighbors();
	bool insideVector(std::vector<int> vector, int value);

	int _maxDiameter;
	int _precision;
	int _neighbors;

	std::vector<int> _neighborsVec;
};



#endif // __CTPOLYHEDRON_H
