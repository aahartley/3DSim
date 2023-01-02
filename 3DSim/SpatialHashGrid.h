#pragma once
#include "Vector3f.h"
#include "Particle.h"
#include "ParticleCollision.h"
#include "Polygon.h"
#include <vector>

struct Voxel {
	Voxel() {};
	bool filled = false;
	std::vector<Polygon*> polys;
	Vector3f index;
};
class SpatialHashGrid {
public:
	SpatialHashGrid(Vector3f dimensions, float spacing, Vector3f origin);
	void initializeGrid(std::vector<Polygon*>& polys);
	void checkCollision(Particle& p);
	void fixLoop(int& xmin, int& xmax, int& ymin, int& ymax, int& zmin, int& zmax);
	Voxel*** voxels;
	//x + y * m_width + z * m_width * m_height
private:
	Vector3f dim;
	int spacing;
	Vector3f origin;
	int width = 0;
	int height = 0;
	int depth = 0;
};