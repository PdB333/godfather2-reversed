// FUNC_NAME: Entity::getNetworkIdentifier
uint __fastcall Entity::getNetworkIdentifier(Entity* this) {
    uint result;
    // +0x330: pointer to a network-related structure (e.g., NetObject)
    int networkPtr = *(int*)(this + 0x330);
    if (networkPtr == 0) {
        result = 0;
    } else {
        // Adjust pointer to get the containing structure (sub 0x48 offset)
        result = networkPtr - 0x48;
    }
    if (result != 0) {
        uint isValid = FUN_0071ce70(result); // likely checks type validity / casts
        if (isValid != 0) {
            // +0x324: index or ID into a network table
            uint index = *(uint*)(this + 0x324);
            return FUN_0071c320(index); // returns network identifier from index
        }
    }
    // Mask off low byte (return only upper 24 bits)
    return result & 0xffffff00;
}