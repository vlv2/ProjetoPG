#include <fmt/format.h>

#include <vector>

#include <glm/glm.hpp>

#include "image/image.h"
#include "renderer/camera.h"
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

    std::vector<Object *> objects;
    objects.emplace_back(new Sphere(glm::vec3(0.5, 0.5, 0), 0.25f));
    objects.emplace_back(new Sphere(glm::vec3(-0.5, 0, -5.0f), 1.5f));

    image.ForEachPixel([&](const glm::vec2 &coord) {
        ray.MutableDirection() = camera.CalculateRayDirection(coord);
        glm::vec4 color {1, 1, 1, 1};

        float closestT {FLT_MAX};
        for (Object *object : objects) {
            const auto &&[t, retColor] = object->TraceRay(ray, lightDir, 2);
            if (t < closestT) {
                closestT = t;
                color = retColor;
            }
        }

        return color;
    });

    for (Object *object : objects) {
        delete object;
    }

    image.SaveImage("teste.png");

    return 0;
}
