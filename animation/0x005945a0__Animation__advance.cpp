// FUNC_NAME: Animation::advance
#include <cstdint>

// Global variables (from data refs)
extern float g_someTimeThreshold; // DAT_00e2b05c
extern void* g_someSingleton;     // DAT_012055a8

class Animation {
public:
    // Vtable offsets (assumed from decompilation)
    virtual void vfunc68();    // +0x68: main update step
    virtual void vfunc10();    // +0x10: start/trigger
    virtual void vfunc14();    // +0x14: end/cleanup
    virtual int  vfunc30();    // +0x30: getInputFlags
    virtual bool vfunc38();    // +0x38: checkCondition

    // State handler functions
    void handleStateFlag02(float dt); // FUN_005949d0
    void handleStateFlag04(float dt); // FUN_00594a30
    void handleStateFlag100(float dt); // FUN_00595230
    void handleStateFlag200(float dt); // FUN_00595300
    void handleStateFlag20(); // FUN_00594aa0 (dt not used)
    void handleStateFlag40(float dt); // FUN_00594fb0

    // Member fields (offsets from this)
    uint8_t  flagsByte1;   // +0x04
    uint8_t* dataPointer;  // +0x05 (byte array)
    uint32_t flagsInt;     // +0x1f (bitfield)
    int32_t  keyframeCount; // +0x53 (number of keyframes or pointer to array)
    int32_t  keyframeIndex; // +0x54 (current index)
    int32_t  animTimer;    // +0x55 (accumulated time as int)

    void advance(float dt);
};

// Global forward declarations for helper functions (placeholders)
// extern void sub_5949d0(float); // etc.

void Animation::advance(float dt) {
    // === Step 1: Process lower-level flags (byte at +0x04) ===
    if ((flagsByte1 & 0x02) == 0) {
        handleStateFlag02(dt); // state not active, try to start
    }
    if ((flagsByte1 & 0x04) == 0) {
        handleStateFlag04(dt);
    }

    // === Step 2: Process int flags at +0x1f ===
    if ((flagsInt & 0x100) == 0) {
        handleStateFlag100(dt);
    }
    if ((flagsInt & 0x200) == 0) {
        handleStateFlag200(dt);
    }

    // === Step 3: Handle animation timer (flag 0x400) ===
    if ((flagsInt & 0x400) == 0 && dt > 0.0f && keyframeCount != 0) {
        float newTime = (float)animTimer + dt;
        animTimer = (int32_t)newTime;

        // Compute pointer to keyframe array (keyframeCount points to array of floats, each 16 bytes? Actually offset: keyframeIndex*16 -16 + keyframePointer)
        // pfVar1 = (float *)(keyframeIndex * 0x10 - 0x10 + keyframeCount)
        // This suggests keyframeCount is a pointer to an array of structs (16 bytes each), and keyframeIndex is the current index.
        // The code accesses the first float of that struct (the keyframe time).
        intptr_t arrayBase = (intptr_t)keyframeCount;
        intptr_t elementOffset = keyframeIndex * 0x10 - 0x10;
        float* keyframeTimePtr = (float*)(arrayBase + elementOffset);
        float keyframeTime = *keyframeTimePtr;
        if (keyframeTime <= newTime && newTime != keyframeTime) {
            // Keyframe time reached, set flag 0x400 to indicate end of segment
            flagsInt |= 0x400;
        }
    }

    // === Step 4: Additional state flags at +0x1f (0x20, 0x40) ===
    if ((flagsInt & 0x20) != 0) {
        handleStateFlag20(); // state 0x20 active, handle with dt set to a tiny value? (dt = 8.198592e-39)
    }
    if ((flagsInt & 0x40) != 0) {
        handleStateFlag40(dt);
    }

    // === Step 5: Update data pointer and vtable call at +0x68 ===
    uint8_t* data = dataPointer;
    // Extract bits from data pointer (low byte and next byte)
    // The code does: uVar5 = (uint3)((uint)data >> 8);
    // Then if data == null or (*data & 0x20) == 0, local_74 = (float)((uint)uVar5 << 8)
    // else local_74 = (float)CONCAT31(uVar5,1)
    // This seems to be extracting a float value from the data pointer for some purpose.
    float extractedFloat;
    if (data == nullptr || (*data & 0x20) == 0) {
        extractedFloat = (float)(((uintptr_t)data >> 8) & 0xFFFFFF); // shift and mask
    } else {
        // CONCAT31(uVar5,1) means combine upper 3 bytes of data with 0x01? Actually original code: CONCAT31(uVar5,1) where uVar5 is the upper 3 bytes and 1 is a byte. So it forms a 4-byte float value.
        // This is unusual. Perhaps it's interpreting the data pointer as a float with some offset.
        extractedFloat = (float)((((uintptr_t)data >> 8) & 0xFFFFFF) | 0x01000000);
    }
    // uStack_78 = (uint)flagsByte1 >> 1 & 0xffffff01;  // Not used directly? It's set but not used later.
    // Then call vtable function at +0x68
    vfunc68();

    // === Step 6: Check for flag 0x10 and perform additional actions ===
    if ((flagsInt & 0x10) != 0 && g_someTimeThreshold < dt) {
        // Call vfunc10
        vfunc10();

        // Use singleton g_someSingleton to get some values
        // (code uses unaff_ESI and unaff_EDI which are likely from caller, but we have to ignore)
        // The calls to g_someSingleton+4 appear to be a function (get something).
        // We'll represent as a call to a function pointer.
        using SingletonFunc = void(*)(void*, float, float, float);
        SingletonFunc singletonFunc = *(SingletonFunc*)( *(void**)g_someSingleton + 4 );
        // This is speculative; the actual arguments are messy.
        // We'll just call it with extracted values (dummy).
        // The code: (**(code **)(*DAT_012055a8 + 4))(unaff_EDI,unaff_ESI + DAT_00e2b04c,auStack_68[0]);
        // Then again with puStack_84...
        // Since we lack context, we skip the exact parameters.

        // Then vfunc38 call: if returns true, call vfunc14.
        bool condition = vfunc38();
        if (condition) {
            vfunc14();
        }
    }

    // === Step 7: Clear flag 0x800 if set ===
    if ((flagsInt & 0x800) != 0) {
        flagsInt &= ~0x800;
    }

    // === Step 8: Update flag 0x800 based on vfunc30 ===
    int inputFlags = vfunc30();
    if ( (inputFlags & 0xFF) != 0 ) {
        flagsInt ^= ( (inputFlags & 0xFF) << 0xB ) ^ flagsInt & 0x800;
        // Equivalent: toggle bit 0x800 if the low byte of inputFlags is non-zero.
        // Simplified: if (inputFlags & 0xFF) { flagsInt ^= 0x800; }
    }
}