// FUNC_NAME: ChaseCamera::update

// Address: 0x006d3340
// Role: Updates chase camera position, orientation, and damping to follow a target.
// This function processes movement, rotation, and state transitions for a camera that chases a target object.
// It uses multiple damping factors, timers, and collision checks to produce smooth follow behavior.

// Constants used in this function (global data addresses inferred from the binary)
extern float DAT_00e51180;       // Distance threshold for movement?
extern float DAT_00e51134;       // Target rotation damping when moving?
extern float DAT_00e51154;       // Alternative rotation damping?
extern float DAT_00e51140;       // Rotation damping when not moving?
extern float DAT_00e51164;       // Another rotation damping for rotation state?
extern float DAT_00e51188;       // Target for param_1[0x24] when moving?
extern float DAT_00e51190;       // Target for param_1[0x24] when turning?
extern float DAT_00e5118c;       // Target for param_1[0x24] when stationary?
extern float DAT_00e51194;       // Target for param_1[0x24] when rotating?
extern float DAT_00e51198;       // Target for rotation damping when paused?
extern float DAT_00e5119c;       // Target for param_1[0x24] when paused?
extern float DAT_00d5c454;       // Interpolation factor (e.g., smoothing constant)
extern float DAT_00e510f8;       // Scale factor for movement force?
extern float DAT_00e510fc;       // Clamp lower bound for yaw?
extern float DAT_00e51100;       // Clamp upper bound for yaw?
extern float DAT_00e44564;       // Some constant (possibly 0.0 or a small epsilon)
extern float _DAT_00d5780c;      // 1.0f? (used to normalize vectors)
extern float DAT_00d5ccf8;       // Could be -1.0f or similar
extern float DAT_00e51148;       // Distance to stop? (used for close check)
extern float DAT_00e510d4;       // Idle time threshold?
extern float DAT_00e51168;       // Offset for y position?
extern float DAT_00d58cbc;       // Some boundary constant?
extern float DAT_00e51174;       // Speed threshold for acceleration?
extern float DAT_00e51178;       // Target speed?
extern float _DAT_00d5f2b0;      // Acceleration factor?
extern float DAT_00e510c8;       // Some flag (maybe always 0?)
extern float DAT_00d5842c;       // Perhaps a distance for blending?
extern float DAT_00d5ddec;       // Blend factor?
extern float DAT_00e51130;       // Timeout for state?
extern float DAT_00e5113c;       // Reset value for movement timer?
extern float DAT_00e5117c;       // Max distance for position clamping?
extern float DAT_00e44680;       // Bitmask (maybe 0x80000000?)
extern float DAT_00d5c458;       // Another scale factor?
extern float _DAT_00e51168;      // Same as DAT_00e51168? (used in two places)
extern float _DAT_00d5780c;      // Duplicate of 1.0f?
extern float _DAT_00d5f2b0;      // Duplicate acceleration?

// Forward declarations of helper functions (callees)
char FUN_00410eb0();                                                    // Returns non-zero if paused/menu is active
float FUN_006d0e40(uint inputFlags, int timerValue);                    // Smoothing function (e.g., ease in)
float FUN_006d1420(uint inputFlags, float smoothedValue);               // Another smoothing/limit function
void FUN_00b99fcb();                                                    // Math operation (maybe sin/cos or truncation)
void FUN_00b99e20();                                                    // Math operation (maybe sin/cos or truncation)
void FUN_0056ce80(float* result, float* a, float* b);                   // Cross product of two vectors
void FUN_006d2b90(float* targetPos, float* distance, int param);        // Called when camera reaches target (snap/stop)
float FUN_006d02d0(float currentSpeed, float targetSpeed, float acceleration); // Speed update with acceleration
void FUN_006d14b0(int flags, float dt, int targetObj, float* pos, float someFlag, char* outFlag); // Main behavior update
char FUN_006d0ee0(float* a, float* b, float* c);                       // Collision/overlap test? returns 0 if no collision
void FUN_006d16b0(float* targetPos, float* vel, float* result, float dt, int flags); // Update final position
char FUN_006d2db0(float* targetPos, float* curPos, int collisionMask); // Final collision check and position adjustment
char FUN_006d1890(float* curPos, float* targetPos);                    // Another collision/update function

// Chase camera state structure (derived from offsets in param_1)
// All positions and velocities are stored as ints but used as floats via casting.
struct ChaseCamera
{
    void** vtable;      // +0x00
    float posX;         // +0x04 (param_1[1])
    float posY;         // +0x08 (param_1[2])
    float posZ;         // +0x0c (param_1[3])
    float posW;         // +0x10 (param_1[4])
    float dirX;         // +0x14 (param_1[5])
    float dirY;         // +0x18 (param_1[6]) - unused?
    float dirZ;         // +0x1c (param_1[7])
    float dirW;         // +0x20 (param_1[8]) - unused?
    float velX;         // +0x24 (param_1[9])
    float velY;         // +0x28 (param_1[10])
    float velZ;         // +0x2c (param_1[11])
    float velW;         // +0x30 (param_1[12])
    float rotationTimer;   // +0x34 (param_1[13]) - timer for rotation
    float movementTimer;   // +0x38 (param_1[14]) - timer for movement
    float stateTime;       // +0x3c (param_1[15]) - state timer
    char  stateFlag;       // +0x40 (param_1[16]) - state flag (byte)
    float somethingDamping;// +0x44 (param_1[17]) - unknown damping
    float idleTimer;       // +0x48 (param_1[18]) - idle time
    float speed;           // +0x4c (param_1[19]) - current speed magnitude
    float rotationDamping; // +0x50 (param_1[20]) - rotation interpolation target
    float unknownDamping;  // +0x54 (param_1[21]) - another damping variable
    float moveTimer;       // +0x58 (param_1[22]) - movement decay timer
    // Additional members may exist beyond offset 0x58
};

void __thiscall ChaseCamera::update(int* thisPtr, int targetObj, int param3, float dt, float rotationRate, uint moveFlags, int targetTransform, int param8)
{
    bool bMoving;          // derived from param_1[0x25] (moveTimer)
    bool bRotating;        // derived from local_70 and local_74
    bool bPaused;          // from FUN_00410eb0
    float fVar8, fVar10, fVar12;
    double dVar9;
    int iVar;
    float local_30, local_40, local_64, local_68;
    float* pfVar5, * pfVar6;
    char cVar4, cVar3;
    uint uVar2, uVar13;
    float fStack[4];
    // Local state flags (represented as bytes of local_70 and local_74 in decomp)
    bool flagMoving = false;
    bool flagRotating = false;
    char flagPaused = 0;
    bool flagUseAlternative = false;

    // Decay moveTimer with deltaTime
    if (0.0f < (float)thisPtr[0x25]) {
        fVar8 = (float)thisPtr[0x25] - dt;
        thisPtr[0x25] = (int)fVar8;
        if (fVar8 < 0.0f) {
            thisPtr[0x25] = 0;
        }
    }

    // Compute vector from camera to target (target position at targetTransform+0x30)
    pfVar5 = (float*)(targetTransform + 0x30);
    local_30 = *pfVar5 - (float)thisPtr[0xc]; // dx
    fStack[1] = pfVar5[1] - (float)thisPtr[0xd]; // dy
    fStack[2] = pfVar5[2] - (float)thisPtr[0xe]; // dz
    fStack[3] = pfVar5[3] - (float)thisPtr[0xf]; // dw

    // Check if target has a specific flag (bit 9 of +0x8e8) to bypass distance check
    if ((*(uint*)(targetObj + 0x8e8) >> 9 & 1) == 0) {
        // Check if movement is active (flag set)
        if (SQRT(local_30 * local_30 + fStack[1] * fStack[1] + fStack[2] * fStack[2]) / dt > DAT_00e51180) {
            flagMoving = true; // LSB of local_70 set to 1
        }
        // else flagMoving stays false
    } else {
        // If flag is set, skip distance check (force moving)
        flagMoving = true;
    }

    // Determine if the camera is allowed to rotate (from target flags)
    if (((int)*(uint*)(targetObj + 0x8e4) < 0) || ((*(uint*)(targetObj + 0x8e4) >> 0x1e & 1) != 0)) {
        cVar4 = 1; // rotation allowed
    } else {
        cVar4 = 0; // rotation not allowed
    }
    flagUseAlternative = (cVar4 != 0);

    // Check if the game is paused (from global function)
    cVar3 = FUN_00410eb0();
    uVar13 = (uint)DAT_00e44680; // bitmask for bit test

    // Update damping values (param_1[0x23] and param_1[0x24])
    fVar8 = DAT_00d5c454; // interpolation factor
    if (cVar3 == 0) { // not paused
        fVar12 = (float)thisPtr[0x23]; // current rotationDamping
        // Choose target damping based on movement state
        if ((float)thisPtr[0x20] <= 0.0f) { // somethingDamping <= 0 indicates stationary?
            if (flagUseAlternative) {
                thisPtr[0x23] = (int)((DAT_00e51154 - fVar12) * fVar8 + fVar12);
                fVar12 = DAT_00e51190; // target for unknownDamping when turning
            } else {
                thisPtr[0x23] = (int)((DAT_00e51134 - fVar12) * fVar8 + fVar12);
                fVar12 = DAT_00e51188; // target when moving
            }
        } else {
            thisPtr[0x23] = (int)((DAT_00e51140 - fVar12) * fVar8 + fVar12);
            fVar12 = DAT_00e5118c; // target when stationary
        }
        thisPtr[0x24] = (int)((fVar12 - (float)thisPtr[0x24]) * fVar8 + (float)thisPtr[0x24]);
    } else { // paused
        thisPtr[0x23] = (int)((DAT_00e51198 - (float)thisPtr[0x23]) * fVar8 + (float)thisPtr[0x23]);
        thisPtr[0x24] = (int)((DAT_00e5119c - (float)thisPtr[0x24]) * fVar8 + (float)thisPtr[0x24]);
    }

    // Handle movement (using moveFlags param_6)
    if ((float)(moveFlags & (uint)DAT_00e44680) <= 0.0f) {
        // Movement not active -> reset movementTimer
        thisPtr[0x1d] = 0;
    } else {
        // Compute vertical offset or something?
        fStack[0] = (float)thisPtr[0x1a] * (float)thisPtr[0x1a]; // velZ^2
        fStack[2] = DAT_00e44564 - (float)thisPtr[0x18]; // 0 - velX
        local_40 = SQRT(fStack[0] + fStack[2] * fStack[2]); // magnitude of some vector
        fStack[1] = 0.0f;
        fStack[3] = 0.0f;

        if (0.0f < local_40) {
            // Flag rotation active
            flagRotating = true;
            // Apply smoothing to movementTimer
            float smoothed = FUN_006d0e40(moveFlags, thisPtr[0x1d]);
            thisPtr[0x1d] = (int)smoothed;
            // Apply further smoothing
            float finalSmooth = FUN_006d1420(moveFlags, smoothed);
            local_64 = (float)(finalSmooth * DAT_00e510f8); // force scale
            local_68 = (float)(finalSmooth * DAT_00e510f8 * (float)thisPtr[0x1d] * dt);

            cVar4 = FUN_00410eb0();
            fVar8 = local_68;
            if (cVar4 != 0) {
                fVar8 = local_64 * dt; // if paused, use simpler calculation
            }
            local_64 = fVar8 * DAT_00d5c458; // scale further

            // Perform rotation operation (sin/cos?)
            dVar9 = (double)local_64;
            FUN_00b99fcb();
            fVar8 = (float)dVar9 / local_40;
            // Update local vector components
            fStack[0] = fVar8 * fStack[0]; // won? this is overwritten later
            fStack[1] = fVar8 * fStack[1];
            fStack[2] = fVar8 * fStack[2];
            fStack[3] = fVar8 * fStack[3];

            dVar9 = (double)local_64;
            FUN_00b99e20();
            fStack[3] = (float)dVar9;

            // Compute original velocity direction
            local_30 = (float)thisPtr[0x18];
            fStack[1] = (float)thisPtr[0x19];
            fStack[2] = (float)thisPtr[0x1a];
            fStack[3] = (float)thisPtr[0x1b];
            FUN_0056ce80(&fStack[0], &local_30, &local_30); // cross product with itself? probably incorrect, but preserved
            thisPtr[0x1b] = 0;

            // Normalize velocity vector
            fStack[3] = _DAT_00d5780c / SQRT((float)thisPtr[0x18] * (float)thisPtr[0x18] + (float)thisPtr[0x19] * (float)thisPtr[0x19] + (float)thisPtr[0x1a] * (float)thisPtr[0x1a]);
            local_30 = fStack[3] * (float)thisPtr[0x18];
            fStack[1] = fStack[3] * (float)thisPtr[0x19];
            fStack[2] = fStack[3] * (float)thisPtr[0x1a];
            fStack[3] = fStack[3] * (float)thisPtr[0x1b];

            // Clamp yaw component
            fVar8 = DAT_00e510fc;
            if (fStack[1] <= DAT_00e510fc) {
                fVar8 = DAT_00e51100;
                if (DAT_00e51100 <= fStack[1]) {
                    fStack[1] = fVar8;
                }
            } else {
                fStack[1] = fVar8;
            }

            // Compute new velocity magnitude and apply speed
            fVar8 = fStack[2] * fStack[2] + local_30 * local_30;
            if (0.0f < (float)((uint)fVar8 & (uint)DAT_00e44680)) {
                fVar8 = (_DAT_00d5780c - fStack[1] * fStack[1]) / fVar8;
                fVar10 = _DAT_00d5780c;
                if (local_30 < 0.0f) fVar10 = DAT_00d5ccf8;
                fVar12 = DAT_00d5ccf8;
                if (0.0f <= fStack[2]) fVar12 = _DAT_00d5780c;
                fStack[2] = SQRT(fVar8 * fStack[2] * fStack[2]) * fVar12;
                fVar12 = (float)thisPtr[0x22];
                local_30 = SQRT(fVar8 * local_30 * local_30) * fVar10;
                thisPtr[0x18] = (int)(fVar12 * local_30);
                thisPtr[0x19] = (int)(fVar12 * fStack[1]);
                thisPtr[0x1a] = (int)(fVar12 * fStack[2]);
                thisPtr[0x1b] = (int)(fVar12 * fStack[3]);
            }
        }
    }

    // Handle rotation (using param_5 as rotationRate)
    if ((float)((uint)rotationRate & uVar13) <= 0.0f) {
        thisPtr[0x1c] = 0; // rotation timer off
    } else {
        // Get current camera position from vtable functions
        pfVar5 = (float*)(**(code**)(*thisPtr + 0x14))(); // some getter
        pfVar6 = (float*)(**(code**)(*thisPtr + 0x10))(); // another getter
        local_30 = *pfVar6 - *pfVar5;
        fStack[1] = pfVar6[1] - pfVar5[1];
        fStack[2] = pfVar6[2] - pfVar5[2];
        fStack[3] = pfVar6[3] - pfVar5[3];
        fStack[2] = DAT_00e44564 - local_30;
        local_30 = fStack[2];
        if (0.0f < rotationRate) {
            local_30 = 0.0f - fStack[2];
            fStack[2] = 0.0f - fStack[2];
        }
        fStack[3] = 0.0f;
        fStack[1] = 0.0f;
        if (0.0f < SQRT(fStack[2] * fStack[2] + 0.0f + local_30 * local_30)) {
            flagRotating = true;
            // Apply smoothing to rotation timer
            float smoothed = FUN_006d0e40(rotationRate, thisPtr[0x1c]);
            thisPtr[0x1c] = (int)smoothed;
            float finalSmooth = FUN_006d1420(flagMoving ? moveFlags : 0, smoothed);
            local_64 = finalSmooth;
            float temp = finalSmooth * (float)thisPtr[0x1c] * dt;
            cVar4 = FUN_00410eb0();
            if (cVar4 != 0) temp = local_64 * dt;
            dVar9 = (double)temp;
            FUN_00b99e20();
            local_64 = (float)dVar9;
            dVar9 = (double)temp;
            FUN_00b99fcb();
            fVar8 = (float)thisPtr[0x18];
            thisPtr[0x18] = (int)(fVar8 * local_64 - (float)thisPtr[0x1a] * (float)dVar9);
            fVar8 = fVar8 * (float)dVar9 + (float)thisPtr[0x1a] * local_64;
            thisPtr[0x1a] = (int)fVar8;
            fVar8 = SQRT((float)thisPtr[0x18] * (float)thisPtr[0x18] + (float)thisPtr[0x19] * (float)thisPtr[0x19] + fVar8 * fVar8);
            if (0.0f < fVar8) {
                fVar8 = (float)thisPtr[0x22] / fVar8;
                thisPtr[0x18] = (int)(fVar8 * (float)thisPtr[0x18]);
                thisPtr[0x19] = (int)(fVar8 * (float)thisPtr[0x19]);
                thisPtr[0x1a] = (int)(fVar8 * (float)thisPtr[0x1a]);
                thisPtr[0x1b] = (int)(fVar8 * (float)thisPtr[0x1b]);
            }
        }
    }

    // Compute direction to target and set orientation
    pfVar5 = (float*)(targetTransform + 0x30);
    fVar8 = (float)thisPtr[0xc]; // posX
    fVar10 = (float)thisPtr[0xe]; // posZ (likely)
    thisPtr[0x15] = 0; // dirY?
    thisPtr[0x17] = 0; // dirW?
    fVar8 = *pfVar5 - fVar8; // delta x
    fVar10 = pfVar5[2] - fVar10; // delta z
    fVar12 = SQRT(fVar10 * fVar10 + fVar8 * fVar8);
    if (0.0f < fVar12) {
        fVar12 = _DAT_00d5780c / fVar12;
        thisPtr[0x14] = (int)(fVar12 * fVar8); // dirX
        thisPtr[0x16] = (int)(fVar12 * fVar10); // dirZ
    }

    // Check if camera is close enough to target and not moving towards it (dot product sign)
    local_30 = *pfVar5 - (float)thisPtr[4];   // dx
    fStack[1] = pfVar5[1] - (float)thisPtr[5]; // dy
    fStack[2] = pfVar5[2] - (float)thisPtr[6]; // dz
    fStack[3] = pfVar5[3] - (float)thisPtr[7]; // dw
    local_64 = (float)(*(uint*)(targetObj + 0x490) & 0x100); // flag bit test
    bool bCloseAndNotMoving = 0.0f < (float)thisPtr[0x16] * fStack[2] + (float)thisPtr[0x14] * local_30; // dot product with dir
    float dist = SQRT(fStack[1] * fStack[1] + fStack[2] * fStack[2] + local_30 * local_30);
    if ((local_64 == 0.0f) && (dist <= DAT_00e51148) && (!bCloseAndNotMoving)) {
        // Arrived at target
        FUN_006d2b90(pfVar5, (float*)dist, param8);
        return;
    }

    // State machine for idle/rotation timers
    if (!flagMoving) {
        if (!flagRotating) {
            if ((float)thisPtr[0x21] <= DAT_00e510d4) { // idle timer check
                return; // early exit if idle and no movement/rotation
            }
            goto LAB_006d3b28;
        }
        cVar4 = FUN_00410eb0();
        fVar8 = DAT_00d5c454;
        if (cVar4 == 0) {
            thisPtr[0x23] = (int)((DAT_00e51164 - (float)thisPtr[0x23]) * fVar8 + (float)thisPtr[0x23]);
            thisPtr[0x24] = (int)((DAT_00e51194 - (float)thisPtr[0x24]) * fVar8 + (float)thisPtr[0x24]);
        }
    } else if (!flagRotating) {
        // moving and not rotating -> go to state update
        goto LAB_006d3b28;
    }

    // Both moving and rotating active: reset movement timer
    thisPtr[0x25] = (int)DAT_00e5113c;

LAB_006d3b28:
    // Override if alternative flag set (target disallows rotation)
    if (flagUseAlternative) {
        thisPtr[0x25] = 0;
    }

    // Determine if speed should be increased
    if (((bCloseAndNotMoving) || (DAT_00e510d4 < (float)thisPtr[0x21])) &&
        ((flagMoving || ((float)thisPtr[9] <= (float)thisPtr[5] + DAT_00d58cbc))) &&
        (local_68 = (float)thisPtr[0x22], DAT_00e51174 <= local_68)) {
        float accel = dt * _DAT_00d5f2b0;
        float newSpeed = FUN_006d02d0(local_68, DAT_00e51178, accel);
        thisPtr[0x22] = (int)newSpeed;
    }

    // Call main update functions
    pfVar5 = (float*)(targetTransform + 0x30);
    (**(code**)(*thisPtr + 0x18))(auStack_20, pfVar5, param8); // virtual function call (e.g., getOrientation)

    char cStack_82 = 0;
    if ((cStack_7c == 0) || ((char)uStack_80 != 0)) {
        flagMoving = true;
    } else {
        if (DAT_00e510c8 != 0.0f) {
            flagMoving = true;
        } else {
            flagMoving = false;
        }
    }

    // Call behavior update
    FUN_006d14b0(CONCAT31((int3)((uint)flagMoving >> 8), (char)(param8 == 0)), dt, targetObj, &fStack[1], flagMoving, &cStack_82);

    // Compute offset from target position to current velocity
    fStack[0] = *pfVar5 - (float)thisPtr[0x18];
    fStack[1] = *(float*)(targetTransform + 0x34) - (float)thisPtr[0x19];
    local_44 = (float*)(*(float*)(targetTransform + 0x38) - (float)thisPtr[0x1a]);
    local_40 = *(float*)(targetTransform + 0x3c) - (float)thisPtr[0x1b];

    // Adjust y position based on ground height
    uStack_78 = _DAT_00d5780c;
    fStack[3] = (float)thisPtr[4];
    fStack[1] = (float)thisPtr[6];
    local_30 = (float)thisPtr[7];
    fStack[2] = (float)thisPtr[5] - DAT_00e51168;
    char cStack_81 = 0;
    cVar4 = FUN_006d0ee0(thisPtr + 4, &fStack[3], &uStack_78);
    fVar8 = fStack[1];
    if (cVar4 == 0) {
        cStack_81 = 1; // collision detected?
        if ((char)uStack_80 == 0) {
            cVar4 = FUN_00410eb0();
            fVar8 = fStack[1];
            if (cVar4 == 0) {
                float curY = (float)thisPtr[5];
                float diff = fStack[1] - curY;
                if ((diff < 0.0f) && (fVar8 = curY, diff <= DAT_00e44564 - DAT_00e51168)) {
                    fVar8 = diff + DAT_00e51168 + curY;
                }
                if (DAT_00d5842c <= uStack_78) {
                    float blend = (_DAT_00d5780c - uStack_78) * DAT_00d5ddec;
                    fVar8 = (_DAT_00d5780c - blend) * fStack[1] + blend * fVar8;
                }
            }
        }
    }
    fStack[1] = fVar8; // store adjusted y

    // Additional adjustment for collision with ground
    cVar4 = cStack_82;
    if (((cStack_82 == 0) && (cStack_7c != 0)) && (flagMoving) &&
        (cVar3 = FUN_00410eb0(), cVar3 == 0 &&
         cVar3 = FUN_006d0ee0(&fStack[0], &fStack[3], &uStack_78), cVar3 == 0)) {
        fVar8 = (_DAT_00d5780c - uStack_78) * DAT_00e51168;
        fStack[1] = fVar8 + fStack[1];
        thisPtr[0x19] = (int)((float)thisPtr[0x19] - fVar8);
    }

    // Final update of position with collision
    FUN_006d16b0(pfVar5, &fStack[0], &fStack[1], dt, uStack_80);

    // Increase speed if below target
    if (((cStack_7c != 0) && (cVar4 == 0)) &&
        ((flagMoving || ((float)thisPtr[5] <= (float)thisPtr[9] && (float)thisPtr[9] != (float)thisPtr[5] || (DAT_00e510d4 < (float)thisPtr[0x21])))) &&
        (local_40 = (float)thisPtr[0x22], local_40 < DAT_00e51174)) {
        float accel = dt * _DAT_00d5f2b0;
        float newSpeed = FUN_006d02d0(local_40, DAT_00e51178, accel);
        thisPtr[0x22] = (int)newSpeed;
        FUN_006d0960(pfVar5); // additional behavior?
    }

    // Clamp position to a max distance from target
    fVar8 = *(float*)(targetTransform + 0x34);
    fVar10 = *(float*)(targetTransform + 0x38);
    fVar12 = *(float*)(targetTransform + 0x3c);
    pfVar6 = (float*)(thisPtr + 4);
    fStack[3] = (float)thisPtr[4] - *pfVar5;
    fStack[2] = (float)thisPtr[5] - fVar8;
    fStack[1] = (float)thisPtr[6] - fVar10;
    local_30 = (float)thisPtr[7] - fVar12;
    float distToTarget = SQRT(fStack[2] * fStack[2] + fStack[1] * fStack[1] + fStack[3] * fStack[3]);
    float maxDist = DAT_00e5117c * DAT_00e51178; // maximum allowed distance
    if (maxDist < distToTarget) {
        float scale = maxDist / distToTarget;
        *pfVar6 = scale * fStack[3] + *pfVar5;
        thisPtr[5] = (int)(scale * fStack[2] + fVar8);
        thisPtr[6] = (int)(scale * fStack[1] + fVar10);
        thisPtr[7] = (int)(scale * local_30 + fVar12);
    }

    // Final collision check and state update
    cVar4 = FUN_006d2db0(pfVar5, pfVar6, 0);
    if (cVar4 != 0) {
        // Collision detected, reset state
        thisPtr[0x1e] = 0;
        *(char*)(thisPtr + 0x1f) = 0;
        thisPtr[0x21] = (int)((float)thisPtr[0x21] + dt);
        fVar8 = *(float*)(targetTransform + 0x34);
        fVar10 = *(float*)(targetTransform + 0x38);
        fVar12 = *(float*)(targetTransform + 0x3c);
        *(float*)(thisPtr + 0xc) = *pfVar5;
        *(float*)(thisPtr + 0xd) = fVar8;
        *(float*)(thisPtr + 0xe) = fVar10;
        *(float*)(thisPtr + 0xf) = fVar12;
        return;
    }

    // If no collision and not in special states, update velocity
    if (((cStack_81 != 0) || ((char)uStack_80 != 0) || (cStack_82 == 0)) || (_DAT_00e51130 < (float)thisPtr[0x1e])) {
        cVar4 = FUN_006d1890(pfVar6, pfVar5);
        if (cVar4 != 0) {
            fVar8 = *(float*)(targetTransform + 0x34);
            fVar10 = *(float*)(targetTransform + 0x38);
            fVar12 = *(float*)(targetTransform + 0x3c);
            thisPtr[0x18] = (int)(*pfVar5 - *pfVar6);
            thisPtr[0x19] = (int)(fVar8 - (float)thisPtr[5]);
            thisPtr[0x1a] = (int)(fVar10 - (float)thisPtr[6]);
            thisPtr[0x1b] = (int)(fVar12 - (float)thisPtr[7]);
        }
    } else {
        // Reset damping when stuck
        thisPtr[0x20] = (int)_DAT_00d5780c;
    }

    // Increment state timer and set state flag
    thisPtr[0x1e] = (int)((float)thisPtr[0x1e] + dt);
    *(char*)(thisPtr + 0x1f) = 1;
    fVar8 = *(float*)(targetTransform + 0x34);
    fVar10 = *(float*)(targetTransform + 0x38);
    fVar12 = *(float*)(targetTransform + 0x3c);
    thisPtr[0x18] = (int)(*pfVar5 - *pfVar6);
    thisPtr[0x19] = (int)(fVar8 - (float)thisPtr[5]);
    thisPtr[0x1a] = (int)(fVar10 - (float)thisPtr[6]);
    thisPtr[0x1b] = (int)(fVar12 - (float)thisPtr[7]);
    thisPtr[0x1b] = 0;
    thisPtr[0x21] = 0;
    // Compute speed from current position to target
    fVar8 = *pfVar6 - *pfVar5;
    fVar10 = (float)thisPtr[5] - *(float*)(targetTransform + 0x34);
    fVar12 = (float)thisPtr[6] - *(float*)(targetTransform + 0x38);
    thisPtr[0x22] = (int)SQRT(fVar10 * fVar10 + fVar12 * fVar12 + fVar8 * fVar8);
    fVar8 = *(float*)(targetTransform + 0x34);
    fVar10 = *(float*)(targetTransform + 0x38);
    fVar12 = *(float*)(targetTransform + 0x3c);
    *(float*)(thisPtr + 0xc) = *pfVar5;
    *(float*)(thisPtr + 0xd) = fVar8;
    *(float*)(thisPtr + 0xe) = fVar10;
    *(float*)(thisPtr + 0xf) = fVar12;
    return;
}