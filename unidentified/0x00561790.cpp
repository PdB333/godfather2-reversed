// FUN_NAME: NetSession::constructor

void __fastcall NetSession::constructor(NetSession* this)
{
    // Set vtable pointer (passed in EAX)
    *(void**)this = reinterpret_cast<void*>(in_EAX);

    // Short yield/delay loop (5 iterations)
    for (int i = 0; i < 5; i++)
    {
        yield(); // FUN_00aa6480: likely Sleep(0) or SwitchToThread
    }

    // Longer delay (1 second, called twice)
    sleep(0, 1000); // FUN_00aad0e0(0,1000)
    sleep(0, 1000);

    // Initialize network session fields
    this->field_0x144 = 0;          // +0x144: often a state or counter
    this->field_0x148 = 0;          // +0x148
    this->field_0x14C = 0x80000000; // +0x14C: enabled flag (bit 31)
    this->field_0x04 = 4;           // +0x04: version/type identifier
    this->field_0x08 = 0;           // +0x08
    this->field_0x0C = 0x2800;      // +0x0C: buffer size (10240 bytes)
    this->field_0x150 = 0x800;      // +0x150: second buffer size (2048 bytes)

    // Retrieve per‑thread data (TLS)
    DWORD tlsIndex = DAT_01139810;   // global TLS index
    void* tlsBlock = TlsGetValue(tlsIndex);
    // Copy value at offset 0x34 from TLS block into object
    this->field_0x130 = *(int*)((char*)tlsBlock + 0x34); // +0x130

    // Final initialization step
    initComponent(); // FUN_005618d0
}