// FUNC_NAME: ObjectArray::clearAll

// Internal structure for each registered item (0x1C bytes)
struct ObjectSlot {
    void* m_object;        // +0x00: pointer to the object
    byte _pad[8];          // +0x04: unknown (8 bytes)
    void (*m_destructor)(void*); // +0x0C: destructor function pointer
    byte _pad2[12];        // +0x10: unknown (12 bytes, total 0x1C)
};

// Array of registered objects with count and capacity
struct ObjectArray {
    ObjectSlot* m_slots;   // +0x00: pointer to array of slots
    int m_count;           // +0x04: number of valid slots
    int m_capacity;        // +0x08: allocated capacity (or maybe state flag)
};

void __thiscall ObjectArray::clearAll(ObjectArray* this)
{
    int count = this->m_count - 1;
    if (count >= 0) {
        int offset = count * 0x1C; // offset into m_slots array
        do {
            void* obj = this->m_slots[count].m_object;
            if (obj != 0) {
                this->m_slots[count].m_destructor(obj);
            }
            count--;
            offset -= 0x1C;
        } while (count >= 0);
    }
    this->m_count = 0;
    FUN_009c8f10(this->m_slots); // Likely free the slot array memory (operator delete or heap free)
    this->m_slots = 0;
    this->m_capacity = 0;
}