// FUNC_NAME: ObjectGroup::processAllChildren
// Address: 0x00482a20
// Iterates over child objects stored in an array at this+0x04,
// calling their 4th virtual function (offset 0x0C in vtable).
// Count of children is stored as unsigned short at this+0x0C.

class ObjectGroup {
public:
    void processAllChildren() {
        // Retrieve number of children (unsigned short at offset 0x0C)
        unsigned int childCount = *(unsigned short*)((char*)this + 0x0C);

        // Loop through each child object pointer in the array (offset 0x04)
        for (unsigned int i = 0; i < childCount; ++i) {
            void* child = *(void**)((char*)this + 0x04 + i * 4);
            // Call virtual function at vtable index 3 (offset 0x0C)
            void (__thiscall* func)(void*) = *(void (__thiscall**)(void*))(*(int*)child + 0x0C);
            func(child);
        }
    }
};