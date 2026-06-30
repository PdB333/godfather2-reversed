// FUNC_NAME: VFXManager::spawnEffect
// Address: 0x0054dd80
// Creates a VFXEffect object (size 0x170) based on parameters from a transform/owner.
// Uses TLS allocations (pool allocator) for small and large objects.

class VFXEffect;

// Global data: _DAT_01126040 (maybe time delta), DAT_00e2e780 (small epsilon)
extern float g_globalTimeDelta;
extern float g_effectEpsilon;

// Pool allocator function (size, tag) -> ptr
void* __fastcall poolAlloc(uint size, uint tag);

// Unknown function: takes two float4 vectors and a scale, returns some handle
int computeBlendedTransform(float* vecA, float* vecB, float scale);

// Called to set up material/texture? (handle, source, param)
void setupMaterial(int handle, int source, int param);

// Global function
void updateGlobalState();

// Send event (eventType, param, flag)
void sendEvent(uint eventType, uint param, uint flag);

class VFXManager {
public:
    // +0x80: base scale factor
    float m_baseScale;          // +0x80
    // +0x84: speed multiplier for life interpolation
    float m_lifeSpeed;          // +0x84
    // +0x90..0x9C: orientation quaternion (w,x,y,z) or rotation matrix third row?
    float m_orientW;            // +0x90
    float m_orientX;            // +0x94
    float m_orientY;            // +0x98
    float m_orientZ;            // +0x9C

    VFXEffect* spawnEffect(uint effectID, float startLife, float currentLife, int extraData);
};

// VFXEffect object layout (size 0x170 = 368 bytes)
class VFXEffect {
public:
    void* vtable;               // +0x00, pointer to PTR_FUN_00e39ec0
    // ... many fields
    uint m_effectID;           // +0x160 (= 0x58*4)
    VFXManager* m_owner;       // +0x164 (= 0x59*4)
};

VFXEffect* VFXManager::spawnEffect(uint effectID, float startLife, float currentLife, int extraData) {
    float progress;    // local_24
    float remaining;   // local_14
    float blendedVec[4];       // local_20,1c,18,14 (w,x,y,z)
    float baseVec[4];          // local_30,2c,28,24 (w,x,y,z)

    // Compute progression factor based on lifeSpeed and currentLife
    progress = m_lifeSpeed * currentLife + g_globalTimeDelta;
    remaining = (startLife - currentLife) * m_lifeSpeed;

    // Clamp/if remaining <= progress, add epsilon
    if (remaining <= progress) {
        remaining = progress + g_effectEpsilon;
    }

    // Create two sets of transformed vectors from the orientation quaternion
    blendedVec[0] = m_orientW * remaining;
    blendedVec[1] = m_orientX * remaining;
    blendedVec[2] = m_orientY * remaining;
    blendedVec[3] = m_orientZ * remaining;   // note: overwrites remaining original? but fine

    baseVec[0] = m_orientW * progress;
    baseVec[1] = m_orientX * progress;
    baseVec[2] = m_orientY * progress;
    baseVec[3] = m_orientZ * progress;

    // Thread-local storage access (not used directly, just a call)
    TlsGetValue(/*DAT_01139810*/);

    // Allocate small buffer (0x40 bytes) - perhaps for a temporary effect node
    int smallBuffer = (int)poolAlloc(0x40, 0x27);
    *(uint16*)(smallBuffer + 4) = 0x40;   // set size?

    // Compute blend using baseVec and blendedVec, scaled by baseScale * currentLife
    int blendHandle = computeBlendedTransform(blendedVec, baseVec, m_baseScale * currentLife);

    TlsGetValue(/*DAT_01139810*/);

    // Allocate the main effect object
    VFXEffect* effect = (VFXEffect*)poolAlloc(0x170, 0x31);
    *(uint16*)(((char*)effect) + 4) = 0x170;   // set size?

    // Set up material or texture for the effect
    setupMaterial(blendHandle, /*DAT_011397d0*/ 0x011397d0, extraData);

    // Initialize vtable and fields
    effect->vtable = (void*)&PTR_FUN_00e39ec0;   // VFXEffect_vtable
    effect->m_effectID = effectID;
    effect->m_owner = this;

    // Update global state
    updateGlobalState();

    // Send an event (probably effect creation event)
    sendEvent(0x2001, effectID, 0);

    return effect;
}