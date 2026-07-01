// FUNC_NAME: Entity::GetNameCopy

// 0x0095d020 - Copies the entity's internal name string to a buffer (max 128 chars).
// Uses a global default string if the internal name is null.
void __thiscall Entity::GetNameCopy(int this, char* destBuffer)
{
    char* internalName = nullptr;
    int nameLength = 0;
    int unused = 0;
    void (*nameDeleter)(char*) = nullptr;

    // Retrieve internal name pointer via engine string table (handle at this+0x08)
    getInternalString(*(int*)(this + 8), &internalName, 1);

    char* source = internalName;
    if (internalName == nullptr) {
        source = (char*)0x0120546e; // Default name string constant
    }

    // Safe copy to destination buffer (max 0x80 = 128 chars)
    safeStringCopy(destBuffer, source, 0x80, nameLength);

    // Free dynamically allocated internal name if it exists and deleter is set
    if (internalName != nullptr) {
        if (nameDeleter != nullptr) {
            nameDeleter(internalName);
        }
    }
}