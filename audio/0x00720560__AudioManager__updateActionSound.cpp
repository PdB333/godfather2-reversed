// FUNC_NAME: AudioManager::updateActionSound

// Function address: 0x00720560
// Called from: 0x00720750
// Purpose: Decides which sound effect to play based on current state flags and external conditions.
// Updates current sound handle (offset +0x1c) to a new sound (offset +0x24) if successful.

typedef unsigned char undefined1;
typedef unsigned int uint;
typedef int undefined4;

// Forward declarations (assumed external)
extern undefined1 __fastcall FUN_0071ef20(void* soundHandle, undefined1 param2); // returns 0 if failed
extern undefined1 __fastcall FUN_0071f2c0(void); // is audio system ready?
extern void* __fastcall FUN_0043b870(void* global); // returns some manager pointer
extern undefined1 __fastcall FUN_0045eef0(void); // check if player is in car?
extern undefined1 __fastcall FUN_0045f120(void); // check if player is on foot?
extern int __fastcall FUN_0071fd90(int param1); // get sound ID for current state

// Global variables referenced
extern void* DAT_0112afb8; // some manager
extern int DAT_00e448a4; // some global constant

// Bit field flags at offset +0x20
#define FLAG_BIT9  (1 << 9)   // 0x200
#define FLAG_BIT3  (1 << 3)   // 0x8
#define FLAG_NEWSOUND  (1 << 9) // same as bit 9, used to mark new sound

undefined1 __fastcall AudioManager__updateActionSound(void* this)
{
    undefined1 retVal;
    undefined1 cVar1;       // intermediate boolean
    undefined1 cVar2;
    void* pvVar3;           // derived pointer
    int iVar4;              // sound ID or pointer
    int* soundHandle;       // current sound handle at +0x1c
    uint flags;             // flags at +0x20

    retVal = 0;

    // Check if a new sound is pending (bit 9 of flags)
    flags = *(uint*)((int)this + 0x20);
    if ((flags >> 9 & 1) != 0) {
        // Derive pointer from member at +0x4 (maybe a larger object)
        if (*(int*)((int)this + 4) == 0) {
            pvVar3 = 0;
        } else {
            pvVar3 = (void*)(*(int*)((int)this + 4) - 0x48);
        }
        cVar1 = 0;
        // If derived object exists and its field at +0x1f3c is zero, skip setting cVar1 to 1
        if (pvVar3 != 0 && *(int*)((int)pvVar3 + 0x1f3c) == 0) {
            goto LAB_00720590;
        }
    }
    cVar1 = 1;  // default true

LAB_00720590:
    soundHandle = *(int**)((int)this + 0x1c);
    if (soundHandle != 0) {
        // Try to play the current sound handle; if successful, store it as new sound
        cVar1 = FUN_0071ef20(soundHandle, cVar1);
        if (cVar1 != 0) {
            *(int*)((int)this + 0x24) = *(int*)((int)this + 0x1c);
            *(uint*)((int)this + 0x20) |= 0x200;  // set bit 9 to indicate new sound
        }
        *(int*)((int)this + 0x1c) = 0; // clear current sound
        return 1;
    }

    // No current sound; check audio system readiness
    cVar2 = FUN_0071f2c0();
    if (cVar2 == 0) {
        return 0;
    }

    // Determine which sound ID to use
    iVar4 = *(int*)((int)this + 0x24); // previous sound ID (or handle)
    if (((flags >> 3) & 1) == 0) {
        // Bit 3 not set: use a constant sound ID
        iVar4 = 0x2ca3cff6;
    } else {
        // Bit 3 set: check player state
        if (*(int*)((int)this + 4) == 0 || *(int*)((int)this + 4) == 0x48) {
            // If the pointer is null or equals 0x48 (some invalid sentinel?)
            cVar2 = FUN_0045eef0();
            if (cVar2 == 0) {
                cVar2 = FUN_0045f120();
                if (cVar2 != 0 || cVar1 == 0) {
                    // Player not in car and not on foot? Or cVar1 false -> use default
                    *(int*)((int)this + 0x10) = DAT_00e448a4; // store global
                    iVar4 = FUN_0071fd90(1); // get sound ID for type 1
                }
                retVal = 1;
            } else {
                iVar4 = FUN_0071fd90(0); // get sound ID for type 0
                retVal = 1;
            }
        } else {
            // Pointer is valid and not the sentinel; get a manager pointer
            void* manager = FUN_0043b870(DAT_0112afb8);
            if (manager != 0 && ((*(uint*)((int)manager + 0x3c) >> 1) & 1) != 0) {
                // Clear specific bit in manager state
                *(uint*)((int)manager + 0x3c) &= ~2;
                // Derive pointer again (same as before)
                if (*(int*)((int)this + 4) == 0) {
                    pvVar3 = 0;
                } else {
                    pvVar3 = (void*)(*(int*)((int)this + 4) - 0x48);
                }
                // Compute sound ID based on a flag in derived object
                retVal = 1;
                int temp = (*(int*)((int)pvVar3 + 0x1f54) & 1) ? 0x486eb57f : 0;
                iVar4 = temp + 0x1a0f4077;
            } else {
                // Fallback: same as earlier branch
                cVar2 = FUN_0045eef0();
                if (cVar2 == 0) {
                    cVar2 = FUN_0045f120();
                    if (cVar2 != 0 || cVar1 == 0) {
                        *(int*)((int)this + 0x10) = DAT_00e448a4;
                        iVar4 = FUN_0071fd90(1);
                    }
                    retVal = 1;
                } else {
                    iVar4 = FUN_0071fd90(0);
                    retVal = 1;
                }
            }
        }
    }

    // Try to play the selected sound ID
    cVar1 = FUN_0071ef20((void*)iVar4, cVar1);
    if (cVar1 != 0) {
        *(int*)((int)this + 0x24) = iVar4;  // store new sound handle
        *(uint*)((int)this + 0x20) &= ~0x200; // clear the "new sound" flag
    }
    return retVal;
}