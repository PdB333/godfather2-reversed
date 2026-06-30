// FUNC_NAME: NetConnection::processNextPacket
void __thiscall NetConnection::processNextPacket(void)
{
    g_processingDepth++; // +0x1205a30: debug/assertion recursion counter increment

    htonl(0); // Potentially a no-op NOP or debug breakpoint placeholder

    // Call virtual method at vtable offset +0x0C (likely handlePacket or processPayload)
    (this->*(this->vtable[0x0C]))();

    // If check returns zero, invoke cleanup/error handler
    if (FUN_00655250() == 0) {
        FUN_00655130(); // handleProcessingError or similar
    }

    g_processingDepth--; // counter decrement
}