// FUNC_NAME: readTlsDword34
// Address: 0x00483a50
// Reads a 32-bit value from thread-local storage at offset 0x34 relative to the TLS base.
// Uses the standard Windows FS segment access (fs:[0x2C] -> TLS array) to obtain the thread's local data.
uint32 readTlsDword34()
{
    // Get the TLS array pointer from the Thread Information Block (TIB)
    uintptr_t* tlsArray = reinterpret_cast<uintptr_t*>(__readfsdword(0x2C));
    // The first entry in the TLS array is the TLS base address for the current module
    uintptr_t tlsBase = *tlsArray;
    // Return the DWORD stored 0x34 bytes into the TLS area
    return *reinterpret_cast<uint32*>(tlsBase + 0x34);
}