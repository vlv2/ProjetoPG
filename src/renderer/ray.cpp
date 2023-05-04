#include "ray.h"

Ray::Ray(const glm::vec3 &originPoint):
        Ray(originPoint, glm::vec3(0.0f)) {
}

Ray::Ray(const glm::vec3 &originPoint, const glm::vec3 &directionVector):
        origin(originPoint),
        direction(directionVector) {
}
