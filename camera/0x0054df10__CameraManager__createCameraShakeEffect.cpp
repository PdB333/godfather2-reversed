// FUNC_NAME: CameraManager::createCameraShakeEffect
// Function address: 0x0054df10
// Creates a camera shake effect object and posts a shake event to the message system.
// Called from 0x007f4620 (presumably part of the camera update or damage handling).
// Uses thread-local storage (TlsGetValue) for per-frame data.

// Note: Offsets documented in comments (e.g., +0x80, +0x84) refer to the CameraManager instance.

CameraShakeEffect* CameraManager::createCameraShakeEffect(uint32 effectId, float time, float intensity, uint32 userData)
{
    // Compute shake offsets based on input parameters and camera properties
    float shakeOffsetX = (time * DAT_00e2cd54 - intensity) * *(float*)(this + 0x84); // +0x84: m_shakeStrength
    float shakeOffsetY = *(float*)(this + 0x84) * intensity + _DAT_01126040;         // _DAT_01126040: base offset
    float shakeOffsetZ = DAT_00e44564 - shakeOffsetX;                                 // unused in further code

    // Prepare output vector for the transformation function
    float outX = 0.0f;
    float outY = 0.0f;
    float outZ = 0.0f;

    // Call to a transformation function (likely computes a direction/velocity)
    // Uses a temporary buffer allocated via thread-local memory pool
    void* tempBuffer = FUN_00aa2680(0x40, 0x27); // Allocate 64-byte scratch buffer (tag 0x27)
    *(uint16*)((uint8*)tempBuffer + 4) = 0x40;   // Store buffer size in header
    uint32 transformResult = FUN_00a65bb0(&outX, &outY, *(float*)(this + 0x80) * intensity); // +0x80: m_shakeFrequency
    TlsGetValue(DAT_01139810); // Per-thread debug/state update (return value unused)

    // Allocate the actual shake effect object (0x170 bytes, tag 0x31)
    CameraShakeEffect* effect = (CameraShakeEffect*)FUN_00aa2680(0x170, 0x31);
    *(uint16*)((uint8*)effect + 4) = 0x170; // Store object size in header

    // Initialize the effect (likely via a factory function that sets global data)
    FUN_009f0c70(transformResult, &DAT_011397d0, userData);

    // Set vtable pointer and store creator reference
    effect->vtable = &PTR_FUN_00e39ec0; // vtable for CameraShakeEffect class
    effect->m_effectId = effectId;      // +0x160 (offset 0x58 * 4)
    effect->m_parentCamera = this;      // +0x164 (offset 0x59 * 4)

    // Post a shake event to the message system
    FUN_0043b490(); // Possibly increment a global counter
    FUN_009f01f0(0x2001, effectId, 0); // Message 0x2001: Shake event

    return effect;
}