// FUNC_NAME: GhostObject::getNetIdentifier
void GhostObject::getNetIdentifier(uint32* outIdentifier) const
{
    // Compute a combined hash of four fields at negative offsets from this pointer.
    // This is likely building a 64-bit network identifier for the ghosted object.
    // Multiplier 0x21 (33) is typical for hash combining.
    int32_t highPart = *(int32_t*)((intptr_t)this - 0x40); // +0xBDC? Actually -0x40 relative to this
    int32_t combined = ((*(int32_t*)((intptr_t)this - 0x38) * 0x21 + *(int32_t*)((intptr_t)this - 0x34)) * 0x21 +
                        *(int32_t*)((intptr_t)this - 0x30)) * 0x21 + *(int32_t*)((intptr_t)this - 0x2c);
    outIdentifier[0] = combined; // Low 32 bits of identifier
    outIdentifier[1] = highPart; // High 32 bits of identifier
}