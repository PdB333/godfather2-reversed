// FUNC_NAME: TNLConnection::cleanupReliable
// Address: 0x00712390
// Destructor or cleanup helper for TNLConnection. Sets vtable to destructor vtable, releases the reliable packet buffer (offset +0x5C), then calls global memory cleanup.

void __fastcall TNLConnection::cleanupReliable(TNLConnection* this)
{
    // +0x00: vtable pointer
    this->vtable = (void**)&PTR_FUN_00d6198c;

    // +0x5C: Pointer to reliable packet buffer (TNL::ReliableBuffer*)
    if (this->reliableBuffer != 0)
    {
        // FUN_0071bc70 is TNL::ReliableBuffer::release (or similar)
        FUN_0071bc70(this->reliableBuffer);
        this->reliableBuffer = 0;
    }

    // FUN_0071e870 is TNL::MemoryManager::cleanup (or global pool flush)
    FUN_0071e870();
}