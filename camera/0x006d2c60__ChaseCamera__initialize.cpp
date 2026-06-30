// FUNC_NAME: ChaseCamera::initialize
// Function address: 0x006d2c60
// Role: Initializes chase camera parameters including source position, target position, 
//       orientation quaternion, and computes initial delta and distance.
//       Performs collision checks between source and target and may adjust delta.

void __thiscall ChaseCamera::initialize(
    float* sourcePos,      // param_2: 3D position (x,y,z) with w=1? Actually 4 floats stored
    float* targetQuat,     // param_3: orientation quaternion (x,y,z,w) stored as undefined4 but likely floats
    float* targetPos       // param_4: 3D target position (x,y,z) with w=1? Actually 4 floats stored
)

{
    float *srcPos;         // will point to this+0x10
    float dx, dy, dz;      // temporary variables
    float tx, ty, tz, tw;  // target temps
    bool bResult;

    // Copy source position to this+0x10 (Vector4)
    *(float*)(this + 0x10) = sourcePos[0]; // x
    *(float*)(this + 0x14) = sourcePos[1]; // y
    *(float*)(this + 0x18) = sourcePos[2]; // z
    *(float*)(this + 0x1C) = sourcePos[3]; // w (usually 1.0 or 0.0)

    // Copy target orientation quaternion to this+0x20 (Vector4)
    *(int*)(this + 0x20) = targetQuat[0]; // ix
    *(int*)(this + 0x24) = targetQuat[1]; // iy
    *(int*)(this + 0x28) = targetQuat[2]; // iz
    *(int*)(this + 0x2C) = targetQuat[3]; // iw

    // Re-read source position for delta calculation
    tx = sourcePos[1]; // Actually reusing tx,ty,tz,tw but not used? Wait, re-read for delta
    ty = sourcePos[2];
    tz = sourcePos[3]; // w not used in delta

    // Compute initial delta: targetPos - sourcePos (3D vector)
    *(float*)(this + 0x60) = targetPos[0] - sourcePos[0];
    *(float*)(this + 0x64) = targetPos[1] - sourcePos[1];
    *(float*)(this + 0x68) = targetPos[2] - sourcePos[2];
    *(float*)(this + 0x6C) = 0.0f; // ensure z component of delta is zero? Actually overwritten to 0

    // Zero out velocity/acceleration fields (0x40-0x5c: 5 floats? Actually 8 floats from 0x40 to 0x5c)
    *(int*)(this + 0x40) = 0;
    *(int*)(this + 0x44) = 0;
    *(int*)(this + 0x48) = 0;
    *(int*)(this + 0x4C) = 0;
    *(int*)(this + 0x50) = 0;
    *(int*)(this + 0x54) = 0;
    *(int*)(this + 0x58) = 0;
    *(int*)(this + 0x5C) = 0;

    // Copy target position to this+0x30 (Vector4)
    *(float*)(this + 0x30) = targetPos[0];
    *(float*)(this + 0x34) = targetPos[1];
    *(float*)(this + 0x38) = targetPos[2];
    *(float*)(this + 0x3C) = targetPos[3];

    // Point to source position for further use
    srcPos = (float*)(this + 0x10);

    // Initialize flags/state
    *(char*)(this + 0x7C) = 0;  // byte flag
    *(int*)(this + 0x80) = 0;   // int flag
    *(int*)(this + 0x78) = 0;   // int flag

    // Compute some speed/factor (e.g., frame rate independent multiplier)
    *(float*)(this + 0x84) = DAT_00e510d4 * DAT_00d5eee4;  // constant product

    // Compute initial distance between source and target
    dx = srcPos[0] - targetPos[0];
    dy = srcPos[1] - targetPos[1];
    dz = srcPos[2] - targetPos[2];
    *(float*)(this + 0x88) = sqrtf(dx*dx + dy*dy + dz*dz);

    // Initialize spring/damping constants? (maybe from global defaults)
    *(int*)(this + 0x70) = 0;
    *(int*)(this + 0x74) = 0;
    *(float*)(this + 0x8C) = DAT_00e51134;  // spring constant?
    *(float*)(this + 0x90) = DAT_00e51188;  // damping constant?
    *(int*)(this + 0x94) = 0;

    // Set global flag? (might be debug or state)
    DAT_0112a863 = 0;

    // Perform collision check: line of sight from source to target
    bResult = checkClearLine(srcPos, targetPos, 0); // FUN_006d0ee0
    if (!bResult) {
        // If first test fails, try alternative test
        bResult = findAlternateTarget(srcPos, targetPos); // FUN_006d1890
        if (bResult) {
            // If alternative found, update delta based on targetPos relative to source
            *(float*)(this + 0x60) = targetPos[0] - srcPos[0];
            *(float*)(this + 0x64) = targetPos[1] - srcPos[1];
            *(float*)(this + 0x68) = targetPos[2] - srcPos[2];
            *(float*)(this + 0x6C) = targetPos[3] - srcPos[3]; // but srcPos[3] is w, likely zero
        }
    }
}