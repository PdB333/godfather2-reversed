// FUNC_NAME: ConstraintSolver::applyConstraintCorrection
// Address: 0x0058f870
// Role: Applies positional constraint corrections between two attached bodies/vertices.
//        Processes a constraint definition, ensures physics system is active,
//        computes corrective impulses using spring-damper math, and applies
//        them to the constraint's child index.

#include <cstring>

// Constants (from global data references) – exact values unknown.
const float kMaxClamp        = 0.0f;        // DAT_00e3ac58
const float kSpringCoeff     = 0.0f;        // DAT_00e2dd14
const float kDampingCoeff    = 0.0f;        // DAT_00e2cd54
const float kThreshSpeed     = 0.0f;        // DAT_00e44754
const float kMinClampLimit   = 0.0f;        // DAT_00e3ac60
const uint  kBitMask         = 0xFFFFFFFF;  // DAT_00e44680

// Function pointer table for constraint type dispatch (0x0103afc0)
typedef int (*ConstraintTypeFn)(void* mgr, byte* data, uint param3, uint param4, uint param5, uint flags, uint param7);

// Forward declarations of internal helpers.
int  ConstraintTypeDispatch(void* mgr, byte* data, uint param3, uint param4, uint param5, uint flags, uint param7);
bool IsSystemInitialized();
int  CreateTemporarySolver();
void SetupSolverA();
void SetupSolverB();
void SetupSolverC();
void SetupSolverD();
int  AllocateDataBlock(int size);
void FinalizeSolver();
bool IsWithinRange(int obj, short val);
void GetWorldPosition(void* mgr, float* outPos);
void ApplyImpulseToVertex(int block, float impulse);

int FUN_0058f870(void* mgr, void* constraintDef, uint param3, uint param4, uint param5,
                 uint flags, uint param7)
{
    byte typeByte;
    short* pJoints;
    byte* pData;
    int constraintFuncResult;
    int solverBlock;
    int numElements;
    int allocatedBlock;
    short jointA, jointB, jointC, jointD, jointE, jointF;
    float pos0[3], pos1[3], pos2[3], pos3[3];
    float diffA, diffB, diffC, diffD, diffE, diffF;
    float temp1, temp2, temp3, temp4, temp5, temp6;
    float clamp, correction;

    // Early exit if constraint definition is invalid.
    if (*(char*)((int)constraintDef + 1) <= 0)
        return 0;

    pJoints  = *(short**)((int)constraintDef + 4);
    pData    = *(byte**)((int)constraintDef + 0xC);
    typeByte = *pData;

    // Dispatch based on constraint type (must be < 0x23).
    if ((typeByte & 0x3F) < 0x23) {
        constraintFuncResult = ((ConstraintTypeFn*)(0x0103afc0))[typeByte & 0x3F](
            mgr, pData, param3, param4, param5, flags, param7);

        if (constraintFuncResult != 0) {
            // Check flags and joint validity.
            if ((((flags & 4) == 0) &&
                 ((*(uint*)((int)mgr + 0x10) >> 8 & 1) == 0 &&
                  (pJoints[0] >= 0 && pJoints[1] >= 0 &&
                   pJoints[2] >= 0 && pJoints[3] >= 0 &&
                   pJoints[4] >= 0 && pJoints[5] >= 0))) &&
                (IsWithinRange(constraintFuncResult, pJoints[0]) &&
                 IsWithinRange(constraintFuncResult, pJoints[3])))
            {
                // Ensure physics system is active.
                if (!IsSystemInitialized()) {
                    solverBlock     = CreateTemporarySolver();
                    SetupSolverA();
                    SetupSolverB();
                    SetupSolverC();
                    SetupSolverD();

                    numElements     = *(int*)(*(int*)(constraintFuncResult + 0x38) + 0xC);
                    allocatedBlock  = AllocateDataBlock(numElements);
                    *(int*)(solverBlock + 0x38) = allocatedBlock;

                    memcpy((void*)(allocatedBlock + 0x10),
                           (void*)(*(int*)(constraintFuncResult + 0x38) + 0x10),
                           numElements << 5);

                    // If constraint is of type 2, copy additional data.
                    if (*(char*)(constraintFuncResult + 0x30) == 0x02) {
                        *(uint*)(solverBlock + 0x10) = *(uint*)(constraintFuncResult + 0x10);
                        *(uint*)(solverBlock + 0x14) = *(uint*)(constraintFuncResult + 0x14);
                        *(uint*)(solverBlock + 0x18) = *(uint*)(constraintFuncResult + 0x18);
                        *(uint*)(solverBlock + 0x1C) = *(uint*)(constraintFuncResult + 0x1C);
                        *(uint*)(solverBlock + 0x20) = *(uint*)(constraintFuncResult + 0x20);
                        *(uint*)(solverBlock + 0x24) = *(uint*)(constraintFuncResult + 0x24);
                        *(uint*)(solverBlock + 0x28) = *(uint*)(constraintFuncResult + 0x28);
                        *(uint*)(solverBlock + 0x2C) = *(uint*)(constraintFuncResult + 0x2C);
                        *(char*)(solverBlock + 0x30) = 0x02;
                    }
                    FinalizeSolver();
                    constraintFuncResult = solverBlock;
                }

                // Retrieve world positions for four points (positions A, B, C, D).
                GetWorldPosition(mgr, &pos3[0]); // actually from stack: uStack_2e0, fStack_2dc, uStack_2d8
                GetWorldPosition(mgr, &pos0[0]); // actually from stack: uStack_320, fStack_31c, uStack_318
                GetWorldPosition(mgr, &pos2[0]); // actually from stack: uStack_130, fStack_12c, uStack_128
                GetWorldPosition(mgr, &pos1[0]); // actually from stack: uStack_170, fStack_16c, uStack_168

                // Calculate differences with joint offsets (pJoints +6, +8, +10).
                diffA = (pos0[1] - pos2[1]) + *(float*)(pJoints + 8);  // pJoints[8]
                diffB = (pos3[1] - pos2[1]) + *(float*)(pJoints + 8);  // pJoints[8]
                diffC = (pos0[0] - pos3[0]) + *(float*)(pJoints + 6);  // pJoints[6]
                diffD = (pos1[0] - pos2[0]) + *(float*)(pJoints + 6);  // pJoints[6]
                diffE = *(float*)(pJoints + 10); // pJoints[10] – max clamp or threshold

                correction = 0.0f;
                if (diffE == 0.0f) {
                    // No max clamp: only prevent negative distances.
                    if (diffB < 0.0f) {
                        correction = kMaxClamp - diffB;
                        diffB = 0.0f;
                    }
                    if (diffA < 0.0f) {
                        correction = kMaxClamp - diffA;
                        diffA = 0.0f;
                    }
                    // Apply clamping and spring-like correction for negative values.
                    if (diffC < 0.0f) {
                        if (kMaxClamp < correction)
                            correction = kMaxClamp;
                        temp1 = (kMaxClamp - correction) * kSpringCoeff;
                        temp2 = pos0[0] - pos3[0];
                        diffC = temp1 * temp1 * diffC;
                        temp1 = 0.0f;
                        if ((temp2 < 0.0f) && (temp1 = temp2, temp2 < kThreshSpeed))
                            temp1 = 0.0f;
                        if (diffC < temp1)
                            diffC = temp1;
                    }
                    if (diffD < 0.0f) {
                        if (kMaxClamp < correction)
                            correction = kMaxClamp;
                        temp2 = pos1[0] - pos0[0];
                        diffE = (kMaxClamp - correction) * kSpringCoeff;
                        diffD = diffE * diffE * diffD;
                        temp1 = 0.0f;
                        if ((temp2 < 0.0f) && (kThreshSpeed <= temp2))
                            temp1 = temp2;
                        if (diffD < temp1)
                            diffD = temp1;
                    }
                } else {
                    // With max clamp: only apply if one value is negative.
                    if ((diffB < 0.0f) || (diffA < 0.0f)) {
                        if (diffA <= diffB) {
                            correction = diffA;
                            if (diffA < diffE)
                                correction = diffE;
                            diffC = diffC - correction;
                            diffB = diffB - correction;
                            diffA = 0.0f;
                            diffD = diffD - correction;
                        } else {
                            correction = diffB;
                            if (diffB < diffE)
                                correction = diffE;
                            diffA = diffA - correction;
                            diffC = diffC - correction;
                            diffB = 0.0f;
                            diffD = diffD - correction;
                        }
                    }
                }

                // Apply damping to the two main axes.
                diffC = (diffC - diffB) * kDampingCoeff + diffC;
                diffD = (diffD - diffA) * kDampingCoeff + diffD;

                // Check if any impulse exceeds a threshold; if so, apply corrections.
                if ((((kMinClampLimit < (float)((uint)diffB & kBitMask)) ||
                      (kMinClampLimit < (float)((uint)diffA & kBitMask))) ||
                     (kMinClampLimit < (float)((uint)correction & kBitMask))) ||
                    ((kMinClampLimit < (float)((uint)diffC & kBitMask) ||
                      (kMinClampLimit < (float)((uint)diffD & kBitMask)))))
                {
                    ApplyImpulseToVertex(constraintFuncResult, diffC);
                    ApplyImpulseToVertex(constraintFuncResult, diffD);

                    // Add correction to the child vertex's data (offset 0x24 of a 0x20 structure).
                    int childIndex = *(int*)((int)constraintDef + 0x10); // hidden variable iStack_360
                    int basePtr = *(int*)(constraintFuncResult + 0x38);
                    *(float*)(basePtr + childIndex * 0x20 + 0x24) += correction;
                }
            }
            return constraintFuncResult;
        }
    }
    return 0;
}