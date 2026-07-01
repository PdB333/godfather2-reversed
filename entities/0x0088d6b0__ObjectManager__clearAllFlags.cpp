// FUNC_NAME: ObjectManager::clearAllFlags
void __fastcall ObjectManager::clearAllFlags(int this) {
    uint count = *(uint*)(this + 0x148); // number of objects in list
    for (uint i = 0; i < count; i++) {
        int objPtr = *(int*)(this + 0x80 + i * 4); // pointer to object from array at +0x80
        *(char*)(objPtr + 0x280) = 0; // clear byte flag at offset 0x280
    }
}