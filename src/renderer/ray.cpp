#include "ray.h"

Ray::Ray(const glm::vec3 &origin):
        Ray(origin, glm::vec3(0.0f)) {
}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction):
        m_origin(origin),
        m_direction(direction) {
}

glm::vec3 Ray::CalculateHitPoint(float t) const {
    return m_origin + m_direction * t;
}
