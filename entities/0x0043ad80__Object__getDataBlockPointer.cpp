// FUNC_NAME: Object::getDataBlockPointer
void __thiscall Object::getDataBlockPointer(uint32_t *outData) {
    // Retrieve the data block pointer stored at offset 0x8 of the object
    // +0x08: m_pDataBlock (pointer to a data block/resource)
    *outData = *(uint32_t *)(this + 0x8);
}