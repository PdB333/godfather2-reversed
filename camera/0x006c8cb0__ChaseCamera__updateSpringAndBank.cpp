// FUNC_NAME: ChaseCamera::updateSpringAndBank
float g_springConstantScale; // DAT_00e445c8
bool g_useNegativeSpring;    // DAT_0112a7a4
float g_one;                 // DAT_00e44564
float g_angleScale;          // DAT_00e44748

void __thiscall ChaseCamera::updateSpringAndBank(float deltaTime, float damping, float springK, float something5, const float* from, float* to, float* outForward)
{
    // Global constants
    float springScale = g_springConstantScale;
    float one = g_one;

    // Compute target offset from spring (vertical component)
    float targetY;
    if (!g_useNegativeSpring)
        targetY = springK * deltaTime * springScale; // Actually param_2 * param_4 * g_springConstantScale
    else
        targetY = one - springK * deltaTime * springScale;

    // Update the spring state (position +0x8c, velocity +0x90)
    float currentY = *(float*)(this + 0x8c) - targetY;
    float springVelocity = *(float*)(this + 0x90);
    float dampingFactor = currentY * something5 + springVelocity;
    dampingFactor *= damping;

    // Some math: sqrt-like or clamp?
    float sqrtOneMinusDampingSq; // actually (double)(one - damping * something5) then call FUN_00b9be2b
    double dVal = (double)(one - damping * something5);
    FUN_00b9be2b(); // Probably sqrt(1 - damping^2) or similar
    float blendFactor = (float)dVal; // use it as blend factor

    float newY = (dampingFactor + currentY) * blendFactor + targetY;
    *(float*)(this + 0x8c) = newY;
    *(float*)(this + 0x90) = (*(float*)(this + 0x90) - dampingFactor * something5) * blendFactor;

    // Now compute horizontal offset from 'from' to 'to'
    float dx = to[0] - from[0];
    float dy = to[1] - from[1];
    float dz = to[2] - from[2];

    // Normalize the horizontal direction (x,z)
    float horizDir[3] = { dx, 0.0f, dz };
    normalizeVector(&horizDir, &horizDir); // FUN_0056afa0 likely normalizes

    // Compute a perpendicular horizontal vector (cross with up)
    float perp[3];
    perp[0] = -horizDir[2];
    perp[1] = 0.0f;
    perp[2] = horizDir[0];

    // Blend the original direction (dx,dy,dz) with the perpendicular direction using newY as weight
    vectorBlend(&dx, &dy, &dz, &perp, newY); // FUN_004a0370 modifies dx,dy,dz in place

    // Update 'to' position
    to[0] = from[0] + dx;
    to[1] = from[1] + dy;
    to[2] = from[2] + dz;

    // Compute output forward vector (likely horizontal)
    double tmpDY = (double)dy;
    FUN_00b9a9fa(); // some operation?
    outForward[0] = (float)tmpDY * g_angleScale; // dy * scale
    double tmpDX = (double)(one - dx);
    FUN_00b9a9fa(); // some operation?
    outForward[1] = (float)tmpDX * g_angleScale; // (1 - dx) * scale
    outForward[2] = 0.0f;
}

// Helper functions (stubs, actual implementations unknown)
void normalizeVector(float* out, const float* in);
void vectorBlend(float* x, float* y, float* z, const float* blendWith, float blendAmount);
void sqrtOneMinusXSq(); // FUN_00b9be2b
void someOtherFunc();   // FUN_00b9a9fa