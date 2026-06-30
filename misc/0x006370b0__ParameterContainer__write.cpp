// FUNC_NAME: ParameterContainer::write
// Address: 0x006370b0
// Role: Serializes a container holding two lists: a typed data list and a sub-object list.
// Uses a serializer object (likely a BitStream/writer) passed via a register (EAX) in the original assembly.
// The container has:
//   +0x08: pointer to array of typed entries (each 8 bytes: type byte+pad, and optional int value)
//   +0x28: count of typed entries
//   +0x10: pointer to array of sub-object pointers (4 bytes each)
//   +0x34: count of sub-objects
//   +0x20: common parameter passed to each sub-object serialization

struct Serializer {
    // vtable[0] unknown, vtable[1] is write(void* data, int size, int arg2)
    int* vtable;
    int* unknown;
    int arg2;
};

// External: handles type 4 entries
extern void handleType4Entry(); // Placeholder for FUN_00636e20

// Forward: serializes a sub-object (from second list)
extern void writeSubObject(int subObject, int param2); // Placeholder for FUN_006371a0

void __thiscall ParameterContainer::write(Serializer& serializer) {
    // First list: typed entries
    int typedCount = *(int*)(this + 0x28); // +0x28
    int tempCount = typedCount;
    serializer.vtable[1](&serializer, &tempCount, 4, serializer.arg2); // Write count as 4-byte int

    for (int i = 0; i < typedCount; ++i) {
        // Each entry is 8 bytes: first int holds type (low byte) and also used as type identifier,
        // second int holds value if type == 3.
        int* entry = (int*)(*(int*)(this + 0x08) + i * 8); // +0x08 base pointer
        unsigned char typeByte = *(unsigned char*)entry; // low byte of first int
        int typeValue = *entry;        // full int (type identifier: 3 or 4)

        serializer.vtable[1](&serializer, &typeByte, 1, serializer.arg2); // Write type as single byte

        if (typeValue == 3) {
            int value = entry[1];
            serializer.vtable[1](&serializer, &value, 4, serializer.arg2); // Write value as 4-byte int
        }
        else if (typeValue == 4) {
            // Custom handler for type 4 items
            handleType4Entry();
        }
    }

    // Second list: sub-object references
    int subCount = *(int*)(this + 0x34); // +0x34
    tempCount = subCount;
    serializer.vtable[1](&serializer, &tempCount, 4, serializer.arg2); // Write sub-object count

    int commonParam = *(int*)(this + 0x20); // +0x20 — passed to each sub-object write
    for (int i = 0; i < subCount; ++i) {
        int subRef = *(int*)(*(int*)(this + 0x10) + i * 4); // +0x10 array of sub-object IDs
        writeSubObject(subRef, commonParam);
    }
}