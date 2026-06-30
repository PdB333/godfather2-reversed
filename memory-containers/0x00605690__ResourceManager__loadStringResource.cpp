// FUNC_NAME: ResourceManager::loadStringResource
// Address: 0x00605690
// Reads a string resource identified by handle, allocates buffer, copies string, returns pointer to buffer and length in outSize.

typedef int (__thiscall *AllocFunc)(void* self, int size, void* allocInfo);
typedef void (__thiscall *FreeFunc)(void* self, void* buffer, int flags);

int __thiscall ResourceManager::loadStringResource(void* this, uint* outSize)
{
    // Stack buffer (128 bytes) used to store resource path or identifier
    char pathBuffer[128]; // 0x80 bytes
    // Initialize stack maybe? FUN_00401aa0 is likely a stack guard or debug fill.
    FUN_00401aa0(0x80); // fill pathBuffer with something? Not shown in decompile.

    // Global singleton access
    int* globalPtr = *(int**)0x01223378; // DAT_01223378
    // Open resource with path from pathBuffer and mode 1 (read text?).
    int resourceHandle = FUN_004015e0(pathBuffer, 1);
    if (resourceHandle != 0)
    {
        // Read length for this resource from a table: globalPtr+0x38 is a table pointer,
        // each entry is 0x10 bytes, offset 0xc stores the length.
        uint length = *(uint*)(*(int*)((char*)globalPtr + 0x38) + 0xc + resourceHandle * 0x10);
        *outSize = length;

        // Prepare allocation info structure:
        // local_94 = 2, local_90 = 0x10, local_8c = 0  (maybe alignment, flags, etc.)
        int allocInfo[3];
        allocInfo[0] = 2;   // alignment? flags?
        allocInfo[1] = 0x10; // alignment or size?
        allocInfo[2] = 0;   // not used?

        // Call allocator method (first vtable entry) with size+1 and allocInfo.
        AllocFunc alloc = *(AllocFunc*)(*(int*)this); // vtable[0]
        char* buffer = (char*)alloc(this, length + 1, &allocInfo);

        // Read resource content into buffer. FUN_00401780 likely reads bytes.
        int bytesRead = FUN_00401780(resourceHandle, buffer, /* unaff_EBX? */);
        // Close resource.
        FUN_004016d0(resourceHandle);

        if (*outSize <= (uint)bytesRead)
        {
            // Null-terminate at the actual length.
            buffer[*outSize] = '\0';
            return (int)buffer;
        }
        else
        {
            // Not enough data read; free buffer and indicate failure.
            FreeFunc free = *(FreeFunc*)(*(int*)this + 4); // vtable[1]
            free(this, buffer, 0);
            *outSize = 0;
        }
    }
    return 0;
}