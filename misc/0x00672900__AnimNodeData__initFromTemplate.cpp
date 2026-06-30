// FUNC_NAME: AnimNodeData::initFromTemplate
int AnimNodeData::initFromTemplate(int* outNodePtr) {
    // Clear output indicator (may be a return error flag)
    *reinterpret_cast<int*>(this) = 0;

    int outputAddr = *outNodePtr;
    // Get the global animation template definition
    AnimDefinition* def = AnimDefinitionManager::getDefaultDefinition(); // FUN_00672a80
    if (!def) return 0;

    // Copy hierarchical relationship pointers from definition
    if (def->parent == 0 && def->sibling == 0) {
        *reinterpret_cast<int*>(outputAddr + 0x11C) = 0; // childA
        *reinterpret_cast<int*>(outputAddr + 0x118) = 0; // childB
    } else if (def->branchFlag == 1) {
        *reinterpret_cast<int*>(outputAddr + 0x11C) = reinterpret_cast<int>(&def->childData); // +0x68 offset
    } else {
        *reinterpret_cast<int*>(outputAddr + 0x118) = reinterpret_cast<int>(&def->childData);
    }

    // Copy transform/matrix data
    *reinterpret_cast<int*>(outputAddr + 0x30) = 0; // some flag or time
    *reinterpret_cast<int*>(outputAddr + 0xCC) = static_cast<int>(def->data[0].shortVal); // +0x14
    *reinterpret_cast<float*>(outputAddr + 0xD0) = def->data[0].float1; // +0x18
    *reinterpret_cast<float*>(outputAddr + 0xD4) = def->data[0].float2; // +0x1C
    *reinterpret_cast<float*>(outputAddr + 0xD8) = def->data[0].float3; // +0x20
    *reinterpret_cast<float*>(outputAddr + 0xDC) = def->data[1].float1; // +0x24
    *reinterpret_cast<float*>(outputAddr + 0xE0) = def->data[1].float2; // +0x28
    *reinterpret_cast<float*>(outputAddr + 0xE4) = def->data[1].float3; // +0x2C
    *reinterpret_cast<int*>(outputAddr + 0xE8) = static_cast<int>(def->data[1].shortVal); // +0x30
    *reinterpret_cast<float*>(outputAddr + 0xEC) = def->data[2].float1; // +0x34
    *reinterpret_cast<float*>(outputAddr + 0xF0) = def->data[2].float2; // +0x38
    *reinterpret_cast<float*>(outputAddr + 0xF4) = def->data[2].float3; // +0x3C
    *reinterpret_cast<float*>(outputAddr + 0xF8) = def->data[3].float1; // +0x40
    *reinterpret_cast<float*>(outputAddr + 0xFC) = def->data[3].float2; // +0x44
    *reinterpret_cast<float*>(outputAddr + 0x100) = def->data[3].float3; // +0x48
    *reinterpret_cast<int*>(outputAddr + 0x10C) = def->flags1; // +0x4C
    *reinterpret_cast<int*>(outputAddr + 0x110) = def->flags2; // +0x50
    *reinterpret_cast<int*>(outputAddr + 0x114) = def->flags3; // +0x54
    *reinterpret_cast<int*>(outputAddr + 0x120) = static_cast<int>(def->data[4].shortVal); // +0x58
    *reinterpret_cast<short*>(outputAddr + 0x108) = def->data[4].short2; // +0x5C

    return 1;
}