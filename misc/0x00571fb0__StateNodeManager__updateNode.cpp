// FUNC_NAME: StateNodeManager::updateNode
// Function at 0x00571fb0: Updates a state node at a given index in a linked list, applying animation blending or state transition logic.
// Offsets: +0x124 = next pointer (linked list), +0x10c = callback object, +0x14 = previous state ID, +0x10 = flags, +0x120 = param5 byte, +0x121 = another byte, +0x110 = active flag (int), +0x114 = float value, +0x118 = computed float, +0x11c = undefined, +0x2f0 = flag pointer, +0x24 = base float (e.g., time or speed).

// Global constants (likely from config or tuning):
extern float g_constBase;     // DAT_00e2b1a4
extern float g_constClampMax; // DAT_00e2cb90
extern float g_divisor;       // _DAT_011260b0
extern float g_multiplier;    // DAT_00e35654
extern float g_decay;         // _DAT_00e446b8

// Forward declarations of called functions:
void applyCallback(int callbackObj, int node, int param6); // FUN_005826b0
void clearState(int stateId);                              // FUN_005786c0
int getRandomStateData();                                  // FUN_00571d70

undefined1 __thiscall StateNodeManager::updateNode(int this, int nodeIndex, int newStateId, bool doTransition, undefined4 param4, byte param5, undefined4 param6)
{
    float fVar1;
    int iVar2;
    float fVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    float fVar7;
    float fVar8;
    undefined1 result;

    result = 0;
    if ((this == 0) || (nodeIndex < 0)) {
        return 0;
    }
    iVar4 = 0;
    iVar6 = *(int *)(this + 0x124); // head of linked list
    if (nodeIndex > 0) {
        do {
            iVar6 = *(int *)(iVar6 + 0x124); // follow next pointer
            if (iVar6 == 0) {
                return 0;
            }
            iVar4 = iVar4 + 1;
        } while (iVar4 < nodeIndex);
    }
    if (iVar6 == 0) {
        return 0;
    }
    if (newStateId != -1) {
        result = 1;
        if (*(int *)(iVar6 + 0x10c) != 0) {
            applyCallback(*(int *)(iVar6 + 0x10c), iVar6, param6);
        }
        iVar4 = *(int *)(iVar6 + 0x14); // previous state ID stored at +0x14
        clearState(newStateId);
        *(int *)(iVar6 + 0x10) &= 0xffffff7f; // clear bit 7 (0x80) of flags
        *(byte *)(iVar6 + 0x120) = param5;
        fVar8 = g_constBase;
        if (doTransition != '\0') {
            iVar2 = *(int *)(iVar6 + 0x110); // old active flag
            fVar1 = *(float *)(iVar6 + 0x114); // old float value
            *(int *)(iVar6 + 0x110) = 1; // set active
            *(byte *)(iVar6 + 0x121) = 0; // clear some byte
            fVar3 = g_constClampMax;
            if (*(int *)(iVar6 + 0x2f0) == 0) {
                // Normal transition: compute blend factor from base value and constants
                fVar7 = ((*(float *)(iVar6 + 0x24) - fVar8) / g_divisor) * g_multiplier;
                *(float *)(iVar6 + 0x118) = fVar7;
                if (fVar3 < fVar7) {
                    *(float *)(iVar6 + 0x118) = fVar3;
                }
                *(int *)(iVar6 + 0x11c) = 0;
            }
            else {
                // Alternate path: fetch random data and use it
                iVar5 = getRandomStateData();
                fVar8 = g_constBase; // re-read (maybe volatile)
                *(float *)(iVar6 + 0x118) = *(float *)(iVar5 + 4) / g_divisor;
                *(int *)(iVar6 + 0x11c) = *(int *)(iVar5 + 0xc);
            }
            if (iVar2 != 0) {
                if (iVar2 < 0) {
                    // Decay the existing float value
                    fVar8 = (fVar8 - fVar1 * g_decay) * *(float *)(iVar6 + 0x118);
                    *(float *)(iVar6 + 0x114) = fVar8;
                    if (fVar8 < 0.0) {
                        *(int *)(iVar6 + 0x10) &= 0xedfffffe; // clear specific flags
                        *(float *)(iVar6 + 0x114) = 0.0;
                        return 1;
                    }
                    goto LAB_0057210d;
                }
LAB_00572160:
                *(int *)(iVar6 + 0x10) &= 0xedfffffe;
                *(float *)(iVar6 + 0x114) = 0.0;
                return 1;
            }
            if (iVar4 == -1) goto LAB_00572160;
        }
        *(int *)(iVar6 + 0x110) = 0; // clear active flag
    }
LAB_0057210d:
    *(int *)(iVar6 + 0x10) &= 0xedfffffe; // clear flags
    return result;
}