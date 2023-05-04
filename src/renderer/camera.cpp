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
    m_view = LookAt(m_position, m_target, m_upGuide);
    m_inverseView = glm::inverse(m_view);
    m_projection = Projection(glm::radians(m_fov),
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

glm::mat4 Camera::LookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &cameraUp) {
    // Based on glm::lookAt

    const glm::vec3 forward = glm::normalize(center - eye);
    const glm::vec3 right = glm::normalize(glm::cross(forward, cameraUp));
    const glm::vec3 up = glm::cross(right, forward);

    glm::mat4 result {1.0f};
    result[0][0] = right.x;
    result[1][0] = right.y;
    result[2][0] = right.z;
    result[0][1] = up.x;
    result[1][1] = up.y;
    result[2][1] = up.z;
    result[0][2] = -forward.x;
    result[1][2] = -forward.y;
    result[2][2] = -forward.z;
    result[3][0] = -glm::dot(right, eye);
    result[3][1] = -glm::dot(up, eye);
    result[3][2] = glm::dot(forward, eye);

    return result;
}

glm::mat4 Camera::Projection(float fov, float width, float height, float zNear, float zFar) {
    // Based on glm::perspectiveFov

    const float h = glm::cos(0.5f * fov) / glm::sin(0.5f * fov);
    const float w = h * height / width;

    glm::mat4 result(0.0f);
    result[0][0] = w;
    result[1][1] = h;
    result[2][2] = -zFar / (zFar - zNear);
    result[2][3] = -1.0f;
    result[3][2] = (-2.0f * zFar * zNear) / (zFar - zNear);

    return result;
}
