#ifndef PROJETO_PG_OBJECT_H
#define PROJETO_PG_OBJECT_H

#include <string>
#include <utility>
#include <vector>

#include <glm/glm.hpp>

#include "renderer/ray.h"

enum class ObjectType { PLANE, SPHERE, TRIANGLE, TRIANGLES_MESH };

class Object {
public:
    explicit Object(ObjectType objectType);

    Object(const Object &) = default;
    Object(Object &&) = delete;
    Object &operator=(const Object &) = default;
    Object &operator=(Object &&) = delete;

    virtual ~Object() = default;

    virtual std::pair<float, glm::vec4>
    TraceRay(const Ray &ray, const glm::vec3 &lightDir, int bounces) = 0;

    [[nodiscard]] inline const ObjectType &Type() const {
        return m_objectType;
    }

private:
    ObjectType m_objectType;
};

#endif /* PROJETO_PG_OBJECT_H */
