// FUNC_NAME: PropertyReplicator::mergeProperty
// Function at 0x00584860: Merges a 32-byte property block from incoming or restores from original.
// This is part of the replication system for stateful data blocks.
// The property has a state byte (0 = invalid, 2 = valid) and a data buffer pointer.

#pragma pack(push, 1)
struct PropertyReplicator {
    char* statePtr;      // +0x00: pointer to a single byte (state: 0 = empty, 2 = valid)
    uint32_t* dataBuffer; // +0x04: pointer to 8 dwords (32 bytes) of data
};
#pragma pack(pop)

enum PropertyState : char {
    PROPERTY_STATE_EMPTY = 0,
    PROPERTY_STATE_VALID = 2
};

void __thiscall PropertyReplicator::mergeProperty(PropertyReplicator* original, PropertyReplicator* incoming, uint32_t context) {
    char incomingState = *(char*)*(incoming); // dereference incoming->statePtr

    if (*(char*)(*(this)) != PROPERTY_STATE_VALID) {
        // Current state is not valid
        if (incomingState == PROPERTY_STATE_VALID) {
            // Incoming has valid data: copy it and set state to valid
            uint32_t* destData = this->dataBuffer;       // +0x04
            *(this->statePtr) = PROPERTY_STATE_VALID;    // set state
            uint32_t* srcData = incoming->dataBuffer;     // +0x04
            // Copy 8 dwords (32 bytes)
            destData[0] = srcData[0];
            destData[1] = srcData[1];
            destData[2] = srcData[2];
            destData[3] = srcData[3];
            destData[4] = srcData[4];
            destData[5] = srcData[5];
            destData[6] = srcData[6];
            destData[7] = srcData[7];
        } else {
            // Incoming invalid: set current to empty
            *(this->statePtr) = PROPERTY_STATE_EMPTY;
        }
        return;
    }

    // Current state is valid
    if (incomingState == PROPERTY_STATE_VALID) {
        // Both valid: call the complex merge function (likely resolves conflicts)
        // FUN_005781f0 - merges data with context (e.g., timestamp or interpolation)
        FUN_005781f0(this->dataBuffer, context);
        return;
    }

    // Current valid, incoming invalid: restore from original
    uint32_t* destData = this->dataBuffer;       // +0x04
    uint32_t* srcData = original->dataBuffer;     // +0x04
    destData[0] = srcData[0];
    destData[1] = srcData[1];
    destData[2] = srcData[2];
    destData[3] = srcData[3];
    destData[4] = srcData[4];
    destData[5] = srcData[5];
    destData[6] = srcData[6];
    destData[7] = srcData[7];
}