// FUNC_NAME: MessageHandlerComponent::handleMessage

#include <cstdint>

// Forward declarations
class MessageHandlerComponent;
class Message;
void processFunction_0046efc0(int* pMsg);
bool checkCondition_004c2300(int param);
void callMethod_004086d0(int* pData);
void resetTimer_004c24f0(int* pTimer);
void setState_004c23f0(int state);
void callMethod_004c2130();
void callMethod_004c10b0(MessageHandlerComponent* pObj);
void decrementRef_004088c0(MessageHandlerComponent* pObj);
void sendEvent_00408a00(void* pData, int param);

// Constants for message types (from global data symbols)
static const int kMsgType_012069c4 = 0x012069c4;
static const int kMsgType_012069d4 = 0x012069d4;
static const int kMsgType_0120e924 = 0x0120e924;
static const int kMsgType_012180f8 = 0x012180f8;
static const int kMsgType_012180f0 = 0x012180f0;

// Message structure
struct Message {
    int type;      // message type ID
    int data;      // additional payload
    // Note: maybe more fields, but only these are used
};

// The class that handles messages
class MessageHandlerComponent {
public:
    // Virtual functions table offset constants
    enum VTableOffsets {
        kFunc_0x14c = 0x14c,
        kFunc_0x150 = 0x150,
        kFunc_0x158 = 0x158
    };

    // Member field offsets (from this)
    // +0x000: vtable pointer (implied)
    // +0x184: pointer to some list structure (maybe list of object IDs)
    // +0x188: flags (bitfield)
    // +0x190: (400 decimal) - message type ID for enable/disable toggle
    // +0x198: message type ID for enabling?
    // +0x1a0: message type ID for disabling?
    // +0x1a8: message data storage (for certain message types)
    // +0x1b0: message data storage (for certain message types)
    // +0x1bc: reference counter or timer
    // The parent object is assumed to be at offset -0x3c from this,
    // but actual parent pointer is at this - 0x3c.

    // VTable accessor
    void* getVTable() const {
        // The vtable pointer is at the beginning of the parent object (this - 0x3c)
        return *(void**)(reinterpret_cast<const char*>(this) - 0x3c);
    }

    void callVirtualFunction(uint32_t offset) const {
        void* vtable = getVTable();
        void* funcPtr = *(void**)(reinterpret_cast<char*>(vtable) + offset);
        reinterpret_cast<void(*)(...)>(funcPtr)(); // simplified
    }

    void handleMessage(Message* pMsg) {
        // Call external function on the message (initial processing)
        processFunction_0046efc0(pMsg);

        int msgType = pMsg->type;

        // Branch based on message type

        if (msgType == kMsgType_012069c4) {
            // This message type deals with a list of objects
            uint32_t* pList = *(uint32_t**)(reinterpret_cast<char*>(this) + 0x184);
            if (pList != nullptr && (*(uint8_t*)(reinterpret_cast<char*>(this) + 0x188) & 0x20) != 0) {
                int* pCount = (int*)pList[1]; // count of items
                int* pArray = (int*)*pList;   // start of array
                if (pCount != nullptr) {
                    int* pCurrent = pArray;
                    do {
                        if (*pCurrent != 0) {
                            int adjusted = *pCurrent - 0x48;
                            if (adjusted != 0) {
                                bool check = checkCondition_004c2300(adjusted);
                                if (!check) {
                                    // Call virtual function at vtable+0x158
                                    callVirtualFunction(0x158);
                                }
                            }
                        }
                        pCurrent += 2; // each item is a pair of ints
                        pCount--;
                    } while (pCount != (int*)0);
                }
                // Check another field in the list structure
                if (*(int*)(*(int*)(reinterpret_cast<char*>(this) + 0x184) + 0x10) == 0) {
                    callMethod_004086d0(&kMsgType_012069c4);
                    return;
                }
                resetTimer_004c24f0(*(int*)(reinterpret_cast<char*>(this) + 0x184) + 0xc);
                setState_004c23f0(0);
                return;
            }
        } else if (msgType == kMsgType_012069d4) {
            if ((*(uint8_t*)(reinterpret_cast<char*>(this) + 0x188) & 0x40) != 0) {
                callMethod_004c2130();
                return;
            }
        } else if (msgType == kMsgType_0120e924) {
            // Delegate to parent object's method (this - 0x3c)
            callMethod_004c10b0(reinterpret_cast<MessageHandlerComponent*>(reinterpret_cast<char*>(this) - 0x3c));
            return;
        } else if (msgType == kMsgType_012180f8) {
            // Store message data in specific field
            *(int*)(reinterpret_cast<char*>(this) + 0x1a8) = pMsg->data;
        } else if (msgType == kMsgType_012180f0) {
            // Store message data in another field
            *(int*)(reinterpret_cast<char*>(this) + 0x1b0) = pMsg->data;
        } else if (msgType == *(int*)(reinterpret_cast<char*>(this) + 400)) { // offset 0x190
            // Toggle enabled state (bit 0 of flags)
            if ((*(uint8_t*)(reinterpret_cast<char*>(this) + 0x188) & 1) != 0) {
                // Currently enabled, disable via virtual function
                callVirtualFunction(0x150);
                *(uint32_t*)(reinterpret_cast<char*>(this) + 0x188) ^= 1;
                return;
            }
            // Currently disabled, enable via virtual function
            callVirtualFunction(0x14c);
            *(uint32_t*)(reinterpret_cast<char*>(this) + 0x188) ^= 1;
            return;
        } else if (msgType == *(int*)(reinterpret_cast<char*>(this) + 0x198)) {
            // Enable (set bit 0)
            if ((*(uint8_t*)(reinterpret_cast<char*>(this) + 0x188) & 1) == 0) {
                callVirtualFunction(0x14c);
                *(uint32_t*)(reinterpret_cast<char*>(this) + 0x188) |= 1;
            }
            return;
        } else if (msgType == *(int*)(reinterpret_cast<char*>(this) + 0x1a0)) {
            // Disable (clear bit 0)
            if ((*(uint8_t*)(reinterpret_cast<char*>(this) + 0x188) & 1) != 0) {
                callVirtualFunction(0x150);
                *(uint32_t*)(reinterpret_cast<char*>(this) + 0x188) &= ~1;
            }
            return;
        } else {
            // Unknown message type, just return (done)
            return;
        }

        // For message types that stored data (0x180f8 and 0x180f0), continue here
        // Use the stored data (local variables)
        int storedData = (msgType == kMsgType_012180f8) ? *(int*)(reinterpret_cast<char*>(this) + 0x1a8) :
                         (msgType == kMsgType_012180f0) ? *(int*)(reinterpret_cast<char*>(this) + 0x1b0) : 0;

        // Decrement reference counter at +0x1bc
        if (0 < *(int*)(reinterpret_cast<char*>(this) + 0x1bc)) {
            int newCount = *(int*)(reinterpret_cast<char*>(this) + 0x1bc) - 1;
            *(int*)(reinterpret_cast<char*>(this) + 0x1bc) = newCount;
            if (newCount == 0) {
                // Counter reached zero, delete or cleanup
                decrementRef_004088c0(reinterpret_cast<MessageHandlerComponent*>(
                    (uint32_t)(reinterpret_cast<char*>(this) - reinterpret_cast<char*>(0x3c)) & (uint32_t)this)); // This is the earlier pattern: -(uint)(this != 0x3c) & this, which essentially passes this when this != 0x3c, else 0.
                // Then call parent method
                callMethod_004c10b0(reinterpret_cast<MessageHandlerComponent*>(reinterpret_cast<char*>(this) - 0x3c));
            }
        }

        // Send event with the stored data
        // Note: local_c and local_8 were from decompilation; we combine into struct
        struct EventData {
            int value1;
            int value2;
            char pad; // original local_4 (unused)
        } eventData;
        eventData.value1 = storedData;
        eventData.value2 = pMsg->data;
        eventData.pad = 0;
        sendEvent_00408a00(&eventData, 0);
    }
};