#include <fmt/format.h>

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "image/image.h"
#include "renderer/camera.h"
#include "renderer/hit_payload.h"
#include "renderer/ray.h"

#include "objects/object.h"
#include "objects/sphere.h"

int main() {
    Image image(500, 500);

    Camera camera(glm::vec3(0, 0, 2.0f),
                  glm::vec3(0, 0, 0),
                  glm::vec3(0, 1, 0),
                  image.Width(),
                  image.Height());

    // Objects on scene
    std::vector<std::unique_ptr<Object>> objects;
    objects.emplace_back(
        std::make_unique<Sphere>(glm::vec3(0.5, -0.5, 0), 0.35f, glm::vec3(1, 0, 0)));
    objects.emplace_back(
        std::make_unique<Sphere>(glm::vec3(-0.5, 0, -1.0f), 1.0f, glm::vec3(0, 0, 1)));

    // World
    glm::vec3 lightDir = glm::normalize(glm::vec3(0, -1, -1));
    constexpr uint8_t bounces {5};

    image.ForEachPixel([&](const glm::vec2 &coord) {
        Ray ray(camera.Position());
        ray.direction = camera.CalculateRayDirection(coord);

        glm::vec3 color {0.0f};
        float multiplier {1.0f};

        for (uint8_t i = 0; i < bounces; ++i) {
            HitPayload hitPayload {};

            for (const auto &object : objects) {
                const auto &payload = object->Intersect(ray);
                if (payload.status == HitStatus::HIT && payload.hitDistance > 0.0f &&
                    payload.hitDistance < hitPayload.hitDistance) {
                    hitPayload = payload;
                }
            }

            if (hitPayload.status == HitStatus::MISS) {
                color += glm::vec3(0.0f) * multiplier;
                break;
            }

            // Diffuse light
            // float lightIntensity = glm::max(glm::dot(hitPayload.normal, -lightDir), 0.0f);

            // Punctual light
            float lightIntensity =
                glm::max(glm::dot(hitPayload.normal, -(lightDir - hitPayload.position)), 0.0f);
            
            hitPayload.color *= lightIntensity;
            color += hitPayload.color * multiplier;

            multiplier *= 0.7f;

            ray.origin = hitPayload.position + hitPayload.normal * 0.0001f;
            ray.direction = glm::reflect(ray.direction, hitPayload.normal);
        }

        return glm::vec4(color, 1.0f);
    });

    image.SaveImage("teste.png");

    return 0;
}
