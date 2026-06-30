// FUNC_NAME: InputDeviceManager::allocateControllerSlot
// Address: 0x00610a80
// Role: Allocates a 0x44-byte controller slot from a free list pool.
//       The pool is part of the InputDeviceManager global singleton.
//       Uses a singly linked list of free blocks. If empty, falls back to a vtable-based allocator.
//       Returns pointer to zeroed memory, or null on failure.

#include <cstring>

class InputDeviceManager {
public:
    // Pool data structure at offsets within InputDeviceManager
    struct ControllerSlotPool {
        void*   m_pFreeListHead;      // +0x400c: head of free list (each block first 4 bytes = next)
        uint32_t m_allocParam1;        // +0x4010: first parameter for fallback allocator
        uint32_t m_allocParam2;        // +0x4014: second parameter for fallback allocator
        int32_t  m_iFreeCount;         // +0x4018: number of free blocks
        int32_t  m_iMinFreeCount;      // +0x401c: low watermark
        void**   m_pAllocatorVTable;   // +0x4020: pointer to allocator vtable (function at index 1)
    };

    // Assume the global InputDeviceManager singleton is at address 0x012058e0
    static InputDeviceManager* s_pInstance;

    // Allocates a controller slot (size 0x44) from the pool
    static void* allocateControllerSlot()
    {
        ControllerSlotPool* pool = &s_pInstance->m_pool; // m_pool at offset 0x400c? Actually we embed the struct
        // In the actual binary, the pool fields are at fixed offsets from the object base.
        // For clarity, we cast the object pointer to the pool structure offset.
        // Here we assume the pool is a member at the appropriate offset.

        void* pSlot = pool->m_pFreeListHead;

        if (pSlot == nullptr)
        {
            // Secondary allocation via vtable
            if (pool->m_pAllocatorVTable == nullptr)
                return nullptr;

            // Allocator function is at vtable[1] (offset 4)
            typedef void* (*AllocFunc)(uint32_t, uint32_t);
            AllocFunc allocator = (AllocFunc)pool->m_pAllocatorVTable[1];
            pSlot = allocator(pool->m_allocParam1, pool->m_allocParam2);
        }
        else
        {
            // Pop from free list
            void* pNext = *(void**)pSlot;
            pool->m_pFreeListHead = pNext;
            pool->m_iFreeCount--;

            // Update low watermark
            if ((uint32_t)pool->m_iFreeCount < (uint32_t)pool->m_iMinFreeCount)
                pool->m_iMinFreeCount = pool->m_iFreeCount;
        }

        // Zero the slot (size 0x44)
        if (pSlot != nullptr)
            std::memset(pSlot, 0, 0x44);

        return pSlot;
    }

private:
    ControllerSlotPool m_pool; // This is a simplification; actual offsets are direct
    // Other members...
};

// Global instance pointer (actual address 0x012058e0)
InputDeviceManager* InputDeviceManager::s_pInstance = (InputDeviceManager*)0x012058e0;