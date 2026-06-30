// FUNC_NAME: NetSession::handleMessage
int NetSession::handleMessage() {
    void* packetData = *(void**)(this + 4);        // +0x4: pointer to packet payload
    int messageType = *(int*)(this + 0xC);         // +0xC: message type identifier

    switch (messageType) {
    case 0x102: // e.g., MSG_CONNECT_REQUEST
        handleConnectRequest();
        return 1;

    case 0x103: // e.g., MSG_CONNECT_ACCEPT
        resetConnectionState();
        processAcceptData();
        processConnectionData(packetData);
        return 0;

    case 0x108: // e.g., MSG_RELIABLE_DATA
        processReliableData(packetData);
        return 0;

    case 0x109: // e.g., MSG_UNRELIABLE_DATA
        processUnreliableData(packetData);
        return 0; // but note: later code may rehandle this case below

    case 0x10A: // e.g., MSG_ACK
        processAck(packetData);
        return 0;

    case 0x10C: // e.g., MSG_KEEPALIVE
        // Fall through to post-switch handling
        break;

    case 0x110: // e.g., MSG_OBJECT_UPDATE
        processObjectUpdate(packetData);
        return 0;

    case 0x111: // e.g., MSG_PING
        handlePingResponse();
        return 1;

    case 0x115: // e.g., MSG_DISCONNECT
        disconnectHandler();
        return 0;

    default:
        handleUnknownMessage();
        return 0;
    }

    // Handle MSG_KEEPALIVE and also special case for MSG_UNRELIABLE_DATA
    resetConnectionState();
    if (messageType == 0x109 && checkUnreliableDataAvailable() != 0) {
        handleUnreliableDataRetransmit();
        return 0;
    }
    processPendingMessages();
    return 0;
}