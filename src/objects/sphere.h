#ifndef PROJETO_PG_SPHERE_H
#define PROJETO_PG_SPHERE_H

#include <vector>

#include <glm/glm.hpp>

#include "object.h"
#include "renderer/hit_payload.h"
#include "renderer/ray.h"

class Sphere: public Object {
public:
    explicit Sphere(const glm::vec3 &center, float radius, const glm::vec3 &color);

    Sphere(const Sphere &) = default;
    Sphere(Sphere &&) = delete;
    Sphere &operator=(const Sphere &) = default;
    Sphere &operator=(Sphere &&) = delete;
    ~Sphere() override = default;

    HitPayload Intersect(const Ray &ray) override;

    [[nodiscard]] inline const glm::vec3 &Center() const {
        return m_center;
    }

    [[nodiscard]] inline const float &Radius() const {
        return m_radius;
    }

private:
    glm::vec3 m_center;
    float m_radius;
    glm::vec3 m_color;
};

#endif /* PROJETO_PG_SPHERE_H */
