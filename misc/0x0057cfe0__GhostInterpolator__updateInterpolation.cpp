// FUNC_NAME: GhostInterpolator::updateInterpolation

#include <cmath>

// Constants from data references
static const float INTERPOLATION_EPSILON = 0.00001f; // Approx from DAT_00e2e780
static const float ROUNDING_ADJUSTMENT = 0.5f; // Approx from DAT_00e44578 (maybe for rounding negative numbers)

// Forward declarations of internal helpers
static void validateInterpolationState(int state, float* outData, void* context);
static int checkInterpolationFlag(int flag);
static void finalizeInterpolation(void* buffer);
static void cleanupInterpolation(void* buffer, void* context);

// Structure for the ghost interpolation node (likely part of GhostManager or similar)
struct GhostInterpolationNode {
    void* m_pOwner;            // +0x00: Pointer to owning system (e.g., GhostManager)
    int* m_pState;             // +0x04: Pointer to state structure (e.g., movement state)
    float m_blendFactor;       // +0x08: Current interpolation blend factor (0..1)
    int m_extraParam;          // +0x0C: Extra parameter for initialization
};

// The cached pointer table or function pointer
struct OwnerData {
    int* m_pCachedFunction;    // +0x38: Cached result from some initialization (or null)
    void* m_pBufferBase;       // +0x34: Base pointer to interpolation buffer (offset+0x14 used)
};

// Main update function
unsigned int __thiscall updateInterpolation(GhostInterpolationNode* this) {
    int* statePtr = this->m_pState;                 // iVar2 = in_EAX[1]
    int integerPart = (int)roundf(this->m_blendFactor);  // local_1c = ROUND(m_blendFactor)
    float fraction = this->m_blendFactor - (float)integerPart; // local_c
    float complement = 1.0f - fraction;               // local_8

    // Determine which offset to use based on a flag in state
    int flag = (*(unsigned char*)(statePtr + 1)); // +0x04 of state, check low byte
    int valueOffset = (flag < 10) ? 0x24 : 0x2C; // local_10: pick from state based on priority
    // local_10 is not used further? Possibly for validation

    // Check if fraction is near 0 or 1 -> interpolation almost complete
    int stateFlag; // local_24
    if (fraction <= INTERPOLATION_EPSILON || complement <= INTERPOLATION_EPSILON) {
        // At endpoint: reset fraction and set stateFlag to 0 (with some bit shift)
        fraction = 0.0f;
        stateFlag = 0; // Actually: (uint)local_24._1_3_ << 8; but simplified
    } else {
        // Mid-interpolation: set stateFlag to 1
        stateFlag = 1;
    }

    // Ensure the cached function pointer in owner is initialized
    OwnerData* owner = (OwnerData*)this->m_pOwner;
    if (owner->m_pCachedFunction == 0) {
        owner->m_pCachedFunction = initializeCache(this->m_extraParam); // FUN_0056ef10
    }

    // Compute buffer pointer for interpolation
    void* buffer = (char*)owner->m_pBufferBase + 0x14;

    // Call external processing function (probably updates interpolation data)
    float outputData = 0.0f;
    processInterpolation(buffer, stateFlag, &outputData, g_context); // FUN_0057cd80

    // Check interpolation flag and possibly finalize
    int flagResult = checkInterpolationFlag(stateFlag); // FUN_0057caa0
    if (flagResult != 0) {
        // Interpolation ongoing: finalize and setup next
        finalizeInterpolation();                          // FUN_0057cc40
        finalizeBuffer(buffer);                          // FUN_0057ccc0
        return 1;
    }

    // Interpolation completed: cleanup
    cleanupBuffer(buffer, g_context);                    // FUN_0057cd30
    return 1;
}

// Dummy implementations of callees (for completeness, not full)
static int initializeCache(int param) { return (int)malloc(16); }
static void processInterpolation(void* buf, int flag, float* out, void* ctx) {}
static int checkInterpolationFlag(int flag) { return flag; }
static void finalizeInterpolation() {}
static void finalizeBuffer(void* buf) {}
static void cleanupBuffer(void* buf, void* ctx) {}
static void* g_context = (void*)0x01223d40; // Global context used in callees