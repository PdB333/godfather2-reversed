// Xbox PDB: TNL::Socket
// FUNC_NAME: Socket::closeSocket

// Reconstructed static method for socket destruction cleanup with debug logging
void Socket::closeSocket()
{
    // Socket type: 2 = UDP, 1 = TCP (likely from Net::SocketType enum)
    if (s_socketType == 2)
    {
        if (s_socketValid)
        {
            // Push debug log for UDP socket destructor if not already logged
            if ((s_debugFlags & 1) == 0)
            {
                s_debugFlags |= 1;
                s_udpDebugMsg.msg = "Socket::~Socket";
                s_udpDebugMsg.id = 0xFFFFFFFF;
                s_udpDebugMsg.next = s_debugListHead;
                s_debugListHead = &s_udpDebugMsg;
            }
            // Output the debug message
            debugOutput(&s_udpDebugMsg);

            s_debugMessageCount++;
            // Hit debug message limit? Trigger breakpoint
            if (s_maxDebugMessages != 0 && s_maxDebugMessages <= s_debugMessageCount)
            {
                __asm { swi 3 } // debug breakpoint
                return;
            }

            // Check if pending shutdown condition (e.g., time or pending sends)
            if (s_ignoreDebugCondition == false && s_pendingOpsCount < s_shutdownTimeout)
            {
                return; // Wait for pending operations to complete
            }
            __asm { swi 3 } // debug breakpoint (forcibly close?)
            return;
        }
    }
    else if ((s_socketType == 1) && (s_socketValid))
    {
        // TCP path (similar logging with different flag bit)
        if ((s_debugFlags & 2) == 0)
        {
            s_debugFlags |= 2;
            s_tcpDebugMsg.msg = "Socket::~Socket";
            s_tcpDebugMsg.id = 0xFFFFFFFF;
            s_tcpDebugMsg.next = s_debugListHead;
            s_debugListHead = &s_tcpDebugMsg;
        }
        debugOutput(&s_tcpDebugMsg);
        // Perform TCP‑specific shutdown (e.g., linger, graceful close)
        socketShutdown(); // calls FUN_0065fab0
    }

    // Decrement global socket reference counter
    s_socketRefCount--;
}