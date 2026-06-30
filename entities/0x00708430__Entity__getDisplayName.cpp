// FUNC_NAME: Entity::getDisplayName
// Address: 0x00708430
// Role: Retrieves a localized display name string handle for this entity.
//       Checks a compact string ID (4 ints at offsets 0x254-0x260) for sentinel values.
//       If not sentinel, resolves the ID to a string; otherwise falls back to default name.

int __thiscall Entity::getDisplayName(unsigned int* outStringHandle)
{
    int resolvedInfo;
    unsigned int stringHandle;

    // Check if the 4 compact string ID fields are all sentinel values (indicating no compact string)
    if ((*(int*)(this + 0x254) != -0x45245246) ||     // +0x254 compactId[0]
        (*(int*)(this + 0x258) != -0x41104111) ||     // +0x258 compactId[1]
        (*(int*)(this + 0x25c) != -0x153ea5ab) ||     // +0x25c compactId[2]
        (*(int*)(this + 0x260) != -0x6eeff6ef)) {     // +0x260 compactId[3]
        // Attempt to resolve the compact string ID (param2=0 indicates default resolution)
        resolvedInfo = FUN_004461c0(this + 0x254, 0); // ResolveCompactStringId
        if (resolvedInfo != 0) {
            stringHandle = FUN_004058a0(*(unsigned int*)(resolvedInfo + 8)); // GetStringFromResource
            stringHandle = FUN_004dafd0(stringHandle); // Possibly copy or get wide string
            *outStringHandle = stringHandle;
            return 1; // Success using compact ID
        }
    }
    // Fallback: get default name (e.g., object name or class name)
    stringHandle = FUN_00472730(outStringHandle); // GetDefaultName
    return stringHandle; // Returns 0 or 1 based on success
}