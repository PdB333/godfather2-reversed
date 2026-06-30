// FUNC_NAME: TNLConnection::constructor(uint8_t flags)
int __thiscall TNLConnection::constructor(TNLConnection* this, uint8_t flags)
{
    // Base initialization (likely sets up network buffers, sequence numbers, etc.)
    TNLConnection::baseInitializer(); // FUN_004c8a80

    // If bit 0 of flags is set, perform additional initialization (e.g., allocate ghost lists)
    if ((flags & 1) != 0) {
        TNLConnection::initGhosting(this); // FUN_009c8eb0
    }

    return this;
}