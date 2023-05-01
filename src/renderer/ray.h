#ifndef PROJETO_PG_RAY_H
#define PROJETO_PG_RAY_H

#include <glm/glm.hpp>

class Ray {
public:
    explicit Ray(const glm::vec3 &origin);
    explicit Ray(const glm::vec3 &origin, const glm::vec3 &direction);

    Ray(const Ray &) = default;
    Ray(Ray &&) = delete;
    Ray &operator=(const Ray &) = default;
    Ray &operator=(Ray &&) = delete;
    ~Ray() = default;

    [[nodiscard]] glm::vec3 CalculateHitPoint(float t) const;

    [[nodiscard]] inline const glm::vec3 &Origin() const {
        return m_origin;
    }

    [[nodiscard]] inline const glm::vec3 &Direction() const {
        return m_direction;
    }

    [[nodiscard]] glm::vec3 &MutableOrigin() {
        return m_origin;
    }

    [[nodiscard]] glm::vec3 &MutableDirection() {
        return m_direction;
    }

private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};

#endif /* PROJETO_PG_RAY_H */
