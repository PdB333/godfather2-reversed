// FUN_00426230: ViewportManager::addViewport
void __thiscall ViewportManager::addViewport(int slotIndex, int x, int y, int width, int height)
{
    // Create a new viewport object from the pool
    VirtualViewport* viewport = (VirtualViewport*)createViewportObject("VirtualViewport");
    
    // Set viewport background or screen dimensions? Call with global screen size and zeros.
    setViewportBackground(g_screenWidth, g_screenHeight, 0, 0);
    
    // Store viewport dimensions in the viewport object
    viewport->m_x = x;       // +0x15C
    viewport->m_y = y;       // +0x160
    viewport->m_width = width;   // +0x164
    viewport->m_height = height; // +0x168
    
    // Check per-thread flag (TLS +0x2C -> structure +0x34)
    // This likely indicates whether viewport tracking is active (e.g., main render thread)
    int* threadDataPtr = *(int**)(*(int*)(__readfsdword(0x2C)) + 0x34);
    if (threadDataPtr == nullptr) {
        // Allocate and add to the viewport node list (global allocator)
        // Each node is 24 bytes: vtable (4), viewport pointer (4), x, y, width, height (4 each)
        int** pNextFree = (int**)(g_viewportNodePool + 0x14);
        **pNextFree = (int)&virtualViewportNodeVTable; // Node vtable
        *pNextFree = *pNextFree + 1; // Advance past vtable slot
        *(int*)*pNextFree = (int)viewport; // Store viewport pointer (offset +4)
        int* currentNode = *pNextFree; // Now points to after viewport pointer (offset +8)
        *(int*)(currentNode + 1) = x;     // offset +8
        *(int*)(currentNode + 2) = y;     // offset +12
        *(int*)(currentNode + 3) = width;  // offset +16
        *(int*)(currentNode + 4) = height; // offset +20
        // Advance free pointer to next node (24 bytes from original node start)
        *pNextFree = currentNode + 6; // 6 ints = 24 bytes
        this->m_viewportSlots[slotIndex] = viewport; // store in array at this+0x14+slotIndex*4
        return;
    }
    
    // If thread flag is non-null, just store without node list
    this->m_viewportSlots[slotIndex] = viewport;
}