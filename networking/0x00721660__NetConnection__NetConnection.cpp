// FUNC_NAME: NetConnection::NetConnection
void __thiscall NetConnection::NetConnection(void* thisPtr, int arg)
{
    // Base class initialization (probably TNLObject or SimObject)
    baseClassInitialize(arg); // FUN_0099d120

    // Define a type for accessing DWORD offsets
    DWORD* dwThis = (DWORD*)thisPtr;

    // Set up multiple vtable pointers (likely multiple inheritance)
    dwThis[0x1a] = (DWORD)&PTR_LAB_00e32854; // temporary, overwritten below
    dwThis[0]    = (DWORD)&PTR_FUN_00d62028; // primary vtable
    dwThis[0x0f] = (DWORD)&PTR_LAB_00d62018; // secondary vtable 1
    dwThis[0x12] = (DWORD)&PTR_LAB_00d62014; // secondary vtable 2
    dwThis[0x1a] = (DWORD)&PTR_LAB_00d62010; // final secondary vtable 3

    // Two short fields, possibly flags or counters
    *(WORD*)(thisPtr + 0x70) = 0; // offset +0x70
    *(WORD*)(thisPtr + 0x72) = 0; // offset +0x72

    // Debug/diagnostics magic numbers – two blocks of 4 DWORDs
    dwThis[0x1d] = 0xbadbadba;
    dwThis[0x1e] = 0xbeefbeef;
    dwThis[0x1f] = 0xeac15a55;
    dwThis[0x20] = 0x91100911;
    dwThis[0x21] = 0xbadbadba;
    dwThis[0x22] = 0xbeefbeef;
    dwThis[0x23] = 0xeac15a55;
    dwThis[0x24] = 0x91100911;

    // Zero out additional fields
    dwThis[0x1b] = 0; // +0x6C
    dwThis[0x27] = 0; // +0x9C
    dwThis[0x26] = 0; // +0x98
    dwThis[0x25] = 0; // +0x94
}