// FUNC_NAME: SlotArray::adjustValue
int __thiscall SlotArray::adjustValue(int index, int delta) {
    if (delta != 0) {
        int *slot = reinterpret_cast<int *>(reinterpret_cast<uint8_t *>(this) + 4 + index * 4); // array at +0x04
        *slot += delta;
        *reinterpret_cast<uint8_t *>(reinterpret_cast<uint8_t *>(this) + 0x1c) = 1; // dirty flag at +0x1c
    }
    return *reinterpret_cast<int *>(reinterpret_cast<uint8_t *>(this) + 4 + index * 4);
}