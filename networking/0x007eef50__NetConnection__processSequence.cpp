// FUNC_NAME: NetConnection::processSequence
void __thiscall NetConnection::processSequence(NetConnection* this, int sequence, uint extraData)
{
    // Field at +0x4: base sequence number or window start
    int baseSequence = *(int*)((uint8_t*)this + 0x4);
    
    if (sequence == 0) {
        // Zero sequence is invalid; reset connection
        errorReset();
        return;
    }
    
    // Sequence validation logic
    if (baseSequence == 0 || baseSequence == 0x48) {
        // Initial or special state: set state byte to 0xFF and clear bit 0 of flags (e.g., "unreliable" flag)
        *(uint8_t*)((uint8_t*)this + 0x12) = 0xFF;
        *(uint16_t*)((uint8_t*)this + 0x10) &= 0xFFFE;
    } else {
        // Compute expected sequence from base
        int expected = (baseSequence == 0) ? 0 : (baseSequence - 0x48);
        if (expected != sequence) {
            // Mismatch: likely an out-of-order or duplicate packet
            errorReset();
        }
    }
    
    // Store the extra data (e.g., timestamp)
    *(uint32_t*)((uint8_t*)this + 0xC) = extraData;
    
    if (baseSequence == 0 || baseSequence == 0x48) {
        // Initialize sequence tracking
        initSequence(sequence);
        // Compute initial state byte (e.g., expected ACK or window position)
        *(uint8_t*)((uint8_t*)this + 0x12) = computeState(this);
    }
    
    // Update internal state (e.g., advance window)
    updateState(this);
}