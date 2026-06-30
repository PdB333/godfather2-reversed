// FUNC_NAME: PhysicsObject::applyForce
// Address: 0x0046cf70
// Reconstructed from Ghidra decompilation

class PhysicsObject {
public:
    // Applies a force/impulse to the object
    // param_2: direction vector (pointer to 3 floats)
    // param_3: force magnitude
    // param_4: unknown parameter (possibly force type or flags)
    __thiscall PhysicsObject* applyForce(float* direction, float magnitude, uint32_t param_4) {
        // Scale magnitude by global time scale factor
        float scaledMagnitude = magnitude * g_timeScale; // DAT_00e445c8

        // Get simulation times (possibly frame time and current time)
        double time1 = getTime1(); // FUN_00b99fcb
        double time2 = getTime2(); // FUN_00b99e20

        // Extract direction components from input vector
        float x = direction[0];
        float y = direction[1];
        float z = direction[2];

        // Compute squared length of direction vector
        float lengthSq = x * x + y * y + z * z;

        // Normalize if length is above epsilon, otherwise zero
        float scale;
        if (lengthSq <= g_epsilonSq) { // DAT_00e2cbe0
            scale = 0.0f;
        } else {
            scale = g_invSqrtScale / sqrtf(lengthSq); // DAT_00e2b1a4 / sqrt(lengthSq)
        }

        // Normalized direction scaled by scale
        float forceX = scale * x;
        float forceY = scale * y;
        float forceZ = scale * z;

        // Apply the force using internal function
        // Arguments: this, force vector, remaining magnitude after time subtraction, time1, param_4
        FUN_0046cd60(this, &forceX, g_forceMax - (float)time2, (float)time1, param_4);

        return this;
    }

private:
    // Internal force application routine (see FUN_0046cd60)
    void FUN_0046cd60(PhysicsObject* obj, float* force, float magnitude, float time, uint32_t flags);

    // External time retrieval functions (likely from EARS engine)
    double getTime1(); // FUN_00b99fcb
    double getTime2(); // FUN_00b99e20

    // Global constants (assumed from data refs)
    static float g_timeScale;           // DAT_00e445c8
    static float g_epsilonSq;           // DAT_00e2cbe0
    static float g_invSqrtScale;        // DAT_00e2b1a4
    static float g_forceMax;            // DAT_00e2b1a4 (same constant used as max force magnitude)
};