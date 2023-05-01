#include "image.h"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>

#include <stb_image_write.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// RGBA Image
Image::Image():
        Image(640, 480, 255, 4) {
}

Image::Image(uint16_t width, uint16_t height):
        Image(width, height, 255, 4) {
}

Image::Image(uint16_t width, uint16_t height, uint8_t color):
        Image(width, height, color, 4) {
}

Image::Image(uint16_t width, uint16_t height, uint8_t color, uint16_t channels):
        m_width(width),
        m_height(height),
        m_channels(channels),
        m_ortho() {
    auto imageSize = static_cast<size_t>(m_width * m_height) * static_cast<size_t>(m_channels);
    m_image = std::make_unique<uint8_t[]>(imageSize);
    std::fill_n(m_image.get(), imageSize, color);
    m_ortho =
        glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
}

void Image::SetPixel(const glm::vec2& coord, const glm::vec4& color) {
    SetPixel(static_cast<uint16_t>(coord.x), static_cast<uint16_t>(coord.y), color);
}

void Image::SetPixel(uint16_t x, uint16_t y, const glm::vec4& color) {
    uint8_t* rawImage = m_image.get();

    int32_t index = (y * m_width + x) * m_channels;
    rawImage[index] = static_cast<uint8_t>(color.r);
    rawImage[index + 1] = static_cast<uint8_t>(color.g);
    rawImage[index + 2] = static_cast<uint8_t>(color.b);
    rawImage[index + 3] = static_cast<uint8_t>(color.a);
}

void Image::ForEachPixel(const std::function<glm::vec4(const glm::vec2&)>& callback) {
    for (uint16_t x = 0; x < m_width; ++x) {
        for (uint16_t y = 0; y < m_height; ++y) {
            glm::vec2 coord = m_ortho * glm::vec4(x, y, 1.0f, 1.0f);
            auto color = callback(coord);
            color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
            SetPixel(glm::vec2(x, y), ConvertToRGBA(color));
        }
    }
}

void Image::SaveImage(const std::string& filename) {
    // stbi_flip_vertically_on_write(true);
    stbi_write_png(filename.c_str(), m_width, m_height, m_channels, m_image.get(), 0);
}

glm::vec4 Image::ConvertToRGBA(const glm::vec4& color) {
    return {
        color.r * 255.0f,
        color.g * 255.0f,
        color.b * 255.0f,
        color.a * 255.0f,
    };
}
