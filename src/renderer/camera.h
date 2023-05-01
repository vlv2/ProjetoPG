#ifndef PROJETO_PG_CAMERA_H
#define PROJETO_PG_CAMERA_H

#include <vector>

#include <glm/glm.hpp>

class Camera {
public:
    explicit Camera(const glm::vec3 &position,
                    const glm::vec3 &target,
                    const glm::vec3 &upGuide,
                    uint16_t width,
                    uint16_t height);
    explicit Camera(const glm::vec3 &position,
                    const glm::vec3 &target,
                    const glm::vec3 &upGuide,
                    uint16_t width,
                    uint16_t height,
                    float fov);
    explicit Camera(const glm::vec3 &position,
                    const glm::vec3 &target,
                    const glm::vec3 &upGuide,
                    uint16_t width,
                    uint16_t height,
                    float fov,
                    float nearClip,
                    float farClip);

    Camera(const Camera &) = default;
    Camera(Camera &&) = default;
    Camera &operator=(const Camera &) = default;
    Camera &operator=(Camera &&) = default;
    ~Camera() = default;

    glm::vec3 CalculateRayDirection(const glm::vec2 &coord);

    [[nodiscard]] inline const glm::vec3 &Position() const {
        return m_position;
    }

private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_upGuide;
    uint16_t m_width;
    uint16_t m_height;
    float m_fov;
    float m_nearClip;
    float m_farClip;

    glm::mat4 m_projection {1.0f};
    glm::mat4 m_inverseProjection {1.0f};
    glm::mat4 m_view {1.0f};
    glm::mat4 m_inverseView {1.0f};

    [[nodiscard]] glm::mat4 LookAt() const;
    [[nodiscard]] glm::mat4 Projection() const;
};

#endif /* PROJETO_PG_CAMERA_H */
