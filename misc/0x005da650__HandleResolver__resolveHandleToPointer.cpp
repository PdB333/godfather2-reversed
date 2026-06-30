// FUNC_NAME: HandleResolver::resolveHandleToPointer
// Address: 0x005da650
// Role: Converts a handle (presumably a pointer into a pool of 0x28-byte objects) into a pointer to the containing object.
//       The handle's low byte is masked off for alignment. The function relies on caller-provided values in EAX and EDI
//       (likely a base address and an offset) to compute the final pointer.
//       It also calls FUN_005da9c0 as a validation/init step.

class HandleResolver {
public:
    // Parameters: handle - the raw handle (pointer-like value)
    //             eaxReg - value passed in EAX by caller (likely an offset or secondary pointer)
    //             ediReg - value passed in EDI by caller (likely a base pointer)
    // Note: This function uses a non-standard calling convention; eaxReg and ediReg are not on the stack.
    static int resolveHandleToPointer(uint handle, int eaxReg, int ediReg);
};

int HandleResolver::resolveHandleToPointer(uint handle, int eaxReg, int ediReg)
{
    uint originalHandle = handle;
    // Mask off lower 8 bits to align to 256-byte boundary (e.g., pool block alignment)
    uint alignedHandle = handle & 0xffffff00;

    // Call validation function with original, masked handle, 0, and masked handle again
    FUN_005da9c0(originalHandle, alignedHandle, 0, alignedHandle);

    // Compute pointer: base (ediReg) + ((offset (eaxReg) - originalHandle) / 0x28) * 0x28
    // 0x28 = 40 bytes, likely the size of objects in the pool.
    // This computes the aligned object base by finding the nearest multiple of 0x28 below the difference.
    return ediReg + ((eaxReg - originalHandle) / 0x28) * 0x28;
}