// FUNC_NAME: NetMessage::initPacket
// Function address: 0x00556be0
// Role: Initializes a network message buffer with type/flags and calls base constructor.
void __thiscall NetMessage::initPacket(uint messageType, int buffer, int connectionId)
{
    // EAX register contains a value from the caller (likely return of another call)
    int eax; // unknown, passed to base init

    // Call base class constructor (e.g., NetObjectBase::init)
    FUN_00556c80(this, connectionId, eax);

    // Set the message type flags at offset 0x2C of the buffer
    // The type is derived from messageType (shifted right 2 bits) and ORed with 0xC0000000 (high priority bits)
    *(uint *)(buffer + 0x2C) = (messageType >> 2) | 0xC0000000; // +0x2C: messageFlags/type field

    // Acquire a lock (e.g., packet pool mutex)
    FUN_0043b490();

    // Log a profiling event (event ID 0x2001) with the connection ID
    FUN_009f01f0(0x2001, connectionId, 0);
}