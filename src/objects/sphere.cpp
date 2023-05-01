#include "sphere.h"

#include <utility>
#include <vector>

#include <glm/glm.hpp>

#include "object.h"

Sphere::Sphere(const glm::vec3& center, float radius):
        Object(ObjectType::SPHERE),
        m_center(center),
        m_radius(radius) {
}

std::pair<float, glm::vec4>
Sphere::TraceRay(const Ray& ray, const glm::vec3& lightDir, [[maybe_unused]] int bounces) {
    glm::vec3 origin = ray.Origin() - m_center;

    float a = glm::dot(ray.Direction(), ray.Direction());
    float b = 2.0f * glm::dot(origin, ray.Direction());
    float c = glm::dot(origin, origin) - m_radius * m_radius;
    float delta = b * b - 4.0f * a * c;

    float t = (-b - std::sqrt(delta)) / 2.0f * a;
    glm::vec3 hitPoint = origin + ray.Direction() * t;
    glm::vec3 normal = glm::normalize(hitPoint);

    if (delta < 0.0f) {
        return {
            FLT_MAX,
            {0, 0, 0, 1}
        };
    }

    // Negative because the light is point to the sphere
    float lightIntensity = glm::max(glm::dot(normal, -lightDir), 0.0f);

    glm::vec3 sphereColor(1, 0, 0);
    // Making the color beeing between 0 and 1
    // sphereColor = normal * 0.5f + 0.5f;
    sphereColor *= lightIntensity;

    return {
        t,
        {sphereColor, 1}
    };
}
