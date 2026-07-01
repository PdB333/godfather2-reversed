// FUNC_NAME: CombatPerception::selectTarget

// Function address: 0x00871ce0
// Selects the best target from the perception list based on distance, line-of-sight, and relative orientation.
// Returns: 2 if extremely close, 1 if a valid target found, 0xFFFFFFFF if no target.

#include <cmath> // for sqrt, abs

// Forward declarations of external functions
extern float __fastcall FUN_00549a20(); // getRandom? or time?
extern int __fastcall FUN_004af8c0(int* outComponent, int componentID); // getComponent by ID
extern int __fastcall FUN_007f7c60(); // some game state check (alive?)
extern int* __fastcall FUN_00471610(); // getTransform of player or camera
extern void* __fastcall FUN_0086d500(); // generateRandomDirection
extern int __fastcall FUN_0084c940(float* startPos, float* endPos, float* direction, void* transform, float unknown1, float unknown2, float* outDotProduct); // line-of-sight test
extern float __fastcall FUN_00871700(float* position); // getAngleToTarget?
extern float __fastcall FUN_007f3770(float* vector); // getAngle of vector?
extern float __fastcall FUN_004a1580(float angle); // normalize angle?

// Constants (from globals)
extern float DAT_00d63484; // 0.0?
extern float DAT_00d7616c; // offset
extern float DAT_00d5c454; // max angle for slowdown?
extern float DAT_00d5c458; // multiplier
extern float DAT_00d76168; // minimum distance
extern float DAT_00d76164; // close distance threshold (return 2)
extern float DAT_00d76160; // random threshold for direction generation
extern float DAT_00d7615c; // random multiplier for dot product
extern float DAT_00d5ef70; // raycast flag?
extern float DAT_00d5f00c; // angle threshold for ignoring?
extern float DAT_00d76158; // angle threshold for further checks

class SomeComponent // placeholder for the target component
{
public:
    // vtable functions
    int (__thiscall* isType)(int hash, float* extra); // +0x10?
    void (__thiscall* getTransform)(void* out); // +0x4c?
    // ... others
};

class CombatPerception
{
private:
    int* playerComponent; // +0x04 pointer to the owning entity's component
    void* targetList; // +0x08 pointer to a struct containing target array
    // The struct at targetList:
    // +0xC0: int** targets (array of pointers)
    // +0xC4: int targetCount

    // Helper constants
    static const int CLOSE_RETURN = 2;
    static const int FOUND_RETURN = 1;
    static const int NOT_FOUND = 0xFFFFFFFF;

public:
    // __thiscall
    int selectTarget()
    {
        // Get a base value (maybe time or random)
        float time = (**(float (__thiscall**)(int*))(*playerComponent + 0x1b8))();
        int* listPtr = *(int**)(this + 8);
        int* bestComponent = nullptr; // piStack_48
        unsigned int resultCode = 0xFFFFFFFF; // uStack_44

        float minDistance = (float)(time * DAT_00d63484 + DAT_00d7616c);
        float randomVal = FUN_00549a20();
        float effectiveDistance = minDistance;
        if (fabs(randomVal) <= DAT_00d5c454) {
            effectiveDistance = minDistance * DAT_00d5c458;
        }
        if (effectiveDistance < DAT_00d76168) {
            effectiveDistance = DAT_00d76168;
        }

        int targetCount = *(int*)(listPtr + 0xC4 / 4);
        if (targetCount > 0) {
            for (int i = 0; i < targetCount; i++) {
                int* targetEntity = *(int**)(listPtr + 0, i); // parse: listPtr + 0xC0? Actually array pointer
                // But the code uses *(*(int*)(listPtr + 0xC0) + i*4)
                int* entityArray = *(int**)(listPtr + 0xC0/4);
                int* entity = entityArray[i];
                if (entity != nullptr && (*(char*)(entity + 0x10/4) + entity) != 0) {
                    // Get a specific component from the entity
                    int* component = nullptr; // apiStack_38
                    if (FUN_004af8c0(&component, 0x2001)) { // 0x2001 is component ID
                        if (component != nullptr && component != playerComponent) {
                            // Check component type via vtable
                            if (component[0] != nullptr) {
                                // vtable function at +0x10: check if can interact?
                                // Note: the original code uses (**(code **)(*piVar6 + 0x10))(0x55859efa,&fStack_5c)
                                // Hash 0x55859efa might represent 'canBeTargeted' or similar
                                // If it returns true, skip further checks? Actually the code calls it and checks result
                                // If it returns false, it still proceeds.
                                bool canTarget = ((int (__thiscall*)(int*, int, float*))*component[0])(component, 0x55859efa, &minDistance);
                                if (canTarget) {
                                    // Game state check
                                    if (FUN_007f7c60()) {
                                        goto nextEntity; // LAB_0087204b
                                    }
                                }
                            }
                        }
                    }
                }
                // If we get here, perform distance/angle checks
                int* transform1 = FUN_00471610(); // first entity transform
                int* transform2 = FUN_00471610(); // second entity transform (maybe the target)
                float dx = *(float*)(transform2 + 0x30/4) - *(float*)(transform1 + 0x30/4);
                float dy = *(float*)(transform2 + 0x34/4) - *(float*)(transform1 + 0x34/4);
                float dz = *(float*)(transform2 + 0x38/4) - *(float*)(transform1 + 0x38/4);
                float distance = sqrtf(dx*dx + dy*dy + dz*dz);
                if (distance <= effectiveDistance) {
                    if (distance < DAT_00d76164) {
                        return CLOSE_RETURN;
                    }
                    // Generate or get direction vector for line-of-sight test
                    float direction[3]; // fStack_2c, fStack_28, fStack_24
                    float randCheck = (**(float (__thiscall**)(int*))(*playerComponent + 0x1b0))(); // get random
                    if (randCheck <= DAT_00d76160) {
                        // Use randomly generated direction
                        unsigned long long* randomDir = (unsigned long long*)FUN_0086d500();
                        direction[0] = *randomDir * DAT_00d76160;
                        direction[1] = (randomDir[0]>>32) * DAT_00d76160; // actually reinterpret
                        direction[2] = *(float*)(randomDir+1) * DAT_00d76160; // maybe third element
                    } else {
                        // Get direction from component (e.g., facing)
                        (**(void (__thiscall**)(int*, float*))*component[0] + 0x1b4))(component, direction);
                    }
                    // Get transform of target
                    char targetTransform[16]; // auStack_14 (likely a matrix or quaternion)
                    (**(void (__thiscall**)(int*, char*))*component[0] + 0x4c))(component, targetTransform);
                    // Perform line-of-sight check
                    float dotResult = 0.0f;
                    int* trans1 = FUN_00471610();
                    int* trans2 = FUN_00471610();
                    bool lineOfSight = FUN_0084c940((float*)(trans2+0x30/4), (float*)(trans1+0x30/4), direction, targetTransform, DAT_00d5ef70, 1.0f, &dotResult);
                    if (lineOfSight) {
                        float randFactor = (**(float (__thiscall**)(int*))*playerComponent + 0x1b0))(); // random again
                        if (dotResult * DAT_00d7615c < randFactor * dotResult?) // actually original: if(fVar7 * DAT_00d7615c < fStack_40)
                        // Wait, original: fVar7 * DAT_00d7615c < fStack_40, so if dotProduct is larger than scaled random
                        if (dotResult * DAT_00d7615c < randFactor) { // need to check order
                            // Actually original: fVar7 (random) * DAT_00d7615c < fStack_40 (dot)
                            if (distance < DAT_00d76168) {
                                goto nextEntity; // distance too small? skip
                            }
                        } else {
                            // Check target's facing angle
                            float angleToTarget = fabs(FUN_00871700(trans1+0x30/4)); // angle from player to target?
                            float angleCheck; // fStack_58
                            if (component[0] != nullptr) {
                                // another property check with hash 0x197c1972
                                bool canSee = ((int (__thiscall*)(int*, int, float*))*component[0])(component, 0x197c1972, &minDistance);
                                if (canSee) {
                                    if (angleToTarget < DAT_00d5f00c) {
                                        goto nextEntity;
                                    }
                                    if (angleToTarget >= DAT_00d76158) {
                                        float forwardAngle = FUN_007f3770(trans1+0x20/4); // get target's forward direction
                                        float diffX = *(float*)(trans2+0x30/4) - *(float*)(trans1+0x30/4);
                                        float diffY = *(float*)(trans2+0x34/4) - *(float*)(trans1+0x34/4);
                                        float diffZ = *(float*)(trans2+0x38/4) - *(float*)(trans1+0x38/4);
                                        float directionAngle = FUN_007f3770(&diffX); // angle of vector from target to player
                                        float angleDiff = fabs(FUN_004a1580(forwardAngle - directionAngle));
                                        if (angleDiff < angleToTarget) {
                                            goto nextEntity; // target not facing player enough
                                        }
                                    }
                                }
                            }
                            // This component becomes the best candidate
                            effectiveDistance = distance;
                            bestComponent = component;
                        }
                    }
                }
nextEntity:
                ; // continue loop
            }
            if (bestComponent != nullptr) {
                resultCode = FOUND_RETURN;
            }
        }
        return resultCode;
    }
};