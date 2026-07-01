// FUNC_NAME: Entity::GetNameString (address: 0x0095d130)
// Role: Retrieves the entity's name string and copies it into a buffer with format flags.
// Offsets: +0x18 = char* mName (name string pointer)
// Callees: FUN_00603d30 (GetNameInternal), FUN_005c4660 (StringCopyWithFormat)
void __thiscall Entity::GetNameString(char* outBuffer, int bufferSize)
{
    char* nameString = (char*)0x0;
    int formatFlags = 0;
    // local_8 and local_4 are unused in decompiled output but present as stack vars
    // local_4 = 0 originally, likely a bug in decompilation; omitted.

    nameString = GetNameInternal(*(undefined4*)(this + 0x18), 1); // Fetch name with flag 1
    char* src = nameString;
    if (nameString == (char*)0x0) {
        src = (char*)0x0120546e; // Default name string
    }
    StringCopyWithFormat(outBuffer, src, bufferSize, formatFlags); // 0 flags means plain copy
    if (nameString != (char*)0x0) {
        // Note: Original had (*local_4)(nameString), but local_4 was null.
        // This appears to be a decompiler artifact or dead code; omitted.
    }
    return;
}