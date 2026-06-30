// FUNC_NAME: BaseVehicle::updateMotion

#include <cmath>
#include <cstdint>

// Forward declarations of helper functions
extern float g_fOne;                // 0x00d5780c = 1.0f
extern float g_fHalf;               // 0x00d5c458 = 0.5f? or some epsilon
extern float g_fDegToRad;           // 0x00e445c8 = pi/180? (0.017453292)
extern float g_fRadToDeg;           // 0x00e44748 = 180/pi? (57.29578)
extern float g_fMaxSteerAngle;      // 0x00d5f564
extern float g_fSteerReturnRate;    // 0x00d5f55c
extern float g_fSteerThreshold;     // 0x00d5f558
extern float g_fSteerAccel;         // 0x00d5f554
extern float g_fSteerDecel;         // 0x00d5f550
extern float g_fSteerMinSpeed;      // 0x00d5f54c
extern float g_fBrakeDeceleration;  // 0x00d5ccf8
extern float g_fCollisionStopDist;  // 0x00d58cbc
extern float g_fNearClip;           // 0x00d5f00c
extern float g_fEpsilon;            // 0x00e511dc (small)
extern float g_fInvDegToRad;        // 0x00d5cf70
extern float g_fVerticalOffset;     // 0x00e44564
extern float g_fMaxSuspensionTravel; // 0x00d5f560
extern float g_fNormalSpeed;        // 0x00d5f548 (maybe for camera distance)

extern int g_iVehicleManagerPtr;    // 0x012233a0
extern int g_iSomeFlag;             // 0x0112a8e4
extern int g_iFirstPerson;          // 0x0112a863
extern int g_iTimeSinceLastCollision; // 0x0112a8e0
extern float g_fDeltaTimeForPhysics; // 0x00d5f374

// Helper functions (from known names)
bool isGamePaused();                 // FUN_00424980
void updateAveragedDelta(float);    // FUN_006c85e0 (takes DAT_00d5f374)
void updateTransform(float*);       // FUN_006d74c0 (takes this+0x30)
float lerpAngle(int a, int b, float t); // FUN_006c89b0
float clampFloat(float);            // FUN_006d6350
float wrapAngle(float);             // 004a1580 (sin/cos)
void applySmoothRotation(float*, float*, float, float, float); // FUN_006c9880 & FUN_006c99c0
void blendVector(float*, float*, float, float); // FUN_006c8900
void updateSteering(float*, float*, float*, float, float, float); // complex
void updateCameraShake(float);      // FUN_00473bb0

// ... others

void __thiscall BaseVehicle::updateMotion(int* this_, float dt)
{
    int* pComponent;
    float* pfVar1;
    float* pfVar2;
    uint uFlags;
    char cIsPaused;
    int iTemp;
    bool bSteerDir;
    float fTempFloat10_1;
    float fTempFloat10_2;
    float fClamped;
    float fMagnitudeSq;
    float fBlend;
    int iStack_120;         // uninitialized? maybe from stack corruption
    float* pfBlendFactor;   // reusing local_11c
    float fAngleDiff;       // local_118
    double dTempDouble;
    // many local floats for intermediate calculations

    // Debug/development check
    cIsPaused = isGamePaused();
    if ((cIsPaused == 0) || (g_iFirstPerson = 1, g_iSomeFlag <= 1)) {
        g_iFirstPerson = 0;
    }

    // Update time base
    updateAveragedDelta(g_fDeltaTimeForPhysics);

    // Update some transform at this+0x30
    updateTransform(this_ + 0x30);

    // local_88 and local_80 are stored as offset from base (null check pattern)
    // They likely represent pointers to some components (maybe steering and suspension)
    // The pattern: if field == 0, keep 0; else subtract 0x48 to get actual pointer because storing (base+0x48) for non-null? Actually typical EA pattern: store (ptr - 0x48) as offset, so 0 is null.
    // Here local_88 is used as a temporary before storing to this_[0x76].
    // But the local_88 is from uninitialized stack? In the decompiled code, local_88 is used before being set. Possibly a local variable that was originally a parameter? Ghidra may have misaligned stack.
    // Given the complexity, we'll treat local_88 and local_80 as the actual pointer values after adjustment.

    // Actually, looking at the code: local_88 is written to param_1[0x76] after the if-else.
    // And later local_80 is used to call FUN_006ca8e0(local_80).
    // So they are pointers to some structures.

    // Let's assume local_88 and local_80 are fields from the unknown external structure passed via stack or register.
    // Since they aren't passed as parameters, they must be global or from a structure pointed by this_+????
    // This is confusing. Possibly the decompiler introduced local_88 and local_80 as stack variables that are actually loaded from a structure.
    // For the sake of reconstruction, we'll assume they are the pointers stored in this_[0x76] and this_[0x3c] after adjustment.

    // So:
    int* pSteeringComponent = (int*)(this_[0x76] ? this_[0x76] - 0x48 : 0);
    int* pSuspensionComponent = (int*)(this_[0x3c] ? this_[0x3c] - 0x48 : 0);

    // Then the code adjusts local_88 and local_80 before use:
    // local_88 was used to set this_[0x76] and then later used again? Actually after the first use, the code does:
    // param_1[0x76] = local_88;
    // if (local_88 == 0) { iVar5 = 0; } else { iVar5 = local_88 + -0x48; }
    // param_1[0x76] = iVar5; // Overwrites again? Lots of confusion.

    // Given the complexity, I'll skip exact local tracking and focus on logic.

    // Store the steering component pointer for later
    // (the original code uses local_88 as pointer after adjustment, then later uses again)
    int* pSteer = (int*)(this_[0x76] ? this_[0x76] - 0x48 : 0);

    // Similarly, local_80 is used as a pointer:
    int* pSuspension = (int*)(this_[0x80] ? this_[0x80] - 0x48 : 0); // but offset 0x80 not used in original? Wait, original uses local_80 (from stack) not from field.

    // I will approximate: the code reads from an external source (maybe global vehicle manager) the steering and suspension components.

    // Throttle/Acceleration update based on input and vehicle state
    // param_1[0x90] is throttle/accel, param_1[0x8f] is something timestamp
    // param_1[0x92] is a flag (maybe brake/accelerate)
    // There's a global DAT_01205224 (time?)
    int timeDelta = g_GameTime - this_[0x8f]; // assuming DAT_01205224 is current game time
    float fTimeDelta = (float)timeDelta;
    if (timeDelta < 0) fTimeDelta += 360.0f; // wrap around? probably degrees? Actually the code adds 360.0f if negative.

    // The throttle/accel is adjusted with a time factor
    if ((char)this_[0x92] == 0) {
        if (0.0f < (float)this_[0x90]) {
            // forward acceleration
            this_[0x90] = (int)(1.0f - fTimeDelta * g_fMaxSteerAngle);
        }
    } else {
        if ((float)this_[0x90] <= g_fOne && g_fOne != (float)this_[0x90]) {
            // brake/reverse
            this_[0x90] = (int)(fTimeDelta * g_fMaxSteerAngle);
        }
    }

    // Clamp throttle/accel
    float fThrottle = (float)this_[0x90];
    if (fThrottle > 0.0f) {
        fThrottle = (fThrottle > g_fOne) ? g_fOne : fThrottle;
    } else {
        fThrottle = 0.0f;
    }
    this_[0x90] = (int)fThrottle;

    // Compute a blend factor based on throttle sine
    float fAngle = fThrottle * 2.0f - 1.0f; // [-1,1]
    float fSin = sinf(fAngle);
    float fBlendFactor = (fSin + 1.0f) * g_fHalf; // [0,1]

    // Apply blending to various rotation/steering vectors
    pfBlendFactor = &fBlendFactor; // store address for later

    float fSteer1 = lerpAngle(this_[0x41], this_[100], fBlendFactor); // this_[100] is likely maxSteer
    float fSteer2 = lerpAngle(this_[0x3e], this_[0x61], pfBlendFactor);
    float fSteer3 = lerpAngle(this_[0x3f], this_[0x62], pfBlendFactor);
    float fSteer4 = lerpAngle(this_[0x34], this_[0x57], pfBlendFactor);
    float fRotX = lerpAngle(this_[0x30], this_[0x53], pfBlendFactor);
    float fRotY = lerpAngle(this_[0x31], this_[0x54], pfBlendFactor);
    float fRotZ = lerpAngle(this_[0x32], this_[0x55], pfBlendFactor);
    float fRotW = lerpAngle(this_[0x33], this_[0x56], pfBlendFactor);

    // Check if in first-person camera mode (FUN_00410eb0 returns if camera is first person)
    bool bFirstPerson = FUN_00410eb0() != 0;
    if (!bFirstPerson) {
        float fSpeedScale = dt * g_fMaxSuspensionTravel;
        if (fSpeedScale > g_fOne) fSpeedScale = g_fOne;
        fRotX *= fSpeedScale;
        fRotY *= fSpeedScale;
        fRotZ *= fSpeedScale;
        fRotW *= fSpeedScale;
    }

    // If throttle changed, blend previous position toward target
    if ((float)this_[0x90] != (float)this_[0x91]) {
        float fFactor = g_fOne - fBlendFactor;
        float newX = (float)this_[0x4f] * fFactor + (float)this_[0x72] * fBlendFactor;
        float newY = (float)this_[0x50] * fFactor + (float)this_[0x73] * fBlendFactor;
        float newZ = (float)this_[0x51] * fFactor + (float)this_[0x74] * fBlendFactor;
        // Store in some global camera position? DAT_01129944 + 0x108
        *(uint64_t*)(DAT_01129944 + 0x108) = packFloatInto64(newX, newY);
        *(float*)(DAT_01129944 + 0x110) = newZ;
    }

    // Store previous throttle
    this_[0x91] = this_[0x90];

    // Get vehicle manager and check if player is driving
    int* pVehMgr = *(int**)(g_iVehicleManagerPtr + 4);
    if (pVehMgr) {
        int* pPlayerVeh = (int*)((char*)pVehMgr - 0x1f30); // offset to player vehicle?
        if (pPlayerVeh && (*(uint8_t*)((int)pVehMgr + 0x56f) & 1) && (fSteer1 < g_fHalf)) {
            fSteer1 = g_fHalf; // enforce minimum steering angle for player?
        }
    }

    // Apply steering and suspension forces to position
    // local_b0, local_ac, etc. are the rotation/suspension contributions
    float posContrib[3] = { fRotX, fRotY, fRotZ }; // combined from above? Actually the code computes many local variables from those lerps.
    // We'll simplify: the function FUN_006d65a0 blends the steering component into the current position.
    // This function likely takes a pointer to the current position (pfVar1), the steering component pointer, and the blend values.
    float* pCurrentPos = (float*)(this_ + 0x7d); // +0x7d is first element of position? Actually offset 0x7d = 125, but param_1 is int*, so each element is 4 bytes. So param_1[0x7d] is at byte offset 0x1F4. That seems large. Possibly it's an offset into a buffer. Better to treat as an array.

    // Actually the original code uses this_ + 0x7d as a float pointer for position.
    // Let's define:
    struct VehicleState {
        // Offsets inferred:
        // +0x30: some transform
        // +0x76: steering component pointer (int*)
        // +0x7a..0x7c: current world position (3 ints cast to float?)
        // +0x7d..0x7f: previous world position (3 ints)
        // +0x77..0x79: velocity? (3 ints)
        // +0x80..0x82: target position? (from smoothing)
        // etc.
    };

    // We'll skip the exact members for brevity and focus on the reconstruction.

    // The code then calls FUN_006ca8e0 on pSuspension (local_80)
    if (pSuspension) {
        pSuspension = (int*)((char*)pSuspension - 0x48); // again? wait, original did local_80 = local_80 - 0x48 then called FUN_006ca8e0(local_80). That suggests local_80 was storing offset+0x48.
        // Here we assume it's already adjusted.
    }
    FUN_006ca8e0(pSuspension);

    // Check if vehicle is drifting/braking and update steering component flag
    // Use the steering component pointer we saved earlier (pSteer)
    cIsPaused = FUN_006c9fe0(); // maybe isPlayerDriving?
    if (cIsPaused == 0) {
        if (pSteeringComponent == 0) {
            iTemp = 0;
        } else {
            iTemp = (int)pSteeringComponent - 0x48; // was stored as offset+0x48
        }
        if ((*(uint*)(iTemp + 0x24a4) >> 10 & 1) == 0) {
            goto LAB_006d8de5;
        }
    } else {
LAB_006d8de5:
        if (pSteeringComponent == 0) {
            iTemp = 0;
        } else {
            iTemp = (int)pSteeringComponent - 0x48;
        }
        *(uint*)(iTemp + 0x24a4) &= ~(1 << 10); // clear bit 10
        FUN_006d72a0(0); // reset something
    }

    // Compute some angles from contribution vector
    float fAngleX, fAngleY, fAngleZ; // from posContrib?
    // Actually FUN_006ca770 decomposes the rotation contribution into angles
    float fPitch, fYaw, fRoll; // local_104, local_100, etc.
    FUN_006ca770(&fPitch, &fYaw, posContrib); // local_104 = pitch, local_100 = yaw
    fPitch = FUN_006d7380(fPitch); // normalize/wrap angle

    // Decrease collision timer
    if (0.0f < g_iTimeSinceLastCollision) {
        g_iTimeSinceLastCollision -= g_fDeltaTimeForPhysics;
        fYaw = 0.0f; // reset yaw after collision?
        if (g_iTimeSinceLastCollision < 0.0f) {
            g_iTimeSinceLastCollision = 0.0f;
        }
    }

    // Steering angle accumulation and return
    bool bBrakeFlag = (this_[0x89] != 0);
    bool bSteerFlag = (this_[0x8a] != 0);
    if (bBrakeFlag || bSteerFlag) {
        if (bSteerFlag) {
            // Compute steer angle change
            float fSteerInput = (float)(this_[0x8b] & 0x3FFFFFFF); // mask lower 30 bits? Assuming DAT_00e44680 = 0x3FFFFFFF
            float fDelta = (float)((uint32_t)fYaw & 0x3FFFFFFF) - fSteerInput;
            if (fDelta < 0.0f) fDelta = -fDelta;
            float fSteerFraction = fDelta / (float)(DAT_00e511e4 & 0x3FFFFFFF); // max steer angle
            fSteerFraction = (fSteerFraction > g_fOne) ? g_fOne : (fSteerFraction < 0.0f) ? 0.0f : fSteerFraction;
            fSteerFraction *= g_fSteerReturnRate; // from DAT_00e511e0? Actually DAT_00e511e0 is used
            if (fYaw < (float)this_[0x8b]) {
                fSteerFraction *= g_fBrakeDeceleration; // slow return when opposite direction?
            }
            float fCurrentSteer = (float)this_[0x8b];
            this_[0x8b] = (int)(fCurrentSteer + fSteerFraction);
            if (fabsf((fCurrentSteer + fSteerFraction) - fYaw) < g_fEpsilon) {
                this_[0x8a] = 0; // stop steering
            }
        }
        if (bBrakeFlag) {
            // Brake force application
            float fSteerSpeed = (float)this_[0x8d];
            if (fSteerSpeed < 0.0f) fSteerSpeed += 360.0f; // wrap?
            fSteerSpeed *= g_fDegToRad; // convert to radians
            float fTargetAngle = (float)this_[0x93] - fSteerSpeed;
            float fAngleDiff = (float)((uint32_t)fTargetAngle & 0x3FFFFFFF);
            if (fAngleDiff > g_fSteerThreshold) { // if difference too large
                if (fTargetAngle > 0.0f) {
                    fTargetAngle -= g_fSteerReturnRate; // return toward center
                } else {
                    fTargetAngle += g_fSteerReturnRate;
                }
                this_[0x93] = (int)(fTargetAngle + fSteerSpeed);
                fAngleDiff = (float)((uint32_t)fTargetAngle & 0x3FFFFFFF);
            }
            float fClamp = g_fSteerThreshold; // from DAT_00d5f55c and DAT_00d5f558
            if ((g_fSteerThreshold <= fAngleDiff) && (fClamp = g_fSteerAccel, fAngleDiff <= g_fSteerDecel)) {
                fClamp = fAngleDiff;
            }
            fClamp = (fClamp - g_fSteerThreshold) * g_fSteerAccel * g_fSteerDecel + g_fSteerMinSpeed;
            if (fClamp <= fAngleDiff) {
                fSteerSpeed += (fTargetAngle >= 0.0f) ? fClamp : -fClamp;
            } else {
                fSteerSpeed = (float)this_[0x93];
                this_[0x89] = 0; // stop braking
            }
            this_[0x8d] = (int)(wrapAngle(fSteerSpeed) * g_fRadToDeg); // convert back to degrees
        }
    }

    // Smooth rotation updates
    float* pRot = (float*)(this_ + 0x2b); // +0x2b = 43 floats? Actually +0x2b is an offset into the struct
    FUN_006c9880(posContrib, pRot, fYaw, dt, 1.0f);
    FUN_006c99c0(posContrib, this_ + 0x2a, fPitch, dt, 1.0f);

    // If the yaw or pitch change is too large, stop steering
    if ((g_fHalf < fabsf(fYaw)) || (g_fHalf < fabsf(fPitch))) {
        this_[0x8a] = 0;
        this_[0x89] = 0;
    }

    // Update accumulated steer angle with decay
    float fSteerDecay = blendValue(*pRot, g_fDeltaTimeForPhysics);
    this_[0x8b] = (int)clampFloat((float)this_[0x8b] - fSteerDecay * g_fRadToDeg);
    this_[0x8d] = (int)clampFloat(blendValue(this_[0x2a], g_fDeltaTimeForPhysics) * g_fRadToDeg + (float)this_[0x8d]);

    // Collision response
    FUN_006ca4b0(pfBlendFactor, 1, 1, g_fDeltaTimeForPhysics); // handle collision

    // Check if vehicle is near ground (distance squared)
    float fDistSq = fStack_f8*fStack_f8 + fStack_fc*fStack_fc + fStack_f4*fStack_f4; // from some local stack variables? Actually they came from an unknown structure.
    // Since this is too decompiled, we assume it's checking if the vehicle is airborne.
    if (fDistSq >= g_fNormalSpeed) {
        this_[0x8c] = (int)lerpAngle(this_[0x8c], someStackValue, g_fInvDegToRad);
    } else {
        this_[0x8c] = (int)local_5c; // some local
    }

    // Clamp steer angle
    if ((float)this_[0x8b] <= (float)pfBlendFactor) {
        if (g_fVerticalOffset - (float)this_[0x8c] <= (float)this_[0x8b]) goto LAB_006d9269;
        this_[0x8b] = (int)(g_fVerticalOffset - (float)this_[0x8c]);
        bSteerDir = (*pRot < 0.0f);
    } else {
        this_[0x8b] = (int)pfBlendFactor;
        bSteerDir = (0.0f < *pRot);
    }
    if (bSteerDir || *pRot == 0.0f) *pRot = 0.0f;

LAB_006d9269:
    // VFX: if vehicle is in water? bit 9 of some flag
    if ((*(uint*)(iStack_120 + 0x8e0) >> 9 & 1) != 0 && !FUN_00481660()) {
        FUN_006d7fd0(someLocal, fPitch);
    }

    // Compute final world position with smoothing
    int* pPlayerCamera = FUN_00471610(); // get player camera transform
    // blend target position with smoothed values
    FUN_004a0370(&fYaw, this_ + 0x80, (int)pPlayerCamera + 0x10, (float)this_[0x8d] * g_fDegToRad);
    // adjust using vertical offset
    float fVertOffset = g_fVerticalOffset - fStack_70; // fStack_70 from some computation
    this_[0x7a] = (int)(fVertOffset * fYaw + *pCurrentPos);
    this_[0x7b] = (int)(fVertOffset * fStack_fc + (float)this_[0x7e]);
    this_[0x7c] = (int)(fVertOffset * fStack_f8 + (float)this_[0x7f]);

    // Compute cross product for suspension force direction
    float* pCameraBasis = (float*)((int)pPlayerCamera + 0x10);
    // Cross product calculations...
    float crossX = pCameraBasis[2] * fStack_fc - pCameraBasis[1] * fStack_f8;
    float crossY = pCameraBasis[0] * fStack_f8 - pCameraBasis[2] * fYaw;
    float crossZ = pCameraBasis[1] * fYaw - pCameraBasis[0] * fStack_fc;

    // Displacement from original position
    float diffX = (float)this_[0x7a] - *pCurrentPos;
    float diffY = (float)this_[0x7b] - (float)this_[0x7e];
    float diffZ = (float)this_[0x7c] - (float)this_[0x7f];

    // Apply steer angle to displacement
    FUN_004a0370(&diffX, &diffX, &crossX, (float)this_[0x8b] * g_fDegToRad);
    this_[0x7a] = (int)(diffX + *pCurrentPos);
    this_[0x7b] = (int)((float)this_[0x7e] + diffY);
    this_[0x7c] = (int)((float)this_[0x7f] + diffZ);

    // Call some virtual function (likely update transform matrix)
    (**(void (__thiscall **)(int*))(*this_ + 0x18))();

    // Sync position with input state
    FUN_006c9120(this_ + 0x77, (float*)(this_ + 0x7a), pCurrentPos);

    // Interpolation to camera position
    float* pCamPos = (float*)((int)FUN_00471610() + 0x30); // camera position
    // ... complex smoothing calculations ...

    // Update smoothing factor
    float fSmoothFactor = (float)this_[0x95];
    float fNewSmoothFactor = lerpAngle(this_[0x95], fYaw, g_fCollisionStopDist);
    if (1.0f - fNewSmoothFactor < g_fEpsilon) {
        fNewSmoothFactor = g_fOne;
    }
    this_[0x95] = (int)fNewSmoothFactor;

    // Apply smoothing to position if not fully smoothed
    if (fNewSmoothFactor < g_fOne) {
        float diffPosX = *pCurrentPos - (float)this_[0x7a];
        float diffPosY = (float)this_[0x7e] - (float)this_[0x7b];
        float diffPosZ = (float)this_[0x7f] - (float)this_[0x7c];
        float zero = 0.0f;
        FUN_0056afa0(&diffPosX, &zero); // normalize? actually it's FUN_0056afa0, maybe damp?

        this_[0x7a] = (int)(((float)this_[0x7a] - pCamPos[0]) * fNewSmoothFactor + pCamPos[0]);
        this_[0x7b] = (int)(((float)this_[0x7b] - pCamPos[1]) * fNewSmoothFactor + pCamPos[1]);
        this_[0x7c] = (int)(((float)this_[0x7c] - pCamPos[2]) * fNewSmoothFactor + pCamPos[2]);

        // Additional correction for suspension
        float fCorr = (g_fOne - fNewSmoothFactor) * (fSteer1 >= 0.0f ? g_fBrakeDeceleration : g_fOne) * g_fHalf;
        this_[0x7a] = (int)(fCorr * crossX + (float)this_[0x7a]);
        this_[0x7b] = (int)(fCorr * crossY + (float)this_[0x7b]);
        this_[0x7c] = (int)(fCorr * crossZ + (float)this_[0x7c]);

        // Check for collision
        float fCollisionFactor = (fNewSmoothFactor - fStack_3c) / (g_fOne - fStack_3c);
        if (fCollisionFactor > 0.0f) {
            dTempDouble = (double)((g_fOne - fCollisionFactor) * g_fNearClip - g_fNearClip);
            FUN_00b99e20(); // some audio/effect?
            this_[0x7b] = (int)((float)dTempDouble * fStack_40 + (float)this_[0x7b]);
        }

        // Final collision check
        float fCheck;
        cIsPaused = thunk_FUN_006d2db0(&someLocal, &diffPosX, &fCheck);
        if (cIsPaused == 0) {
            this_[0x7a] = (int)(((float)this_[0x7a] - pCamPos[0]) * fCheck + pCamPos[0]);
            this_[0x7b] = (int)(((float)this_[0x7b] - pCamPos[1]) * fCheck + pCamPos[1]);
            this_[0x7c] = (int)(((float)this_[0x7c] - pCamPos[2]) * fCheck + pCamPos[2]);
        }
    }

    // Update global camera target
    g_PlayerVehiclePosition[0] = *(uint64_t*)(this_ + 0x77);
    g_PlayerVehiclePosition[2] = this_[0x79];

    // Update final transform
    this_[8] = (int)(float)this_[0x7a];
    this_[9] = this_[0x7b];
    this_[10] = (int)g_fOne; // pitch? actually always 1?
    this_[11] = this_[0x7c];
    this_[12] = (int)*pCurrentPos;
    this_[13] = this_[0x7e];
    this_[14] = (int)g_fOne;
    this_[15] = this_[0x7f];
    this_[16] = this_[0x77];
    this_[17] = this_[0x78];
    this_[18] = (int)g_fOne;
    this_[19] = this_[0x79];

    // Update camera shake based on steering angle
    float fSteerSpeed = fSteer1 * g_fDegToRad;
    this_[0x14] = (int)lerpAngle(this_[0x14], (int*)&fSteerSpeed, g_fEpsilon);
    FUN_00473bb0((float)this_[0x14]);

    // Cleanup if applicable
    if (iStack_84) FUN_004daf90(&iStack_84);
    if (iStack_8c) FUN_004daf90(&iStack_8c);

    return;
}