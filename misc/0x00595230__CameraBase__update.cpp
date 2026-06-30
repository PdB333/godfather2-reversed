// FUNC_NAME: CameraBase::update
void __thiscall CameraBase::update(CameraBase* this) {
    byte* pByteVar1;
    char cVar2;
    int* thisPtr = reinterpret_cast<int*>(this); // ESI
    undefined4 local_50;
    undefined4 local_4c;
    undefined4 local_48;
    undefined4* local_44;
    undefined4 local_3c;
    undefined4 local_38;
    undefined4 local_34;
    undefined4 local_30[11];

    // Setup stack locals
    local_44 = reinterpret_cast<undefined4*>(this);
    local_48 = 0x59524c; // constant? maybe an identifier
    // Call unknown sub-function (likely initializes something)
    subFunctionA();

    // Reassign pointer for next operation
    local_44 = &local_3c;
    local_48 = 0x595256; // another constant
    cVar2 = subFunctionB();
    if (cVar2 == '\0') {
        // Clear bit 8 (0x100) at offset 0x7C (0x1F * 4)
        thisPtr[0x1F] = thisPtr[0x1F] & 0xFFFFFEFF;
    } else {
        // Set bit 8 at offset 0x7C
        thisPtr[0x1F] = thisPtr[0x1F] | 0x100;
    }

    // Build a math/transform structure from local variables
    local_44 = local_30; // point to local_30 array
    local_48 = 0x3F800000; // 1.0f as float
    local_4c = local_34;   // some x component
    local_50 = local_38;   // some y component
    // Call a function on the global math singleton: offset 0x04 = "setIdentity"?
    (**(code**)(*g_mathSingleton + 4))(local_3c);

    // Access pointer at this+0x14 (5 * 4)
    pByteVar1 = reinterpret_cast<byte*>(thisPtr[5]);
    if ((pByteVar1 != NULL) && ((*pByteVar1 & 4) != 0)) {
        // Perform transformation: offset 0x18 = "multiply", offset 0x10 = "store"?
        (**(code**)(*g_mathSingleton + 0x18))(&local_44, pByteVar1 + 0x10, &local_34);
        (**(code**)(*g_mathSingleton + 0x10))(&local_34, &local_50);
    }

    // Call virtual function at vtable offset 0x48 (e.g., "updateView")
    (**(code**)(*thisPtr + 0x48))(&local_44);

    // If the bit at offset 0x7C is set, call another virtual function at offset 0x3C
    if ((thisPtr[0x1F] & 0x100U) != 0) {
        (**(code**)(*thisPtr + 0x3C))();
    }
    return;
}