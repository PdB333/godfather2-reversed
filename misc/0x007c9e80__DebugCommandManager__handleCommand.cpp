// FUNC_NAME: DebugCommandManager::handleCommand

#include <cstdint>

// Function at 0x007c9e80: Likely a debug/cheat command handler for player state, camera, etc.
// Receives command code in param_5, additional data in param_2..param_6.
// Returns 1 if command handled, otherwise delegates to base class handler (FUN_007abec0).

typedef int int32;
typedef unsigned int uint32;

class DebugCommandManager
{
public:
    // Member variables (offsets from object start)
    // +0x00: vtable
    // +0x04: ...
    // +0x74: m_unk1D[3]? (param_1[0x1d] -> +0x74)
    // +0x80: m_unk20[3]? (param_1[0x20] -> +0x80)
    // +0x94: m_unk25[3]? (param_1[0x25] -> +0x94)
    // +0xC4: m_unk31 (param_1[0x31] -> +0xC4)
    // +0x118: m_unk46 (param_1[0x46] -> +0x118)
    // +0x11C: m_unk47 (param_1[0x47] -> +0x11C)
    // +0x128: m_flags (param_1[0x4a] -> +0x128)
    // +0x12C: m_unk4B (param_1[0x4b] -> +0x12C)
    // +0x130: m_unk4C (param_1[0x4c] -> +0x130)

    // Vtable offsets (example, not all)
    // +0x2C: some method
    // +0x304: some method

    // Subobject pointer at +0x58 (param_1[0x16]) for internal struct

    int32 m_flags;         // +0x128
    int32 m_unk31;         // +0xC4
    int32 m_unk46;         // +0x118
    int32 m_unk47;         // +0x11C
    int32 m_unk4B;         // +0x12C
    int32 m_unk4C;         // +0x130
    // ... other members
};

// Forward declarations (from other functions)
extern "C" {
    void FUN_007c9770();                     // handle cheat case 0x31
    void FUN_007c7d60();                     // handle cheat case 0x32
    char FUN_00481660();                     // returns non-zero if player is allowed
    void FUN_00472130(int);                  // enable/disable something
    int FUN_006252f0();                      // get some bool parameter from input
    void FUN_007c6a20(int);                  // set cheat state
    void FUN_007c6a50(int);
    void FUN_007c6a80(int);
    void FUN_007c83a0();                     // handle cheat case 0x38
    void FUN_007c8890();                     // handle cheat case 0x39
    void FUN_007c6bc0(int);                  // set cheat state
    void FUN_007f6420(int);                  // send event with type
    void FUN_007f63e0(int);                  // send different event
    void FUN_007c8200();                     // handle cheat case 0x3d
    void FUN_007c6690(int);                  // set cheat state
    char FUN_00481620();                     // returns non-zero if something is active
    void FUN_007c9860();                     // handle cheat case 0x3f
    void FUN_007c7070();                     // handle cheat case 0x43
    void FUN_007c7130(int);                  // toggle something
    void FUN_007c71c0();                     // handle cheat case 0x46/0x48
    void FUN_007c7240();                     // handle cheat case 0x49
    void FUN_007c7cf0(int);                  // handle cheat case 0x4d
    char FUN_004ac260();                     // returns non-zero if some mode
    void FUN_007c72f0();                     // handle cheat case 0x4a/0x4c inner
    void FUN_007ab470(int);                  // send event/action with ID
    void FUN_007ab4d0(int);                  // remove event?
    void FUN_007c7330();                     // handle cheat case 0x4e
    void FUN_007c7650();                     // handle cheat case 0x50
    int FUN_00471610();                      // get player state pointer
    void FUN_007ab120(int*, int*, int*, int, int); // copy/transform vector
    void FUN_007e95c0();                     // camera or movement function
    void FUN_0079fb90(int, int, int, long, int); // log or trigger function
    void FUN_007c69e0();                     // initialise something
    void FUN_007c77f0();                     // handle cheat case 0x53
    void FUN_007c79a0();                     // handle cheat case 0x54
    int FUN_007ab130();                      // get some manager object pointer
    void FUN_006901b0(int);                  // play sound/effect
    void FUN_007c6920();                     // handle cheat case 0x59
    int FUN_007abec0(int, int, int, int, int); // base class command handler
    void FUN_007c9b00();                     // handle cheat case 0x5c
}

int __thiscall DebugCommandManager::handleCommand(int param_2, int param_3, int param_4, int param_5, int param_6)
{
    char cVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int local_c;
    int local_4;
    int local_1c;
    int uStack_10;

    int32* thisPtr = (int32*)this; // for convenience

    // Default return value (handled by base)
    int result = 1;

    switch (param_5)
    {
        case 0x31: // '1'
            FUN_007c9770();
            return 1;

        case 0x32: // '2'
            FUN_007c7d60();
            return 1;

        case 0x33: // '3'
            thisPtr[0x4a] |= 8; // set flag bit 3
            cVar1 = FUN_00481660();
            if (cVar1 != 0) {
                FUN_00472130(1);
                thisPtr[0x4a] &= 0xfffeffff; // clear bit 16
                return 1;
            }
            break; // fall through to default if not allowed?

        case 0x34: // '4'
            iVar4 = FUN_006252f0();
            FUN_007c6a20(iVar4 != 0);
            return 1;

        case 0x35: // '5'
            iVar4 = FUN_006252f0();
            FUN_007c6a50(iVar4 != 0);
            return 1;

        case 0x36: // '6'
            iVar4 = FUN_006252f0();
            FUN_007c6a80(iVar4 != 0);
            return 1;

        case 0x37: // '7'
            iVar4 = FUN_006252f0();
            if (iVar4 == 0) {
                thisPtr[0x4a] &= 0xfffffdff; // clear bit 9
                return 1;
            }
            thisPtr[0x4a] |= 0x200; // set bit 9
            return 1;

        case 0x38: // '8'
            FUN_007c83a0();
            return 1;

        case 0x39: // '9'
            FUN_007c8890();
            return 1;

        case 0x3a: // ':' (ASCII 0x3a)
            iVar4 = FUN_006252f0();
            FUN_007c6bc0(iVar4 != 0);
            return 1;

        case 0x3b: // ';'
            iVar4 = FUN_006252f0();
            iVar6 = 0x1a;
            goto label_0x007c9ffc;

        case 0x3c: // '<'
            iVar4 = FUN_006252f0();
            iVar6 = 0x1b;
        label_0x007c9ffc:
            if (iVar4 == 0) {
                FUN_007f6420(iVar6);
                return 1;
            }
            FUN_007f63e0(iVar6);
            return 1;

        case 0x3d: // '='
            FUN_007c8200();
            return 1;

        case 0x3e: // '>'
            iVar4 = FUN_006252f0();
            FUN_007c6690(iVar4 != 0);
            return 1;

        case 0x3f: // '?'
            cVar1 = FUN_00481620();
            if (cVar1 != 0) {
                FUN_007c9860();
                return 1;
            }
            break;

        case 0x40: // '@'
            cVar1 = FUN_00481620();
            if (cVar1 != 0) {
                thisPtr[0x47] = thisPtr[0x46]; // copy value
                return 1;
            }
            break;

        case 0x43: // 'C'
            FUN_007c7070();
            return 1;

        case 0x44: // 'D'
            FUN_007c7130(1);
            goto label_0x007ca0fd;

        case 0x45: // 'E'
            FUN_007c7130(0);
            return 1;

        case 0x46: // 'F'
        case 0x48: // 'H'
            FUN_007c71c0();
            return 1;

        case 0x47: // 'G'
            FUN_007c7130(1);
            return 1;

        case 0x49: // 'I'
            FUN_007c7240();
            thisPtr[0x31] = param_2; // store param_2
            return 1;

        case 0x4a: // 'J'
        case 0x4c: // 'L'
            cVar1 = FUN_004ac260();
            if (cVar1 == 0) {
                return 1; // if not active, ignore
            }
            FUN_007c72f0();
        label_0x007ca0fd:
            cVar1 = FUN_00481660();
            if ((cVar1 != 0) && ((*(uint8*)((int)this + 0x12a) & 1) == 0)) {
                FUN_00472130(0);
                thisPtr[0x4a] |= 0x10000; // set bit 16
                return 1;
            }
            break;

        case 0x4b: // 'K'
            FUN_007ab470(0x21);
            thisPtr[0x31] = param_2;
            return 1;

        case 0x4d: // 'M'
            FUN_007c7cf0(param_3);
            return 1;

        case 0x4e: // 'N'
            FUN_007ab4d0(0x21);
            FUN_007c7330();
            return 1;

        case 0x4f: // 'O'
            FUN_007ab4d0(0x15);
            FUN_007ab4d0(0x21);
            if (((uint32)thisPtr[0x4a] >> 0xe & 1) != 0) { // check bit 14
                thisPtr[0x4a] &= 0xffffbfff; // clear bit 14
                // Call vtable method at offset 0x304 from subobject at thisPtr[0x16]
                (**(void (***)(int32))thisPtr[0x16])[0x304]();
                return 1;
            }
            break;

        case 0x50: // 'P'
            FUN_007c7650();
            return 1;

        case 0x51: // 'Q'
            iVar4 = FUN_00471610();
            // Copy 3 ints from player struct at offset +0x30
            *(int64*)(thisPtr + 0x2e) = *(int64*)(iVar4 + 0x30);
            thisPtr[0x30] = *(int32*)(iVar4 + 0x38);
            thisPtr[0x4a] |= 2; // set bit 1
            return 1;

        case 0x52: // 'R'
            cVar1 = FUN_00481620();
            if (cVar1 == 0) {
                // Not in some mode
                iVar4 = thisPtr[0x16];
                iVar3 = FUN_00471610();
                // Copy 3 ints from player
                *(int64*)(thisPtr + 0x25) = *(int64*)(iVar3 + 0x30);
                thisPtr[0x27] = *(int32*)(iVar3 + 0x38);
                // Determine value based on field at iVar4+0x2248
                thisPtr[0x46] = (*(int32*)(iVar4 + 0x2248) != 0) + 1;
                FUN_007c69e0();
                *(uint8*)(iVar4 + 0x2240) = 1;
                return 1;
            }
            // In some mode: perform vector transformation
            FUN_007ab120(thisPtr + 0x25, thisPtr + 0x1d, thisPtr + 0x20, 0x10000, 8);
            FUN_007e95c0();
            cVar1 = FUN_00481660();
            if (cVar1 != 0) {
                FUN_00472130(0);
                thisPtr[0x4a] |= 0x10000;
                // Prepare arguments for logging/trigger
                local_1c = (1 << 24); // set high byte to 1
                FUN_0079fb90(6,
                    (2 << 24) | local_1c, // concatenation of 2 and local_1c
                    (thisPtr[0x46] == 2) << 24 | uStack_10, // concatenation
                    local_c,
                    local_4);
                return 1;
            }
            break;

        case 0x53: // 'S'
            FUN_007c77f0();
            return 1;

        case 0x54: // 'T'
            FUN_007c79a0();
            return 1;

        case 0x55: // 'U'
            // Call vtable method at offset 0x2c
            (**(void (***)(int32))thisPtr)[0x2c]();
            return 1;

        case 0x56: // 'V'
            iVar4 = FUN_007ab130();
            thisPtr[0x4b] = *(int32*)(iVar4 + 4); // copy value from manager
            {
                int** ppVoid = (int**)FUN_007ab130();
                (**(void (***)(int))(*ppVoid))(4); // call manager method with arg 4
            }
            {
                int** ppVoid = (int**)FUN_007ab130();
                (**(void (***)())(*ppVoid))(); // call manager no-arg method
            }
            return 1;

        case 0x57: // 'W'
            {
                int** ppVoid = (int**)FUN_007ab130();
                (**(void (***)(int))(*ppVoid))(thisPtr[0x4b]); // call with stored value
            }
            thisPtr[0x4b] = 0;
            return 1;

        case 0x58: // 'X'
            if (((uint32)thisPtr[0x4a] >> 10 & 1) != 0) { // check bit 10
                FUN_006901b0(0x26);
            }
            thisPtr[0x4a] &= 0xfffffbff; // clear bit 10
            return 1;

        case 0x59: // 'Y'
            FUN_007c6920();
            return 1;

        case 0x5a: // 'Z'
            // Store into subobject field at offset 0x30ac
            *(int32*)(thisPtr[0x16] + 0x30ac) = thisPtr[0x4c];
            return 1;

        case 0x5b: // '['
            *(int32*)(thisPtr[0x16] + 0x30ac) = 0;
            return 1;

        case 0x5c: // '\'' (backslash, but ASCII 0x5c)
            cVar1 = FUN_00481620();
            if (cVar1 != 0) {
                FUN_007c9b00();
                return 1;
            }
            break;

        default:
            result = FUN_007abec0(param_2, param_3, param_4, param_5, param_6);
            break;
    }

    return result;
}