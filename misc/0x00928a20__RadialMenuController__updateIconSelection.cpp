// FUNC_NAME: RadialMenuController::updateIconSelection

// Reconstructed C++ function at address 0x00928a20
// Handles analog stick input to select a radial menu icon (e.g., weapon wheel).
// Object structure offsets:
//   +0x50: flags (uint32) - bit 1 = force selection?, bit 2 = dirty flag?
//   +0x5c: selectedIconIndex (int32)
//   +0x60: stickXNormalized (float) - current stick x after processing
//   +0x64: stickYNormalized (float) - current stick y after processing

#include <cmath>  // for sqrtf
#include <cstdint>

// External globals
extern uint32_t DAT_01129814;  // some input state base (e.g., controller array)
extern float DAT_00d5842c;     // max stick magnitude for deadzone?
extern float _DAT_00d5780c;   // max allowed stick magnitude (clamp)
extern float DAT_00d71c44;
extern float _DAT_00d87c4c;
extern float DAT_00d87c48;
extern float DAT_00d87c44;
extern float DAT_00d87c40;
extern float DAT_00d87c3c;
extern float DAT_00d87c38;
extern float _DAT_00d87c34;
extern float DAT_00d87b2c;     // some string parameter for UpdateIconSelected/UpdateStickXY
extern float DAT_00e44564;     // initial stick magnitude?
extern float DAT_00d5ccf8;     // constant used in math functions (likely 0.0 or 1.0)

// Forward declarations of called functions
bool FUN_00466240(float a, int b);       // checks something about input mode
float FUN_00465ca0(float, int, int);     // math: perhaps atan2 or magnitude
float FUN_00465ce0(float, int, int);     // math: perhaps direction component
void FUN_00465e30(float, int, float*, float*, int, int, float, float, float); // vector math
bool FUN_00410eb0();                     // returns true if using legacy input mode?
void FUN_00b9a9fa();                     // unknown, but called after updating stick
void FUN_00402050(uint32_t*, int);       // some kind of update function
void FUN_005a04a0(const char*, int, float*, int); // string-based event trigger
void FUN_00928660();                     // update icon rendering?
void FUN_00928900();                     // clear selection / fallback

// __thiscall reconstruction (this in ECX)
int __fastcall RadialMenuController::updateIconSelection(void* thisPtr)
{
    char cVar1;
    int iVar2;
    float fVar3;
    float fVar4;
    double dVar5;
    float fVar6;
    float local_10;  // actually used as both float and bitfield (union-like)
    float local_c;
    float local_8;
    float local_4;

    fVar6 = local_10;  // note: local_10 uninitialized here? but likely from previous assignment
    cVar1 = '\0';
    // Extract low byte? (masking out lower 8 bits)
    local_10 = (float)((uint32_t)local_10 & 0xffffff00);
    fVar4 = local_10;

    // Check number of active controllers? (byte at +0x14 of base)
    if (*(uint8_t*)(DAT_01129814 + 0x14) < 0x10) {
        // Replace low 8 bits of local_10 with that byte
        local_10 = (float)CONCAT31(SUB43(fVar6, 1), *(uint8_t*)(DAT_01129814 + 0x14));
        fVar4 = local_10;
        cVar1 = FUN_00466240(local_10, 2) ? '\x01' : '\0';
    }

    // If bit 1 of flags is set OR the check failed, use fallback/clear
    if (((*(uint32_t*)((char*)thisPtr + 0x50) >> 1) & 1) != 0 || cVar1 == '\0') {
        FUN_00462100();  // clear selection or reset
        return 1;
    }

    // Compute stick direction and magnitude from fVar4 (which now encodes raw stick values?)
    fVar3 = FUN_00465ca0(fVar4, 1, 1);  // maybe magnitude?
    local_4 = (float)fVar3;
    fVar3 = FUN_00465ce0(fVar4, 1, 0);   // maybe direction (angle)?
    local_8 = (float)fVar3;
    // More vector math: decompose fVar4 into local_10, local_c (likely normalized x,y)
    FUN_00465e30(fVar4, 1, &local_10, &local_c, 0, 0, DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8);

    cVar1 = FUN_00410eb0();  // check if using new input mode?
    fVar6 = DAT_00e44564;    // initial magnitude

    if (cVar1 == '\0') {
        // New input mode: store normalized stick directly
        *(float*)((char*)thisPtr + 0x60) = local_10;
        *(float*)((char*)thisPtr + 0x64) = local_c;
        fVar6 = local_4;   // magnitude
        fVar4 = local_8;   // direction angle
        goto CHECK_MAGNITUDE;
    } else {
        // Legacy mode: accumulate (add) recent stick to stored values
        local_4 = local_10 + *(float*)((char*)thisPtr + 0x60);
        local_8 = local_c + *(float*)((char*)thisPtr + 0x64);
        *(float*)((char*)thisPtr + 0x60) = local_4;
        *(float*)((char*)thisPtr + 0x64) = local_8;
        dVar5 = (double)(fVar6 - local_4);  // some difference
        FUN_00b9a9fa();  // unknown, maybe clamp or normalize?
        fVar6 = sqrtf(local_8 * local_8 + local_4 * local_4);  // compute magnitude
        fVar4 = (float)dVar5;  // reuse fVar4 as difference
        if (fVar6 <= _DAT_00d5780c) {
            goto CHECK_MAGNITUDE;
        }
        // Clamp magnitude to max allowed
        fVar6 = _DAT_00d5780c / fVar6;
        *(float*)((char*)thisPtr + 0x60) = fVar6 * local_4;
        *(float*)((char*)thisPtr + 0x64) = fVar6 * local_8;
    }

CHECK_MAGNITUDE:
    // If magnitude is below deadzone, skip icon selection update
    if (fVar6 <= DAT_00d5842c) {
        goto SKIP_ICON_UPDATE;
    }

    // fVar4 holds the angle (or some directional measure)
    // Determine icon index based on angular thresholds (likely 10 pie slices)
    if ((DAT_00d71c44 <= fVar4) || (fVar4 < _DAT_00d87c4c)) {
        // angles outside [DAT_00d87c4c, DAT_00d71c44)? -> index 5?
        // Actually this is a multi-way if-else ladder mapping angle ranges to indices 0-10
        if ((_DAT_00d87c4c <= fVar4) || (fVar4 < DAT_00d87c48)) {
            // etc.
        }
        // ... large nested if-else follows
    }

    // Determine index from angle
    // The ladder is reconstructed here (simplified for clarity)
    int newIndex = 10;  // default
    if (fVar4 < DAT_00d71c44) {
        // first zone
        if (fVar4 >= _DAT_00d87c4c) newIndex = 0;
        else if (fVar4 >= DAT_00d87c48) newIndex = 1;
        else if (fVar4 >= DAT_00d87c44) newIndex = 2;
        else if (fVar4 >= DAT_00d87c40) newIndex = 3;
        else if (fVar4 >= DAT_00d87c3c) newIndex = 4;
        else if (fVar4 >= DAT_00d87c38) newIndex = 5;
        else if (fVar4 >= _DAT_00d87c34) newIndex = 6;
        else newIndex = 7;
    } else {
        // opposite side
        if (fVar4 >= DAT_00d87c48) newIndex = 8;
        else if (fVar4 >= DAT_00d87c44) newIndex = 9;
        else newIndex = 10; // fallback is 10 actually (0-indexed 10?) but original sets 10 earlier
    }

    // If index changed, update icon selection
    if (*(int32_t*)((char*)thisPtr + 0x5c) != newIndex) {
        *(int32_t*)((char*)thisPtr + 0x5c) = newIndex;
        FUN_00402050(&DAT_011301f0, 0);  // some external update
        FUN_005a04a0("UpdateIconSelected", 0, &DAT_00d87b2c, 0);
        FUN_00928660();  // refresh icon display
    }

SKIP_ICON_UPDATE:
    // Clear bit 2 of flags (dirty flag)
    *(uint32_t*)((char*)thisPtr + 0x50) &= 0xfffffffb;
    // Notify that stick position has been processed
    FUN_005a04a0("UpdateStickXY", 0, &DAT_00d87b2c, 0);
    return 0;
}