// FUNC_NAME: UIReticle::updateScreenPosition

void __thiscall UIReticle::updateScreenPosition(int *this) // this is unaff_ESI in decomp
{
    float scaleFactor;
    int *resourcePtr;
    int *oldResourcePtr;
    int *newResourcePtr;
    int *someResource;
    int resourceID;
    undefined matrix1[16]; // 4x4 float matrix? (16 bytes)
    undefined matrix2[16];
    undefined transformData[76]; // possibly matrices + vectors

    // First call: some initialization or update
    FUN_005d0580(this, this); // likely base class method or utility

    resourceID = DAT_01205668 + 0x10; // global + 0x10 -> probably camera/rendering context
    this[7] = 1; // flag at offset 0x1c (int)

    // Get resource pointer from ID stored at this[0] (offset 0x00)
    someResource = (int *)FUN_005ce530(this[0]);

    // Compute screen position using camera matrices and resource data
    FUN_005ced60(resourceID, someResource, matrix1, matrix2, transformData, 0, 0, 0, 0, 1);

    // Reference counting / smart pointer logic
    newResourcePtr = (int *)*someResource;
    if (newResourcePtr != (int *)this[0]) {
        oldResourcePtr = (int *)this[0];
        if (oldResourcePtr != newResourcePtr) {
            this[0] = (int)newResourcePtr;
            if (newResourcePtr != 0) {
                // call AddRef on new
                (**(code **)*newResourcePtr)(); // vtable[0] likely AddRef
            }
            if (oldResourcePtr != 0) {
                // call Release on old
                (**(code **)(*oldResourcePtr + 4))(); // vtable[1] likely Release
            }
        }
    }

    // Compute screen position from resource data
    scaleFactor = *(float *)(*someResource + 0xc); // scaling factor at resource + 0x0C
    // SomeResource[4] and [5] are ints (screen coordinates) scaled by scaleFactor
    *(float *)((int)this + 0x48) = (float)someResource[4] * scaleFactor; // screenX
    *(float *)((int)this + 0x4c) = (float)someResource[5] * scaleFactor; // screenY

    return;
}