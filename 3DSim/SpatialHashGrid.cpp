#include "SpatialHashGrid.h"

SpatialHashGrid::SpatialHashGrid(Vector3f dimensions, float spacing,Vector3f origin) {
	this->dim = dimensions;
	this->spacing = spacing;
	this->width = dim.x / spacing; 
	this->height = dim.y/ spacing;
	this->depth = dim.z / spacing;
	this->origin = origin;

	voxels = new Voxel**[depth];

	for (int p = 0; p < depth; p++) {
		voxels[p] = new Voxel* [height];
		for (int r = 0; r < height; r++) {  //switch to width?
			voxels[p][r] = new Voxel[width];
			for (int c = 0; c < width; c++) {
				voxels[p][r][c] =  Voxel();
				//std::cout << p << ' ' << r << ' ' << c << '\n';

			}
		}
	}

}

void SpatialHashGrid::initializeGrid(std::vector<Polygon*>& polygons) {
	
	for (int j = 0; j < polygons.size(); j++) {
		if (polygons[j]->getType() == PLANE) {
			Plane plane = (Plane&)*polygons[j];
		
			int cmin = (int)(plane.xmin - origin.x) / spacing;
			int rmin = (int)(plane.ymin - origin.y) / spacing;
			int cmax = (int)(plane.xmax - origin.x) / spacing;
			int rmax = (int)(plane.ymax - origin.y) / spacing;
			int pmin = (int)(plane.zmin - origin.z) / spacing;
			int pmax = (int)(plane.zmax - origin.z) / spacing;
			if (rmin == rmax) {
				if (rmin == 0) {
					rmax++;
				}
				else if (rmax == height - 1) {
					rmin--;
				}
				else rmax++;
			}
			if (cmin == cmax) {
				if (cmin == 0) {
					cmax++;
				}
				else if (cmax == width - 1) {
					cmin--;
				}
				else cmax++;
			}
			if (pmin == pmax) {
				if (pmin == 0) {
					pmax++;
				}
				else if (pmax == depth - 1) {
					pmin--;
				}
				else pmax++;
			}
	

			//std::cout << pmin << ' ' << pmax << ' ' << rmin << ' ' << rmax << ' ' << cmin << ' ' << cmax << '\n';
			for (int p = pmin; p < pmax; p ++) {
				for (int r = rmin; r < rmax; r ++) {
					for (int c = cmin; c < cmax; c ++) {
						voxels[p][r][c].filled = true;
						//std::cout << p << ' ' << r << ' ' << c << '\n';
						voxels[p][r][c].polys.push_back(polygons[j]);
					}
				}
			}
		}
	}

	

}
void SpatialHashGrid::checkCollision(Particle& p) {
	
		int z = (int)(p.pos.z - origin.z) / spacing;
		int y = (int)(p.pos.y - origin.y) / spacing;
		int x = (int)(p.pos.x - origin.x) / spacing;


		if (z < depth && y < height && x < width && z>=0 && y>=0 && x>=0) {
			if (voxels[z][y][x].filled) {
				ParticleCollision pc(p);
				for (int j = 0; j < voxels[z][y][x].polys.size(); j++) {
					if (pc.ParticleDetection(*voxels[z][y][x].polys[j])) {
						pc.ParticleResponse(*voxels[z][y][x].polys[j]);
					}
				}
			}
	
		}
		

	

}