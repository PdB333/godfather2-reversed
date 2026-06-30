// FUNC_NAME: TLSManagedObject::~TLSManagedObject
// Address: 0x0054bcf0
// Destructor: Changes vtable to base class, frees TLS-associated memory if index >= 0.
// Likely part of a thread-local storage managed object pool (EA EARS engine).
// Offsets relative to this:
// [0x00] = vtable pointer (derived class)
// [0x04] = vtable pointer (base class?) [not used directly]
// [0x10] = pointer to array/block (used in deallocation) [offset 4 words]
// [0x18] = index value (flags in top 2 bits, size index in lower 30) [offset 6 words]

__thiscall void TLSManagedObject::~TLSManagedObject() {
    // Save the derived class vtable pointer (set by constructor)
    // Note: PTR_LAB_00e397fc is the vtable for the derived class
    *(void**)this = &PTR_LAB_00e397fc;

    // Read index from offset 0x18
    uint tmpIndex = *(uint*)((char*)this + 0x18);

    // If index >= 0 (signed), meaning it is a valid allocated slot
    if ((int)tmpIndex >= 0) {
        // Retrieve TLS value for the given index (likely thread-specific pool)
        TlsGetValue(DAT_01139810);

        // Call deallocation function:
        // First arg: pointer to data block from offset 0x10
        // Second arg: (index masked to 30 bits) * 0x30 (size of each element)
        // Third arg: 0x17 (perhaps alignment or type tag)
        FUN_00aa26e0(
            *(void**)((char*)this + 0x10),
            (tmpIndex & 0x3fffffff) * 0x30,
            0x17
        );
    }

    // Restore vtable to base class (PTR_LAB_00dc4710) – typical for destructor
    *(void**)this = &PTR_LAB_00dc4710;
}