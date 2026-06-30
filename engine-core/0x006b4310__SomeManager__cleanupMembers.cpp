// FUNC_NAME: SomeManager::cleanupMembers
void __thiscall SomeManager::cleanupMembers(int thisPtr)
{
    // Cleanup four sub-objects at specific offsets within this class
    FUN_006b2dc0(thisPtr + 0x84); // +0x84: first sub-object (e.g., component list)
    FUN_006b2dc0(thisPtr + 0x9c); // +0x9c: second sub-object
    FUN_006b2dc0(thisPtr + 0xa8); // +0xa8: third sub-object
    FUN_006b2dc0(thisPtr + 0xb4); // +0xb4: fourth sub-object
    return;
}