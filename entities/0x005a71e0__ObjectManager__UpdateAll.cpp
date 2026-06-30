// FUNC_NAME: ObjectManager::UpdateAll
// Address: 0x005a71e0
// Role: Iterates over a fixed array of objects (max 512), calls their type-specific update function via global dispatch table.
// Structure: this->activeCount (int at +0x00), this->objects (void* array of 512 at +0x04)
// Global dispatch table at address 0x0103aee0, indexed by (obj->typeId & 0x7FFF)

extern void (*g_typeUpdateTable[0x8000])(void*); // Function pointers for each type ID (up to 0x7FFF)

void __thiscall ObjectManager::UpdateAll(void)
{
    int count = this->activeCount;          // +0x00: number of active objects
    void** objPtr = &this->objects[0];      // +0x04: start of pointer array
    int i = 0;

    do {
        void* obj = *objPtr;
        if (obj != 0) {
            // Read type ID from first 4 bytes of object, mask to 15 bits
            uint typeId = *(uint*)obj & 0x7FFF;
            // Call the appropriate update function from global table
            g_typeUpdateTable[typeId](obj);
            count--;
            if (count == 0) {
                return;                     // All active objects processed
            }
        }
        i++;
        objPtr++;
    } while (i < 0x200);                   // Max array size = 512
    return;
}