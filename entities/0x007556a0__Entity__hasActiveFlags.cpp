// FUNC_NAME: Entity::hasActiveFlags
// Function checks if either the entity's own bit0 flag (at +0x58) or
// an external object's bit1 flag (via pointer at +0x50, offset +0x8e0) is set.
// Returns 1 (true) if either condition is true, otherwise 0 (false).
bool __thiscall Entity::hasActiveFlags(Entity* this) {
    // Check own byte flag at offset +0x58, bit 0
    bool ownFlag = (this->field_0x58 & 0x01) != 0;
    // Dereference pointer at +0x50 to get another object, then check its uint at +0x8e0 bit 1
    uint* external = *(uint**)((uint8_t*)this + 0x50);
    bool externalFlag = external && ((*external >> 1) & 0x01) != 0;
    return ownFlag || externalFlag;
}