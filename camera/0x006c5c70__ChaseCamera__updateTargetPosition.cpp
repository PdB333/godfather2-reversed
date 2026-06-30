// FUNC_NAME: ChaseCamera::updateTargetPosition
// Function at 0x006c5c70 updates the camera target position based on input parameters and interpolation.
// The class is likely ChaseCamera (from Godfather 2 EARS engine), which tracks a target with rotational offset.

void __fastcall ChaseCamera::updateTargetPosition(float *this)
{
    // Local variables from decompiled code
    float deltaTime = getGameDeltaTime();         // FUN_00471610 -> likely returns frame delta
    // Note: param_1 (this) offsets used:
    // +0x2a0: targetRotationOrOffset
    // +0x29c: someAngleOrFactor
    // +0x2a4: anotherAngle
    // +0x294: rotationSpeed
    // +0x284: angleAccumulator
    // +0x2b0: scaleFactor
    // +0x298: currentState or parameter to FUN_006c91c0
    // +0x10c: currentValue
    // +0x108: maxValue
    // +0x80: interpolationFactor (0-1)
    // +0x2ec: baseOffset
    // +0x238,0x23c,0x240: computed target position (x,y,z)
    // +0x220,0x224,0x228: previous position (x,y,z)
    // +0x22c,0x230,0x234: target orientation (yaw, pitch, roll?) (0x22c,0x230,0x234)
    // +0x214,0x208,0x21c,0x210: final output (position and orientation)

    float angle1 = this[0xA8];  // +0x2a0
    float angle2 = this[0xA7];  // +0x29c
    float angle3 = this[0xA9];  // +0x2a4

    // FUN_0056c180 likely converts or adjusts angles.
    FUN_0056c180(deltaTime, &angle1, &angle2, &angle3);

    float rotSpeed = this[0xA5]; // +0x294
    float rotDelta = rotSpeed * DAT_00e445c8; // global delta factor (probably frame dt)
    float newAngle1 = rotDelta + angle1;
    this[0xA8] = newAngle1; // +0x2a0

    double dVar7 = (double)newAngle1;
    FUN_00b99fcb(); // potentially a no-op or float conversion
    double dVar8 = (double)newAngle1;
    FUN_00b99e20(); // another no-op or conversion

    float constant1 = DAT_00e44564; // likely 1.0f
    float diff1 = constant1 - (float)dVar7;
    float diff2 = constant1 - (float)dVar8;

    float angleAccum = this[0xA1]; // +0x284
    float someAngle = FUN_006c3c90(); // returns angle (e.g., from sin wave or time)
    float blendFactor = (someAngle + angleAccum) * DAT_00e445c8;
    double dBlend = (double)blendFactor;

    FUN_00b99e20(); // maybe f2d conversion
    float sinBlend = fsin((float)blendFactor);

    float offset1 = (float)dBlend * diff1;
    float offset2 = sinBlend; // note: later used for yaw, but reassigned

    float resultScale = FUN_006c3910(0, 0, 0); // likely returns some scale (maybe height offset)
    this[0xAC] = resultScale; // +0x2b0

    // FUN_006c91c0 might be a lerp/easing function
    float easeFactor = FUN_006c91c0(
        this[0xA6], // +0x298 (some state)
        0,
        1.0f, 1.0f,
        this[0x43] / this[0x42] // +0x10c / +0x108 (ratio)
    );

    float interpolated = (easeFactor - DAT_00d5780c) * this[0x20] + DAT_00d5780c; // +0x80 is interpolation alpha
    float finalScale = interpolated * (this[0xBB] + this[0xAC]); // +0x2ec and +0x2b0 (baseOffset + resultScale)

    // Compute target position (x,y,z) from previous position and offsets
    float posX = finalScale * offset1 + this[0x88]; // +0x220
    float posY = finalScale * sinBlend + this[0x89]; // +0x224 (sinBlend already used? careful)
    float posZ = finalScale * (float)dBlend * diff2 + this[0x8A]; // +0x228

    this[0x8E] = posX; // +0x238
    this[0x8F] = posY; // +0x23c
    this[0x90] = posZ; // +0x240

    // Set orientation (yaw, pitch, roll) – note: the code reassigns sinBlend and offset1
    double dYaw = (double)sinBlend;
    FUN_00b9a9fa(); // conversion
    float yaw = (float)dYaw;
    this[0x8B] = yaw; // +0x22c

    double dPitch = (double)(constant1 - offset1); // note: offset1 was computed as (float)dBlend*diff1
    FUN_00b9a9fa();
    float pitch = (float)dPitch;
    this[0x8C] = pitch; // +0x230

    this[0x8D] = 0.0f; // +0x234 (roll = 0)

    // Copy computed position to final output
    // The code copies 8 bytes (position XY) from 0x238 to 0x214, then 8 bytes (orientation XY) from 0x22c to 0x208,
    // then Z from 0x240 to 0x21c, and roll from 0x234 to 0x210.
    // This suggests final struct:
    // +0x208: orientation (vec3) - but stored as 8-byte copy of yaw+pitch? Actually 0x208 to 0x210: 8 bytes (yaw,pitch)
    // +0x210: roll (4 bytes)
    // +0x214: position (vec3) - first two floats from 0x238, third from 0x240
    // So final layout: orientation(yaw,pitch), then roll, then position(x,y,z).

    *(double *)&this[0x82] = *(double *)&this[0x8E]; // copy position XY (0x214 = 0x238)
    *(double *)&this[0x82 - 4] = *(double *)&this[0x8B]; // copy orientation XY (0x208 = 0x22c)
    this[0x87] = this[0x90]; // copy Z (0x21c = 0x240)
    this[0x84] = this[0x8D]; // copy roll (0x210 = 0x234)
}