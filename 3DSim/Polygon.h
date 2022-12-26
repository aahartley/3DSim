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
	float cr = 0.5f;
	float cf = 0.1f;
	
	Plane() {};
	Plane(std::vector<Vector3f> vertices, Vector3f origin): vertices(vertices), origin(origin) {
		surfaceNormal = (vertices[1] - vertices[0]).cross((vertices[3] - vertices[0])).normalize();
	}
	PolygonType getType() const override {
		return PLANE;
	}

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
	PolygonType getType() const  {
		return INFINITEPLANE;
	}

};