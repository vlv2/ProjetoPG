#ifndef PROJETO_PG_IMAGE_H
#define PROJETO_PG_IMAGE_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include <glm/glm.hpp>

class Image {
public:
    Image();
    explicit Image(uint16_t width, uint16_t height);
    explicit Image(uint16_t width, uint16_t height, uint8_t color);
    explicit Image(uint16_t width, uint16_t height, uint8_t color, uint16_t channels);

    Image(const Image &) = delete;
    Image(Image &&) = default;
    Image &operator=(const Image &) = delete;
    Image &operator=(Image &&) = default;
    ~Image() = default;

    void SetPixel(const glm::vec2 &coord, const glm::vec4 &color);
    void SetPixel(uint16_t x, uint16_t y, const glm::vec4 &color);
    void ForEachPixel(const std::function<glm::vec4(const glm::vec2 &)> &callback);
    void SaveImage(const std::string &filename);

    [[nodiscard]] inline const uint16_t &Width() const {
        return m_width;
    }

    [[nodiscard]] inline const uint16_t &Height() const {
        return m_height;
    }

    [[nodiscard]] inline const uint16_t &Channels() const {
        return m_channels;
    }

private:
    uint16_t m_width;
    uint16_t m_height;
    uint16_t m_channels;
    std::unique_ptr<uint8_t[]> m_image;
    glm::mat4 m_ortho;

    static glm::vec4 ConvertToRGBA(const glm::vec4 &color);
};

#endif /* PROJETO_PG_IMAGE_H */
