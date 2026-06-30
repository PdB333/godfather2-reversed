// FUNC_NAME: MessageSystem::dispatch
// Function address: 0x00609340
// Role: Dispatches messages to object handlers in the EARS engine.
// Handles object creation (messageType 0), destruction (messageType 4), and other events.
// Uses a global table of ObjectNode structures (0x38 bytes each) indexed by handle.
// The handle is passed in EAX (first register parameter).

#include <cstdint>

// Globals (likely provided by the engine)
extern uintptr_t g_messageSystem;          // DAT_01205750 - singleton pointer to MessageSystem
extern uint8_t g_objectTable[];            // DAT_011a0f28 - array of ObjectNode (size 0x38 per entry)
extern uint32_t g_createdFlag;             // DAT_01223538 - flag indicating a new object was created
extern uint32_t g_secondaryTable[];        // DAT_00f158f0 - lookup table for param2 when flags & 2 is set

// Forward declaration of helper
uint32_t getNextAvailableHandle();          // FUN_00609260 - returns a new handle for creation

// Structure representing an entry in the object table
struct ObjectNode {
    uint8_t unknown_0x00[0x0C];           // +0x00
    uint32_t flags;                        // +0x0C
    uint8_t unknown_0x10[0x04];           // +0x10
    void* handler1;                        // +0x14 - primary handler (vtable)
    void* handler2;                        // +0x18 - secondary handler (vtable)
    uint32_t nextHandle;                   // +0x1C - linked list next handle
    uint8_t unknown_0x20[0x18];           // +0x20 to +0x38 (size 0x38 total)
};

// MessageSystem vtable offsets (relative to base of g_messageSystem)
// +0x94: processMessage(MessageSystem* this, int messageType, void* data)
// +0x9C: destroyObject(MessageSystem* this, void* data)

void __fastcall MessageSystem::dispatch(
    uint32_t handle,              // in EAX at entry
    int param2,                   // param_2 in decompiled
    int messageType,              // param_3
    void** outData,                // param_4 - output pointer
    int param5                     // param_5
) {
    // Check if handle and param2/param5 match (likely to avoid redundant dispatch)
    if (handle == reinterpret_cast<uint32_t>(outData) && param2 == param5) {
        return;
    }

    ObjectNode* node = nullptr;
    uint32_t effectiveHandle = handle;

    // If handle is 0, handle special broadcast cases
    if (handle == 0) {
        if (messageType == 4) {
            // Destroy broadcast
            void* data = nullptr;
            // Call destroy via vtable at +0x9C
            (*(void(__thiscall*)(void*, void*))(*reinterpret_cast<uintptr_t*>(g_messageSystem) + 0x9C))
                (reinterpret_cast<void*>(g_messageSystem), data);
            return;
        }
        if (messageType != 0) {
            // Process message with null data
            (*(void(__thiscall*)(void*, int, void*))(*reinterpret_cast<uintptr_t*>(g_messageSystem) + 0x94))
                (reinterpret_cast<void*>(g_messageSystem), messageType, nullptr);
            return;
        }
        // messageType == 0: create new object
        uint32_t newHandle = getNextAvailableHandle();
        (*(void(__thiscall*)(void*, int, void*))(*reinterpret_cast<uintptr_t*>(g_messageSystem) + 0x94))
            (reinterpret_cast<void*>(g_messageSystem), 0, reinterpret_cast<void*>(newHandle));
        g_createdFlag = 1;
        return;
    }

    // Resolve node from handle
    if (handle < 0x1000) {
        node = reinterpret_cast<ObjectNode*>(&g_objectTable[handle * 0x38]);
    } else {
        node = nullptr; // invalid handle
    }

    // If messageType is not destroy, follow the linked list (nextHandle at +0x1C)
    if (messageType != 4 && node != nullptr) {
        uint32_t nextHandle = node->nextHandle; // +0x1C
        if (nextHandle != 0) {
            if (nextHandle < 0x1000) {
                node = reinterpret_cast<ObjectNode*>(&g_objectTable[nextHandle * 0x38]);
            } else {
                node = nullptr;
            }
        }
    }

    // Process the message based on flags
    if (node != nullptr) {
        if ((node->flags & 2) == 0) {
            if ((node->flags & 4) == 0) {
                // Normal path: use handler1 if present, else handler2
                void* handler = node->handler1; // +0x14
                if (handler != nullptr) {
                    // Call handler vtable +0x48 with (handler, param2, &outData)
                    (*(void(__thiscall*)(void*, int, void**))(*reinterpret_cast<uintptr_t*>(handler) + 0x48))
                        (handler, param2, outData);
                } else {
                    handler = node->handler2; // +0x18
                    if (handler != nullptr) {
                        // Call handler vtable +4 (likely release or decrement)
                        (*(void(__thiscall*)(void*))(*reinterpret_cast<uintptr_t*>(handler) + 4))(handler);
                    }
                }
            }
        } else {
            // Flags bit1 set: use handler1 with param2 looked up in secondary table
            void* handler = node->handler1; // +0x14
            if (handler != nullptr) {
                // Call handler vtable +0x48 with (handler, g_secondaryTable[param2], 0, &outData)
                (*(void(__thiscall*)(void*, uint32_t, int, void**))(*reinterpret_cast<uintptr_t*>(handler) + 0x48))
                    (handler, g_secondaryTable[param2], 0, outData);
            }
        }
    }

    // Handle messageType-specific final actions
    if (messageType == 4) {
        // Destroy: call destroy on the system with outData
        (*(void(__thiscall*)(void*, void*))(*reinterpret_cast<uintptr_t*>(g_messageSystem) + 0x9C))
            (reinterpret_cast<void*>(g_messageSystem), *outData);
        // If creation flag is set, also call processMessage with 0 and the new handle
        if (g_createdFlag != 0) {
            uint32_t newHandle = getNextAvailableHandle();
            (*(void(__thiscall*)(void*, int, void*))(*reinterpret_cast<uintptr_t*>(g_messageSystem) + 0x94))
                (reinterpret_cast<void*>(g_messageSystem), 0, reinterpret_cast<void*>(newHandle));
        }
    } else {
        if (messageType == 0) {
            g_createdFlag = 0; // Reset creation flag
        }
        // Process message normally
        (*(void(__thiscall*)(void*, int, void*))(*reinterpret_cast<uintptr_t*>(g_messageSystem) + 0x94))
            (reinterpret_cast<void*>(g_messageSystem), messageType, *outData);
    }

    // If the original handle's node had a handler2, release it
    // (Note: This uses the original node before following linked list? The decompiled code uses a variable unaff_retaddr which might be the original handler2 pointer)
    // For simplicity, we note this step: release the secondary handler if it exists.
    // This is likely a cleanup step.
    // The original decompiled uses "unaff_retaddr" which is actually the saved stack value of node->handler2? More complex.
}