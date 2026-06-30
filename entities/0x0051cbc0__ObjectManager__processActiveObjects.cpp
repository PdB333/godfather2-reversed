// FUNC_NAME: ObjectManager::processActiveObjects
// Address: 0x0051cbc0
// Iterates over an array of entries starting at offset +0xf4, count at +0x80.
// Each entry is 20 bytes (flags+0x00, object*+0x04, unk+0x08, +0x0c, +0x10).
// If flag bit 0x40000 is set and object pointer is non-null, calls virtual method at vtable+0x44 (index 0x11) with param2 and param3.
class UpdatableObject
{
public:
    virtual void unknown_vtable_0(); // filler
    virtual void unknown_vtable_1();
    // ... many vtable slots
    virtual void update(void* param2, void* param3); // vtable+0x44 (slot 0x11)
};

struct Entry
{
    int   flags;   // +0x00
    void* object;  // +0x04 - pointer to UpdatableObject
    int   unk_08;  // +0x08
    int   unk_0c;  // +0x0c
    int   unk_10;  // +0x10
};

class ObjectManager
{
public:
    // Total size unknown. Relevant fields:
    // +0x80: short m_count
    // +0xf4: Entry m_entries[] (count determined by m_count)
    short m_count; // at +0x80
    // padding...
    // at +0xf4, contiguous array of Entry structs
    void processActiveObjects(void* param2, void* param3);
};

void ObjectManager::processActiveObjects(void* param2, void* param3)
{
    if (m_count > 0)
    {
        Entry* entry = reinterpret_cast<Entry*>(reinterpret_cast<char*>(this) + 0xf4);
        for (short i = 0; i < m_count; ++i, ++entry)
        {
            if ((entry->flags & 0x40000) != 0 && entry->object != nullptr)
            {
                UpdatableObject* obj = static_cast<UpdatableObject*>(entry->object);
                obj->update(param2, param3);
            }
        }
    }
}