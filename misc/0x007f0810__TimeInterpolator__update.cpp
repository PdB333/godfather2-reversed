// FUNC_NAME: TimeInterpolator::update

// Global time variable (likely from EARS engine)
extern float g_currentTime; // _DAT_00d5780c

// Forward declaration of the helper function
void setBlendValue(float sourceVal, float targetVal, float blendFactor); // FUN_007f27a0

class TimeInterpolator {
public:
    // Offsets:
    // +0x00: vtable? (not used here)
    // +0x04: pointer to source object (has float at +0x128)
    // +0x08: pointer to target object (has float at +0x128)
    // +0xf4: start time (float)

    void* m_pSource;   // +0x04
    void* m_pTarget;   // +0x08
    float m_startTime; // +0xf4

    void update() {
        float elapsed = g_currentTime - m_startTime; // fVar1
        // Compute blend factor: quadratic easing (global - (global - start)^2)
        float blendFactor = g_currentTime - elapsed * elapsed;

        // Get the source and target values from their respective objects at offset 0x128
        float sourceVal = *(float*)(*(int*)m_pSource + 0x128);
        float targetVal = *(float*)(*(int*)m_pTarget + 0x128);

        // Call the blending function
        setBlendValue(sourceVal, targetVal, blendFactor);
    }
};