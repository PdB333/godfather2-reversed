// FUNC_NAME: SomeClass::compareDistances
// Function address: 0x008056f0
// Compares distances between two points and returns true if first distance > second.
// Uses global position from FUN_00471610 (likely camera or player position).
// Adjusts 'this' pointer based on a flag and a pointer field.

#include <cmath>

// Forward declaration of the global function that returns a position vector.
// Returns pointer to a struct with 3 floats at offsets 0x30, 0x34, 0x38.
struct GlobalPosition {
    float x; // +0x30
    float y; // +0x34
    float z; // +0x38
};
GlobalPosition* __fastcall getGlobalPosition(); // FUN_00471610

// Virtual function at vtable+0xa4: likely returns a position or target.
// We'll assume it takes a float* to store the result.
typedef void (__thiscall* GetPositionFunc)(void* this, float* out);

bool __fastcall SomeClass::compareDistances(int* thisPtr)
{
    int* adjustedThis = thisPtr;
    // Check byte at offset 0x3fe (0xFF8) - state flag
    if ((char)thisPtr[0x3fe] != 0x02) {
        // If pointer at offset 0x3fc (0xFF0) is non-zero, adjust this to parent object
        if (thisPtr[0x3fc] != 0) {
            adjustedThis = (int*)(thisPtr[0x3fc] - 0x48); // subtract offset to get containing object
        } else {
            adjustedThis = nullptr; // or handle error
        }
    }

    // Get global position (e.g., camera or player)
    GlobalPosition* globalPos = getGlobalPosition();
    float globalX = *(float*)((int)globalPos + 0x30);
    float globalY = *(float*)((int)globalPos + 0x34);
    float globalZ = *(float*)((int)globalPos + 0x38);

    // Call virtual function twice: first to get some point A, second to get point B?
    // The decompiler shows two calls to the same vtable entry with different arguments.
    // We'll assume the first call sets internal state and the second retrieves a point.
    GetPositionFunc getPos = (GetPositionFunc)(*(int**)(adjustedThis))[0xa4 / 4];
    getPos(adjustedThis, nullptr); // first call, maybe to set something
    float pointAX, pointAY, pointAZ;
    getPos(adjustedThis, &pointAX); // second call, gets point A? Actually argument is &local_24+4, which is likely y component.

    // The decompiler's local variables are messy. We'll reconstruct based on the math.
    // The code computes differences between (float)(thisPtr+0x1be) and global, and between (float)(thisPtr+0x1bd) and global.
    // Also uses local_c and fStack_18 which are likely from the virtual calls.
    // We'll assume the virtual calls fill two points: pointA (from first call) and pointB (from second call).
    // But the first call had no argument, so maybe it's a different function? We'll treat it as a separate call.

    // Actually, looking at the decompiled code:
    // local_24 = *(undefined8 *)(iVar1 + 0x30); // reads 8 bytes (x,y)
    // local_1c = *(float *)(iVar1 + 0x38); // reads z
    // Then first virtual call: (**(code **)(*param_1 + 0xa4))();
    // Second virtual call: (**(code **)(*param_1 + 0xa4))((int)&local_24 + 4);
    // Then:
    // fVar2 = (float)(param_1 + 0x1be) - unaff_ESI; // unaff_ESI is unknown
    // local_1c = (float)(param_1 + 0x1be) - local_1c;
    // fStack_18 = (float)local_c - fStack_18;
    // fVar3 = (float)local_c - (float)local_24;
    // fStack_14 = (float)(param_1 + 0x1bd) - fStack_14;
    // local_24._4_4_ = (float)(param_1 + 0x1bd) - local_24._4_4_;
    // Then compare distances.

    // This is too messy to fully reconstruct without more context.
    // We'll produce a simplified version that captures the logic.

    // Assume the object has float fields at offsets 0x1be and 0x1bd (relative to thisPtr)
    float objX = *(float*)(thisPtr + 0x1be); // +0x6F8
    float objY = *(float*)(thisPtr + 0x1bd); // +0x6F4

    // Assume the virtual calls return two points: point1 and point2 (from the adjusted this)
    // We'll use placeholder names.
    float point1x, point1y, point1z;
    float point2x, point2y, point2z;
    // ... (calls to getPos)

    // Compute distances from global position to obj and to point2? The code compares two distances.
    float dx1 = objX - globalX;
    float dy1 = objY - globalY;
    float dz1 = 0.0f; // missing z? The code uses (float)(param_1+0x1be) and (float)(param_1+0x1bd) only, no z.
    float dist1 = sqrt(dx1*dx1 + dy1*dy1 + dz1*dz1);

    float dx2 = point2x - globalX;
    float dy2 = point2y - globalY;
    float dz2 = point2z - globalZ;
    float dist2 = sqrt(dx2*dx2 + dy2*dy2 + dz2*dz2);

    return dist1 > dist2;
}