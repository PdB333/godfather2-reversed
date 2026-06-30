// FUNC_NAME: AccumulateBlendWeight

/**
 * Address: 0x0050be90
 * Role: Adds a scaled weight to a float element in a per-thread attribute array.
 * The array base is computed from TLS (fs:0x2c) plus an offset stored in *baseOffset.
 * The scale factor is read from config->pointerAt0x28->floatAt0x68.
 * Called by FUN_00510110 in a loop for each element of an array (index in eax, multiplier in xmm1).
 */

#include <windows.h> // for __readfsdword

void AccumulateBlendWeight(
    void* config,          // stack parameter: pointer to a config structure
    int index,             // register: eax (index into array)
    float multiplier,      // register: xmm1
    int* baseOffset        // register: esi (pointer to an integer offset)
)
{
    // Get thread-local base from TEB at fs:[0x2c] +8
    int** tlsPtr = (int**)__readfsdword(0x2c);
    int* objectArray = (int*)(*(tlsPtr + 2)); // +8 is +2 ints
    int* objectBase = (int*)((char*)objectArray + *baseOffset);

    // Target float: offset 0x44 + index * 0x50 (struct size 0x50)
    float* target = (float*)((char*)objectBase + 0x44 + index * 0x50);

    // Source scale: config->ptrAt0x28->floatAt0x68
    float* source = (float*)(*(int*)((char*)config + 0x28) + 0x68);

    // Accumulate
    *target += *source * multiplier;
}