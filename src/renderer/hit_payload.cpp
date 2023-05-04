#include "hit_payload.h"

HitPayload::HitPayload():
        HitPayload(HitStatus::MISS) {
}

HitPayload::HitPayload(HitStatus hitStatus):
        HitPayload(hitStatus, glm::vec3(0.0f), FLT_MAX, glm::vec3(1, 1, 1)) {
}

HitPayload::HitPayload(HitStatus hitStatus,
                       const glm::vec3& normalVec,
                       float t,
                       const glm::vec3& objectColor):
        status(hitStatus),
        normal(normalVec),
        hitDistance(t),
        color(objectColor) {
}
