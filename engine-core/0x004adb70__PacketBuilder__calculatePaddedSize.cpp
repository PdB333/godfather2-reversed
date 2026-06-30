// FUNC_NAME: PacketBuilder::calculatePaddedSize
int PacketBuilder::calculatePaddedSize() {
    // this+0x4: array of pointers to serializable objects
    // this+0x8: count of objects in array
    uint32_t index = 0;
    int totalSize = *(int*)((char*)this + 8) * 4; // base size: count * 4 (e.g., header for each object)
    if (*(int*)((char*)this + 8) != 0) {
        do {
            // Each object's vtable: first entry unknown, second entry (offset 4) is getPackedSize()
            void** objectPtr = *(void***)(*(int*)((char*)this + 4) + index * 4);
            int size = (*(int (**)(void))(*(int*)objectPtr + 4))(); // call virtual function
            index++;
            totalSize = totalSize + size + (4 - (totalSize + size & 3)); // align to 4 bytes
        } while (index < *(uint32_t*)((char*)this + 8));
    }
    return totalSize;
}