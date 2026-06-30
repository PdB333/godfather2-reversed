// FUNC_NAME: ItemManager::findAndExecuteByName
// Address: 0x00569940
// This function searches through an array of child objects (pointers) with a wide string name.
// It uses a mutex lock/unlock around the search. On match, it calls a virtual function (at vtable+0x14)
// on the parent object (this) with the child object pointer and param_3.

typedef unsigned int uint;
typedef unsigned char byte;

// Mutex lock/unlock functions (likely from EA EARS threading)
void __cdecl mutexLock(uint* mutexPtr);   // addr 0x00ab4db0
void __cdecl mutexUnlock();                // addr 0x00ab4e70

class ItemManager
{
public:
    // Virtual function at vtable+0x14 (index 5) called when a matching item is found.
    // The signature likely: int __thiscall processItem(void* item, int zero, uint param3)
    // But we don't know the exact type, so we treat as a function pointer.
    int (__thiscall *processItem)(void* param1_task, int zero, uint param3);

    // Known members based on offsets:
    // +0x228? Actually offset 0x8a * 4 = 0x228 = 552 bytes. Array of pointers to child objects.
    // +0x328? offset 0xca * 4 = 0x328 = 808 bytes. Count of children.
    // Offsets are large – typical for a class with many members.
    void** itemsArray;   // at +0x228 (param_1 + 0x8a)
    uint numItems;       // at +0x328 (param_1 + 0xca)
};

// Decompiled function with meaningful names
byte __thiscall ItemManager::findAndExecuteByName(int *thisPtr, wchar_t *name, uint param3)
{
    uint i;
    byte result = 0;
    bool found = false;

    mutexLock(&DAT_00e2cbe8);   // Lock global mutex

    if (thisPtr[0xca] != 0)      // numItems > 0
    {
        void** itemsArray = (void**)(thisPtr + 0x8a);  // array of pointers at offset 0x8a

        for (i = 0; i < (uint)thisPtr[0xca]; i++)
        {
            void* child = itemsArray[i];
            if (*(int*)((byte*)child + 0x104) != 0)   // Check some flag at child+0x104 (non-zero means active?)
            {
                void* namePtr = *(void**)((byte*)child + 4);   // Pointer to string at child+4
                wchar_t* wname = (wchar_t*)((byte*)namePtr + 8); // String data at that pointer+8

                // Compare wide strings (UTF-16) until mismatch or null
                wchar_t* a = wname;
                wchar_t* b = name;
                bool equal = true;
                while (*a == *b)
                {
                    if (*a == 0) break;
                    a++;
                    b++;
                }
                // After loop, if both null and all match, equal remains true.
                // Equivalent of wcscmp(wname, name)
                if (*a == *b)   // If the loop ended because of null equality
                {
                    // Call virtual function on this with the child object, 0, param3
                    // vtable+0x14 corresponds to index 5
                    result = (this->*(this->processItem))(child, 0, param3);
                    found = true;  // break after first match
                }
            }
            if (found) break;
        }
    }

    mutexUnlock();   // Unlock mutex
    return result;
}