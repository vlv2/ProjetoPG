#ifndef PROJETO_PG_OBJECT_H
#define PROJETO_PG_OBJECT_H

#include <glm/glm.hpp>

#include "renderer/hit_payload.h"
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

    virtual HitPayload Intersect(const Ray &ray) = 0;

    [[nodiscard]] inline const ObjectType &Type() const {
        return m_objectType;
    }

private:
    ObjectType m_objectType;
};

#endif /* PROJETO_PG_OBJECT_H */
