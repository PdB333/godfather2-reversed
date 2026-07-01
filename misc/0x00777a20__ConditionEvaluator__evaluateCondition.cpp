//FUNC_NAME: ConditionEvaluator::evaluateCondition
// Function address: 0x00777a20
// Role: Dispatches various condition checks based on a condition type (param_4).
// The function returns a boolean (undefined1) indicating whether the condition is met.
// Fields: this+0x30 (float), +0x38 (uint bitmask), +0x50 (int base), +0x5c (int*), +0x70 (int), +0xa4 (float), +0xac (uint bitmask)

typedef unsigned char undefined1;
typedef unsigned int uint;
typedef unsigned char byte;

// Forward declarations for called functions (assumed to be elsewhere)
undefined1 __thiscall FUN_00776a60(void); // e.g., isSomethingEnabled()
undefined1 __thiscall FUN_00776650(int param); // e.g., checkSomethingWithParam(int)
int __thiscall FUN_00800a90(void); // e.g., isGlobalFlagSet()
char __thiscall FUN_00701280(void); // e.g., getPlayerState()
undefined1 __thiscall FUN_00776540(void); // e.g., isAnotherCondition()
undefined1 __thiscall FUN_00776b00(int param); // e.g., checkSomethingElse(int)
char __thiscall FUN_007f47a0(void); // e.g., isPlayerInCombat()
undefined1 __thiscall FUN_0045f120(void); // e.g., getCombatState()
uint __thiscall FUN_006252d0(void); // e.g., getBitmaskForCondition()
byte __thiscall FUN_008754b0(int param); // e.g., getSomeFlag(int)
undefined1 __thiscall FUN_0073e300(int param2, undefined4 param3, int param4, undefined4 param5); // default handler

// Global constants (from data section)
extern float DAT_00e44578; // e.g., 0.5f
extern float DAT_00d5efb8; // e.g., 1.0f
extern float _DAT_00d6826c; // e.g., 0.0f
extern float _DAT_00d577a0; // e.g., 0.0f

undefined1 __thiscall ConditionEvaluator::evaluateCondition(int this, int param_2, undefined4 param_3, int param_4, undefined4 param_5)
{
    float fVar1;
    char cVar2;
    byte bVar3;
    undefined1 uVar4;
    uint uVar5;
    int iVar6;
    byte bVar7;

    uVar4 = 0; // default false

    switch (param_4 - 0x12) {
        case 0: // condition type 0x12
            uVar4 = FUN_00776a60();
            return uVar4;

        case 1:
        case 2:
        case 3: // condition types 0x13-0x15
            fVar1 = (float)param_2;
            if (param_2 < 0) {
                fVar1 = fVar1 + DAT_00e44578; // adjust negative values
            }
            // Compare scaled param_2 with field at +0xa4
            if (*(float *)(this + 0xa4) < fVar1 * DAT_00d5efb8) {
                return true;
            }
            break;

        case 4: // condition type 0x16
            uVar4 = FUN_00776650(param_2);
            return uVar4;

        case 5: // condition type 0x17
            // Check bit 5 of field at +0xac
            if ((*(uint *)(this + 0xac) >> 5 & 1) == 0) {
                return true;
            }
            iVar6 = FUN_00800a90();
            if (iVar6 == 0) {
                return false;
            }
            cVar2 = FUN_00701280();
            goto LAB_00777b25;

        case 6: // condition type 0x18
            uVar4 = FUN_00776540();
            return uVar4;

        case 7: // condition type 0x19
            // Compare field at +0x30 with global constant
            if (*(float *)(this + 0x30) <= _DAT_00d6826c) {
                return false;
            }
            return true;

        case 8: // condition type 0x1a
            uVar4 = FUN_00776b00(param_2);
            return uVar4;

        case 9: // condition type 0x1b
            // Compare field at +0x30 with another global constant
            if (*(float *)(this + 0x30) <= _DAT_00d577a0) {
                return false;
            }
            return true;

        case 10: // condition type 0x1c
            cVar2 = FUN_007f47a0();
LAB_00777b25:
            if (cVar2 == '\0') {
                uVar4 = FUN_0045f120();
                return uVar4;
            }
            break;

        case 0xb: // condition type 0x1d
            cVar2 = FUN_007f47a0();
            if (cVar2 != '\0') {
                uVar4 = FUN_0045f120();
                return uVar4;
            }
            break;

        case 0xc:
        case 0x10: // condition types 0x1e and 0x22
            uVar4 = FUN_007f47a0();
            return uVar4;

        case 0xd: // condition type 0x1f
            // Check field at +0x70; if non-zero, must equal 0x48
            if (*(int *)(this + 0x70) != 0) {
                return *(int *)(this + 0x70) == 0x48;
            }
            return true;

        case 0xe: // condition type 0x20
            // Read bit 13 from structure pointed by +0x5c at offset 0x1f58
            return (byte)(*(uint *)(*(int *)(this + 0x5c) + 0x1f58) >> 0xd) & 1;

        case 0xf: // condition type 0x21
            uVar5 = FUN_006252d0();
            // Check bit 10 of field at +0xac
            if ((*(uint *)(this + 0xac) >> 10 & 1) != 0) {
                // Clear bits in +0x38 according to mask
                *(uint *)(this + 0x38) = *(uint *)(this + 0x38) & ~uVar5;
                return false;
            }
            uVar4 = (uVar5 & *(uint *)(this + 0x38)) != 0;
            if ((bool)uVar4) {
                // Clear bits in +0x38 according to mask
                *(uint *)(this + 0x38) = ~uVar5 & *(uint *)(this + 0x38);
                return (bool)uVar4;
            }
            break;

        case 0x11: // condition type 0x23
            bVar7 = (byte)(*(uint *)(this + 0xac) >> 1) & 1; // bit 1 of +0xac
            iVar6 = *(int *)(this + 0x50) + 0x860; // pointer to some structure
            if (*(int *)(this + 0x70) != 0) {
                bVar3 = FUN_008754b0(iVar6);
                return bVar7 != bVar3;
            }
            bVar3 = FUN_008754b0(iVar6);
            return bVar7 != bVar3;

        default:
            uVar4 = FUN_0073e300(param_2, param_3, param_4, param_5);
    }
    return uVar4;
}