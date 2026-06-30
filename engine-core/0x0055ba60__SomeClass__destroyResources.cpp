// FUNC_NAME: SomeClass::destroyResources
void __thiscall SomeClass::destroyResources() // addr 0x55ba60
{
    // Offset +0x484: flag indicating resources have been destroyed (set to 1)
    this->m_destroyed = 1;

    // +0x710 to +0x71c: four resource pointers (could be child objects or handles)
    int* resourcePtrs[4];
    resourcePtrs[0] = this->m_resource0; // +0x710
    resourcePtrs[1] = this->m_resource1; // +0x714
    resourcePtrs[2] = this->m_resource2; // +0x718
    resourcePtrs[3] = this->m_resource3; // +0x71c

    // Global memory pool/stack pointer at DAT_01206880 + 0x14
    // Each resource is "pushed" as a record onto this pool for deferred cleanup
    for (int i = 0; i < 4; i++)
    {
        if (resourcePtrs[i] != 0)
        {
            // Get the current top of the memory pool stack
            uint* stackPtr = (uint*)(*(int*)(DAT_01206880 + 0x14));
            // Write a type descriptor (vtable/function pointer) to the stack
            *(int**)stackPtr = &PTR_LAB_01124690; // likely type info for cleanup
            stackPtr++; // advance 4 bytes

            // Store the resource pointer
            *stackPtr = (int)resourcePtrs[i];
            stackPtr++;

            // Store the identity of the owner (address of some member at +0x54)
            *stackPtr = (int)(&this->field_0x54);
            stackPtr++;

            // Write a zero byte (padding or flag)
            *(byte*)stackPtr = 0;
            stackPtr = (uint*)(((uint)stackPtr + 4) & 0xFFFFFFFC); // align to 4 bytes

            // Update the global stack pointer
            *(int*)(DAT_01206880 + 0x14) = (int)stackPtr;
        }
    }
}