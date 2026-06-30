// FUNC_NAME: ReflectionManager::registerFieldNode
uint32 ReflectionManager::registerFieldNode(void) {
    // Global manager pointer: DAT_01205590 -> points to a vtable object
    // Vtable method at offset 0x10 (index 4) is used for allocation and field writing

    uint32 constValue0 = 0x700;          // Possibly a field offset or size constant
    uint32 constValue1 = 2;              // Field type or flags
    uint32 addressConst = 0x59802b;      // Address of something (maybe a default function)

    // First call to vtable method (allocates a new node slot)
    // Returns a pointer to the new node
    void* node = (*(void* (__thiscall *)(void*))((uint32*)*DAT_01205590 + 4))(DAT_01205590);

    addressConst = 2; // Overwrite with constant

    // Prepare pointers to stack data for field writes
    uint32* ptrToData0 = &constValue0;
    uint32* ptrToData1 = &addressConst;
    uint32 selfRef = (uint32)node + 2; // Self-referential field value

    // Write three fields of the node at byte offsets +4, +5, +6
    // Each call: (destination, source pointer, count)
    (*(void (__thiscall *)(void*, void**, uint32))((uint32*)*DAT_01205590 + 4))(node + 4, &ptrToData0, 1);
    (*(void (__thiscall *)(void*, void**, uint32))((uint32*)*DAT_01205590 + 4))(node + 5, ptrToData1, 1);
    (*(void (__thiscall *)(void*, void**, uint32))((uint32*)*DAT_01205590 + 4))(node + 6, &selfRef, 1);

    return 8; // Return constant (likely size or status code)
}