// FUNC_NAME: NetSession::processGhostUpdate
// Function address: 0x00657220
// Role: Handles an update packet for a replicated ghost object from the network stream.
// The function searches for a matching ghost entry using the provided key, then reads
// field updates from the bitstream and applies them to the ghost.
// It also manages creation, destruction, and state transitions of ghost objects.

#include <cstdint>
#include <cstring>

// Forward declarations of internal functions with reconstructed names
void* memset(void*, int, size_t);
bool isLocalSession(); // FUN_00654910
bool isOnlineSession(); // FUN_006549b0
int  getGlobalContextId(); // FUN_00655250
void sessionStateChange(void* thisPtr); // FUN_00656440
void beginBitstreamRead(void* stream); // FUN_0065a5e0
bool readBitFromStream(void* stream, void* buffer); // FUN_0064ca10
void* allocateMemory(size_t size); // FUN_009c8e50
void* deserializeObjectFromStream(void* stream); // FUN_00654840
void onObjectUpdated(); // FUN_00657960
void linkObjectToGhost(void* ghostList, void** outRef, void* object); // FUN_0065e570
void endObjectUpdateSequence(); // FUN_006544b0
void decrementRefCount(void* obj); // inline
void cleanupSomeState(); // FUN_00656aa0
void clearMemory(void* ptr, size_t size); // FUN_0064b9e0 (memset)
void copyMemory(void* dest, void* src, size_t size); // FUN_0065bf00 (memcpy possibly)
char getCurrentUpdatePhase(); // FUN_0046d790
void handleGlobalGhost(void* thisPtr, int contextId); // FUN_006576b0
void createGhostEffect(void* dest, void* src); // FUN_0065a500
void signalObjectCreated(); // FUN_00653fa0
void sendObjectRemoval(void* thisPtr, short* key); // FUN_00656600
void finishLocalAction(); // FUN_006550d0
void startLocalAction(); // FUN_00655420

struct GhostEntry {
    uint32_t vtable;
    // many fields...
    int field_0x24;   // +0x24 (some handle)
    int field_0x28;   // +0x28
    int field_0x2a;   // +0x2a
    int field_0x2c;   // +0x2c (count or size)
    int field_0x30;   // +0x30 (capability flag)
    int field_0x40;   // +0x40 (key part 0-3)
    int field_0x44;   // +0x44 (key part 4)
    int field_0x54;   // +0x54 (pointer to attached object, refcounted)
    int field_0x55;   // +0x55 (some list pointer)
    int field_0x61;   // +0x61 (count of key entries)
    int field_0x66;   // +0x66 (phase/state byte)
    int field_0x6d;   // +0x6d (ghost type/state)
    int field_0x64;   // +0x64 (100? index? actually 0x64 bytes from base)
    int field_0x100;  // +0x100 (key storage start)
    // Ghost key array at offset +0x63c? Actually piVar11[99] => offset 99*4 = 0x18c
    // The key array is short[10] per entry? Not precise.
};

struct BitStream {
    uint8_t* buffer;   // +0x0c (bit buffer pointer)
    uint32_t bitPos;   // +0x18 (current bit position)
    uint32_t bitSize;  // +0x2c (total bit size)
    uint8_t overflow;  // +0x1c (overflow flag)
    // other fields
};

void NetSession::processGhostUpdate(short* objectKey, BitStream* stream) {
    // local variable declarations as per decompiled
    GhostEntry* matchedGhost = nullptr;
    int numEntries;
    int entryIndex;
    short* keyList;
    int* entryPtrArray;  // array of pointers to GhostEntry
    int* currentEntryPtr;
    int* outRef = nullptr;
    int local_504 = 0;
    char phase;
    int contextId;

    // Initialize some local state
    clearMemory(&local_504, 0x40); // actually clearing a local buffer, but simplified

    contextId = getGlobalContextId();
    if (contextId != 0 && isLocalSession()) {
        sessionStateChange(this);
        return;
    }

    numEntries = *(int*)((uint8_t*)this + 0x24); // number of entries in ghost array
    entryPtrArray = *(int**)((uint8_t*)this + 0x2c); // array of GhostEntry pointers
    entryIndex = 0;

    // Search for matching ghost entry by key
    if (numEntries > 0) {
        currentEntryPtr = entryPtrArray;
        do {
            matchedGhost = (GhostEntry*)*currentEntryPtr;
            if (matchedGhost->field_0x6d == 2 && // ghost type 2
                *(char*)&matchedGhost->field_0x64 == 0 && // some flag cleared
                !isOnlineSession()) {
                // Compare the key: objectKey is a packed 20-byte key (5 ints)
                int keyCount = matchedGhost->field_0x61;
                if (keyCount > 0) {
                    keyList = (short*)matchedGhost->field_0x18c; // offset 99*4 = 0x18c?
                    // Actually piVar11[99] -> offset 0x18c (assuming 32-bit pointers)
                    int j = 0;
                    do {
                        if (*objectKey == *keyList &&
                            *(int*)(objectKey + 1) == *(int*)(keyList + 1) &&
                            *(int*)(objectKey + 2) == *(int*)(keyList + 2) &&
                            *(int*)(objectKey + 3) == *(int*)(keyList + 3) &&
                            *(int*)(objectKey + 4) == *(int*)(keyList + 4)) {
                            break; // match found
                        }
                        j++;
                        keyList += 10; // each key entry is 10 shorts = 20 bytes
                    } while (j < keyCount);
                }
                if (j != keyCount) {
                    // key found
                    break;
                }
            }
            entryIndex++;
            currentEntryPtr++;
        } while (entryIndex < numEntries);
    }

    if (entryIndex == numEntries) {
        // No matching ghost
        return;
    }

    // Begin reading field update
    beginBitstreamRead(stream);
    if (!readBitFromStream(stream, &local_504)) {
        // Cleanup linked list if any
        if (outRef != nullptr) {
            uint32_t* next;
            do {
                next = (uint32_t*)outRef[2];
                outRef[0] = 0;
                outRef[1] = 0;
                outRef[2] = 0;
                outRef = (int*)next;
            } while (next != nullptr);
        }
        return;
    }

    // Align stream position to 8 bytes
    stream->bitPos = (stream->bitPos + 7) & ~7;

    clearMemory(&local_504, 0x40); // clear again

    if (isOnlineSession()) {
        if (outRef != nullptr) {
            uint32_t* next;
            do {
                next = (uint32_t*)outRef[2];
                outRef[0] = 0;
                outRef[1] = 0;
                outRef[2] = 0;
                outRef = (int*)next;
            } while (next != nullptr);
        }
        return;
    }

    // Read bit to determine if this ghost has updates
    uint32_t bitPos = stream->bitPos;
    if (bitPos >= stream->bitSize) {
        stream->overflow = 1;
    } else {
        uint8_t byteVal = *((uint8_t*)((uint8_t*)stream->buffer + (bitPos >> 3)));
        stream->bitPos = bitPos + 1;
        if (byteVal & (1 << (bitPos & 7))) {
            // Bit set => there is an update
            if (*(int*)((uint8_t*)this + 0x30) == 0) {
                goto cleanup;
            }
            *(uint8_t*)((uint8_t*)matchedGhost + 0x131) = 1; // flag

            // Create update object
            int newObj = (int)allocateMemory(0x24);
            if (newObj) {
                newObj = (int)deserializeObjectFromStream(stream);
            }
            // Replace the attached object (refcounted)
            int oldObj = matchedGhost->field_0x54;
            if (oldObj) {
                decrementRefCount((void*)oldObj);
            }
            matchedGhost->field_0x54 = newObj;
            if (newObj) {
                incrementRefCount((void*)newObj);
            }

            onObjectUpdated();

            // Align again
            stream->bitPos = (stream->bitPos + 7) & ~7;

            linkObjectToGhost((void*)matchedGhost->field_0x55, &outRef, (void*)matchedGhost->field_0x54);

            endObjectUpdateSequence();

            // Release outRef if we had one from linking
            if (outRef) {
                decrementRefCount(outRef);
            }

            // Read next field: a flag
            beginBitstreamRead(stream);
            if (!readBitFromStream(stream, &local_504)) {
                cleanupSomeState();
                goto cleanup;
            }

            // Clear ghost buffer for future updates
            clearMemory((uint8_t*)matchedGhost + 0x162, 0x80);
            copyMemory((uint8_t*)matchedGhost + 0x172, 0, 0x10); // zero out

            cleanupSomeState();
        }
    }

    phase = getCurrentUpdatePhase();
    *(uint8_t*)((uint8_t*)matchedGhost + 0x66) = phase;

    clearMemory(&outRef, 0x20);

    if (contextId != 0) {
        handleGlobalGhost(this, contextId);
    }

    // Copy the key into the ghost's key storage (partial)
    *(uint64_t*)((uint8_t*)matchedGhost + 0x100) = *(uint64_t*)objectKey; // first 8 bytes
    *(uint64_t*)((uint8_t*)matchedGhost + 0x108) = *(uint64_t*)(objectKey + 4); // next 8 bytes
    matchedGhost->field_0x44 = *(int*)(objectKey + 8);

    matchedGhost->field_0x28 = (int)outRef;
    matchedGhost->field_0x24 = (int)outRef;
    matchedGhost->field_0x2a = (int)outRef;

    if (*(uint8_t*)((uint8_t*)matchedGhost + 0x131) != 0) {
        int effectBuffer = (int)allocateMemory(0x274);
        if (effectBuffer) {
            createGhostEffect((void*)effectBuffer, (uint8_t*)matchedGhost + 0x172);
        }
        signalObjectCreated();
    }

    local_504 = 0;
    char result = ((int (__thiscall*)(GhostEntry*, BitStream*, int*))((uint32_t*)matchedGhost->vtable)[9])(matchedGhost, stream, &local_504);
    if (result == 0) {
        sendObjectRemoval(this, objectKey);
        finishLocalAction();
    } else {
        startLocalAction((int)matchedGhost);
        finishLocalAction();
        matchedGhost->field_0x6d = 7;
        ((void (__thiscall*)(GhostEntry*))((uint32_t*)matchedGhost->vtable)[5])(matchedGhost); // vtable[5] = some virtual function
        sessionStateChange(this);
    }

cleanup:
    cleanupSomeState();
    return;
}