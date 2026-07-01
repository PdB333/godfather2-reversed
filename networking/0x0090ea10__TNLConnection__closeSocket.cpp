// FUNC_NAME: TNLConnection::closeSocket
void __fastcall TNLConnection::closeSocket(int thisPtr)
{
    uint flags = *(uint *)(thisPtr + 0xb0); // +0xB0: connection state flags
    if (((flags & 0x8) == 0) || ((flags & 0x1) == 0)) {
        // State invalid: log error
        logError(&g_debugContext);
    }
    else if (*(int *)(thisPtr + 0xb8) != -1) { // +0xB8: socket handle
        // Close the socket
        destroySocket(*(int *)(thisPtr + 0xb8));
        // Clear the pending close flag (bit 3)
        *(uint *)(thisPtr + 0xb0) = flags & 0xFFFFFFF7;
        // Invalidate socket handle
        *(int *)(thisPtr + 0xb8) = -1;
        return;
    }
    // Clear the pending close flag
    *(uint *)(thisPtr + 0xb0) = flags & 0xFFFFFFF7;
}