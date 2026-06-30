// FUNC_NAME: Building::loadFromData
void __thiscall Building::loadFromData(void* this, const uint32_t* data)
{
    // +0x184, +0x188, +0x18c, +0x190: first 4 fields from data[0..3]
    *(uint32_t*)((uintptr_t)this + 0x184) = data[0];
    *(uint32_t*)((uintptr_t)this + 0x188) = data[1];
    *(uint32_t*)((uintptr_t)this + 0x18c) = data[2];
    *(uint32_t*)((uintptr_t)this + 0x190) = data[3];

    // +0x38: building ID (used for name)
    *(uint32_t*)((uintptr_t)this + 0x38) = data[5];
    // +0x48: some field
    *(uint32_t*)((uintptr_t)this + 0x48) = data[6];
    // +0x40 and +0x3c both set to data[4] (likely a category/type)
    *(uint32_t*)((uintptr_t)this + 0x40) = data[4];
    *(uint32_t*)((uintptr_t)this + 0x3c) = data[4];
    // +0x34: flags – OR with data[7]
    *(uint32_t*)((uintptr_t)this + 0x34) |= data[7];
    // +0x36: clear (ushort)
    *(uint16_t*)((uintptr_t)this + 0x36) = 0;

    // +0xc4: some field
    *(uint32_t*)((uintptr_t)this + 0xc4) = data[8];
    // +0x50: another field
    *(uint32_t*)((uintptr_t)this + 0x50) = data[9];

    // Position (3 floats): +0x10, +0x14, +0x18 from data[0xb..0xd]
    *(float*)((uintptr_t)this + 0x10) = *(float*)&data[0x0b];
    *(float*)((uintptr_t)this + 0x14) = *(float*)&data[0x0c];
    *(float*)((uintptr_t)this + 0x18) = *(float*)&data[0x0d];
    // Orientation/rotation (3 floats): +0x1c, +0x20, +0x24 from data[0xe..0x10]
    *(float*)((uintptr_t)this + 0x1c) = *(float*)&data[0x0e];
    *(float*)((uintptr_t)this + 0x20) = *(float*)&data[0x0f];
    *(float*)((uintptr_t)this + 0x24) = *(float*)&data[0x10];
    // Scale (3 floats): +0x28, +0x2c, +0x30 from data[0x11..0x13]
    *(float*)((uintptr_t)this + 0x28) = *(float*)&data[0x11];
    *(float*)((uintptr_t)this + 0x2c) = *(float*)&data[0x12];
    *(float*)((uintptr_t)this + 0x30) = *(float*)&data[0x13];

    // +0x104, +0x108: two more fields
    *(uint32_t*)((uintptr_t)this + 0x104) = data[0x14];
    *(uint32_t*)((uintptr_t)this + 0x108) = data[0x15];

    // AddRef for six resource handles (data[0x16..0x1b])
    addRefResource(data[0x16]);
    addRefResource(data[0x17]);
    addRefResource(data[0x18]);
    addRefResource(data[0x19]);
    addRefResource(data[0x1a]);
    addRefResource(data[0x1b]);

    // Build building name string "building_name_XXX"
    char* formattedName = nullptr;  // Will be heap allocated via formatString
    uint32_t unknown = 0;
    uint32_t unknown2 = 0;
    void* unknown3 = nullptr;

    formatString(&formattedName, "building_name_%03u", *(uint32_t*)((uintptr_t)this + 0x38));
    const char* nameToHash = (formattedName != nullptr) ? formattedName : "";
    uint32_t nameHash = hashStringToId(nameToHash);
    *(uint32_t*)((uintptr_t)this + 0xdc) = nameHash;

    // Free formatted string if it was allocated
    if (formattedName != nullptr) {
        freeString(formattedName);
    }
}