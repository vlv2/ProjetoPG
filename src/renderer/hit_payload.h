#ifndef PROJETO_PG_HIT_PAYLOAD_H
#define PROJETO_PG_HIT_PAYLOAD_H

#include <glm/glm.hpp>

enum class HitStatus { MISS, HIT };

struct HitPayload {
    HitPayload();
    explicit HitPayload(HitStatus hitStatus);
    explicit HitPayload(HitStatus hitStatus,
                        const glm::vec3& normalVec,
                        const glm::vec3& positionPoint,
                        float t,
                        const glm::vec3& objectColor);

    HitStatus status;
    glm::vec3 normal;
    glm::vec3 position;
    float hitDistance;
    glm::vec3 color;
    // Material
};

#endif /* PROJETO_PG_HIT_PAYLOAD_H */
