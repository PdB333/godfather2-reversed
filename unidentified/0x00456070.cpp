// FUN_00456070: ObjectManager::findFirstMatchingObject
int __fastcall ObjectManager::findFirstMatchingObject(void* this)
{
    uint count = *(uint*)((char*)this + 0x38);        // +0x38: number of slots
    int result = 0;
    uint i = 0;
    if (count != 0) {
        // +0x34: pointer to array of ObjectSlot (each 36 bytes)
        ObjectSlot* slots = *(ObjectSlot**)((char*)this + 0x34);
        do {
            // First field of slot is a pointer to an object (nullable)
            if (slots[i].object != nullptr) {
                // Call a method on that object; returns non-zero if condition met
                result = reinterpret_cast<int(__thiscall*)(void*)>(0x004cbf10)(slots[i].object);
                if (result != 0) {
                    return result;
                }
            }
            i++;
        } while (i < count);
    }
    return result; // 0 if nothing matched
}