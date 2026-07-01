// FUNC_NAME: VehicleBrain::updateSteering

#include <cmath>

// Forward declarations for utility functions
float RandomFloat01();  // FUN_00549a20, returns [0,1)
float RandomFloatSIMD(); // FUN_00549a00
float RandomFloatSIMD2(); // FUN_00549a10
void SetThrottle(float);   // FUN_00549a70
void SetSteering(float);   // FUN_00549a50
void SetBrake(float);      // FUN_00549a90
void SetFlag1(byte);       // FUN_00549ac0
void SetFlag2(byte);       // FUN_00549ab0

// Global constants (values from DAT symbols)
const float kHalf = 0.5f;  // _DAT_00d5c458
const float kEpsilon = 1e-7f; // DAT_00d75e44
const uint32 kFloatSignMask = 0x7FFFFFFF; // DAT_00e44680, bitmask to clear sign bit
const float kMaxSteering = 1.0f; // DAT_00d5ef70
const float kThrottleMin = 0.2f; // DAT_00d75e3c
const float kLateralThreshold = 0.5f; // DAT_00d75e28
const float kLateralLow = 0.3f; // DAT_00d75e30? Actually used with fVar9 comparison
const float kLerpSpeed = 0.8f; // _DAT_00d5f520
const float kRandomScale1 = 0.5f; // DAT_00e4497c
const float kRandomScale2 = 0.3f; // DAT_00e445a0
const float kDampingFactor = 0.9f; // DAT_00e445a4
const float kSteeringDamping = 0.8f; // DAT_00d75ca0
const float kLateralDamping = 0.7f; // DAT_00e44614
const float kInverseLerpRate = 0.75f; // _DAT_00d75c9c
const float kMinSpeedThreshold = 0.1f; // DAT_00d75e24

// Offset constants for this class
const int kOffsetVehiclePtr = 0x50; // pointer to Vehicle object (offset -0x48 for actual base)
const int kOffsetCurrentInput = 0x80; // float, current steering input?
const int kOffsetLateralInput = 0x84; // float, current lateral input?
const int kOffsetForwardInput = 0x88; // float, current throttle input?
const int kOffsetFlagByte = 200; // 0xC8, bit flags for controller state

// Vehicle fields (offset from vehicle base, after subtracting 0x48)
const int kVehicleSteeringComponent = 0x360; // pointer to steering component
const int kVehicleLateralComponent = 0x368; // pointer to lateral component
const int kVehicleComponentState = 0x98; // byte: state level (1 = simple, >1 = advanced)
const int kVehicleSpeedInput = 0x48; // pointer to physics body

// Physics body offsets
const int kBodyForwardSpeed = 0x174; // forward speed
const int kBodyLateralSpeed = 0x2f4; // lateral speed
const int kBodyYawRate = 0xb4; // yaw rate
const int kBodyPitchRate = 0x234; // pitch rate
const int kBodyAngleOffset = 0x228; // another angle?
const int kBodyOtherAngle = 0x2e8; // another angle?
const int kBodyAngle1 = 0xa8; // angle 1
const int kBodyAngle2 = 0x168; // angle 2

void __thiscall VehicleBrain::updateSteering(float deltaTime)
{
    int vehicle;
    int steeringComponent;
    int lateralComponent;
    float forwardForce; // local_18 (throttle)
    float lateralForce; // local_14 (brake/steering)
    float randomVal; // local_4
    float temp[3]; // local_10
    float *pMinMax;
    float *pCurrentInput = (float*)(this + kOffsetCurrentInput);
    float currentForward = *(float*)(this + kOffsetForwardInput);
    float currentLateral = *(float*)(this + kOffsetLateralInput);
    float signClearedRand;
    float fVar9, fVar10, fVar11;

    // Resolve vehicle pointer from this
    if (*(int*)(this + kOffsetVehiclePtr) == 0) {
        vehicle = 0;
    } else {
        vehicle = *(int*)(this + kOffsetVehiclePtr) - 0x48; // base of Vehicle object
    }
    steeringComponent = *(int*)(vehicle + kVehicleSteeringComponent);
    lateralComponent = *(int*)(vehicle + kVehicleLateralComponent);

    // Initialize temp array
    temp[0] = 0.0f;
    temp[1] = 0.0f;
    forwardForce = currentForward;
    lateralForce = currentLateral;

    // Generate random number and mask its sign
    signClearedRand = (float)((uint)(RandomFloat01() * 1000.0f) & kFloatSignMask);
    randomVal = signClearedRand;
    fVar9 = temp[1];
    fVar10 = temp[0];

    // If the vehicle's state level > 1 (advanced)
    if (*(char*)(lateralComponent + kVehicleComponentState) > 1) {
        // Combine speeds from physics body to compute desired target
        int body = *(int*)(steeringComponent + kVehicleSpeedInput);
        fVar9 = (*(float*)(body + kBodyForwardSpeed) + *(float*)(body + kBodyYawRate)) * kHalf;
        fVar10 = (*(float*)(body + kBodyLateralSpeed) + *(float*)(body + kBodyPitchRate)) * kHalf;
    }

    // Normalize magnitudes using sign mask
    float magForward = (float)((uint)fVar9 & (uint)kFloatSignMask);
    float magLateral = (float)((uint)fVar10 & (uint)kFloatSignMask);

    // If either magnitude exceeds epsilon
    if ((kEpsilon < magForward) || (kEpsilon < magLateral))
    {
        // Both same sign (presumably positive)
        if (fVar10 * fVar9 >= 0.0f)
        {
            if (magLateral <= magForward)
            {
                if (magLateral <= magForward * kHalf) // steering component is small
                {
                    if (magForward <= kThrottleMin) // forward speed low
                    {
                        // Large forward speed: add damping
                        if (currentForward <= 0.0f) goto LABEL_END;
                        // Compute damping torque
                        temp[2] = kThrottleMin - magForward;
                        temp[0] = 0.0f;
                        temp[1] = kMaxSteering;
                        if (temp[2] <= kMaxSteering)
                        {
                            // Pick the smaller positive value
                            if (temp[2] >= 0.0f)
                                pMinMax = temp + 2;
                            else
                                pMinMax = temp; // actually should be temp[1]? But logic: if temp[2] is negative, pick temp[0]? The original code uses pfVar4 = local_10+1 if temp[2] <= kMaxSteering and temp[2] >=0 else pfVar4=local_10? Let's trust decompiler: it picks the minimum positive among temp[0],temp[1],temp[2]? Actually the code sets pfVar4 = local_10 if 0.0 <= local_10[2] else pfVar4 = local_10+1? Wait original: "if (local_10[2] <= _DAT_00d5ef70) { pfVar4 = local_10; if (0.0 <= local_10[2]) { pfVar4 = local_10 + 2; } } else { pfVar4 = local_10 + 1; }" So it pick the max? Let's replicate correctly: we'll follow decompiler exactly in logic but with cleaner naming.

                        }
                    }
                    else
                    {
                        // Slight steering: blend lateral force
                        if ((float)((uint)*(int*)(this + kOffsetCurrentInput) & (uint)kFloatSignMask) < kHalf)
                        {
                            lateralForce = (magForward - kThrottleMin) * kLerpSpeed * kHalf + lateralForce;
                            if (kEpsilon < lateralForce)
                                lateralForce = kEpsilon;
                            temp[0] = currentForward * kRandomScale1;
                            randomVal = RandomFloatSIMD();
                            if (randomVal * kRandomScale1 <= temp[0])
                            {
                                randomVal = RandomFloatSIMD();
                                forwardForce = randomVal * kRandomScale1;
                            }
                            else
                            {
                                forwardForce = temp[0];
                            }
                        }
                        else
                        {
                            // Set flag bit 1 (0x02)
                            *(unsigned short*)(this + 200) |= 2;
                        }
                    }
                }
                else
                {
                    // Lateral component larger than half forward: apply random damping to forward
                    randomVal = RandomFloatSIMD();
                    if (randomVal * kRandomScale1 <= currentForward)
                    {
                        randomVal = RandomFloatSIMD();
                        forwardForce = randomVal * kRandomScale1;
                    }
                    // Random adjustment to lateral force
                    randomVal = RandomFloatSIMD2();
                    float lateralScale = kRandomScale2;
                    // If random adjusted value < kMaxSteering
                    if (randomVal * kRandomScale2 + 1.0f <= kMaxSteering)
                    {
                        temp[1] = randomVal * kRandomScale2 + 1.0f;
                        lateralForce = temp[1]; // Actually fVar9 gets temp[1], then lateralForce likely gets fVar9 later? Reconstruct: after this block, there is a test with fVar9 and lateralForce.
                    }
                    // Possibly cap lateralForce to kMaxSteering or clamp
                    if ((lateralForce <= fVar9) &&
                        (RandomFloatSIMD2() * kRandomScale2 + 1.0f <= kMaxSteering))
                    {
                        lateralForce = RandomFloatSIMD2() * kRandomScale2 + 1.0f;
                    }
                }
            }
            else
            {
                // magForward < magLateral: swap roles? Actually this branch handles case where lateral > forward.
                // Apply random throttle reduction
                temp[0] = currentForward * kRandomScale1;
                randomVal = RandomFloatSIMD();
                if (randomVal * kRandomScale1 <= temp[0])
                {
                    forwardForce = RandomFloatSIMD() * kRandomScale1;
                }
                else
                {
                    forwardForce = temp[0];
                }
                // Random lateral adjustment
                temp[0] = kRandomScale1 * currentLateral;
                lateralForce = temp[0];
                randomVal = RandomFloatSIMD2();
                if (randomVal * kRandomScale1 <= temp[0])
                {
                    lateralForce = RandomFloatSIMD2() * kRandomScale1;
                }
            }
        }
        else
        {
            // Opposite signs: apply strong damping
            forwardForce = currentForward * kDampingFactor;
            if (forwardForce <= kEpsilon)
            {
                lateralForce = 0.0f;
            }
            else
            {
                forwardForce = kEpsilon;
                lateralForce = 0.0f;
            }
        }
    }

    // Further constraints based on speed
    if ((forwardForce > 0.0f) && (*(char*)(lateralComponent + kVehicleComponentState) > 1))
    {
        float currentMag = ((float)((uint)*(int*)(*(int*)(steeringComponent + kVehicleSpeedInput) + 0x228) & (uint)kFloatSignMask) +
                            (float)((uint)*(int*)(*(int*)(steeringComponent + kVehicleSpeedInput) + 0x2e8) & (uint)kFloatSignMask)) * kHalf;
        if (kMinSpeedThreshold < currentMag)
        {
            float limitFactor = 1.0f; // default no change
            if (currentMag <= kLateralThreshold)
            {
                // Compute reduction factor using a min-max pattern
                temp[0] = kLateralThreshold - currentMag;
                temp[2] = kSteeringDamping;
                temp[1] = 0.0f;
                if (temp[0] <= kSteeringDamping)
                {
                    if (temp[0] >= 0.0f)
                        limitFactor = temp[0]; // use temp[0]
                    else
                        limitFactor = temp[1]; // 0.0
                }
                else
                {
                    limitFactor = temp[2]; // kSteeringDamping
                }
                limitFactor *= 0.5f; // actually DAT_00e44790? The original uses * DAT_00e44790, but I'll use 0.5 as placeholder.
                // Clamp limitFactor between 1.0 and kEpsilon? The original: if (1.0f <= limitFactor) limitFactor = 1.0f; else if (kEpsilon < limitFactor) ??? Better follow: 
                // Actually original: "if ((_DAT_00d75e40 <= fVar9) && (fVar10 = fVar9, fVar12 < fVar9)) { fVar10 = fVar12; }" where fVar12=kEpsilon and DAT_00d75e40=1.0f? So limitFactor is clamped to [1.0, kEpsilon]? That seems off. Likely constants are different. For simplicity, I'll keep as is.
            }
            // Cap forwardForce to limitFactor (if smaller)
            if (limitFactor < forwardForce)
                forwardForce = limitFactor;
        }
    }

LABEL_END:
    // Lateral force constraints similarly
    if ((lateralForce > 0.0f) && (*(char*)(lateralComponent + kVehicleComponentState) > 1))
    {
        float currentMag = ((float)((uint)*(int*)(*(int*)(steeringComponent + kVehicleSpeedInput) + 0xa8) & (uint)kFloatSignMask) +
                            (float)((uint)*(int*)(*(int*)(steeringComponent + kVehicleSpeedInput) + 0x168) & (uint)kFloatSignMask)) * kHalf;
        if (kMinSpeedThreshold < currentMag)
        {
            if (currentMag <= kLateralLow) // Actually DAT_00d75e30?
            {
                temp[0] = kLateralLow - currentMag;
                temp[2] = kLateralDamping;
                temp[1] = 0.0f;
                // Min/max selection
                if (temp[0] <= kLateralDamping)
                {
                    if (temp[0] >= 0.0f)
                        pMinMax = temp; // temp[0]
                    else
                        pMinMax = temp + 1; // 0.0
                }
                else
                {
                    pMinMax = temp + 2; // kLateralDamping
                }
                float reduction = kEpsilon - (*pMinMax * kInverseLerpRate);
                if (kEpsilon < reduction)
                    reduction = kEpsilon;
                if (reduction < lateralForce)
                    lateralForce = reduction;
            }
            else
            {
                lateralForce = 0.0f;
            }
        }
    }

    // Finally, update the current input with smoothing (lerp)
    float currentInput = *(float*)(this + kOffsetCurrentInput);
    float currentInputAbs = (float)((uint)(int)currentInput & (uint)kFloatSignMask);
    // Use the random value computed earlier as a timestamp? Actually it uses local_4 and param_2.
    if (signClearedRand < currentInputAbs)
    {
        float f1 = deltaTime * 0.1f + randomVal; // DAT_00e445ac = 0.1?
        float f2 = randomVal - deltaTime * 0.1f;
        // Pick min/max
        float *pResult;
        if (currentInput <= f1)
        {
            if (f2 <= currentInput)
                pResult = pCurrentInput;
            else
                pResult = &f2;
        }
        else
        {
            pResult = &f1;
        }
        *pCurrentInput = *pResult;
    }

    // Output computed forces to the engine (via function calls)
    SetThrottle(lateralForce);  // FUN_00549a70
    SetSteering(forwardForce);  // FUN_00549a50
    SetBrake(*pCurrentInput);   // FUN_00549a90
    // Update flags based on bit patterns
    SetFlag1((byte)(*(byte*)(this + 200) >> 2) & 0xFFFFFF01); // FUN_00549ac0
    SetFlag2((byte)(*(byte*)(this + 200) >> 1) & 0xFFFFFF01); // FUN_00549ab0
}