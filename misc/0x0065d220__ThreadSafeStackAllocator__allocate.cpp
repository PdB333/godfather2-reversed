// FUNC_NAME: ThreadSafeStackAllocator::allocate
uint __thiscall ThreadSafeStackAllocator::allocate(uint size, int alignment, void* unknownParam, int requiredSize) {
    // 0x00: uint m_ownerThreadId;  // thread ID associated with this allocator
    // 0x04: padding? 
    // 0x08: padding?
    // 0x0C: CRITICAL_SECTION m_cs;
    // ...
    // 0x6C: Allocator* m_fallbackAllocator; // secondary allocator for large requests

    unsigned int result;
    DWORD currentThreadId;
    Allocator* fallback;

    // Get the process-level thread manager
    ProcessManager* procMgr = GetProcessManager(); // FUN_00ad8d40
    if (!procMgr) {
        return 0xFFFFFFFF;
    }

    // Retrieve the thread manager and then the current thread's ID
    ThreadManager* threadMgr = procMgr->getThreadManager(); // vtable+0x34
    if (!threadMgr) {
        return 0xFFFFFFFF;
    }

    CurrentThread* thread = threadMgr->getCurrentThread();  // vtable+0x24
    if (!thread) {
        return 0xFFFFFFFF;
    }

    ThreadInfo* threadInfo = thread->getThreadInfo();       // vtable+0x08
    if (!threadInfo) {
        return 0xFFFFFFFF;
    }

    currentThreadId = threadInfo->getThreadId();           // vtable+0x0C

    // If this allocator is owned by the current thread, perform a swift cleanup/drain
    if (this->m_ownerThreadId == currentThreadId) {
        EnterCriticalSection(&this->m_cs);
        DrainStackAllocations();   // FUN_0065d730
        LeaveCriticalSection(&this->m_cs);
        return size;               // return the requested size as success
    }

    // Not the owning thread – use full slow path
    result = 0;  // param_2 set to 0 in original

    fallback = this->m_fallbackAllocator;  // iVar3 + 0x6c
    if (fallback != nullptr && size > 199) { // large allocation path
        unsigned int bufferSize;
        unsigned int allocatedSize;

        // Call fallback's size query (vtable+0x0C)
        bufferSize = fallback->getBufferSize();  // iVar6

        // Prepare a stack-based frame for dynamic allocation
        // (Original uses __alloca_probe_16, here we simulate with arbitrary buffer)
        StackFrame frame;
        frame.alignment = alignment;
        frame.requiredSize = requiredSize;
        frame.requestedSize = size;
        frame.bufferSize = bufferSize;

        // Call the fallback's allocate method (vtable entry 0)
        allocatedSize = fallback->allocate(size);

        if (allocatedSize < size) {
            // Fallback didn't allocate enough – retry with the obtained size
            return this->doDefaultAllocate(allocatedSize, alignment, requiredSize); // vtable+0x28
        } else {
            // Fallback succeeded – use the full size
            return this->doDefaultAllocate(size, alignment, requiredSize); // vtable+0x28
        }
    } else {
        // No fallback or small size – go directly to default allocation
        StackFrame frame2;
        frame2.requiredSize = requiredSize;
        frame2.alignment = alignment;
        frame2.requestedSize = size;
        frame2.reserved = 0x65d34a;  // SEH marker (ignored in cleanup)

        result = this->doDefaultAllocate(size, alignment, requiredSize); // vtable+0x28
    }

    return result;
}