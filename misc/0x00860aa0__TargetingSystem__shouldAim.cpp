// FUNC_NAME: TargetingSystem::shouldAim
// Address: 0x00860aa0
// This function determines whether the entity (this) should aim at the target.
// It computes angular differences, applies noise, and checks various conditions.

#include <cmath>

// Global constants (likely from game config)
extern const float kMinFacingAngle;          // DAT_00d75858
extern const float kTwoPi;                   // DAT_00d5d70c
extern const float kPi;                      // DAT_00d5eeec (approx 3.14159)
extern const float kNegativePi;              // DAT_00e44588 (approx -3.14159)
extern const float kAngleThreshold;          // DAT_00e447a4 (some threshold)
extern const float kSpeedThreshold;          // DAT_00d5f00c
extern const float kSomeFactor;              // DAT_00d75750
extern const float kAnotherFactor;           // DAT_00d75758
extern const float kMinSpeed;                // DAT_00d5efd0
extern const float kGlobalZero;              // DAT_00d577a0 (maybe 0.0)

// Forward declarations of helper functions
float getRandomFloat();                      // FUN_008750c0
void someDoubleConversion();                 // FUN_00b9a9fa (likely no-op or inline)
void* getSomeGlobalObject();                 // FUN_00471610
void transformVector(void* mat, float* vec, void* mat2, float* result); // FUN_004a0cd0
void setFacingAngle(void* obj, float* angle); // FUN_00875220
int checkSomeSystem();                       // FUN_00542d70

// Virtual function indices
const int kGetFacingAngle = 0x1b0; // vtable offset for getFacingAngle

bool __thiscall TargetingSystem::shouldAim(void* this, void* target, float deltaTime, float* inOutAngle)
{
    float targetAngle = (*(float (__thiscall**)(void*))(*(int*)target + kGetFacingAngle))(target);
    float thisAngle = (*(float (__thiscall**)(void*))(*(int*)this + kGetFacingAngle))(this);
    if (thisAngle < kMinFacingAngle) {
        thisAngle = kMinFacingAngle;
    }

    // Generate random noise for angle perturbation
    float noise1 = getRandomFloat();
    float noise2 = getRandomFloat();
    double dNoise1 = (double)noise1;
    someDoubleConversion(); // Possibly a no-op or inline conversion
    double dNoise2 = (double)noise2;
    someDoubleConversion();

    float angleDiff = (float)dNoise1 - (float)dNoise2;
    // Wrap angleDiff to [-PI, PI]
    if (angleDiff <= kPi) {
        if (angleDiff < kNegativePi) {
            angleDiff += kTwoPi;
        }
    } else {
        angleDiff -= kTwoPi;
    }

    // Check if angle difference is within threshold
    if (fabs(angleDiff) <= kAngleThreshold) {
        // Within threshold, check speed conditions
        if (fabs(*inOutAngle) > kSpeedThreshold) {
            // Check if the entity's speed factor is too high
            if (*(float*)((int)this + 1000 * 4) * kSomeFactor <= deltaTime) {
                return false;
            }
            // Compute new angle based on noise and target direction
            float newNoise = getRandomFloat();
            void* obj1 = getSomeGlobalObject();
            void* obj2 = getSomeGlobalObject();
            transformVector((void*)((int)obj2 + 0x30), &newNoise, (void*)((int)obj1 + 0x30), &kGlobalZero);
            *inOutAngle = (float)extraout_ST0; // result from transformVector
            if (fabs(*inOutAngle) > kSpeedThreshold) {
                return false;
            }
        }

        // Compute angle difference between current inOutAngle and target's facing
        void* obj = getSomeGlobalObject();
        float targetFacing = (*(float (__thiscall**)(void*))(*(int*)target + kGetFacingAngle))(target);
        setFacingAngle(this, (float*)((int)obj + 0x30));
        float angleDiff2 = *inOutAngle - targetFacing;
        // Wrap angleDiff2
        if (angleDiff2 <= kPi) {
            if (angleDiff2 < kNegativePi) {
                angleDiff2 += kTwoPi;
            }
        } else {
            angleDiff2 -= kTwoPi;
        }

        if (fabs(angleDiff2) <= kAngleThreshold) {
            // Check if target's facing angle is larger than current
            if (fabs(*inOutAngle) <= fabs(targetFacing)) {
                // Compute interpolation factor
                float thisFacing = (*(float (__thiscall**)(void*))(*(int*)this + kGetFacingAngle))(this);
                (*(void (__thiscall**)(void*))(*(int*)target + kGetFacingAngle))(targetapsed);
                if (targetFacing + thisFacing <= 0.0f) {
                    return true;
                }
                float noise = getRandomFloat();
                float factor = deltaTime / (targetFacing + thisFacing);
                void* obj = getSomeGlobalObject();
                float newAngle[3];
                newAngle[0] = noise * factor + *(float*)((int)obj + 0x30);
                newAngle[1] = *(float*)((int)obj + 0x34); // likely y component
                newAngle[2] = *(float*)((int)obj + 0x38); // likely z component
                setFacingAngle(this, newAngle);
                *inOutAngle = (float)extraout_ST0_02; // result from setFacingAngle
                return true;
            }
        } else {
            // Check additional conditions
            if (*(float*)((int)this + 0x3f1 * 4) > 0.0f || *(float*)((int)this + 0x3f1 * 4) == 0.0f ||
                (*(float*)((int)target + 0x3f1 * 4) < 0.0f &&
                 (thisAngle <= targetAngle || deltaTime <= *(float*)((int)this + 1000 * 4) * kSomeFactor))) {
                if (*(float*)((int)target + 0x3f1 * 4) <= 0.0f && *(float*)((int)target + 0x3f1 * 4) != 0.0f) {
                    return true;
                }
                if (thisAngle <= targetAngle) {
                    return true;
                }
                if (deltaTime <= *(float*)((int)this + 1000 * 4) * kSomeFactor) {
                    return true;
                }
                return false;
            }
            return false;
        }
        return false;
    }

    // Outside angle threshold
    if (targetAngle <= kGlobalZero || targetAngle < thisAngle * kMinSpeed) {
        // Check if this entity has a certain flag and if the target is the same as some system's object
        if (((*(int*)((int)this + 0x322 * 4) >> 0xb) & 1) != 0) {
            int sysResult = checkSomeSystem();
            if (sysResult != 0) {
                void* sysObj = nullptr;
                if (*(int*)(sysResult + 0x70) != 0) {
                    void* temp = (void*)(*(int*)(sysResult + 0x70) - 0x48);
                    if (temp != nullptr && (*(byte*)(sysResult + 0xc9) & 1) != 0) {
                        sysObj = temp;
                    }
                }
                if (sysObj == target) {
                    return false;
                }
            }
        }
    } else {
        if (thisAngle <= targetAngle) {
            return false;
        }
        if (*(float*)((int)this + 1000 * 4) * kAnotherFactor < deltaTime) {
            return false;
        }
    }
    return true;
}