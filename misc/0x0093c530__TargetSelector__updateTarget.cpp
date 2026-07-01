// FUNC_NAME: TargetSelector::updateTarget
// Address: 0x0093c530
// Role: Determines the current target object for this selector, checking multiple sources and managing a switch cooldown.

#include <cstdint>

// Constants
const uint32_t kPlayerHash = 0x369ac561; // Hash identifying the player object
const int kSwitchCooldownLimit = 500;   // Max time before forced switch (from DAT_01206804)

void __thiscall TargetSelector::updateTarget(int thisPtr, int gameManager)
{
    int *piVar1;
    char cVar2;
    uint uVar3;
    int iVar4;
    uint uVar5;
    bool bFoundInFirstAttempt;
    uint firstAttemptResult;
    uint secondAttemptResult;
    uint thirdAttemptResult;

    // If bit 9 of this+0x5c is set, skip main logic entirely
    if ((*(uint *)(thisPtr + 0x5c) >> 9 & 1) != 0) goto LAB_0093c73f;

    // Attempt 1: Try to get object handle from gameManager+0x1c78
    if ((*(int *)(gameManager + 0x1c78) == 0) ||
        (piVar1 = (int *)(*(int *)(gameManager + 0x1c78) + -0x48), piVar1 == (int *)0x0)) {
        uVar3 = 0;
    }
    else {
        firstAttemptResult = 0;
        cVar2 = (**(code **)(*piVar1 + 0x10))(kPlayerHash, &firstAttemptResult);
        uVar3 = -(uint)(cVar2 != '\0') & firstAttemptResult;
    }
    bFoundInFirstAttempt = (uVar3 == 0) ? false : true; // Actually bFoundInFirstAttempt = (uVar3 != 0)? Wait: code sets bVar6 = (uVar3==0). Let's keep original variable name.

    // If first attempt failed, try other sources
    if (uVar3 == 0) {
        // Check flag at gameManager+0x8e6 bit 0
        if (((*(byte *)(gameManager + 0x8e6) & 1) != 0) && (iVar4 = FUN_0079d7c0(), iVar4 != 0)) {
            uVar3 = FUN_006bc8d0(iVar4, kPlayerHash);
            if (uVar3 != 0) goto LAB_0093c5dc;
        }
        // Try gameManager+0xffc
        if ((*(int *)(gameManager + 0xffc) == 0) ||
            (piVar1 = (int *)(*(int *)(gameManager + 0xffc) + -0x48), piVar1 == (int *)0x0)) {
            uVar3 = 0;
        }
        else {
            secondAttemptResult = 0;
            cVar2 = (**(code **)(*piVar1 + 0x10))(kPlayerHash, &secondAttemptResult);
            uVar3 = -(uint)(cVar2 != '\0') & secondAttemptResult;
        }
    }
LAB_0093c5dc:
    // Compute pointer from gameManager+0x74c (used for additional checks)
    if (*(int *)(gameManager + 0x74c) == 0) {
        iVar4 = 0;
    }
    else {
        iVar4 = *(int *)(gameManager + 0x74c) + -0x48;
    }

    // If still not found and certain conditions allow, try additional sources
    if ((uVar3 == 0) &&
        (((((*(uint *)(gameManager + 0x8e0) >> 10 & 1) == 0 || (iVar4 == 0)) ||
          (*(char *)(iVar4 + 0x1a8) != '\x01')) ||
         (((iVar4 = FUN_006d6ac0(), iVar4 == 0 || (uVar3 = FUN_006bc8d0(iVar4, kPlayerHash), uVar3 == 0))
          && ((iVar4 = FUN_0072dee0(), iVar4 == 0 ||
              (uVar3 = FUN_006bc8d0(iVar4, kPlayerHash), uVar3 == 0)))))))) {
        // If all else fails, try gameManager+0x24fc
        if ((*(int *)(gameManager + 0x24fc) == 0) ||
            (piVar1 = (int *)(*(int *)(gameManager + 0x24fc) + -0x48), piVar1 == (int *)0x0)) {
            uVar3 = 0;
        }
        else {
            thirdAttemptResult = 0;
            cVar2 = (**(code **)(*piVar1 + 0x10))(kPlayerHash, &thirdAttemptResult);
            uVar3 = -(uint)(cVar2 != '\0') & thirdAttemptResult;
        }
    }

    // Decision logic: If first attempt succeeded OR flag bit 8 in gameManager+0x8e4 is set, and uVar3 non-zero
    if ((!bFoundInFirstAttempt) || ((*(uint *)(gameManager + 0x8e4) & 0x100) != 0)) {
        if (uVar3 != 0) {
            // Get current target handle from this+0x114
            uVar5 = 0;
            if (*(int *)(thisPtr + 0x114) != 0) {
                uVar5 = *(int *)(thisPtr + 0x114) - 0x48; // Convert pointer to handle?
            }
            // If found handle differs from current target, switch to it
            if (uVar5 != uVar3) {
                FUN_0093b780(uVar3);
                goto LAB_0093c73f;
            }
        }
    }

    // Compare current target with found handle
    uVar5 = 0;
    if (*(int *)(thisPtr + 0x114) != 0) {
        uVar5 = *(int *)(thisPtr + 0x114) - 0x48;
    }
    if (uVar5 == uVar3) {
        // Same: clear pending target if present
        if (*(int *)(thisPtr + 0x11c) != 0) {
            FUN_004daf90((undefined4 *)(thisPtr + 0x11c));
            *(undefined4 *)(thisPtr + 0x11c) = 0;
        }
    }
    else {
        // Different: check if pending target matches found handle
        uVar5 = 0;
        if (*(int *)(thisPtr + 0x11c) != 0) {
            uVar5 = *(int *)(thisPtr + 0x11c) - 0x48;
        }
        if (uVar5 == uVar3) {
            // Increment switch timer
            *(int *)(thisPtr + 0x104) = *(int *)(thisPtr + 0x104) + DAT_01206804; // external time delta
            if (*(uint *)(thisPtr + 0x104) > kSwitchCooldownLimit) {
                // Force switch
                if (uVar3 == 0) {
                    FUN_0093aca0();
                }
                else {
                    FUN_0093b780(uVar3);
                }
            }
            goto LAB_0093c73f;
        }
        // Otherwise, start new pending target
        FUN_006e61a0(uVar3);
    }
    // Reset switch timer
    *(undefined4 *)(thisPtr + 0x104) = 0;

LAB_0093c73f:
    // Final check: if bit 11 of this+0x5c is set, handle special case
    if ((*(uint *)(thisPtr + 0x5c) >> 0xb & 1) != 0) {
        // If no current target (or pointer is exactly 0x48?), reset
        if ((*(int *)(thisPtr + 0x114) == 0) || (*(int *)(thisPtr + 0x114) == 0x48)) {
            FUN_0093aca0();
            return;
        }
        // If some flag is set, update something
        if (*(int *)(thisPtr + 0x100) != 0) {
            FUN_0093b840();
        }
    }
    return;
}