// FUNC_0045d070: EventManager::unregisterNamedHandler
// Calls: getStringHash (0x4dafd0), initHashKey (0x08260), freeHashNode (0x08af0), destroyHashKey (0x08310)

struct HashNode {
    HashNode* next;           // +0x00
    uint32_t field_0x04;      // +0x04
    uint32_t field_0x08;      // +0x08
    uint32_t dataRef;         // +0x0C - reference count or pointer
    uint32_t key;             // +0x10 - full hash key
    uint16_t flags;           // +0x16 - bit0 = processing flag
};

struct HashKey {
    uint32_t key;             // +0x00
    uint16_t field_0x04;      // +0x04 (unused here)
    uint16_t field_0x06;      // +0x06 (unused here)
};

class CallbackHandler {
public:
    virtual void execute(HashKey* key) = 0; // vtable+4
};

class EventManager {
public:
    CallbackHandler* callbackHandler; // +0xBC

    void unregisterNamedHandler(void* registrationData);
};

extern HashNode* gHashTable[]; // DAT_01162380
extern uint32_t getStringHash(const char* str); // FUN_004dafd0
extern void initHashKey(HashKey* key, uint32_t hash); // FUN_00408260
extern void freeHashNode(); // FUN_00408af0 (no params? likely frees node)
extern void destroyHashKey(HashKey* key); // FUN_00408310

void __thiscall EventManager::unregisterNamedHandler(void* registrationData) {
    HashKey key;
    key.key = 0;
    key.field_0x04 = 0;
    key.field_0x06 = 0;

    // Extract name from registration data
    const char* name = *(const char**)((uint8_t*)registrationData + 4);
    if (name && *name != '\0') {
        uint32_t hash = getStringHash(name);
        initHashKey(&key, hash);
    }

    HashNode** bucketArray = *(HashNode***)((uint8_t*)this + 0xBC);
    uint32_t local_8 = (uint32_t)((uint8_t*)registrationData + 8); // pointer to additional data
    uint32_t local_4 = 0; // unused?
    uint32_t searchKey = key.key;

    if (bucketArray && searchKey && (*(uint8_t*)(bucketArray + 1) & 1)) {
        uint32_t bucketIdx = searchKey & 0xFFF;
        HashNode* node = gHashTable[bucketIdx];
        while (node && node->key != searchKey) {
            node = node->next;
        }

        if (node) {
            uint16_t oldFlags = node->flags;
            node->flags = oldFlags | 1;

            // Call the registered callback with our hash key
            CallbackHandler* handler = *bucketArray; // dereference pointer to get object
            handler->execute(&key); // vtable+4

            // Restore flag, preserving bit0 only if it was set
            node->flags = (oldFlags & 1) | (node->flags & 0xFFFE);

            // If there's a data reference and the flag was not set before, free the node
            if (node->dataRef != 0 && (oldFlags & 1) == 0) {
                freeHashNode(); // likely free(node->dataRef) or free node itself
            }
        }
    }

    destroyHashKey(&key);
}