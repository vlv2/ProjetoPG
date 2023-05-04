#ifndef PROJETO_PG_RAY_H
#define PROJETO_PG_RAY_H

#include <glm/glm.hpp>

struct Ray {
    explicit Ray(const glm::vec3 &originPoint);
    explicit Ray(const glm::vec3 &originPoint, const glm::vec3 &directionVector);

    glm::vec3 origin;
    glm::vec3 direction;
};

#endif /* PROJETO_PG_RAY_H */
