// FUNC_NAME: MessageDispatcher::dispatchMessage
// Function at 0x004560e0: Dispatches incoming messages based on a 32-bit type hash at message+0x8.
// This is a common pattern in EARS engine where messages have a 4-byte type field at offset 8.
// The adjustment of this by -0xC suggests the dispatcher is a sub-object (or derived from a base 12 bytes earlier).

#include <cstdint>

// Forward declarations for handler functions (likely in same translation unit)
void handleCreateRequest(void* obj);       // FUN_004565e0 - e.g., object creation
void handleDeleteRequest();                // FUN_00456460 - e.g., object deletion
void handleUpdateRequest();                // FUN_004564c0 - e.g., update
void handleQueryRequest();                 // FUN_00456430 - e.g., query
void handleSyncBase(void* obj);            // FUN_004562f0 - e.g., sync with base
void handleSyncExtended(void* obj);        // FUN_004563c0 - e.g., extended sync

// Message structure (typical EARS packet header)
struct MessageHeader {
    uint32_t sequenceOrId; // +0x00
    uint32_t flags;        // +0x04
    uint32_t typeHash;     // +0x08  -- type identifier (likely CRC32/Hash)
    // ... payload follows
};

// The class this method belongs to (base offset -0xC from 'this')
class MessageDispatcher {
public:
    // param_1 = this, param_2 = pointer to MessageHeader (or derived struct)
    uint32_t dispatchMessage(MessageHeader* msg);
};

uint32_t MessageDispatcher::dispatchMessage(MessageHeader* msg) {
    uint32_t typeHash = msg->typeHash; // +0x08
    uint32_t result = 0;

    // Object reference for handlers that need the base object (this - 0xC)
    void* baseObject = reinterpret_cast<char*>(this) - 0xC;

    if (typeHash < 0x3615B43D) {
        if (typeHash == 0x3615B43C) {
            // Handle create-related message
            result = handleCreateRequest(baseObject);
            return result;
        }
        if (typeHash < 0x3038FD10) {
            if (typeHash == 0x3038FD0F) {
                result = handleDeleteRequest();
                return result;
            }
            if (typeHash == 0x661992) { // 0x00661992
                result = handleUpdateRequest();
                return result;
            }
        }
        else if (typeHash == 0x33265871) {
            result = handleQueryRequest();
            return result;
        }
    }
    else if (typeHash != 0x361FB6B2) { // ignore this hash? Or default?
        if (typeHash == 0x39030F7C) {
            result = handleSyncBase(baseObject);
        }
        else if (typeHash == 0x390E1228) {
            result = handleSyncExtended(baseObject);
            return result;
        }
    }
    return result;
}