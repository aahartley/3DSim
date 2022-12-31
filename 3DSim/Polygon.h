#pragma once
#include "Vector3f.h"
#include "Vec2.h"
#include <vector>
//todo: planes into triangles for performance?
enum PolygonType {
	PLANE,
	INFINITEPLANE
};
struct Polygon {
	virtual PolygonType getType() const = 0;
	virtual ~Polygon() {};

};


struct Plane: public Polygon {
	std::vector<Vector3f> vertices;
	std::vector<Vec2> twoDVertices;
	Vector3f surfaceNormal;
	Vector3f origin;
	//boudnign box add
	float cr = 0.5f;
	float cf = 0.1f;
	float xmin = 0;
	float xmax = 0;
	float ymin = 0;
	float ymax = 0;
	float zmin = 0;
	float zmax = 0;
	Plane() {};
	Plane(std::vector<Vector3f> vertices, Vector3f origin): vertices(vertices), origin(origin) {
		surfaceNormal = (vertices[1] - vertices[0]).cross((vertices[3] - vertices[0])).normalize();
		xmin = vertices[0].x;
		xmax = vertices[0].x;
		ymin = vertices[0].y;
		ymax = vertices[0].y;
		zmin = vertices[0].z;
		zmax = vertices[0].z;

		for (Vector3f v : vertices) {
			if (v.x < xmin)xmin = v.x;
			if (v.x > xmax)xmax = v.x;
			if (v.y < ymin)ymin = v.y;
			if (v.y > ymax)ymax = v.y;
			if (v.z < zmin)zmin = v.z;
			if (v.z > zmax)zmax = v.z;

		}
	

	}
	PolygonType getType() const override {
		return PLANE;
	}
	~Plane() {};

};
struct InfinitePlane : public Polygon {
	std::vector<Vector3f> vertices;
	std::vector<Vec2> twoDVertices;

	Vector3f surfaceNormal;
	float cr = 0.f;
	float cf = 0.f;
	InfinitePlane() {};
	InfinitePlane(std::vector<Vector3f> vertices) : vertices(vertices) {
		surfaceNormal = Vector3f(-vertices[0].y, vertices[0].x, 0).normalize();
	}
	PolygonType getType() const override {
		return INFINITEPLANE;
	}
	~InfinitePlane() {};

};