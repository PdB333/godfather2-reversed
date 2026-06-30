// FUNC_NAME: NetSession::NetSession
// Reconstructed constructor for a network session object (EARS engine, The Godfather 2)
// Uses multiple inheritance (two vtable pointers at offsets 0x00 and 0x04)
// Sets up fields from passed manager/ID and initializes a sub-object for data flow
// Handles server/client flags and sends creation events based on type ID

#include <cstdint> // for uint32_t

// Forward declarations of called functions
void FUN_006b4ca0(void);
void* FUN_008c74d0(void* ptr);
void FUN_006beed0(uint32_t param, void* fieldPtr, uint32_t value);
void FUN_006bf2b0(void);
int FUN_0043b870(uint32_t globalAddress);
void FUN_009aefd0(void* vtablePtr, uint32_t flags);
void FUN_006bec10(void);
void FUN_008c36b0(uint32_t hash, void* objectOwner, int flag);
void FUN_008c3660(uint32_t hash, void* objectOwner, int flag);

// Global constants (from disassembly)
const uint32_t HASH_TYPE_CLIENT = 0x637b907;
const uint32_t HASH_EVENT_CREATE_SERVER = 0xdb4df9fa;
const uint32_t HASH_EVENT_CREATE_CLIENT = 0x4c2f9353;
const uint32_t GLOBAL_MANAGER = 0x12233a0; // DAT_012233a0 (pointer to some global)
const uint32_t GLOBAL_ALT = 0x1131018;    // DAT_01131018 (another global)

class NetSession {
public:
    // Vtable pointers (inherited from two base classes)
    void* vtable1;          // +0x00, set to PTR_LAB_00d5ebb0
    void* vtable2;          // +0x04, set to PTR_LAB_00d5eb9c
    int32_t unknown0;       // +0x08, initially 0
    // +0x0C (uninitialized)
    void* objectManager;    // +0x10 (param_2)
    uint32_t sessionID;     // +0x14 (param_3)
    void* streamHandle;     // +0x18 (result from FUN_008c74d0)
    // Sub-object starting at +0x1C, initialized by FUN_006beed0
    uint8_t subObject[12];  // +0x1C to +0x27 (covers param_1[7] to param_1[9])
    // +0x28 (param_1[10]) zeroed
    // +0x2C (param_1[0xB]) used in final check (non-zero if sub-object active)
    // +0x30 (param_1[0xC]) zeroed
    // +0x34 (param_1[0xD]) flags (bit 2 set if param_5 true)
    // +0x38 (param_1[0xE]) zeroed
    // +0x3C (param_1[0xF]) zeroed
    // +0x40 (param_1[0x10]) zeroed

    // Constructor
    NetSession(void* objMgr, uint32_t id, uint32_t data, char isServer, char skipInit);
};

NetSession::NetSession(void* objMgr, uint32_t id, uint32_t data, char isServer, char skipInit) {
    // Initialize fields
    unknown0 = 0;
    vtable1 = reinterpret_cast<void*>(0x00d5ebb0); // PTR_LAB_00d5ebb0
    vtable2 = reinterpret_cast<void*>(0x00d5eb9c); // PTR_LAB_00d5eb9c

    objectManager = objMgr;
    sessionID = id;

    // Zero out fields from +0x18 to +0x40
    streamHandle = nullptr;                     // +0x18
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1C) = 0; // top of sub-object
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x20) = 0; // param_1[8]
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x24) = 0; // param_1[9]
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x28) = 0; // param_1[10]
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x2C) = 0; // param_1[0xB]
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x30) = 0; // param_1[0xC]
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x34) = 0; // param_1[0xD]
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x38) = 0; // param_1[0xE]
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x3C) = 0; // param_1[0xF]
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x40) = 0; // param_1[0x10]

    // Global initialization
    FUN_006b4ca0();

    // Get stream handle from object manager (offset 0x40)
    streamHandle = FUN_008c74d0(*reinterpret_cast<void**>(reinterpret_cast<char*>(objMgr) + 0x40));

    // Initialize sub-object at +0x1C with data and value from sessionID's offset 0x54
    uint32_t sessionOffset54 = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(sessionID) + 0x54);
    FUN_006beed0(data, reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x1C), sessionOffset54);

    // Secondary initialization
    FUN_006bf2b0();

    // Server-side flag handling
    if (isServer != '\0') {
        // Set bit 2 in flags field (+0x34)
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x34) |= 2;

        // Check global pointer condition
        void* globalPtr = *reinterpret_cast<void**>(GLOBAL_MANAGER + 4); // *(DAT_012233a0+4)
        if (globalPtr != nullptr && *reinterpret_cast<int*>(globalPtr) != 0x1f30) {
            if (FUN_0043b870(GLOBAL_ALT) != 0) {
                FUN_009aefd0(&vtable2, 0x8000); // Set flag on second vtable
            }
        }
    }

    // Skip initialization flag
    if (skipInit != '\0') {
        FUN_006bec10();
        return;
    }

    // Check if sub-object is active (fields at +0x20 and +0x2C non-zero)
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x20) != 0 &&
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x2C) != 0) {
        // Determine type and send creation event
        uint32_t typeID = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(streamHandle) + 0x54);
        if (typeID != HASH_TYPE_CLIENT) {
            // Not client type -> check if session is client type
            if (*reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(sessionID) + 0x54) == HASH_TYPE_CLIENT) {
                FUN_008c36b0(HASH_EVENT_CREATE_SERVER, objectManager, 0);
            } else {
                FUN_008c3660(HASH_EVENT_CREATE_SERVER, objectManager, 0);
            }
            return;
        }
        // Client type -> send client creation event
        FUN_008c36b0(HASH_EVENT_CREATE_CLIENT, objectManager, 0);
    }
}