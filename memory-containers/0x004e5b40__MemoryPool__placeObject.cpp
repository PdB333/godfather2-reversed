// FUNC_NAME: MemoryPool::placeObject
// Address: 0x004e5b40
// Role: Places an object into a pre-allocated memory pool with vtable, type ID, and aligned data.
// The pool is a raw memory block whose base address is stored as the first field of this class (offset 0).
// Within the pool, offset 0x14 stores a bump-allocator cursor (char*).

void __thiscall MemoryPool::placeObject(int typeID, void* data) {
    // Get the base address of the memory block (first field of this)
    char* base = m_pBase; // +0x00: pointer to pool memory

    // The pool header contains a cursor at base + 0x14 (a char*)
    char* cursor = *(char**)(base + 0x14);

    // Write the vtable pointer for the object class
    *(void**)cursor = (void*)&g_PTR_LAB_01124b30; // vtable for some game object
    cursor += 4;

    // Write the type identifier (e.g., object type or size) after the vtable
    *(int*)cursor = typeID;
    cursor += 4; // note: original code doesn't advance cursor after writing typeID, but alignment step effectively does

    // Align cursor to a 16-byte boundary for the object data
    cursor = (char*)(((uint32_t)(cursor + 0x13)) & ~0xF);

    // Copy the object initialization data (48 bytes = 0x30)
    memcpy(cursor, data, 0x30);

    // Advance cursor past the object
    cursor += 0x30;

    // Update the pool cursor
    *(char**)(base + 0x14) = cursor;
}