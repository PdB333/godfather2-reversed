// FUNC_NAME: Entity::applyCharacterTemplate
bool __thiscall Entity::applyCharacterTemplate(uint templateIndex, void* templateBase) {
    // Guard: only indices 0..4 are valid (e.g., 5 character slots/crew members)
    if (templateIndex < 5) {
        // Each template entry is 0x4a4 bytes (1188 bytes) – likely a full character definition
        char* entry = (char*)templateBase + templateIndex * 0x4a4;

        // Copy selected fields from template to the entity
        // Entity offsets:
        // +0x10 : int (e.g., modelId, archetype, or rep)
        // +0x14 : byte (e.g., flag, faction, or gender)
        // +0x18 : int (e.g., health, rank)
        // +0x1c : int (e.g., weaponId, skill)
        this->field_0x14 = *(byte*)(entry + 0x494);  // template +0x494 -> byte
        this->field_0x18 = *(int*)(entry + 0x210);   // template +0x210 -> int
        // Call helper to copy additional data (likely a name string or sub-struct) at template+0x498
        sub_4d3e20(entry + 0x498);
        this->field_0x10 = *(int*)(entry + 0x490);   // template +0x490 -> int
        this->field_0x1c = *(int*)(entry + 0x1f8);   // template +0x1f8 -> int
        return true;
    }
    return false;
}