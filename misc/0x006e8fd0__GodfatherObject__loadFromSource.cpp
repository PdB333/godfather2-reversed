// FUNC_NAME: GodfatherObject::loadFromSource
void __thiscall GodfatherObject::loadFromSource(int this, int sourceId) {
    byte buffer[32]; // 32-byte temporary buffer

    // Fill buffer with structured data from the given source (e.g., ID, handle)
    // Callee: FUN_0043a2a0
    FUN_0043a2a0(buffer, sourceId);

    // Extract fields from buffer and store into object memory
    uint64_t field_0x6c = *(uint64_t*)(buffer);
    uint64_t field_0x78 = *(uint64_t*)(buffer + 8);
    uint32_t field_0x74 = *(uint32_t*)(buffer + 16);
    uint32_t field_0x80 = *(uint32_t*)(buffer + 20);

    // Write to object (offsets relative to this)
    *(uint64_t*)(this + 0x6c) = field_0x6c;
    *(uint64_t*)(this + 0x78) = field_0x78;
    *(uint32_t*)(this + 0x74) = field_0x74;
    *(uint32_t*)(this + 0x80) = field_0x80;
}