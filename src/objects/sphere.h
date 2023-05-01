#ifndef PROJETO_PG_SPHERE_H
#define PROJETO_PG_SPHERE_H

#include <utility>
#include <vector>

#include <glm/glm.hpp>

#include "object.h"
#include "renderer/ray.h"

class Sphere: public Object {
public:
    explicit Sphere(const glm::vec3 &center, float radius);

    Sphere(const Sphere &) = default;
    Sphere(Sphere &&) = delete;
    Sphere &operator=(const Sphere &) = default;
    Sphere &operator=(Sphere &&) = delete;
    ~Sphere() override = default;

    std::pair<float, glm::vec4>
    TraceRay(const Ray &ray, const glm::vec3 &lightDir, int bounces) override;

    [[nodiscard]] inline const glm::vec3 &Center() const {
        return m_center;
    }

    [[nodiscard]] inline const float &Radius() const {
        return m_radius;
    }

private:
    glm::vec3 m_center;
    float m_radius;
};

#endif /* PROJETO_PG_SPHERE_H */
