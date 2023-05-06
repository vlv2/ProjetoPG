#include "hit_payload.h"

HitPayload::HitPayload():
        HitPayload(HitStatus::MISS) {
}

HitPayload::HitPayload(HitStatus hitStatus):
        HitPayload(hitStatus, glm::vec3(0.0f), glm::vec3(0.0f), FLT_MAX, glm::vec3(1.0f)) {
}

HitPayload::HitPayload(HitStatus hitStatus,
                       const glm::vec3& normalVec,
                       const glm::vec3& positionPoint,
                       float t,
                       const glm::vec3& objectColor):
        status(hitStatus),
        normal(normalVec),
        position(positionPoint),
        hitDistance(t),
        color(objectColor) {
}
