//FUNC_NAME: generateObjectDebugIdentifier
void generateObjectDebugIdentifier(void* debugOutput, void* debugContext, void* objectPtr)
{
    ushort counter = 0;
    // Check if debug output is enabled (global flag at offset 0xc from some base)
    if (*(int*)(DAT_01223484 + 0xc) == 0) {
        // Attempt to get a counter from the object's internal data
        if (objectPtr != 0) {
            void* internalData = FUN_006b0ee0(objectPtr); // likely getObjectInternalData
            if (internalData != 0) {
                counter = *(short*)((int)internalData + 0xc4) + 1; // increment counter at +0xC4
            }
            // Check if object type matches a specific hash (0x637b907)
            if (FUN_006b0f50(objectPtr) == 0x637b907) {
                counter |= 0x8000; // set high bit to indicate special type
            }
        }
        // Format the identifier as object pointer (8 hex digits) and counter (4 hex digits)
        char buffer[16];
        __snprintf(buffer, 0x10, "%08X%04X", objectPtr, counter);
        buffer[15] = 0; // ensure null termination (though snprintf already does)
        // Call a virtual method on the debug output object (vtable offset 0x14)
        (**(code**)(*(int*)DAT_012234e0 + 0x14))(debugOutput, debugContext, buffer);
    }
}