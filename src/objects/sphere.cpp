#include "sphere.h"

#include <vector>

#include <glm/glm.hpp>

#include "object.h"
#include "renderer/hit_payload.h"

Sphere::Sphere(const glm::vec3& center, float radius, const glm::vec3& color):
        Object(ObjectType::SPHERE),
        m_center(center),
        m_radius(radius),
        m_color(color) {
}

HitPayload Sphere::Intersect(const Ray& ray) {
    glm::vec3 origin = ray.origin - m_center;

    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(origin, ray.direction);
    float c = glm::dot(origin, origin) - m_radius * m_radius;

    float delta = b * b - 4.0f * a * c;
    if (delta < 0.0f) {
        return HitPayload(HitStatus::MISS);
    }

    float t = (-b - std::sqrt(delta)) / 2.0f * a;
    glm::vec3 hitPoint = origin + ray.direction * t;
    glm::vec3 normal = glm::normalize(hitPoint);

    hitPoint += m_center;

    return HitPayload(HitStatus::HIT, normal, hitPoint, t, m_color);
}
