// FUNC_NAME: NetSession::attemptConnect

int __fastcall NetSession::attemptConnect(void* thisPtr)
{
    // Network initialization check (global)
    if (!isNetworkInitialized()) {
        return 1; // Network not ready
    }

    // Virtual function at +0x9c: check if already connected or something
    typedef bool (__thiscall* IsConnected)(void*);
    if (!((IsConnected)(*(void**)((char*)thisPtr + 0x9c)))()) {
        int handshakeResult = performHandshake(); // returns non-zero to abort
        if (handshakeResult != 0) {
            return handshakeResult;
        }
    }

    // Form IP address string from object fields at +0x80..+0x8c
    wchar_t ipString[44]; // enough for "xxx.xxx.xxx.xxx"
    swprintf(ipString, L"%d.%d.%d.%d",
        *(int*)((char*)thisPtr + 0x80),  // +0x80: IP octet 1
        *(int*)((char*)thisPtr + 0x84),  // +0x84: IP octet 2
        *(int*)((char*)thisPtr + 0x88),  // +0x88: IP octet 3
        *(int*)((char*)thisPtr + 0x8c)); // +0x8c: IP octet 4

    // Prepare buffer for response (2048 bytes)
    char responseBuffer[2048];

    // Virtual function at +0xa0: send a packet containing our IP (e.g., to master server)
    typedef bool (__thiscall* SendPacket)(void*, const wchar_t*, void*, const wchar_t*, int);
    if (!((SendPacket)(*(void**)((char*)thisPtr + 0xa0)))(
            L"connect",    // message type/command
            thisPtr,       // object context?
            ipString,      // our IP as wide string
            responseBuffer, // buffer for any reply
            0x800))        // buffer size
    {
        return 3; // Send failed
    }

    // Check if we received a port number in the first short of the response
    short receivedPort = *(short*)responseBuffer; // responseBuffer[0] as short
    if (receivedPort != 0) {
        startListening(); // Set up a listening socket
        int bindResult = bindSocket(receivedPort, /* additional arg (uninitialized in decomp)? */ 0);
        if (bindResult < 0) {
            cleanupConnection();
            return 4; // Bind failed
        }
        cleanupConnection();
    }

    return 0; // Success
}