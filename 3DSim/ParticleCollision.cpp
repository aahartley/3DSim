#pragma once
#include "ParticleCollision.h"
bool ParticleCollision::ParticleDetection(Polygon& poly) {
    if (poly.getType() == PLANE) {
        Plane plane = (Plane&)poly;
        normal = plane.surfaceNormal;
        dn = (p->oldPos - plane.vertices[0]).dot(normal);
        dn > 0 ? dn -= 0.3f : dn += 0.3f;

        dn1 = (p->pos - plane.vertices[0]).dot(normal);
        dn1 > 0 ? dn1 -= 0.3f : dn1 += 0.3f;
        Vec2 xHit;

        ////check to see if sign changed (above or below plane)
        if (((dn1 < 0) != (dn < 0))) {
            float sign = 0;
            for (int i = 0; i < plane.vertices.size(); i++) {
                if (std::abs(normal.x) > std::abs(normal.y) && std::abs(normal.x) > std::abs(normal.z)) {
                    //y,z
                    float x = plane.vertices[i].y;
                    float y = plane.vertices[i].z;
                    Vector3f hit = p->pos-(normal* dn1);
                    xHit = Vec2(hit.y, hit.z);
                    Vec2 coord(x, y);
                    //std::cout << "xhit: " << xHit.x << ' ' << xHit.y << '\n';
                    plane.twoDVertices.push_back(coord);
                }
                else if (std::abs(normal.y) > std::abs(normal.x) && std::abs(normal.y) > std::abs(normal.z)) {
                    //z,x
                    float x = plane.vertices[i].z;
                    float y = plane.vertices[i].x;
                    Vector3f hit = (p->pos) - (normal * dn1);
                    xHit = Vec2(hit.z, hit.x);
                    Vec2 coord(x, y);
                    plane.twoDVertices.push_back(coord);

                }
                else {
                    //x,y
                    float x = plane.vertices[i].x;
                    float y = plane.vertices[i].y;
                    Vector3f hit = (p->pos) - (normal * dn1);
                    xHit = Vec2(hit.x, hit.y);
                    Vec2 coord(x, y);
                    plane.twoDVertices.push_back(coord);
                }


            }
            bool pos = false;
            for (int i = 0; i < plane.vertices.size(); i++) {
                float x1 = plane.twoDVertices[(i + 1) % plane.vertices.size()].x - plane.twoDVertices[i].x;
                float y1 = plane.twoDVertices[(i + 1) % plane.vertices.size()].y - plane.twoDVertices[i].y;


                float x2 = xHit.x - plane.twoDVertices[i].x;
                float y2 = xHit.y - plane.twoDVertices[i].y ;

                float determinant = (x1 * y2) - (y1 * x2);
                if (i == 0) {
                    sign = determinant;
                    if (sign >= 0)pos = true;
                }
                sign *= determinant;
                if (sign < 0 && pos == true) return false;
                if (sign >= 0 && pos == false) return false;

            }
            return true;
        }
        else return false;
       
    }
    else return false;

}
void ParticleCollision::ParticleDetermination(float deltaTime) {
 
}
void ParticleCollision::ParticleResponse(Polygon& poly) {
    if (poly.getType() == PLANE) {
        Plane plane = (Plane&)poly;
        p->pos = p->pos  - normal * (1 + plane.cr) * dn1;
        Vector3f vN = normal * (p->vel.dot(normal));
        Vector3f vT = p->vel - vN;
        p->vel = (vN * -plane.cr) + (vT * (1 - plane.cf));
    }
}