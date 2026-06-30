// 0x0041d310: activateQuadEffect
// Description: Activates a quad-based screen effect (likely part of the effect system).
// Parameters:
//   effectId - uint32 ID for the effect (used to look up material/texture)
//   slotIndex - int32 index into an array of effect slots (e.g., for split-screen or layering)
// Globals heavily referenced; many are likely render state flags or current effect settings.
// The function appears to be called from a UI or gameplay context to start playing a full-screen effect.

#include <cstdint>

// Forward declarations of known engine functions (with guessed prototypes)
// These are likely part of the EA EARS engine library.
extern void FUN_0060d740(const char* className); // get class pointer from hash? Returns some handle.
extern void FUN_00417cf0(int a1, int a2, int a3); // maybe set blend mode or effect state
extern void FUN_00609340(int unk, int texHandlePrev, int texHandlePrev2); // set texture
extern void FUN_0060db60(int unk, float u1, float v1, float u2, float v2); // set UV coordinates
extern void FUN_00609890(int unk); // maybe commit/update render state
extern void FUN_0060df60(int fromTex, int toTex); // copy texture or blend
extern void FUN_0060a460(int handle); // release resource
extern void FUN_00611500(); // unknown, maybe begin scene
extern void FUN_00606e60(int handle, uint32 flags); // set resource flags
extern void FUN_006189c0(); // unknown, maybe update something
extern void FUN_006063b0(); // unknown
extern void FUN_0041ceb0(float* rect, float* rect2); // set viewport/rectangle

// Global variables (renamed with guessed purposes)
// These are from the decompiled code and likely part of a global state structure.
extern uint32 DAT_012058d0;      // some render priority/quality threshold (min)
extern uint32 DAT_00f15988;      // some render priority/quality threshold (max)
extern uint32 DAT_012058d4;      // another threshold (min)
extern uint32 DAT_00f1598c;      // another threshold (max)
extern uint32 DAT_011f3a30;      // some flag (effect active?)
extern uint32 DAT_011f3a44;      // some flag (maybe modified later)
extern int    DAT_011f38f0;      // current texture handle (maybe for quad effect)
extern int    DAT_011f38f4;      // previous texture handle
extern bool   DAT_01206a8c;      // boolean flag (use alternative texture source?)
extern int    DAT_01206af0[16];  // array of texture handles for slots
extern int    DAT_01206afc;      // default texture handle (maybe fallback)
extern int    DAT_01206a78;      // some counter
extern int    DAT_01206a7c;      // another value
extern int    DAT_00e2b05c;      // constant
extern float  DAT_01206a90;      // factor
extern float  DAT_00e44584;      // multiplier
extern uint32 DAT_011f3cdc;      // color (ARGB)
extern uint32 DAT_011f39f4;      // some flag
extern uint32 DAT_011f3a10;      // some flag
extern uint32 DAT_011f3c78;      // alpha value?
extern uint32 DAT_011f3cd0;      // alpha value?
extern int    DAT_012058e8;      // pointer to current effect object (same as piVar4?)
extern float  DAT_00e2eff4;      // constant for rectangle
extern float  DAT_00e2b1a4;      // constant for rectangle
extern float  DAT_01206a9c;      // offset for rectangle

// Memory-mapped array for effect data (size 0x38 per entry)
extern uint8  DAT_011a0f28[0x1000 * 0x38]; // base address for effect entries

void activateQuadEffect(uint32 effectId, int32 slotIndex)
{
    int iVar3;
    int* piVar4;
    float fStack_30, fStack_2c, fStack_28, fStack_24;
    float fStack_1c, fStack_18;
    uint32 uStack_20, uStack_14;

    // Look up the class pointer for "SM_QuadEffectClass"
    iVar3 = FUN_0060d740("SM_QuadEffectClass");
    // Traverse a global linked list to find the matching instance
    for (piVar4 = DAT_012058ec; piVar4 != (int*)0x0; piVar4 = (int*)piVar4[1]) {
        if (iVar3 == piVar4[2]) goto LAB_0041d345;
    }
    piVar4 = (int*)0x0;
LAB_0041d345:

    // Adjust render priority thresholds (min/max)
    if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
    }
    if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
    }
    _DAT_011f3a30 = 1;  // effect active flag

    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 0;  // some flag

    FUN_00417cf0(1, 2, 1); // likely sets blend mode (alpha or additive)

    // Save previous texture handles
    uint32 prevTexF4 = DAT_011f38f4;
    uint32 prevTexF0 = DAT_011f38f0;
    DAT_011f38f4 = 0;

    if (DAT_01206a8c == 0) {
        // Normal path: use texture from slot array
        DAT_011f38f0 = DAT_01206af0[slotIndex];
        FUN_00609340(0, prevTexF0, prevTexF4);
        FUN_0060db60(0, 0.0f, 0.0f, 1.0f, 1.0f); // full UV rectangle
    } else {
        // Alternative path: use default texture
        DAT_011f38f0 = DAT_01206afc;
        FUN_00609340(0, prevTexF0, prevTexF4);
        FUN_0060db60(0, 0.0f, 0.0f, 1.0f, 1.0f);
        if (DAT_01206afc == DAT_011f38f0) {
            FUN_00609890(1);
        } else {
            FUN_0060df60(DAT_01206afc, DAT_011f38f0);
        }

        // Adjust thresholds again
        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
        if (0x1a < DAT_00f15988) {
            DAT_00f15988 = 0x1b;
        }
        _DAT_011f3a44 = 1;

        // Compute effect color (alpha blending)
        if ((DAT_01206a78 < 3) || (DAT_01206a7c == DAT_00e2b05c)) {
            _DAT_011f3cdc = 0xFF; // full white
        } else {
            float factor = DAT_01206a90 * DAT_00e44584;
            _DAT_011f3cdc = (uint32)factor;
        }
        _DAT_011f3cdc &= 0xFF;
        _DAT_011f3cdc = ((_DAT_011f3cdc << 8 | _DAT_011f3cdc) << 8 | _DAT_011f3cdc) << 8 | _DAT_011f3cdc; // replicate byte to full 32-bit ARGB

        if (DAT_012058d4 < 0xc1) {
            DAT_012058d4 = 0xc1;
        }
        if (0xc0 < DAT_00f1598c) {
            DAT_00f1598c = 0xc1;
        }
        FUN_00417cf0(1, 0xe, 0xf); // different blend mode
    }

    // Additional global flag adjustments
    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 0;

    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 0;

    if (DAT_012058d4 < 0xa8) {
        DAT_012058d4 = 0xa8;
    }
    if (0xa7 < DAT_00f1598c) {
        DAT_00f1598c = 0xa8;
    }
    _DAT_011f3c78 = 0xf; // alpha

    if (DAT_012058d4 < 0xbe) {
        DAT_012058d4 = 0xbe;
    }
    if (0xbd < DAT_00f1598c) {
        DAT_00f1598c = 0xbe;
    }
    _DAT_011f3cd0 = 0xf; // alpha

    // Write parameters to the effect object (piVar4)
    piVar4[0x4e] = 0x10;              // offset 0x138: some parameter
    piVar4[5] = piVar4[0x60];         // offset 0x14 -> 0x180 (copy)
    piVar4[4] = piVar4[0x74];         // offset 0x10 -> 0x1D0 (copy)

    // If this is the active effect, release the old texture from offset 0x60
    if (DAT_012058e8 == piVar4) {
        FUN_0060a460(piVar4[0x60]);   // release resource at offset 0x180
    }

    FUN_00611500(); // begin scene or update

    // Handle effect ID lookup: if valid, update the corresponding effect entry
    if ((effectId != 0xFFFFFFFF) && (effectId < 0x1000)) {
        iVar3 = effectId * 0x38; // size of each effect entry
        uint8* entryBase = &DAT_011a0f28[iVar3];
        if ((entryBase != nullptr) && (entryBase[0] < 4)) {
            int entryHandle = *(int*)&DAT_011a0f44[iVar3]; // handle at offset 0x1C inside entry
            if (entryHandle != 0) {
                FUN_00606e60(entryHandle, 0x200000); // set flags (e.g., 'in use')
            }
            // Modify flags at offset 0x0C (within entry)
            *(uint32*)&DAT_011a0f34[iVar3] = *(uint32*)&DAT_011a0f34[iVar3] & 0xFCAC8FFF | 0x200000;
            FUN_006189c0(); // update/rebuild something
        }
    }

    piVar4[0x40] = effectId; // store the effect ID at offset 0x100

    // If this is the active effect and the previous effect (offset 0xFC) is non-zero, call cleanup
    if ((DAT_012058e8 == piVar4) && (piVar4[0x3f] != 0)) {
        FUN_006063b0();
    }

    // Call virtual function at vtable+0x18 (maybe update)
    (**(code**)(*piVar4 + 0x18))();

    // Set up viewport rectangle using global constants
    uStack_20 = DAT_00e2eff4;            // left/top?
    uStack_14 = DAT_00e2eff4;            // right/bottom? (same)
    fStack_1c = DAT_00e2b1a4;            // width?
    fStack_18 = DAT_00e2b1a4;            // height?
    fStack_28 = DAT_00e2b1a4 - DAT_01206a9c; // adjusted width
    fStack_30 = DAT_01206a9c;            // offset
    fStack_2c = DAT_01206a9c;
    fStack_24 = fStack_28;               // adjusted height

    // The following function likely takes two rectangles: source and destination
    FUN_0041ceb0(&uStack_20, &fStack_30);

    // Call virtual function at vtable+0x20 (maybe render)
    (**(code**)(*piVar4 + 0x20))();

    FUN_00609890(1); // commit render state

    // Texture restoration for the alternative path
    uint32 curTexF4 = DAT_011f38f4;
    int curTexF0 = DAT_011f38f0;
    if (DAT_01206a8c != 0) {
        DAT_011f38f0 = DAT_01206af0[slotIndex];
        DAT_011f38f4 = 0;
        FUN_00609340(0, curTexF0, curTexF4);
        FUN_0060db60(0, 0.0f, 0.0f, 1.0f, 1.0f);
        if (DAT_01206afc == DAT_011f38f0) {
            FUN_00609890(1);
        } else {
            FUN_0060df60(DAT_01206afc, DAT_011f38f0);
        }
        FUN_00609890(1);
    }

    // Finally, set the global texture to the effect ID (as a handle?)
    curTexF4 = DAT_011f38f4;
    curTexF0 = DAT_011f38f0;
    DAT_011f38f0 = effectId;
    DAT_011f38f4 = 0;
    FUN_00609340(0, curTexF0, curTexF4);
    FUN_0060db60(0, 0.0f, 0.0f, 1.0f, 1.0f);
}