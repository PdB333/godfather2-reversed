// FUNC_NAME: Actor::releaseChildObject
void __fastcall Actor::releaseChildObject(int thisPtr)
{
    int childObjPtr;
    int innerPtr;

    // Check if child object pointer (at offset 0x36C) is not null
    if (*(int*)(thisPtr + 0x36C) != 0) {
        // Get pointer at child+0x14 (some owned resource or sub-object)
        childObjPtr = *(int*)(thisPtr + 0x36C);
        innerPtr = *(int*)(childObjPtr + 0x14);
        if (innerPtr != 0) {
            // Release inner resource (e.g., sound handle, texture)
            FUN_004cb8a0(innerPtr);
        }
        // Notify global manager (singleton callback) if present
        if (DAT_0122344c != (int*)0x0) {
            // Call the function stored at first field of global manager
            (**(code**)*DAT_0122344c)(1);
        }
    }
    // Clear child object pointer and two other fields (possibly vtable/ref count)
    *(int*)(thisPtr + 0x36C) = 0;
    *(int*)(thisPtr + 8) = 0;
    *(int*)(thisPtr + 0xC) = 0;
}