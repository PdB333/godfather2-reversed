// FUNC_NAME: SharedPtr::SharedPtr
// Function address: 0x005e0170
// Role: Constructor for a ref-counted smart pointer (EA EARS engine style)
// Takes an internal object pointer (param_2) and an optional handle (param_3)
// Manages reference counting via vtable calls at offsets +0x04, +0x08, +0x0C

int SharedPtr_constructor(int thisPtr, int *internalObj, int handle)
{
    int uVar1;
    int *piVar2;
    
    piVar2 = internalObj;
    // Call addRef on internal object (vtable[2] = offset 0x08)
    (**(code **)(*internalObj + 8))(internalObj);
    if (handle == 0) {
        uVar1 = 0;
    } else {
        // Duplicate the handle (FUN_004265d0 - likely returns a new reference)
        uVar1 = duplicateHandle(handle, piVar2);
    }
    // Attach the internal object with the (possibly null) handle
    attachInternal(piVar2, uVar1); // FUN_005e0b60
    
    // Store the internal pointer at offset 0x14
    *(int **)(thisPtr + 0x14) = internalObj;
    // Second addRef call (maybe for separate ref count)
    (**(code **)(*internalObj + 8))();
    if (handle != 0) {
        uVar1 = duplicateHandle(handle, *(undefined4 *)(thisPtr + 0x14));
        // Store duplicated handle at offset 0x18
        *(undefined4 *)(thisPtr + 0x18) = uVar1;
        // Call release on internal object (vtable[1] = offset 0x04)
        (**(code **)(*internalObj + 4))(handle, 0);
        // Call finalize (vtable[3] = offset 0x0C)
        (**(code **)(*internalObj + 0xc))();
        return thisPtr;
    }
    // No handle: store 0 at offset 0x18 and finalize
    *(undefined4 *)(thisPtr + 0x18) = 0;
    (**(code **)(*internalObj + 0xc))();
    return thisPtr;
}