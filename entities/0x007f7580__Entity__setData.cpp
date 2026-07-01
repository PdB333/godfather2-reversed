// FUNC_NAME: Entity::setData
void __thiscall Entity::setData(int thisPtr, const DataPair* data, uint8_t type) {
    // Store type byte at offset +0xA80
    *(uint8_t*)(thisPtr + 0xA80) = type;
    // Copy 8-byte value from data->key to offset +0xA84
    *(uint64_t*)(thisPtr + 0xA84) = data->key;
    // Copy 4-byte value from data->value to offset +0xA8C
    *(uint32_t*)(thisPtr + 0xA8C) = data->value;
}