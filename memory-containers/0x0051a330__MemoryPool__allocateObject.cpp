// FUNC_NAME: MemoryPool::allocateObject
void MemoryPool::allocateObject(void)
{
    // Call base initialization (likely sets up object state)
    baseConstruct();
    
    // Get pointer to the current allocation position in the pool (DAT_01206880 + 0x14)
    int* pCurrent = reinterpret_cast<int*>(DAT_01206880 + 0x14);
    
    // Write the vtable pointer at the current position
    *reinterpret_cast<void**>(*pCurrent) = reinterpret_cast<void*>(&PTR_LAB_01125180);
    (*pCurrent) += 4; // Advance past vtable pointer
    
    // Align to next 4-byte boundary
    uint32_t aligned = (*pCurrent + 3) & ~3;
    *pCurrent = aligned;
    
    // Store the object address (returned by constructor via in_EAX) at the aligned position
    reinterpret_cast<void* volatile*>(aligned)[0] = reinterpret_cast<void*>(in_EAX);
    (*pCurrent) += 4; // Advance past stored pointer
}