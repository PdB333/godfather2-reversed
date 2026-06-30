// FUNC_NAME: Entity::getInterpolatedWorldTransform
// Function address: 0x00728b20
// Role: Retrieves the world transform (two 8-byte fields: possibly position and quaternion or matrix rows)
// from the entity, optionally blending with an interpolation context.

#include <cstdint>

class Entity {
public:
    // +0x5c: flags (bit0=use interpolation)
    uint8_t flags;
    // +0x7c: first 8 bytes of world transform data (e.g., position)
    uint64_t worldTransformPart1;
    // +0x84: second 8 bytes of world transform data (e.g., rotation quaternion or velocity)
    uint64_t worldTransformPart2;
    // +0x9c: transform state identifier (0 = not ready, 0x48 = not loaded)
    int transformState;
};

// Forward declarations of called functions
void FUN_00729ef0(uint64_t outTransform[2], const void* interpContext);
void FUN_007283d0(float interpolatedValue);

// Global time value (game time or frame timestamp)
extern float g_currentGameTime;

// Interpolation context structure (tentative)
struct InterpolationContext {
    float timeStep;      // +0x0c
    float maxTime;       // +0x10
    // ... other fields
};

void __thiscall Entity::getInterpolatedWorldTransform(uint64_t outTransform[2], const InterpolationContext* interpContext)
{
    // Copy current transform data to output
    outTransform[0] = this->worldTransformPart1;
    outTransform[1] = this->worldTransformPart2;

    if (interpContext != nullptr) {
        // Apply additional transform if the entity has valid transform data
        if ((this->transformState != 0) && (this->transformState != 0x48)) {
            FUN_00729ef0(outTransform, interpContext);
        }

        // Interpolation flag check (bit0)
        if ((this->flags & 1) != 0) {
            float step = interpContext->timeStep;
            float maxTime = interpContext->maxTime;

            // Clamp step to [0, maxTime] if positive; set to 0 if step <= 0
            if (step > 0.0f) {
                if (maxTime <= step) {
                    step = maxTime;
                }
            } else {
                step = 0.0f;
            }

            // Compute blended value and pass to time update callback
            float blendFactor = g_currentGameTime - (step / maxTime);
            FUN_007283d0(blendFactor);
        }
    }
}