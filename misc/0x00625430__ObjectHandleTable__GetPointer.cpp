// FUNC_NAME: ObjectHandleTable::GetPointer
int * __thiscall ObjectHandleTable::GetPointer(int id)
{
    // This function resolves an ID to a pointer.
    // ObjectHandleTable is a container managing arrays of 8-byte objects.
    // Offsets:
    // +0x08: pointer to an array of 8-byte elements for IDs > -10000
    // +0x0C: pointer to a lookup structure (likely a descriptor for a secondary table)
    // +0x10: pointer to another base used for ID == -10000
    // +0x40: special sentinel value for ID == -10001

    // IDs > -10000: direct index into an array at offset +0x08
    if (id > -10000)
    {
        // Each slot is 8 bytes; return base + id * 8
        return (int *)(*(int *)(this + 8) + id * 8);
    }

    // ID == -10001: return a fixed offset from this object (likely a sentinel value)
    if (id == -10001)
    {
        return (int *)(this + 0x40);
    }

    // ID == -10000: use an indirect pointer to an array at offset +0x10
    if (id == -10000)
    {
        return (int *)(*(int *)(this + 0x10) + 0x2C);
    }

    // For IDs < -10000 and not the special cases, use a secondary table.
    // First, dereference the pointer at +0x0C to get a descriptor, then read the address before that descriptor.
    int *descriptor = *(int **)(this + 0xC);
    int *tableBase = *(int **)((char *)descriptor - 4); // +0x0C points to a structure; the content at -4 is the start of the table.

    // At offset 7 of the table base, there is a byte giving the maximum index count.
    unsigned char count = *(unsigned char *)(tableBase + 7);

    // The index is computed as -10001 - id (same as -(id + 10001))
    int index = -10001 - id; // This yields a non-negative value for id < -10001

    if (index <= (int)count)
    {
        // Return pointer to element at tableBase + 8 + index * 8
        return (int *)((char *)tableBase + 8 + index * 8);
    }

    return 0;
}