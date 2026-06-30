// FUNC_NAME: EffectManager::updateSounds
class EffectManager {
public:
    void updateSounds(uint this_ptr);
};

struct SoundEmitter {
    char active;      // +0x04
    char unknown6;    // +0x06
    byte flags;       // +0x08
    char field26;     // +0x0E? Wait offset 0x26
    char index2d;     // +0x2D? Actually used as byte at +0x2D in some struct
    int float30;      // +0x30
    int float34;      // +0x34
    short field3c;    // +0x3C
    short field40;    // +0x40
    short field42;    // +0x42
    void* somePtr;    // +0x50
    int field60;      // +0x60
    int field64;      // +0x64 // array of ints? accessed with index
};

extern int g_soundSystemToggle;  // DAT_011da800
extern int g_musicSystemToggle;  // DAT_011da804
extern void* g_engine;           // DAT_01205750

void EffectManager::updateSounds(uint this_ptr) {
    int count;
    int* arrayBase;
    int index;
    int* current;
    int emitterPtr;
    double local_24_low, local_24_high; // from double at +0xB0
    double local_c_low, local_c_high;   // from double at +0xC8

    // Extract fields
    int field4 = *(int*)(this_ptr + 4);
    double valueB0 = *(double*)(this_ptr + 0xB0); // double
    double valueC0 = *(double*)(this_ptr + 0xC0); // double
    double valueC8 = *(double*)(this_ptr + 0xC8); // double
    float valueAC = *(float*)(this_ptr + 0xAC);

    // Complex condition check
    bool leftCond = false;
    if ((0.0 <= valueAC * (float)valueB0) || 
        ((float)valueC0 != 0.0f) || 
        ((float)valueC8 != 0.0f) || 
        ((float)((ulonglong)valueC8 >> 32) != 0.0f)) {
        leftCond = true;
    }

    // Right condition
    bool rightCond = ((float)((ulonglong)valueB0 >> 32) >= 0.0f) && (2 < field4);

    if (leftCond && rightCond) {
        FUN_004c5da0(); // presumably setup/reset

        index = 0;
        count = *(int*)(this_ptr + 0xA0);
        arrayBase = (int*)*(int*)(this_ptr + 0xA4);

        if (count != 0) {
            for (int i = 0; i < count; i++) {
                current = (int*)(arrayBase + index); // each element 0x1C bytes
                emitterPtr = *(int*)((int)arrayBase + 4 + index); //? Actually: *(int*)(*arrayBase + 4 + index) but the decompiler uses iVar2.

                // Re-read from decompiler:
                // iVar1 = *(int*)(*(int*)(iVar2 + 0xa4) + 4 + iVar3);
                // piVar4 = (int*)(*(int*)(iVar2 + 0xa4) + iVar3);
                // So we have: base = *(int*)(this_ptr+0xA4)
                // then itemPtr = *(int*)(base + 4 + index)
                // and current = base + index (but index increments by 0x1C)
                // Actually index is iVar3, which increments by 0x1C each loop.
                // piVar4 = (int*)(base + iVar3)  (pointer to the ith element's beginning)
                // iVar1 = *(int*)(base + 4 + iVar3) -> that's the actual emitter pointer stored at offset 4 within the element?
                // Wait, let's parse step by step.

                // From decompiler:
                // piVar4 = (int *)(*(int *)(iVar2 + 0xa4) + iVar3); -> piVar4 points to start of current element in array
                // iVar1 = *(int *)(*(int *)(iVar2 + 0xa4) + 4 + iVar3); -> iVar1 is the value at offset 4 within that element (since base + iVar3 + 4)
                // So each element is an int (4 bytes?) No, iVar3 increments by 0x1C, so element size is 0x1C (28 bytes).
                // At offset 0 from element start: some int (not used here)
                // At offset 4: a pointer to an emitter (iVar1)
                // So structure: struct ArrayElement { int unknown; int* emitterPtr; ... other fields up to 0x1C }

                // Therefore:
                int elementStart = (int)(base + iVar3);
                int* emitterPtrAddr = (int*)(elementStart + 4);
                emitterPtr = *emitterPtrAddr;
                // piVar4 = (int*)elementStart;

                if ((*(char*)(emitterPtr + 4) == '\x01') && (*(char*)(emitterPtr + 6) != '\0') &&
                    ((*(byte*)(emitterPtr + 8) & 0x10) == 0) &&
                    (((*(byte*)(elementStart + 0xB2) & 1) != 0) && (*(int*)(this_ptr + 8) == *(int*)(this_ptr + 4)))) {
                    
                    FUN_00613b40(*(int*)(this_ptr + 0x94)); // get some handle

                    FUN_004c5d70(); // some prepare

                    int soundIndex1 = *(int*)(emitterPtr + 0x64 + (uint)*(byte*)(*(int*)(emitterPtr + 0x50) + 0x2D) * 4);
                    char param2 = *(char*)(emitterPtr + 0x26);
                    FUN_0060c8d0(0, soundIndex1, param2, 0, 0, 0, 1); // play sound 1

                    int soundIndex2 = *(int*)(elementStart + 5 + (*(int*)(this_ptr + 8) & 1) * 4); // piVar4[(field8 & 1) + 5]
                    FUN_0060c8d0(1, soundIndex2, 0x0C, 0, 0, 0, 1); // play sound 2

                    FUN_0060cb70(*(short*)(emitterPtr + 0x3C), *(int*)(emitterPtr + 0x60),
                                 *(int*)(emitterPtr + 0x34), *(int*)(emitterPtr + 0x30),
                                 *(short*)(emitterPtr + 0x40), *(short*)(emitterPtr + 0x42)); // set position/parameters
                }
                iVar3 += 0x1C;
            }
        }

        // Global toggles
        if (g_soundSystemToggle != 1) {
            (**(code**)(*(int*)g_engine + 0x198))(g_engine, 1, 1);
            g_soundSystemToggle = 1;
        }
        if (g_musicSystemToggle != 0) {
            (**(code**)(*(int*)g_engine + 400))(g_engine, 1, 0, 0, 0);
            g_musicSystemToggle = 0;
        }
    }
}

// Note: The above uses simplified variable names and assumes structures.
// The decompiled code had some complex double/float conversions which are approximated.
// FUN_004c5da0, FUN_004c5d70, etc., are placeholder names.
// The loop increment and array access are reconstructed to match the original logic.