// FUNC_NAME: EventScheduler::dispatchFromHashParts
// Address: 0x006b6c50
// Role: Computes a 32-bit hash from four 32-bit fields (polynomial base-33) and dispatches to a global event handler.
// The object layout begins with uint32 hashParts[4] at offsets 0x00, 0x04, 0x08, 0x0C.
// The call to 0x008142f0 likely registers or posts the hash along with a context parameter.

extern void EventDispatch(int type, uint32_t hash, uint32_t context, int flag);

class EventScheduler {
public:
    uint32_t hashParts[4];  // +0x00: Parts of a 128-bit hash or packed string
    // ... other internal fields
};

void __thiscall EventScheduler::dispatchFromHashParts(uint32_t contextParam) {
    uint64_t acc;

    // Polynomial hash: ((a*33 + b)*33 + c)*33 + d
    acc = (uint64_t)hashParts[0] * 33 + hashParts[1];
    acc = acc * 33 + hashParts[2];
    acc = acc * 33 + hashParts[3];

    uint32_t hash = (uint32_t)acc;

    // Dispatch the computed hash with the given context
    EventDispatch(2, hash, contextParam, 1);
}