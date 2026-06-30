// FUNC_NAME: CharacterController::updateMovement

/*
 * Address: 0x00425410
 * Role: Updates character movement based on controller input.
 * Integrates input flags into velocity and applies physics.
 * Handles initialization and state transitions.
 */
void CharacterController::updateMovement() {
    int controllerIndex;
    int* piVar1;
    float* pfControllerState;
    bool bActive;
    float dt;
    float fVar10, fVar11, fVar14, fVar15, fVar16, fVar17;
    float fInputX, fInputY, fInputZ, fInputW; // raw input components
    uint uControllerSlot;
    undefined4* pSource;
    float fStack_15c, fStack_150, fLocal160;
    float fStack_154; // frame time
    int iStack_158; // braking?
    float fStack_114; // sin/cos?
    undefined4 auStack_110[3]; // temporary quaternion
    undefined4 uStack_14c, uStack_148, uStack_144; // rotation components

    // === Initialization check ===
    if (this->m_bInitialized == 0) {
        this->m_bFirstUpdate = 0;
    }

    uControllerSlot = 1;
    controllerIndex = FUN_00424cf0(0); // get active controller index
    if ((controllerIndex != -1) &&
        (piVar1 = *(int**)(*(int*)(DAT_012233a0 + 4) + controllerIndex * 4), piVar1 != (int*)0x0) &&
        (iVar5 = (**(code**)(*piVar1 + 8))(), iVar5 == 1)) {
        uControllerSlot = 0; // keyboard/mouse?
    }

    if (this->m_bInitialized == 0) {
        return;
    }

    if (this->m_bFirstUpdate == 0) {
        // First time initialization
        if (this->m_bUseSourceData == 0) {
            pSource = NULL;
        } else {
            pSource = (undefined4*)this->m_pRotationMatrix; // +0x10
        }

        if ((controllerIndex == -1) ||
            (piVar1 = *(int**)(*(int*)(DAT_012233a0 + 4) + controllerIndex * 4), piVar1 == (int*)0x0) ||
            ((controllerIndex = (**(code**)(*piVar1 + 0xc))(), controllerIndex == 0) || (this->m_bActive == 0))) {
            // No active controller or character inactive -> reset all movement state
            this->m_fTargetYaw = 0.0f;       // +0x12c
            this->m_pitch = 0.0f;            // +0x118
            this->m_roll = 0.0f;             // +0x104
            this->m_yaw = 0.0f;              // +0xf0
            this->m_forwardVel = 0.0f;       // +0xfc
            this->m_strafeVel = 0.0f;        // +0x100
            this->m_upVel = 0.0f;            // +0xf8
            this->m_vertVel = 0.0f;          // +0xf4
            this->m_targetForward = 0.0f;    // +0x10c
            this->m_targetStrafe = 0.0f;     // +0x114
            this->m_targetUp = 0.0f;         // +0x110
            this->m_unknown108 = 0.0f;       // +0x108
            this->m_pitchVel = 0.0f;         // +0x11c
            this->m_rollVel = 0.0f;          // +0x128
            this->m_yawVel = 0.0f;           // +0x124
            this->m_unknown120 = 0.0f;       // +0x120

            // Set rotation from source matrix (first 3x3 part)
            this->m_rotationX = pSource[8];   // +0x130
            this->m_rotationY = pSource[9];   // +0x134
            this->m_rotationZ = pSource[10];  // +0x138
            this->m_posX = *pSource;          // +0x13c
            this->m_posY = pSource[1];        // +0x140
            this->m_posZ = pSource[2];        // +0x144
        } else {
            // Copy full rotation matrix from controller state
            undefined4* pControllerRot = (undefined4*)(controllerIndex + 0xd0);
            undefined4* pDest = (undefined4*)this->m_rotationMatrix; // +0xf0
            undefined4 localMatrix[16];
            for (int i = 0; i < 16; i++) {
                localMatrix[i] = *pControllerRot++;
            }
            // Zero out some entries
            localMatrix[2] = 0; // uStack_98
            localMatrix[1] = 0; // uStack_9c
            localMatrix[0] = 0; // uStack_a0
            localMatrix[3] = 0; // uStack_84
            localMatrix[4] = 0; // uStack_74
            localMatrix[5] = 0; // uStack_64
            localMatrix[6] = 0.0f; // uStack_54
            FUN_00424770(); // normalize? or compute something

            localMatrix[7] = 0; // uStack_44
            localMatrix[8] = 0; // uStack_34
            localMatrix[9] = 0; // uStack_24
            localMatrix[10] = 0.0f; // uStack_14

            uStack_14c = pSource[8];
            uStack_148 = pSource[9];
            uStack_144 = pSource[10];
            FUN_00424720(auStack_110, &uStack_14c); // convert to quaternion

            // Zero another temporary matrix
            undefined4 temp2[12];
            temp2[0] = 0;
            temp2[1] = 0;
            temp2[2] = 0;
            temp2[3] = 0.0f;
            FUN_00417560(); // initialize something

            // Copy temporary matrix to object state
            pControllerRot = (undefined4*)localMatrix;
            pDest = (undefined4*)(this + 0xf0);
            for (int i = 0; i < 16; i++) {
                *pDest++ = *pControllerRot++;
            }

            this->m_posX = *pSource;        // +0x13c
            this->m_posY = pSource[1];       // +0x140
            this->m_posZ = pSource[2];       // +0x144

            FUN_00424750(this + 0x130, auStack_110); // set rotation from quaternion
        }
        this->m_bFirstUpdate = 1;
    }

    // === Regular update ===
    // Compute frame time
    fStack_154 = DAT_01206800 * DAT_00e44620; // delta time

    // Determine acceleration scale based on input
    dt = fStack_154;
    if (FUN_00410280(uControllerSlot, 0x400, 1)) { // trigger/button?
        fStack_154 = DAT_00e4495c;
        dt = DAT_00e4495c;
    }
    if (FUN_00410280(uControllerSlot, 0x100, 1)) { // another input
        fStack_154 = DAT_00e2b334;
        dt = DAT_00e2b334;
    }

    iStack_158 = 0;
    if (FUN_00410280(uControllerSlot, 0x200, 1)) {
        iStack_158 = -1; // brake or reverse
    }
    if (FUN_00410280(uControllerSlot, 0x800, 1)) {
        iStack_158 = iStack_158 + 1; // forward/accelerate
    }

    // Get raw input axes (normalized -1..1)
    fInputX = 0.0f; fInputY = 0.0f; fInputZ = 0.0f; fInputW = 0.0f;
    if (uControllerSlot == 0x11) {
        pfControllerState = (float*)(DAT_012233b4 + 0x2c); // keyboard/mouse state
    } else {
        if (uControllerSlot > 0xf) goto SKIP_READ;
        pfControllerState = (float*)(DAT_012233b4 + 0x2c + uControllerSlot * 0x44);
    }
    if (pfControllerState != NULL) {
        fInputX = *pfControllerState;
        fInputY = pfControllerState[1];
        fInputZ = pfControllerState[2];
        fInputW = pfControllerState[3];
    }
SKIP_READ:

    float fRawX = fInputX;
    float fRawY = fInputY;
    float fRawZ = fInputZ;
    float fRawW = fInputW;

    // Check if look-stick is used (0x80)
    if (FUN_00410280(uControllerSlot, 0x80, 1)) {
        fRawX = 0.0f;
        fRawY = 0.0f;
        fInputX = 0.0f;
        fInputY = 0.0f;
    }

    // Dead zones (threshold DAT_00e44680)
    if (*(float*)&((uint)fRawX & DAT_00e44680) <= DAT_00e30ba0) {
        fInputX = 0.0f;
    }
    if (*(float*)&((uint)fRawY & DAT_00e44680) <= DAT_00e30ba0) {
        fInputY = 0.0f;
    }
    if (*(float*)&((uint)fRawZ & DAT_00e44680) <= DAT_00e30ba0) {
        fInputZ = 0.0f;
    }
    if (*(float*)&((uint)fRawW & DAT_00e44680) <= DAT_00e30ba0) {
        fInputW = 0.0f;
    }

    // Apply input to movement with rate limits (0x10, 0x20 flags)
    if (FUN_00410280(uControllerSlot, 0x10, 1)) {
        float fRateX = dt * DAT_00e44958;
        this->m_posX += this->m_targetForward * fRateX;
        this->m_posY += this->m_targetStrafe * fRateX;
        this->m_posZ += this->m_targetUp * fRateX;
    }
    if (FUN_00410280(uControllerSlot, 0x20, 1)) {
        float fRateY = dt * DAT_00e44954;
        this->m_posX += this->m_targetForward * fRateY;
        this->m_posY += this->m_targetStrafe * fRateY;
        this->m_posZ += this->m_targetUp * fRateY;
    }

    // Compute angular velocity component
    fStack_114 = (float)sin(this->m_rotationY); // or cos? actually FUN_00b99fcb and FUN_00b99e20 might be sin/cos
    // (FUN_00b99fcb might be cos, FUN_00b99e20 might be sin)
    double dAngle = this->m_rotationY;
    FUN_00b99fcb(); // cos?
    fStack_114 = (float)dAngle;
    dAngle = this->m_rotationY;
    FUN_00b99e20(); // sin?
    float fSin = (float)dAngle;
    float fCos = fStack_114;

    float fGravity = DAT_00e44828;
    float fMoveX = fSin * fInputX * fStack_154 * fGravity;
    this->m_posX += this->m_forward * fMoveX;
    this->m_posY += this->m_strafe * fMoveX;
    this->m_posZ += this->m_up * fMoveX;

    fMoveX = fCos * fInputX * fStack_154 * DAT_00e35654;
    this->m_posX += this->m_forwardTarget2 * fMoveX;
    this->m_posY += this->m_strafeTarget2 * fMoveX;
    this->m_posZ += this->m_upTarget2 * fMoveX;

    float fMoveY = fCos * fInputY * fStack_154 * fGravity;
    this->m_posX += this->m_forward * fMoveY;
    this->m_posY += this->m_strafe * fMoveY;
    fMoveX = DAT_00e2b1a0;
    float fMoveZ = fSin * fInputY * fStack_154 * fGravity;
    this->m_posZ += this->m_up * fMoveY;
    this->m_posX += fMoveZ * this->m_forwardTarget2;
    this->m_posY += fMoveZ * this->m_strafeTarget2;

    // Apply damping to angular velocity (0x30?)
    float fDamping = (DAT_00f17958 < fStack_154) ? ( (DAT_00e2b1a0 <= fStack_154) ? DAT_00e2b1a0 : fStack_154 ) : DAT_00f17958;
    this->m_rotationY -= fDamping * fInputZ * DAT_00e44950;

    fDamping = (DAT_00f17958 < fStack_154) ? ( (DAT_00e2b1a0 <= fStack_154) ? DAT_00e2b1a0 : fStack_154 ) : DAT_00f17958;
    this->m_rotationX += fDamping * fInputW * DAT_00e44950;

    // Apply braking
    float fBrake;
    if (DAT_00f17958 < fStack_154) {
        fBrake = (DAT_00e2b1a0 <= fStack_154) ? DAT_00e2b1a0 : fStack_154;
    } else {
        fBrake = DAT_00f17958;
    }
    this->m_rotationZ += (float)iStack_158 * fBrake * DAT_00e44950;

    // === Final application ===
    if (this->m_bActive == 0) {
        // If not active, only apply position with speed multiplier
        float fSpeedMult = this->m_speedMultiplier * DAT_00e445c8;
        FUN_00425ea0(0, this->m_posX, this->m_rotationX, this->m_posY, this->m_rotationY, this->m_posZ, this->m_rotationZ, 0.0f, 0.0f, fSpeedMult);
        return;
    }

    // Active: compute orientation from rotation vector
    undefined4 temp[4];
    FUNCTION_0056b8a0(this->m_rotationY, this->m_rotationX, this->m_rotationZ, auStack_110);

    undefined4 tempQuat[3];
    tempQuat[0] = 0;
    tempQuat[1] = 0;
    tempQuat[2] = 0;
    tempQuat[3] = 0.0f;
    FUN_00417560();

    // Combine rotation and input forces
    undefined4 finalQuat[4];
    FUNCTION_0056c180(tempQuat, &uStack_148, &uStack_14c, &uStack_144);

    float fSpeedMult = this->m_speedMultiplier * DAT_00e445c8;
    FUN_00425ea0(0, this->m_posX, this->m_posY, this->m_posZ, finalQuat[0], finalQuat[1], finalQuat[2], finalQuat[3]? (actually parameters unclear)
    // Need to examine call more carefully, but for reconstruction assume it applies final transform
        , fSpeedMult);
}