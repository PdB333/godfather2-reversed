// FUNC_NAME: Entity::updateAttachWorldPosition
void __thiscall Entity::updateAttachWorldPosition(Entity* thisPtr) {
    // Global scale factor (DAT_00e445ac) – likely world units per meter or similar
    float worldScale = *(float*)0x00e445ac;

    // Retrieve two transform sources (e.g., parent bone and local offset)
    // FUN_00471610 returns pointer to a transform node (likely a scene graph node or attachment point)
    TransformNode* parentNode = (TransformNode*)FUN_00471610(); // +0x20: translation x, +0x24: y, +0x28: z
    TransformNode* localOffset = (TransformNode*)FUN_00471610(); // +0x30: offset x, +0x34: y, +0x38: z

    // Scale parent translation by world scale
    float scaledParentX = parentNode->translationX * worldScale; // +0x20
    float scaledParentY = parentNode->translationY * worldScale; // +0x24
    float scaledParentZ = parentNode->translationZ * worldScale; // +0x28

    // Local offset (unscaled)
    float offsetX = localOffset->offsetX; // +0x30
    float offsetY = localOffset->offsetY; // +0x34
    float offsetZ = localOffset->offsetZ; // +0x38

    // Mark dirty flag at offset 0xD4 (bit 0)
    thisPtr->flagsDwordAt0xD4 |= 1;

    // Store combined X and Y as a 64-bit value at offset 0xC8 (packed as two floats)
    // CONCAT44(order: high32, low32) maps to (ay+by) and (ax+bx)
    uint64_t packedXY = (uint64_t)(*(uint32_t*)&(scaledParentY + offsetY)) << 32
                        | (uint64_t)(*(uint32_t*)&(scaledParentX + offsetX));
    *(uint64_t*)((uint8_t*)thisPtr + 0xC8) = packedXY;

    // Store combined Z as a separate float at offset 0xD0
    *(float*)((uint8_t*)thisPtr + 0xD0) = scaledParentZ + offsetZ;
}