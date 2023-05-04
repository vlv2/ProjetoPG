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

    Ray ray(camera.Position());
    glm::vec3 lightDir = glm::normalize(glm::vec3(-1, -1, -1));

    std::vector<std::unique_ptr<Object>> objects;
    objects.emplace_back(
        std::make_unique<Sphere>(glm::vec3(0.5, 0.5, 0), 0.25f, glm::vec3(1, 0, 0)));
    objects.emplace_back(
        std::make_unique<Sphere>(glm::vec3(-0.5, 0, -5.0f), 1.5f, glm::vec3(0, 0, 1)));

    image.ForEachPixel([&](const glm::vec2 &coord) {
        ray.direction = camera.CalculateRayDirection(coord);

        HitPayload hitPayload {};
        for (const auto &object : objects) {
            const auto &payload = object->Intersect(ray, 2);
            if (payload.status == HitStatus::HIT && payload.hitDistance < hitPayload.hitDistance) {
                hitPayload = payload;
            }
        }

        if (hitPayload.status == HitStatus::HIT) {
            float lightIntensity = glm::max(glm::dot(hitPayload.normal, -lightDir), 0.0f);
            hitPayload.color *= lightIntensity;
        }

        // float lightIntensity = glm::max(glm::dot(hitPayload.normal, -lightDir), 0.0f);
        // hitPayload.color *= lightIntensity;

        return glm::vec4(hitPayload.color, 1.0f);
    });

    image.SaveImage("teste.png");

    return 0;
}
