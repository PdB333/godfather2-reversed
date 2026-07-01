// FUNC_NAME: TNLConnection::clearPendingFragments
void __thiscall FUN_007f3e50(int this)
{
    // Call virtual function at vtable+0x28 (likely handleTimeoutOrDisconnect or resetSendQueue)
    // Pass 0x20 (32) as parameter - potential timeout value or queue size
    (**(code **)(*(int *)(this + 0x58) + 0x28))(0x20);
    
    // Clear buffer at offset 0x8E0 (pending fragment data) - size 0x80 (128 bytes)
    // +0x8E0 is likely mPendingFragmentBuffer
    FUN_004dde90(this + 0x8E0, 0x80);
    
    return;
}