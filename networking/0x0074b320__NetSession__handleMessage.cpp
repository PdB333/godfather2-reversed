// FUNC_NAME: NetSession::handleMessage

#include <cstdint>

// Forward declarations for called functions (inferred)
extern void netMessageSetup(); // FUN_0074a9d0
extern bool isGameLoaded();    // FUN_00717700
extern bool isMissionActive(); // FUN_00717cc0
extern bool isNetworkActive(); // FUN_0072d630
extern void* allocNetworkBuffer(int zero, int zero2); // FUN_006fbc40
extern void sendReliableMessage(uint32_t hash, int zero, void* buffer, uint32_t flags); // FUN_007f96a0
extern void freeNetworkBuffer(); // FUN_006fbc70
extern void clearBufferQueue(void* bufferQueue); // FUN_0074a040 (param_1 + 0x90)
extern int resolveEntityId(uint32_t id); // FUN_006eafe0
extern void sendUnreliableMessage(int entityId, int zero, void* buffer, uint32_t flags); // FUN_006f3eb0
extern bool handleOtherMessage(void* param_2, void* param_3, void* param_4, int messageType, void* param_6); // FUN_0074abd0 (default handler)

// Class definition inferred from offsets
class NetSession {
public:
    // +0x70: uint32_t m_flags
    // +0x90: BufferQueue m_bufferQueue (implied by FUN_0074a040 taking this+0x90)
    // +0x9c: int* m_pendingEntity2 (some pointer)
    // +0xb0: int* m_pendingEntity1
    // +0xb4: int* m_entityHandle1
    // +0xb8: int* m_entityHandle2
    // +0xbc: uint32_t m_messageHash
    // +0x5c: uint32_t m_sceneId

    uint32_t m_flags;               // offset +0x70
    // padding? Actually only used via offset, no struct layout needed.
};

// Reconstructed function
undefined1 __thiscall NetSession::handleMessage(int this_ptr,
                                                undefined4 param_2,
                                                undefined4 param_3,
                                                undefined4 param_4,
                                                int messageType,
                                                undefined4 param_6)
{
    char cVar1;
    undefined1 result;
    int entityId;
    int handle;
    uint32_t flags;
    void* buffer;

    result = 1; // default success
    // Message type is based on original param_5, subtract 0x26 to get switch index
    // Original switch: param_5 + -0x26
    switch (messageType - 0x26) {
    case 0: // messageType == 0x26
        netMessageSetup();
        if (isGameLoaded() != 0 && (cVar1 = isMissionActive(), cVar1 == '\0')) {
            // Game loaded but mission not active -> join in progress?
            *(uint32_t*)(this_ptr + 0x70) |= 8; // set flag bit 3
            if (isNetworkActive() == '\0') {
                // Not active, create a "join" message
                buffer = allocNetworkBuffer(0, 0);
                sendReliableMessage(0xac19ac96, 0x10, buffer, 0);
                freeNetworkBuffer();
            } else {
                // Already active, send a "already joined" message
                buffer = allocNetworkBuffer(0, 0);
                sendReliableMessage(0xfc336f1d, 0x10, buffer, 0);
                freeNetworkBuffer();
            }
            return 1;
        }
        // Either game not loaded or mission active, clear flag
        *(uint32_t*)(this_ptr + 0x70) &= ~8;
        return 1;

    case 1: // messageType == 0x27
        *(uint32_t*)(this_ptr + 0x70) |= 2;   // set bit 1
        *(uint32_t*)(this_ptr + 0x70) &= ~1; // clear bit 0
        netMessageSetup();
        return 1;

    case 2: // messageType == 0x28
        if (*(int*)(this_ptr + 0xb0) != 0 || *(int*)(this_ptr + 0x9c) != 0) {
            // Clear pending buffers?
            clearBufferQueue(this_ptr + 0x90);
        }
        handle = *(int*)(this_ptr + 0xb4);
        if (handle != 0 || *(int*)(this_ptr + 0xb8) != 0) {
            uint32_t sceneId = *(uint32_t*)(this_ptr + 0x5c);
            if (isNetworkActive() != '\0') {
                // If network active, prefer the second handle?
                handle = *(int*)(this_ptr + 0xb8);
            }
            if (handle != 0 && (entityId = resolveEntityId(sceneId), entityId != 0)) {
                buffer = allocNetworkBuffer(0, 0);
                sendUnreliableMessage(handle, 0, buffer, 0);
                freeNetworkBuffer();
                return 1;
            }
        }
        // fall through to default? Actually no break, but default returns result.
        break;

    case 3: // messageType == 0x29
        uint32_t msgHash = *(uint32_t*)(this_ptr + 0xbc);
        if (msgHash != 0) {
            buffer = allocNetworkBuffer(0, 0);
            sendReliableMessage(msgHash, 0, buffer, 0);
            freeNetworkBuffer();
            return 1;
        }
        break;

    default:
        result = handleOtherMessage( (void*)param_2, (void*)param_3, (void*)param_4, messageType, (void*)param_6);
    }
    return result;
}