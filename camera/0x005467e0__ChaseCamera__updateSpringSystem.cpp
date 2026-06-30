// FUNC_NAME: ChaseCamera::updateSpringSystem

// Function address: 0x005467e0
// Purpose: Updates spring-based camera velocity from position difference between camera and target.
// This is likely part of ChaseCamera's smooth follow logic.

// Note: unaff_ESI = this, unaff_EDI = pointer to camera position (x,y,z,w)
// The class contains at least two sub-objects:
// - m_pTarget (offset +0x2e8): target object with position, spring factor
// - m_pSpring (offset +0x368): spring state storing velocity

void ChaseCamera::updateSpringSystem(void) {
    float frameTime;
    float springFactor;
    float diff[4];           // cameraPos - targetPos
    float output[4];         // computed spring force/reset (unused directly here?)
    float* cameraPos;        // unaff_EDI

    cameraPos = /* passed in EDI (via calling convention) */ nullptr; // actual pointer from caller

    // Call a virtual function on the target object (likely a method like "getPosition"?)
    // vtable at +0xd0, function at +0x14 (maybe update or getLatest)
    (*(void (**)(void))(**(int**)(*(int*)((char*)this + 0x2e8) + 0xd0) + 0x14))();

    // Get frame time (likely in seconds)
    frameTime = FUN_009efd10();

    // Compute difference: cameraPos - targetPos
    float* target = *(float**)((char*)this + 0x2e8);
    diff[0] = cameraPos[0] - target[0x160 / 4]; // x
    diff[1] = cameraPos[1] - target[0x164 / 4]; // y
    diff[2] = cameraPos[2] - target[0x168 / 4]; // z
    diff[3] = cameraPos[3] - target[0x16c / 4]; // w (if used)

    // Compute spring force / damping based on difference and time
    FUN_009df220(&diff, frameTime, output);

    // Process camera position (maybe store or transform)
    FUN_009f4400(cameraPos);

    // Process output (maybe rotation or acceleration)
    FUN_009f3dc0(output);

    // Apply spring force scaled by factor from target object
    springFactor = target[0x19c / 4];

    float* spring = *(float**)((char*)this + 0x368);
    // Note: offsets 0x74,0x78,0x7c correspond to velocity components (vx,vy,vz)
    spring[0x74 / 4] = output[2] * springFactor; // possibly vz? Using diff[2]? Check
    spring[0x78 / 4] = output[1] * springFactor;
    spring[0x7c / 4] = output[0] * springFactor;

    return;
}