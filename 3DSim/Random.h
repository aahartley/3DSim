#pragma once
#include "Vector3f.h"
#include "Constants.h"
#include <random>
#include <vector>
#include <chrono>
class Random {
public:
	Random() {}
	~Random() {}
	std::vector<float> uniformR;
	std::vector<float> gaussR;
	int uIndex=0;
	int gIndex=0;



	 float createRandUniform(float min, float max) {
		unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();

		static std::default_random_engine generator(seed);
		std::uniform_real_distribution<float> distribution(min, max);
		return distribution(generator);
	}
	 float createRandGauss(float mean, float stdv) {
		unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();

		static std::default_random_engine generator(seed);
		std::normal_distribution<float> distribution(mean, stdv);
		return distribution(generator);
	}
	 void populateRand(int num) {

		for (int i = 0; i < num; i++) {
			uniformR.push_back(createRandUniform(0, 1));
			gaussR.push_back(createRandGauss(0, 1));
		}
	}
	 float randUniform(float min, float max) {

		if (uIndex == uniformR.size())uIndex = 0;
		return (max - min) * uniformR[uIndex++] + min;
	}
	 float randGauss(float mean, float stdv) {
		if (gIndex == gaussR.size())gIndex = 0;
		return (stdv) * gaussR[gIndex++] + mean;
	}

	 Vector3f randUVSphere() {
		float theta = randUniform(-PI, PI);
		float y = randUniform(-1, 1);
		float r = std::sqrtf(1 - std::powf(y, 2));
		return Vector3f(r * std::cosf(theta), y, -r * std::sinf(theta));
	}

	 Vector3f randUVUniformW(Vector3f w, float angle) {
		Vector3f coordFrame;
		if (w.y == 0 && w.z == 0)
			coordFrame = Vector3f(0, 1, 0);
		else
			coordFrame = Vector3f(1, 0, 0);
		Vector3f direction = w.normalize(); //z-axis
		Vector3f unitZ = direction; //col vecs
		Vector3f unitX = coordFrame.cross(unitZ).normalize();
		Vector3f unitY = unitZ.cross(unitX);
		float f = randUniform(0, 1);
		float omega = std::sqrtf(f) * angle;
		float theta = randUniform(-PI, PI);
		Vector3f unitOffsetZ(std::cosf(theta) * std::sinf(omega), std::sinf(theta) * std::sinf(omega), std::cosf(omega));
		return Vector3f((unitX.x * unitOffsetZ.x) + (unitY.x * unitOffsetZ.y) + (unitZ.x * unitOffsetZ.z),
			(unitX.y * unitOffsetZ.x) + (unitY.y * unitOffsetZ.y) + (unitZ.y * unitOffsetZ.z),
			(unitX.z * unitOffsetZ.x) + (unitY.z * unitOffsetZ.y) + (unitZ.z * unitOffsetZ.z));
	}
	 Vector3f randUVGaussW(Vector3f w, float angle) {
		float stdDev = angle / 3;
		Vector3f coordFrame;
		if (w.y == 0 && w.z == 0)
			coordFrame = Vector3f(0, 1, 0);
		else
			coordFrame = Vector3f(1, 0, 0);
		Vector3f direction = w.normalize(); //z-axis
		Vector3f unitZ = direction; //col vecs
		Vector3f unitX = coordFrame.cross(unitZ).normalize();
		Vector3f unitY = unitZ.cross(unitX);
		float f = randGauss(0, stdDev);
		float omega = std::sqrtf(f) * angle;
		float theta = randUniform(-PI, PI);
		Vector3f unitOffsetZ(std::cosf(theta) * std::sinf(omega), std::sinf(theta) * std::sinf(omega), std::cosf(omega));
		return Vector3f((unitX.x * unitOffsetZ.x) + (unitY.x * unitOffsetZ.y) + (unitZ.x * unitOffsetZ.z),
			(unitX.y * unitOffsetZ.x) + (unitY.y * unitOffsetZ.y) + (unitZ.y * unitOffsetZ.z),
			(unitX.z * unitOffsetZ.x) + (unitY.z * unitOffsetZ.y) + (unitZ.z * unitOffsetZ.z));
	}

	 Vector3f randUniPos(Vector3f c, Vector3f normal, float radius) {
		Vector3f coordFrame;
		if (c.y == 0 && c.z == 0)
			coordFrame = Vector3f(0, 1, 0);
		else
			coordFrame = Vector3f(1, 0, 0);
		Vector3f direction = normal;
		Vector3f unitZ = direction; //col vecs, make dir math with axis??
		Vector3f unitX = coordFrame.cross(unitZ).normalize();
		Vector3f unitY = unitZ.cross(unitX);
		float f = randUniform(0, 1);
		float r = std::sqrtf(f) * radius;
		float theta = randUniform(-PI, PI);
		Vector3f pos(r * std::cosf(theta), r * std::sinf(theta), 0);
		Vector3f rotatedPos((unitX.x * pos.x) + (unitY.x * pos.y) + (unitZ.x * pos.z),
			(unitX.y * pos.x) + (unitY.y * pos.y) + (unitZ.y * pos.z),
			(unitX.z * pos.x) + (unitY.z * pos.y) + (unitZ.z * pos.z));
		return c + rotatedPos;
	}
	 Vector3f randGaussPos(Vector3f c, Vector3f normal, float radius) {
		float stdDev = radius / 3;
		Vector3f coordFrame;
		if (c.y == 0 && c.z == 0)
			coordFrame = Vector3f(0, 1, 0);
		else
			coordFrame = Vector3f(1, 0, 0);
		Vector3f direction = normal;
		Vector3f unitZ = direction; //col vecs, make dir math with axis??
		Vector3f unitX = coordFrame.cross(unitZ).normalize();
		Vector3f unitY = unitZ.cross(unitX);
		float f = randUniform(0, stdDev);
		float r = std::sqrtf(f) * radius;
		float theta = randUniform(-PI, PI);
		Vector3f pos(r * std::cosf(theta), r * std::sinf(theta), 0);
		Vector3f rotatedPos((unitX.x * pos.x) + (unitY.x * pos.y) + (unitZ.x * pos.z),
			(unitX.y * pos.x) + (unitY.y * pos.y) + (unitZ.y * pos.z),
			(unitX.z * pos.x) + (unitY.z * pos.y) + (unitZ.z * pos.z));
		return c + rotatedPos;
	}
};