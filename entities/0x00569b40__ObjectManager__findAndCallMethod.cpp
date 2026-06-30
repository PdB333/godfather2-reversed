// FUNC_NAME: ObjectManager::findAndCallMethod

void ObjectManager::findAndCallMethod(const wchar_t* name) {
    // Lock a critical section (global lock at DAT_00e2cbe8)
    FUN_00ab4db0(&DAT_00e2cbe8);

    // m_entryCount stored at this+0xca words (offset 0x328)
    if (m_entryCount == 0) {
        FUN_00ab4e70(); // unlock
        return;
    }

    // m_entries array starts at this+0x8a words (offset 0x228)
    NamedEntry** entries = reinterpret_cast<NamedEntry**>(reinterpret_cast<char*>(this) + 0x228);
    int count = m_entryCount;

    for (uint i = 0; i < count; ++i) {
        NamedEntry* entry = entries[i];
        // entry flags at offset 0x104
        if (entry->someFlag != 0) {
            // pObject at entry offset 0x4
            NamedObject* obj = entry->pObject;
            // obj->name starts at obj offset 0x8 (wide string)
            const wchar_t* objName = reinterpret_cast<const wchar_t*>(reinterpret_cast<char*>(obj) + 8);
            
            // Compare wide strings (2-byte characters)
            int cmp = wcscmp(objName, name);
            if (cmp == 0) {
                // call vtable function at offset 0x18 (index 6)
                void (*method)(NamedObject*) = reinterpret_cast<void (*)(NamedObject*)>(
                    (*reinterpret_cast<int**>(obj))[0x18 / 4]
                );
                method(obj);
                FUN_00ab4e70(); // unlock
                return;
            }
        }
    }

    FUN_00ab4e70(); // unlock
}