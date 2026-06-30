// FUNC_NAME: Entity::getFirstUint32
void __thiscall Entity::getFirstUint32(uint32_t* outValue) {
    // Copies the first 4-byte member of the entity into the output pointer.
    // This is typically used to retrieve an identifier, handle, or reference stored at offset +0x00.
    *outValue = *(uint32_t*)this;
}