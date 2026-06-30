// FUNC_NAME: NetworkEventRegistry::registerEvents
// Function address: 0x0067e140
// Registers network events (RPCs, ghost messages) with the EARS networking layer.
// Called during engine initialization (from 0x00681840).
// Hashes are likely CRC32 of string names for the events.

void NetworkEventRegistry::registerEvents()
{
    uint32_t ptr;

    // Register first event (hash 0x5393ac01) with the result from getNetSession()
    ptr = NetSession::getInstance(); // FUN_009c89c0 - returns a pointer to the net session manager
    NetSession::registerEvent(0x5393ac01, ptr); // FUN_00421670

    // Register second event
    ptr = NetSession::getInstance();
    NetSession::registerEvent(0x9dc401b7, ptr);

    // Register third event using a different manager (likely NetConnection)
    ptr = NetConnection::getInstance(); // thunk_FUN_009c9730 - returns a pointer to the connection manager
    NetSession::registerEvent(0x7a10372b, ptr); // note: same registration function, but different owner?

    // Register fourth event
    ptr = NetSession::getInstance();
    NetSession::registerEvent(0x38b2b8d2, ptr);

    // Register fifth event
    ptr = NetSession::getInstance();
    NetSession::registerEvent(0x67a6002e, ptr);
}