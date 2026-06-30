// FUNC_NAME: NetSession::startLocalServer
// Function address: 0x006a2b50
// Role: Initialize a local network session by calling FUN_006a2950 and then a member function pointer at offset 0x94 to start a server on localhost with game name "The Godfather II".
// Returns: 0 on success, 1 if network init fails, 2 if start fails.

int __thiscall NetSession::startLocalServer(NetSession* this)
{
    bool bNetworkReady; // cVar1
    bool bStartResult;  // cVar1 after call

    // Check if the network subsystem is initialized.
    // FUN_006a2950 likely returns nonzero if ready.
    bNetworkReady = FUN_006a2950();
    if (!bNetworkReady) {
        return 1; // Network not ready
    }

    // Call a stored function pointer at this+0x94.
    // Parameters: L"localhost" (server address), this+0x40 (some buffer, e.g., for session info),
    // L"The Godfather II" (game name), 0 (flags).
    // The function pointer is assumed to be of type: bool (*)(const wchar_t*, void*, const wchar_t*, int)
    // Returning nonzero on success.
    bStartResult = ((bool (__stdcall*)(const wchar_t*, void*, const wchar_t*, int))(*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x94)))
        (L"localhost", reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x40), L"The Godfather II", 0);

    // Convert bool to int: returns 0 on success (bStartResult != 0), 2 on failure (bStartResult == 0).
    // The bitwise expression: (-(uint)(bStartResult) & 0xfffffffe) + 2.
    // if bStartResult true -> 0, false -> 2.
    return (bStartResult ? 0 : 2);
}