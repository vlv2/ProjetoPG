#include "camera.h"

#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 &position,
               const glm::vec3 &target,
               const glm::vec3 &upGuide,
               uint16_t width,
               uint16_t height):
        Camera(position, target, upGuide, width, height, 45.0f) {
}

Camera::Camera(const glm::vec3 &position,
               const glm::vec3 &target,
               const glm::vec3 &upGuide,
               uint16_t width,
               uint16_t height,
               float fov):
        Camera(position, target, upGuide, width, height, fov, 0.1f, 100.0f) {
}

Camera::Camera(const glm::vec3 &position,
               const glm::vec3 &target,
               const glm::vec3 &up,
               uint16_t width,
               uint16_t height,
               float fov,
               float nearClip,
               float farClip):
        m_position(position),
        m_target(target),
        m_upGuide(up),
        m_width(width),
        m_height(height),
        m_fov(fov),
        m_nearClip(nearClip),
        m_farClip(farClip) {
    // m_view = LookAt();
    m_view = glm::lookAt(m_position, m_target, m_upGuide);
    m_inverseView = glm::inverse(m_view);
    // m_projection = Projection();
    m_projection = glm::perspectiveFov(glm::radians(m_fov),
                                       static_cast<float>(m_width),
                                       static_cast<float>(m_height),
                                       m_nearClip,
                                       m_farClip);
    m_inverseProjection = glm::inverse(m_projection);
}

glm::vec3 Camera::CalculateRayDirection(const glm::vec2 &coord) {
    glm::vec4 target = m_inverseProjection * glm::vec4(coord.x, coord.y, 1, 1);
    glm::vec3 rayDirection =
        glm::vec3(m_inverseView *
                  glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0));    // World space

    return rayDirection;
}

glm::mat4 Camera::LookAt() const {
    glm::vec3 forward = glm::normalize(m_target - m_position);
    glm::vec3 right = glm::normalize(glm::cross(forward, m_upGuide));
    glm::vec3 up = glm::cross(right, forward);

    // Set the translation part of the matrix
    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -m_position.x;
    translation[3][1] = -m_position.y;
    translation[3][2] = -m_position.z;

    // Set the rotation part of the matrix
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = right.x;
    rotation[1][0] = right.y;
    rotation[2][0] = right.z;
    rotation[0][1] = up.x;
    rotation[1][1] = up.y;
    rotation[2][1] = up.z;
    rotation[0][2] = -forward.x;
    rotation[1][2] = -forward.y;
    rotation[2][2] = -forward.z;

    return rotation * translation;
}

glm::mat4 Camera::Projection() const {
    float f = 1.0f / std::tan(glm::radians(m_fov) * 0.5f);
    float range = 1.0f / (m_nearClip - m_farClip);
    float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);

    glm::mat4 result;
    result[0][0] = f / aspect;
    result[1][1] = f;
    result[2][2] = -1.0f * (m_nearClip + m_farClip) * range;
    result[2][3] = 1.0f;
    result[3][2] = 2.0f * m_nearClip * m_farClip * range;
    result[3][3] = 0.0f;

    return result;
}
