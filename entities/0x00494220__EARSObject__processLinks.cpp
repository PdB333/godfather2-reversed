// FUNC_NAME: EARSObject::processLinks
// Function address: 0x00494220

extern void FUN_0060b020(void (*func)(void*, void*, void*), void* object, void* context);
extern void FUN_0060ad20(void (*func)(void*, void*, void*), void* object, void* context);

class EARSObject
{
public:
    // Offsets from 'this':
    // +0x00: vtable pointer
    // +0x04: first linked component pointer
    // +0x14: second linked component pointer
    // +0x1c: third linked component pointer
    // +0x18: context data for second link (passed to FUN_0060ad20)
    // +0x20: context data for third link (passed to FUN_0060ad20)

    void processLinks()
    {
        // Fetch the virtual process function from vtable at offset 0x14 (5th entry, 4-byte pointers)
        void (*processFunc)(void*, void*, void*) = *(void (**)(void*, void*, void*))(*(int*)this + 0x14);

        // First link (offset 0x04)
        if (*(int*)(this + 0x04) != 0)
        {
            FUN_0060b020(processFunc, *(void**)(this + 0x04), (void*)(this + 0x04));
        }

        // Second link (offset 0x14)
        if (*(int*)(this + 0x14) != 0)
        {
            FUN_0060ad20(processFunc, *(void**)(this + 0x14), (void*)(this + 0x18));
        }

        // Third link (offset 0x1c)
        if (*(int*)(this + 0x1c) != 0)
        {
            FUN_0060ad20(processFunc, *(void**)(this + 0x1c), (void*)(this + 0x20));
        }
    }
};