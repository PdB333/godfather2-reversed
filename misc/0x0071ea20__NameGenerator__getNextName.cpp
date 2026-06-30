// FUNC_NAME: NameGenerator::getNextName
void __thiscall NameGenerator::getNextName(int thisPtr, int nameTypeIndex, undefined4 textTarget)
{
    byte currentCount;
    byte maxCount;
    byte newCount;
    undefined1 *nameString;
    undefined1 *localStringPtr;
    undefined4 resultHandle;

    // Load the name list from the string table (base + typeIndex * 4)
    // The string table is at 0x00d61f04, each entry is a pointer to a string like "lw_irish_firstname_m_*"
    FUN_004d3bc0((&PTR_s_lw_irish_firstname_m__00d61f04)[nameTypeIndex]);

    // Get current usage count for this name type (offset from thisPtr by nameTypeIndex + 4)
    currentCount = *(byte *)(nameTypeIndex + 4 + thisPtr);
    // Get max count per name type from array at 0x00d61efc
    maxCount = (&DAT_00d61efc)[nameTypeIndex];

    // Increment count, wrapping to 0 if at max
    newCount = currentCount + 1;
    *(byte *)(nameTypeIndex + 4 + thisPtr) = newCount;
    if (maxCount <= newCount) {
        *(undefined1 *)(nameTypeIndex + 4 + thisPtr) = 0;
    }

    // Generate a localized string using a format string at 0x00e325c4 (e.g., "%d" or something)
    // The new count is used as an index into the name list
    FUN_004d4b00(local_10, &DAT_00e325c4, currentCount + 1);
    localStringPtr = local_10[0];
    if (localStringPtr == (undefined1 *)0x0) {
        localStringPtr = &DAT_0120546e; // fallback string
    }
    resultHandle = FUN_004dafd0(localStringPtr); // load string from resource
    FUN_00603330(resultHandle, textTarget); // set text on target (likely UI widget)

    if (local_10[0] != (undefined1 *)0x0) {
        // Call destructor on temp string object via function pointer at local_4
        (*(code *)local_4)(local_10[0]);
    }
    return;
}