// FUNC_NAME: Entity::getFloatAttribute
// Address: 0x004aabd0
// Fetches a float value from a global table indexed by this entity's attribute offset (stored at +0x18).
// The global table is accessed via thread-local storage (FS:[0x2C]), which holds a pointer to per-thread game data.
float __fastcall Entity::getFloatAttribute() const
{
    // FS:[0x2C] points to a per-thread structure containing a pointer to the game data singleton.
    uintptr_t tlsValue = __readfsdword(0x2C);
    // Dereference once to get the game data pointer.
    // Then dereference at offset +0x08 to get the base of the float attribute table.
    uintptr_t gameDataPtr = *reinterpret_cast<uintptr_t*>(tlsValue);
    uintptr_t floatTable  = *reinterpret_cast<uintptr_t*>(gameDataPtr + 8);
    // Retrieve the byte offset stored in the entity at +0x18 (e.g., an attribute index).
    int attributeOffset = *reinterpret_cast<const int*>(reinterpret_cast<const char*>(this) + 0x18);
    // Use a hardcoded base offset of 0x60 (24 floats) plus the entity-specific offset.
    return *reinterpret_cast<const float*>(floatTable + 0x60 + attributeOffset);
}