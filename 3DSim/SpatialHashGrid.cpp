#include "SpatialHashGrid.h"

SpatialHashGrid::SpatialHashGrid(Vector3f dimensions, float spacing, Vector3f origin) {
	this->dim = dimensions;
	this->spacing = spacing;
	this->width = dim.x / spacing;
	this->height = dim.y / spacing;
	this->depth = dim.z / spacing;
	this->origin = origin;

	voxels = new Voxel * *[depth];

	for (int p = 0; p < depth; p++) {
		voxels[p] = new Voxel * [height];
		for (int r = 0; r < height; r++) {  //switch to width?
			voxels[p][r] = new Voxel[width];
			for (int c = 0; c < width; c++) {
				voxels[p][r][c] = Voxel();
				voxels[p][r][c].index = Vector3f(c, r, p);
				//std::cout << p << ' ' << r << ' ' << c << '\n';

			}
		}
	}

}

void SpatialHashGrid::initializeGrid(std::vector<Polygon*>& polygons) {
	int cmin = 0;
	int cmax = 0;
	int pmin = 0;
	int pmax = 0;
	int rmax = 0;
	int rmin = 0;
	for (int j = 0; j < polygons.size(); j++) {
		if (polygons[j]->getType() == PLANE) {
			Plane plane = (Plane&)*polygons[j];

			cmin = (int)(plane.xmin - origin.x) / spacing;
			rmin = (int)(plane.ymin - origin.y) / spacing;
			cmax = (int)(plane.xmax - origin.x) / spacing;
			rmax = (int)(plane.ymax - origin.y) / spacing;
			pmin = (int)(plane.zmin - origin.z) / spacing;
			pmax = (int)(plane.zmax - origin.z) / spacing;
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
		}

		else if (polygons[j]->getType() == TRIANGLE) {
			Triangle triangle = (Triangle&)*polygons[j];

			cmin = (int)(triangle.xmin - origin.x) / spacing;
			rmin = (int)(triangle.ymin - origin.y) / spacing;
			cmax = (int)(triangle.xmax - origin.x) / spacing;
			rmax = (int)(triangle.ymax - origin.y) / spacing;
			pmin = (int)(triangle.zmin - origin.z) / spacing;
			pmax = (int)(triangle.zmax - origin.z) / spacing;
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
		}
		//std::cout << pmin << ' ' << pmax << ' ' << rmin << ' ' << rmax << ' ' << cmin << ' ' << cmax << '\n';
		for (int p = pmin; p < pmax; p++) {
			for (int r = rmin; r < rmax; r++) {
				for (int c = cmin; c < cmax; c++) {
					voxels[p][r][c].filled = true;
					//std::cout << p << ' ' << r << ' ' << c << '\n';
					voxels[p][r][c].polys.push_back(polygons[j]);
				}
			}
		}

	}



}
void SpatialHashGrid::fixLoop(int& xmin, int& xmax, int& ymin, int& ymax, int& zmin, int& zmax) {
	if (ymin == ymax) {
		if (ymin == 0) {
			ymax++;
		}
		else if (ymax == height - 1) {
			ymin--;
		}
		else ymax++;
	}
	if (xmin == xmax) {
		if (xmin == 0) {
			xmax++;
		}
		else if (xmax == width - 1) {
			xmin--;
		}
		else xmax++;
	}
	if (zmin == zmax) {
		if (zmin == 0) {
			zmax++;
		}
		else if (zmax == depth - 1) {
			zmin--;
		}
		else zmax++;
	}
}
void SpatialHashGrid::checkCollision(Particle& p) {
	int z = (int)(p.oldPos.z - origin.z) / spacing;
	int y = (int)(p.oldPos.y - origin.y) / spacing;
	int x = (int)(p.oldPos.x - origin.x) / spacing;
	int z2 = (int)(p.pos.z - origin.z) / spacing;
	int y2 = (int)(p.pos.y - origin.y) / spacing;
	int x2 = (int)(p.pos.x - origin.x) / spacing;

	int zmax = z; int k = z2;
	if (z < z2) { zmax = z2; k = z; }
	int ymax = y; int j = y2;
	if (y < y2) { ymax = y2; j = y; }
	int xmax = x; int i = x2;
	if (x < xmax) { xmax = x2; i = x; }
	fixLoop(i, xmax, j, ymax, k, zmax);


	if ((z < depth && y < height && x < width && z >= 0 && y >= 0 && x >= 0) || (z2 < depth && y2 < height && x2 < width && z2 >= 0 && y2 >= 0 && x2 >= 0)) {
		//std::cout << "hit" << '\n';
		std::vector<Voxel> voxelsInPath;
		for (int zz = k; zz < zmax; zz++) {
			for (int yy = j; yy < ymax; yy++) {
				for (int xx = i; xx < xmax; xx++) {
					voxelsInPath.push_back(voxels[zz][yy][xx]);
				}
			}
		}


		for (Voxel v : voxelsInPath) {
			if (v.filled) {
				ParticleCollision pc(p);
				for (int j = 0; j < voxels[(int)v.index.z][(int)v.index.y][(int)v.index.x].polys.size(); j++) {
					if (pc.ParticleDetection(*voxels[(int)v.index.z][(int)v.index.y][(int)v.index.x].polys[j])) {
						pc.ParticleResponse(*voxels[(int)v.index.z][(int)v.index.y][(int)v.index.x].polys[j]);
					}
				}
			}
		}

	}




}