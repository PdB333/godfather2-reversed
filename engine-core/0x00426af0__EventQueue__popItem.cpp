// FUNC_NAME: EventQueue::popItem
int* EventQueue::popItem() {
    // this+0x60: bool enabled (non-zero if queue is active)
    if (*(char*)(this + 0x60) != 0) {
        // 00426a90: checks thread state or queue readiness (in_EAX is ignored or global)
        int ready = checkThreadState();  // returns 0 if queue can be read
        if (ready == 0) {
            enterCriticalSection(&g_criticalSection);  // DAT_00e2e6f0
            
            if (*(int*)(this + 0x48) != 0) {  // +0x48: current queue count
                // +0x3c: base address of item pointer array
                // +0x44: current head index (circular)
                int* item = *(int**)( *(int*)(this + 0x3c) + *(int*)(this + 0x44) * 4 );
                
                // Advance head index, wrap if needed
                int newIndex = *(int*)(this + 0x44) + 1;
                *(int*)(this + 0x44) = newIndex;
                if (newIndex >= *(int*)(this + 0x40)) {  // +0x40: capacity
                    *(int*)(this + 0x44) = 0;
                }
                
                // Decrement count
                *(int*)(this + 0x48) = *(int*)(this + 0x48) - 1;
                
                leaveCriticalSection(&g_criticalSection);
                
                // 004c6fa0: post-pop processing (e.g. yield, notify)
                yieldThread();
                
                if (*item == 0) {  // first member indicates validity (0 = deleted/empty)
                    // 00426e40: handle invalid item
                    handleInvalidItem(&item);  // might delete or skip
                    return nullptr;
                }
                
                // 00426f80: handle valid item (maybe dispatch)
                handleValidItem(&item);
                return item;
            }
            
            leaveCriticalSection(&g_criticalSection);
        }
    }
    return nullptr;
}