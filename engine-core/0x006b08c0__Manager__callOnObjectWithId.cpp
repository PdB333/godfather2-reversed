// FUNC_NAME: Manager::callOnObjectWithId
void __thiscall Manager::callOnObjectWithId(int id, void* data)
{
    // this+0x34: pointer to array of 8-byte entries (struct Entry { int unused; void* object; })
    // this+0x38: number of entries in the array
    uint count = *(uint*)(this + 0x38);
    if (count == 0) return;

    // base pointer to the array of entries
    int* entries = *(int**)(this + 0x34);
    for (uint i = 0; i < count; i++)
    {
        // Each entry is 8 bytes: at offset 0 is something, at offset 4 is a pointer to an object
        void* object = ((void**)entries)[i * 2 + 1]; // equivalent to *(int*)((char*)entries + 4 + i * 8)
        // Check object's field at +0x40 (likely an ID or key)
        if (object != nullptr && *(int*)((char*)object + 0x40) == id)
        {
            FUN_006b5850(data); // call some handling function with the provided data
        }
    }
}