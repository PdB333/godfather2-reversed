// FUNC_NAME: ObjectManager::registerObject
void __thiscall ObjectManager::registerObject(int thisPtr, int value) {
    // Store the value in member at offset +0x30
    *(int *)(thisPtr + 0x30) = value;

    // Global list management: DAT_01206880 is likely a static allocation manager
    // Get pointer to the current insertion point (at global+0x14)
    uint *currentPtr = (uint *)(DAT_01206880 + 0x14);

    // Write a vtable/type identifier at the current allocation slot
    **(int **)(DAT_01206880 + 0x14) = (int)&PTR_LAB_01123c74;

    // Advance pointer by 4 bytes (size of a pointer)
    *currentPtr = *currentPtr + 4;

    // Align to 4-byte boundary
    int *alignedPtr = (int *)((*currentPtr + 3) & 0xfffffffc);
    *currentPtr = (uint)alignedPtr;

    // Store the actual value in the aligned slot
    *alignedPtr = value;

    // Advance pointer again for next allocation
    *currentPtr = *currentPtr + 4;
}