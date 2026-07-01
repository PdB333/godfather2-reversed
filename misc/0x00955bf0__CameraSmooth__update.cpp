// FUNC_NAME: CameraSmooth::update
// Function address: 0x00955bf0
// Reconstructed smoothing function for a camera scalar (e.g., distance, FOV)
// Uses a spring-like interpolation with acceleration/deceleration based on delta time.
// Global _DAT_00d5780c is a constant damping factor (likely 0.0f or near 0.0f).

#include <cstdint>

// Forward declaration
class CameraSmooth;

// Assuming the global constant is stored at 0x00d5780c
extern float g_cameraSmoothDamping;

// Reconstructed class layout (offsets from this)
// +0x60 : float minOutputLimit   (lower bound for output)
// +0x70 : float maxOutputLimit   (upper bound for output)
// +0x90 : float currentOutput    (smoothed output value)
// +0xa4 : float decelerationThreshold (lower speed threshold)
// +0xa8 : float maxChangeRate    (max per-frame change)
// +0xb0 : float targetMultiplier (scale applied to target difference)
// +0xb4 : float currentChangeRate (current per-frame change, smoothed)
// +0xb8 : float upperChangeLimit (upper limit for change rate)
// +0xc8 : float scaledOutput     (internal scaled value)
// +0xcc : float outputScale      (scale factor for output)

class CameraSmooth {
public:
    void update(float deltaTime);
};

void CameraSmooth::update(float deltaTime)
{
    float fVar1, fVar2, fVar3;

    // Compute desired change rate from target difference
    // (targetMultiplier - damping) * deltaTime + damping then multiplied by currentChangeRate
    fVar1 = ((*(float *)((uintptr_t)this + 0xb0) - g_cameraSmoothDamping) * deltaTime + g_cameraSmoothDamping) *
            *(float *)((uintptr_t)this + 0xb4);

    // Clamp to max change rate
    fVar2 = *(float *)((uintptr_t)this + 0xa8);  // maxChangeRate
    fVar3 = fVar2;
    if (fVar1 < fVar2) {
        fVar3 = fVar1;  // take the smaller value
    }

    // Update current change rate
    *(float *)((uintptr_t)this + 0xb4) = fVar3;

    // Compute scaled output
    *(float *)((uintptr_t)this + 0xc8) = (*(float *)((uintptr_t)this + 0xcc) / fVar2) * fVar3;

    // If change rate is within upper limit, apply ease-out interpolation
    if (fVar3 <= *(float *)((uintptr_t)this + 0xb8)) {
        fVar2 = (*(float *)((uintptr_t)this + 0xb8) - fVar3) /
                (*(float *)((uintptr_t)this + 0xb8) - *(float *)((uintptr_t)this + 0xa4));
        // Quadratic ease-out (fVar2 squared)
        *(float *)((uintptr_t)this + 0x90) =
            *(float *)((uintptr_t)this + 0x70) -
            (*(float *)((uintptr_t)this + 0x70) - *(float *)((uintptr_t)this + 0x60)) * fVar2 * fVar2;
    } else {
        // Above limit, set output directly to max
        *(float *)((uintptr_t)this + 0x90) = *(float *)((uintptr_t)this + 0x70);
    }
}