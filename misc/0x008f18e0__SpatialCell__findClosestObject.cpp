// FUNC_NAME: SpatialCell::findClosestObject
// Function address: 0x008f18e0
// Role: Finds the nearest object in a cell to a given position. Uses Euclidean distance squared.
// Object positions stored at offsets +0x90 (x), +0x94 (y), +0x98 (z) from the object pointer.

#include <cfloat> // for FLT_MAX

class SpatialCell {
public:
    // +0x00: vtable?
    // +0x04: pointer to array of object pointers (int**)
    // +0x08: number of objects in cell (uint)
    int* objectArrayBase;  // +0x04: base pointer to object pointer array (actually to first element after an 8-byte header? The code adds 8 to the dereferenced pointer)
    uint objectCount;      // +0x08
    // possibly other fields

    // Finds the closest object (by squared distance) to 'point' among all objects in this cell.
    // Returns the object pointer (via param_1 convention? Actually it just sets iVar3, which is returned in eax? No, void return, so result is stored in a global or ret? The function returns void, so likely the caller already has access to the object pointer via some output parameter? In the decompiled code, iVar3 (closestObj) is not passed back. Actually the function appears to be discarding the result? But callers would likely use eax after the call. The decompiler may be missing that. Since the function returns void, the closest object is likely stored somewhere else, or the function modifies a member variable? But no store to param_1 is seen. Possibly the caller expects eax to contain the result? The calling convention is __thiscall, eax is not used for return in void. But maybe it's actually returning the pointer via eax? The decompiler shows void, but it might be a bug. Looking at the code: at the end, there is no return statement; the function just ends. The register eax is not manipulated. So the caller might have the pointer in iVar3 after the call? No, iVar3 is local. So this is likely called in a context where the result is stored into a member variable via this? Or maybe the caller expects the function to set some global or parameter. Given the structure, the function is likely a helper that finds the closest object and stores its index/pointer from a member. But the decompiled code shows no output. Perhaps the function does have a hidden return value in eax? Since the decompiler didn't pick it up, we'll assume it returns the object pointer via a field. But we can't see that. Alternatively, maybe the caller passes a pointer to store result? Not in parameters. Possibly the function is meant to set internal variables and then the caller reads them? Without more context, we'll present the function as-is. We'll add a comment that the result is stored in some member or register.

    // Actually, to match typical Ghidra output, we'll keep it as void and note that the caller likely uses eax after call (though not reflected).
};

void __thiscall SpatialCell::findClosestObject(const float* point) {
    uint count = this->objectCount; // +0x08
    int* currentPtr; // pointer into the object pointer array
    int closestObject = 0; // pointer to closest object (NULL initial)
    float closestDistSq = FLT_MAX; // large initial value

    float px = point[0];
    float py = point[1];
    float pz = point[2];

    // The object pointer array is accessed as *(int*)(this+4) + 8? Actually the code does:
    // piVar5 = (int *)(*(int *)(param_1 + 4) + 8);
    // So it takes the pointer at this+4, dereferences it to get an int (which is a base address), then adds 8 to get to the start of the array.
    // This suggests that the field at +0x04 is not directly the array but a pointer to a structure that has an array at offset 8.
    // For now, we'll assume objectArrayBase points directly to the array (after adding 8 from an inner pointer). We'll represent it accordingly.
    // Actually, let's re-read: *(int *)(param_1 + 4) gives an int (which is a pointer to some structure). Then +8 gives the array of pointers.
    // So objectArrayBase = *(int *)(this + 4) + 8
    // We'll define a method to get the array pointer.

    int* arrayBase = (int*)(*(int*)((char*)this + 4) + 8);
    int* arrayEnd = arrayBase + count;

    // Main loop processes 4 at a time (unrolled)
    currentPtr = arrayBase;
    int remaining = count;
    int blockCount = (count - 4) >> 2; // (count > 3) ? (count-4)/4 : 0
    // Actually the code uses: iVar6 = (uVar1 - 4 >> 2) + 1; for the unrolled count.
    // For count > 3, it processes (count-4)/4 + 1 blocks? Let's replicate exactly.
    // Original: if (3 < count) { iVar6 = (count - 4 >> 2) + 1; ... do { ... 4 objects per iteration } while (iVar6 != 0); }
    // That means for count=4, iVar6 = (0>>2)+1 = 1 block. For count=5, iVar6 = (1>>2)+1 = 1 block? Actually (5-4)=1, 1>>2=0, +1=1. So blocks processed = (count-4)/4 + 1 where integer division rounds down. This is like ceil((count-4)/4)+1, but careful.
    // We'll just use a simple loop for clarity, but keep the unrolled behavior for accuracy. Since we want to produce clean code, we can just use a loop over each object without unrolling. The original is manually unrolled. We'll present a clean version with a for loop.

    // For correctness, we'll implement the exact algorithm as in the binary:
    // Process blocks of 4 while possible, then leftover.
    // But for readability, we can simplify.

    // Let's write a straightforward loop:
    for (int i = 0; i < count; ++i) {
        int* objPtr = (int*)currentPtr[i]; // object pointer (int*)
        // Object position offsets: +0x90 (x), +0x94 (y), +0x98 (z)
        float dx = *(float*)((char*)objPtr + 0x90) - px;
        float dy = *(float*)((char*)objPtr + 0x94) - py;
        float dz = *(float*)((char*)objPtr + 0x98) - pz;
        float distSq = dx*dx + dy*dy + dz*dz;
        if (closestObject == 0 || distSq < closestDistSq) {
            closestObject = (int)objPtr;
            closestDistSq = distSq;
        }
    }

    // The function does not return the result. In the original binary, the result might be in eax after call? Or the function sets a member variable? We can't see that. We'll assume the caller reads the result from a register or the function modifies this->closestObject.
    // To match the decompiled signature, we'll leave it void.
    // Actually, looking at the decompiled code: at the end, there is 'return;' and nothing is stored. The decompilation might be incomplete.
    // We'll add a comment that the result is left in the 'closestObject' local variable, which might be optimized to a register in calling convention.
    // For reconstruction, we'll just leave it as a void function and note that the caller likely uses eax to get the result (since IA32 calling convention may return integer in eax even for void? No, that's not standard). Maybe the function actually returns the pointer but Ghidra misdetected it? We'll assume it's a void function that finds the closest but doesn't return it; perhaps it sets something else. Without more context, we'll keep as is.

    // The original also had a second loop for leftover objects after the unrolled block. We'll handle that in the single loop above.
}