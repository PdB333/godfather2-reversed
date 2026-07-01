//FUNC_NAME: SomeClass::processData
// Function address: 0x007a9330
// Role: Copies data from external source into internal buffer at +0x10, then processes a pointer stored at +0x20 with a 32-byte operation.

void __thiscall SomeClass::processData(void* param_2) {
    // Copy data from param_2 into the internal buffer at this+0x10
    // FUN_004a9cf0 is likely a memory copy or assignment function (dest = this+0x10, src = param_2)
    FUN_004a9cf0(param_2, this + 0x10); // +0x10: internal buffer (size unknown)

    // Read a pointer from this+0x20 and pass it to a processing function with size 0x20
    // Note: The decompiler shows &param_2, but param_2 is overwritten with the value at this+0x20.
    // This suggests param_2 is reused as a local variable to hold the pointer.
    param_2 = *(void**)(this + 0x20); // +0x20: pointer to a 32-byte buffer
    FUN_0064b810(0x20, &param_2); // Process the buffer (likely a hash, encryption, or validation)
}