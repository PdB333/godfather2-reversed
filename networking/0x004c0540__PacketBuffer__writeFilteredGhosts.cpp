// FUNC_NAME: PacketBuffer::writeFilteredGhosts

// Function address: 0x004c0540
// Role: Writes a subset of ghost objects (filtered by a mask) into a packet buffer.
//   Uses a global ghost manager (DAT_0122341c) to enumerate all ghost entries.
//   Allocates a new buffer via the provided allocator interface (param_2)
//   and copies matched ghost data (including possible payload from virtual functions).
//   Returns 1 on success, 0 on failure.

#include <cstring> // for memcpy

class PacketBuffer
{
public:
    // Offsets:
    // +0x00: vtable
    // +0x14: m_pAllocator (some interface)
    // +0x18: m_nBufferSize
    // +0x1c: m_pBufferData
};

class GhostManager
{
public:
    // +0x0c: m_pGhostArray (array of entries, each 0xC bytes)
    // +0x10: m_nGhostCount
};

// The global ghost manager (address 0x0122341c)
extern GhostManager* g_pGhostManager;

// Virtual call helper: calls vtable[index] on an object
template<typename T>
inline T vcall(void* obj, int index)
{
    return (*(T (**)(void))(*(int*)obj + index))(obj);
}

// Unknown allocator interface (param_2)
class Allocator
{
public:
    virtual ~Allocator();
    virtual void* getBuffer();   // vtable+0
    virtual void* allocate();    // vtable+4
    virtual void  copyTo(void*, int); // vtable+8
    virtual void  free();        // vtable+12
};

// Unknown ghost entry (0xC bytes)
struct GhostEntry
{
    void* m_pPointer1;    // +0x00
    void* m_pPointer2;    // +0x04
    uint32 m_nFlags;      // +0x08
};

// ---------------------------------------------------------------------------
// Return 1 on success, 0 on failure.
// param_1 = this (PacketBuffer)
// param_2 = allocator interface
// param_3 = filter mask (bits to match against GhostEntry::m_nFlags)
// ---------------------------------------------------------------------------
int __thiscall PacketBuffer::writeFilteredGhosts(
        int     thisPtr,          // param_1
        int*    pAllocator,       // param_2
        uint32  filterMask)       // param_3
{
    // Local stack buffer for matched ghost indices (allocated via alloca)
    // Each matched ghost occupies 4 ints: [pPointer1, pPointer2, payloadSize, originalPointer]
    int*   pMatchedList = nullptr;
    uint32 matchedCount = 0;

    GhostManager* pMgr = g_pGhostManager;  // DAT_0122341c
    uint32 totalGhosts = *(uint32*)((int)pMgr + 0x10);

    // First pass: count how many ghosts match the mask
    for (uint32 i = 0; i < totalGhosts; i++)
    {
        GhostEntry* entry = (GhostEntry*)(*(int*)((int)pMgr + 0xC) + i * 0xC);
        if (entry->m_nFlags & filterMask)
        {
            matchedCount++;
        }
    }

    if (matchedCount == 0)
    {
        return 1; // Nothing to write, success
    }

    // Allocate space on stack for matched ghost temp data (16 bytes per entry)
    // Using alloca (inject __alloca_probe_16)
    int stackSize = matchedCount * (-0x10);
    pMatchedList = (int*)((char*)&stackSize + stackSize); // approximate, actual alloca
    // The decompiled code uses pointer arithmetic on &stack0xffffffc0

    // Second pass: collect matching ghosts and call virtual function to get payload size
    uint32 idx = 0;
    for (uint32 i = 0; i < totalGhosts; i++)
    {
        GhostEntry* entry = (GhostEntry*)(*(int*)((int)pMgr + 0xC) + i * 0xC);
        if (entry->m_nFlags & filterMask)
        {
            // Store pointer1 and pointer2 in the temp list
            pMatchedList[idx * 4 + 0] = (int)entry->m_pPointer1;
            pMatchedList[idx * 4 + 1] = (int)entry->m_pPointer2;

            // Call virtual function on pointer2 (vtable+4) to get payload size
            // The function returns a size (uint32) – likely "getSize()"
            auto* obj = entry->m_pPointer2;
            auto* vtable = *(int**)obj;
            auto getSizeFn = (uint32 (*)(void*))(vtable[1]); // vtable+4
            uint32 payloadSize = getSizeFn(obj);
            pMatchedList[idx * 4 + 2] = (int)payloadSize;
            pMatchedList[idx * 4 + 3] = 0; // originalPointer (cleared)

            idx++;
        }
    }

    // Now process the existing buffer (if any) and remap pointers
    int& bufSize   = *(int*)(thisPtr + 0x18);
    int& bufData   = *(int*)(thisPtr + 0x1c);
    int  allocator = *(int*)(thisPtr + 0x14);

    if (bufSize != 0 && bufData != 0)
    {
        // Walk through the existing buffer entries (each: [pointer1, pointer2, payloadSizeAligned, ...])
        int readPtr = bufData + 4; // skip first 4 bytes? The code uses +4 on bufData + 0x1c
        // Actually inside the loop: piVar18 = *(int*)(local_18 + 0x1c) + 4
        for (int remaining = bufSize - 4; remaining > 0xC; )
        {
            // Check if the current entry's pointer1 matches any matched ghost
            bool found = false;
            for (uint32 m = 0; m < matchedCount; m++)
            {
                if (pMatchedList[m * 4 + 0] == *(int*)readPtr) // compare pointer1
                {
                    // Found match: store original pointer (the readPtr itself) into pMatchedList[3]
                    pMatchedList[m * 4 + 3] = readPtr;
                    found = true;
                    break;
                }
            }

            // Advance to next entry: size = aligned(payloadSize) + 0xC
            int payloadSize = *(int*)(readPtr + 8); // pointer2's size? Actually entry layout: [pointer1, pointer2, payloadSize]
            int alignedSize = (payloadSize + 3) & ~3;
            int entrySize = 0xC + alignedSize;
            remaining -= entrySize;
            readPtr += entrySize;
        }
    }

    // Calculate new total size: old buffer size + sizes of matched entries (with maybe removed duplicates)
    int newTotalSize = bufSize; // start from old size
    for (uint32 m = 0; m < matchedCount; m++)
    {
        int payloadSize = pMatchedList[m * 4 + 2];
        int alignedSize = (payloadSize + 3) & ~3;
        newTotalSize += 0xC + alignedSize; // add new entry size

        // If this entry already existed in the old buffer, subtract its old size
        if (pMatchedList[m * 4 + 3] != 0)
        {
            int oldEntryPayloadSize = *(int*)(pMatchedList[m * 4 + 3] + 8); // old payload
            int oldAlignedSize = (oldEntryPayloadSize + 3) & ~3;
            newTotalSize -= 0xC + oldAlignedSize;
        }
    }

    // Use the allocator to allocate a new buffer
    auto* allocVtable = *(int**)pAllocator;
    auto allocBuffFn = (void* (*)(int))(allocVtable[2]); // vtable+8 (allocate? Actually they call vtable+8 first to get something)
    // In decompiled: pcVar1 = *(code **)(*param_2 + 8); then call it, then later call *param_2 (vtable+0)
    // The code calls allocate, then calls getBuffer to get the pointer
    // Let's replicate step by step

    // First call vtable[2] (index 8) – likely prepare/check allocation
    auto prepareFn = (void* (*)(int*))(allocVtable[2]);
    prepareFn(pAllocator);

    // Then call vtable[0] to actually allocate buffer of size newTotalSize
    auto allocFn = (void* (*)(int*))(allocVtable[0]);
    void* newBuffer = nullptr;
    if (newTotalSize > 0)
    {
        // The decompiled code calls vtable[0] with params (size and a reference to buffer)
        // Actually it does: local_34 = 0; local_30 = 0; local_2c = 0; then passes address of local_34 and size to allocFn
        // That suggests allocFn fills a struct with buffer pointer and size? Or it returns pointer.
        // For simplicity, assume allocFn returns pointer
        newBuffer = allocFn(pAllocator);
    }

    if (newBuffer == nullptr)
    {
        return 0; // allocation failed
    }

    int* writePtr = (int*)newBuffer;
    *writePtr = 0; // first int is zero (header?)

    // Now copy entries into new buffer, consulting the matched list
    // Iterate over old buffer and add/update entries
    int oldReadPtr = (bufSize != 0) ? bufData + 4 : 0;
    int oldRemaining = bufSize - 4;
    bool copiedAll = false;

    // Loop over old buffer entries
    while (oldRemaining > 0xC)
    {
        int* entry = (int*)oldReadPtr;
        bool isMatched = false;
        for (uint32 m = 0; m < matchedCount; m++)
        {
            if (pMatchedList[m * 4 + 3] == oldReadPtr) // original pointer matches
            {
                // This entry is matched – write new data from the local temp
                int payloadSize = pMatchedList[m * 4 + 2];
                int alignedSize = (payloadSize + 3) & ~3;
                writePtr[0] = pMatchedList[m * 4 + 0]; // pointer1
                writePtr[1] = 0; // pointer2 is 0?
                writePtr[2] = payloadSize;

                // Call virtual function on pointer1 (vtable+8) to copy payload
                auto* obj = (void*)pMatchedList[m * 4 + 0];
                auto* objVtable = *(int**)obj;
                auto copyFn = (void (*)(void*, void*, int))(objVtable[2]); // vtable+8
                copyFn(obj, (void*)&writePtr[3], payloadSize);
                // Actually the decompiled code passes writePtr+3 as destination

                writePtr += 3 + (alignedSize / 4);
                isMatched = true;
                break;
            }
        }

        if (!isMatched)
        {
            // Unchanged entry: copy as-is
            int payloadSize = entry[2];
            int alignedSize = (payloadSize + 3) & ~3;
            int entrySize = 0xC + alignedSize;
            memcpy(writePtr, entry, entrySize);
            writePtr = (int*)((char*)writePtr + entrySize);
        }

        // Advance old read pointer
        int entrySize = 0xC + ((entry[2] + 3) & ~3);
        oldRemaining -= entrySize;
        oldReadPtr += entrySize;
    }

    // After processing old buffer, add any matched ghosts that were NOT already in the buffer
    if ((int)((int)newBuffer + (newTotalSize - (int)writePtr)) > 0xC && matchedCount > 0)
    {
        for (uint32 m = 0; m < matchedCount; m++)
        {
            if (pMatchedList[m * 4 + 3] == 0) // not already in buffer
            {
                int payloadSize = pMatchedList[m * 4 + 2];
                int alignedSize = (payloadSize + 3) & ~3;
                writePtr[0] = pMatchedList[m * 4 + 0];
                writePtr[1] = 0;
                writePtr[2] = payloadSize;

                auto* obj = (void*)pMatchedList[m * 4 + 0];
                auto* objVtable = *(int**)obj;
                auto copyFn = (void (*)(void*, void*, int))(objVtable[2]);
                copyFn(obj, (void*)&writePtr[3], payloadSize);

                writePtr = (int*)((char*)writePtr + 0xC + alignedSize);
            }
        }
    }

    // Free old buffer if it existed
    if (allocator != 0)
    {
        auto* allocObj = *(int**)allocator;
        auto freeFn = (void (*)(void*))(allocObj[1]); // vtable+4? Actually they call vtable[1] (index 4) to free data
        freeFn((void*)bufData);
        // The code also calls vtable[3] (index 12) to free allocator itself?
        // It sets allocator to null later.
        bufData = 0;
        bufSize = 0;
        auto destroyFn = (void (*)(void*))(allocObj[3]); // vtable+12
        destroyFn((void*)allocator);
        *(int*)(thisPtr + 0x14) = 0;
    }

    // Store new data
    if (newBuffer != nullptr)
    {
        *(int*)(thisPtr + 0x14) = (int)pAllocator; // store allocator interface
        *(int*)(thisPtr + 0x1c) = (int)newBuffer;
        *(int*)(thisPtr + 0x18) = newTotalSize;
    }

    return 1;
}