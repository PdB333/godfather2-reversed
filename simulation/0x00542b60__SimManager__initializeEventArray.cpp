// FUNC_NAME: SimManager::initializeEventArray
void __thiscall SimManager::initializeEventArray(SimManager* this, uint scopeId) {
    // Profiler scope push
    profiler::pushScope(scopeId);
    profiler::setScopeColor(scopeId, 0xb390b11a);
    profiler::setScopeEnabled(true);
    
    // Check if we should call virtual functions related to profiling
    bool bVar6;
    if (this->m_profileFlag == 0) {
        bVar6 = *this->m_profileCounter == 0;
    } else {
        bVar6 = this->m_profileCompareA == this->m_profileCompareB;
    }
    
    if (!bVar6) {
        // Create a scope string buffer (12 bytes)
        char scopeBuffer[12] = {0};
        profiler::createScope(scopeBuffer); // likely writes a formatted scope name
        // Call virtual functions
        (this->vtable[0x28])(scopeBuffer);  // onProfilerEvent
        (this->vtable[0x194])();            // flush or update
    }
    
    // Second scope (pop/end)
    profiler::setScopeColor(scopeId, 0xf8b45dfb);
    profiler::setScopeEnabled(false);
    
    // Again check condition
    if (this->m_profileFlag == 0) {
        bVar6 = *this->m_profileCounter == 0;
    } else {
        bVar6 = this->m_profileCompareA == this->m_profileCompareB;
    }
    
    if (!bVar6) {
        // A different virtual call? offset 0xb0 = 176 bytes? Actually param_1+0xb0 is field at +0x2C0? 
        profiler::endScope((int*)((char*)this + 0x2C0)); // +0x2C0 = param_1[0xb0]
    }
    
    // Initialize the event array if not done yet
    if (this->m_eventArrayInitialized == 0) { // +0x2D8 = param_1[0xb6]
        uint count = this->m_eventArrayCount; // +0x2BC = param_1[0xaf]
        if (count != 0) {
            uint allocSize = count * 8;
            // Custom allocator
            uint* memory = (uint*)allocator::allocate(allocSize + 4);
            if (memory != nullptr) {
                uint* arrayBegin = memory + 1;
                *memory = count; // store count at head
                // Construct each 8-byte element using internal constructor
                _vector_constructor_iterator_(arrayBegin, 8, count, (_func_void_ptr_void_ptr*)&elementConstructor);
                this->m_eventArray = (EventElement*)arrayBegin; // +0x2B8 = param_1[0xae]
                
                // Initialize each element (clear or reset)
                for (uint i = 0; i < count; i++) {
                    EventElement* element = &this->m_eventArray[i];
                    if (element->somePtr != 0) {
                        elementDestructor(element); // FUN_004daf90
                        element->somePtr = 0;
                    }
                }
            }
        }
        this->m_eventArrayInitialized = 1; // +0x2D8
    }
    return;
}