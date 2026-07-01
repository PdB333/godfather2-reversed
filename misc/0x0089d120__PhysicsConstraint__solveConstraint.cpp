// FUNC_NAME: PhysicsConstraint::solveConstraint

// Address: 0x0089d120
// Role: Solves a physics constraint (likely for ragdoll or vehicle) by computing
//       penetration depth and applying impulses based on constraint type.
// Offsets:
//   +0x30: relative position vector (3 floats)
//   +0x44: constraint type (uint, 0-6)
//   +0x50: active flag (int, 0 = active, non-zero = inactive)

#include <cstdint>

// Forward declarations of helper functions (addresses from callees)
void vectorZero(float* out);                          // 0x00425060
void transformVector(const float* in, float* out);    // 0x0056b8a0
float computePenetration(float param, const float* a, const float* b, const float* c); // 0x004a0cd0
void* getPhysicsWorld();                              // 0x004262f0 (returns pointer to global physics world)
float convertToFloat(double d);                       // 0x00b99e20 (placeholder)
float convertToFloat2(double d);                      // 0x00b99fcb (placeholder)
uint32_t solveConstraintImpulse(float* penetration, const float* constraintDir, const float* worldMatrix,
                                const float* someArray, int param1, int param2, int* param3); // 0x004df270
void* allocateObject(uint32_t size);                  // 0x00414db0
void solveConstraintInactive(float* scaledPenetration); // 0x004df870

// Typedef for constraint-specific function that returns a direction vector
typedef const float* (*ConstraintDirFunc)();

void __thiscall PhysicsConstraint::solveConstraint(void* thisPtr, uint32_t param2)
{
    // Read relative position from this+0x30
    float relPos[3];
    relPos[0] = *(float*)((uint8_t*)thisPtr + 0x30);
    relPos[1] = *(float*)((uint8_t*)thisPtr + 0x34);
    relPos[2] = *(float*)((uint8_t*)thisPtr + 0x38);

    // Zero vector for initialization
    float zeroVec[3];
    vectorZero(zeroVec);

    // Temporary storage for transform result
    float transformResult[3];
    float temp1[3], temp2[3];
    // Call transform function (likely converts relative position to world space)
    transformVector(zeroVec, transformResult); // parameters may differ; simplified

    // Compute penetration depth
    float penetration = computePenetration(param2, transformResult, relPos, &DAT_00d77cc0);
    penetration += DAT_00d5f00c; // add constant offset

    // Check constraint type (0-6)
    uint32_t constraintType = *(uint32_t*)((uint8_t*)thisPtr + 0x44);
    if (constraintType < 7)
    {
        // Get global physics world (returns pointer to a structure with matrix at +0x40)
        void* physicsWorld = getPhysicsWorld();
        float worldMatrix[16];
        // Read 4x4 matrix from physicsWorld+0x40 to +0x7c
        for (int i = 0; i < 16; i++)
            worldMatrix[i] = *(float*)((uint8_t*)physicsWorld + 0x40 + i * 4);

        // Scale penetration by constants
        float scaledPenX = penetration * DAT_00d5c458;
        float scaledPenY = penetration * DAT_00d5c454;

        // Check if constraint is active
        int activeFlag = *(int*)((uint8_t*)thisPtr + 0x50);
        if (activeFlag == 0)
        {
            // Jump table for constraint type (7 functions returning direction vectors)
            static const ConstraintDirFunc constraintDirFuncs[7] = {
                &func0, &func1, &func2, &func3, &func4, &func5, &func6
            };
            // Call the appropriate function to get constraint direction
            const float* constraintDir = constraintDirFuncs[constraintType]();

            // Prepare parameters for impulse solving
            float penetrationCopy = penetration;
            int someParam = 5;
            int worldIndex = (int)physicsWorld; // used as parameter
            uint32_t result = solveConstraintImpulse(&penetrationCopy, constraintDir, worldMatrix,
                                                      &scaledPenX, 0x1ff, 4, &someParam);
            // Allocate object based on result
            void* newObj = allocateObject(result);
            if (penetrationCopy != 0.0f)
            {
                *(uint32_t*)((uint8_t*)newObj + 8) = 0;
                return;
            }
        }
        else
        {
            // Inactive path: call alternative solver
            solveConstraintInactive(&scaledPenX);
        }
    }
    return;
}