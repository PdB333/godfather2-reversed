// FUNC_NAME: PhysicsHelpers::computeForceFromVelocity
void __fastcall computeForceFromVelocity(void* this, void* object, float* outForce, float* outOffset) 
{
    // This function computes a force/torque vector based on object's velocity components (at offsets 0x144, 0x148)
    // and various engine global parameters. Outputs a 4-float force vector (outForce) and optionally an offset (outOffset).
    // Called by multiple update functions (e.g., 0x00518010, 0x005186d0, etc.) for physics processing.

    float baseValue = g_fBaseValue; // DAT_012192d0
    int flags = g_iFlags; // DAT_012192f4

    if ((flags & 4) != 0) {
        // Apply interpolation using four global coefficients and time-based values
        baseValue = g_fCoeff0 * g_fTime0 + g_fCoeff1 * g_fTime1 + g_fCoeff2 * g_fTime2 + g_fCoeff3 * g_fTime3 + g_fBaseValue;
    }

    float velX = *(float*)((int)object + 0x144);   // Linear velocity X
    float velY = *(float*)((int)object + 0x148);   // Linear velocity Y (or angular component)

    float horizontalForce;
    if ((flags & 2) == 0) {
        horizontalForce = 0.0f;
    } else {
        horizontalForce = g_fTimeDelta - g_fWindOffset; // DAT_00e44564 - _DAT_012192e8
    }

    bool useVertical = (flags & 1) != 0;
    *outForce = horizontalForce;

    float verticalForce = g_fVerticalBase; // DAT_012192ec
    if (!useVertical) {
        verticalForce = 0.0f;
    }
    outForce[1] = verticalForce;

    // Get a per-thread/per-context index
    int contextIndex = *(int*)(**(int**)(*(int*)(__readfsdword(0x2c)) + 0x34)); // FS:0x2c -> pointer + 0x34 -> int
    float dampingFactor = g_fDamping; // DAT_012192d4
    float drag = dampingFactor * velY;

    // Intermediate calculations for force components
    float temp = (baseValue * baseValue * (velY - velX)) / (drag * velX);
    outForce[2] = (((velY / baseValue) * velX - velX) / (velY - velX)) * temp - temp;
    float globalParam = g_fGlobalParam; // DAT_00e2b1a4
    outForce[3] = temp;

    // Adjust final outForce[3] using an extra per-context scale
    float scale = globalParam;
    if (contextIndex != -1) {
        scale = *(float*)(&g_ContextFloatArray[contextIndex * 3]); // DAT_011f6bbc + contextIndex*3
    }
    outForce[3] = (globalParam / scale) * temp;

    // Optionally write an offset vector (if non-null output pointer)
    if (outOffset != nullptr) {
        float offsetScale = g_fOffsetScale; // _DAT_012192d8
        outOffset[0] = g_fOffsetX * offsetScale; // DAT_01218e44
        outOffset[1] = g_fOffsetY * offsetScale; // DAT_01218e48
        outOffset[2] = 0.0f;
        outOffset[3] = 0.0f;
    }
}