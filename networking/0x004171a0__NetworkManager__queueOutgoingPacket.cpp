// FUNC_NAME: NetworkManager::queueOutgoingPacket
void __fastcall NetworkManager::queueOutgoingPacket(int this, void* srcData)
{
    // Call virtual method on the behavior/controller object at offset +0x0C
    // Offset 0x60 in its vtable (slot 24) - likely a "prepareSerialize" or "validate"
    (**(code (__thiscall**)(void*))(*(int*)(this + 0x0C) + 0x60))();

    // Check global condition (e.g., queue active or space available)
    if (FUN_004166b0() != 0) {
        // Global memory pool for small packets (DAT_01206880)
        // The pool maintains a current allocation pointer at offset +0x14
        int* currentPtr = *(int**)(DAT_01206880 + 0x14);
        
        // Write vtable pointer for the allocated packet node
        *(int*)currentPtr = (int)&PTR_LAB_0112467c;   // vtable for packet node
        currentPtr++;                                    // skip vtable (4 bytes)
        
        // Store the 'this' pointer (owner of the queue) in the node
        *(int*)currentPtr = this;
        
        // Align next address to 16-byte boundary
        void* dst = (void*)(((int)currentPtr + 0x13) & 0xFFFFFFF0);
        
        // Update the pool's current pointer
        *(int**)(DAT_01206880 + 0x14) = (int*)dst;
        
        // Copy packet data (0x40 = 64 bytes) into the aligned buffer
        memcpy(dst, srcData, 0x40);
    }
}