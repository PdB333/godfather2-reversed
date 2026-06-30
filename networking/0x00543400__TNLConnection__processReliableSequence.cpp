// FUNC_NAME: TNLConnection::processReliableSequence
// Function address: 0x00543400
// Role: Handles incoming reliable packet sequence/acknowledgment logic.
// Called from 0x0087CB80 likely as part of packet receive processing.
// Parameters:
//   this - pointer to TNLConnection object
//   param_2 - likely pointer to packet buffer or connection-related data
//   param_3 - likely packet data or sequence number
//   param_4 - likely packet type or additional identifier
// Returns 1 on success, 0 on failure.

#include <cstdint>

class TNLConnection {
public:
    // Virtual function table offsets (in bytes):
    // +0x1E4: virtual int isSequenceStateValid(); // may check sequence window
    // +0x1EC: virtual void sendAcknowledgment(uint32_t param4, uint32_t param3);
    // +0x1F8: virtual int getReceivedPacketData(void* param2, void** outData);
    // +0x20C: virtual void acknowledgePacket(void* param2);
    // +0x210: virtual void processPacketData(void* param2, uint32_t param3);

    // External function: likely validates packet integrity/checksum
    bool validatePacketIntegrity(void* param_2, uint32_t param_4);
};

// Meta: assume validatePacketIntegrity is defined elsewhere
// Actually defined at 0x00542f80

bool __thiscall TNLConnection::processReliableSequence(
    TNLConnection* thisPtr,
    void* param_2,
    uint32_t param_3,
    uint32_t param_4)
{
    char cVar1;
    int iVar2;
    // Note: 'unaff_retaddr' appears to be a leftover from decompilation;
    // it may represent a fifth parameter or a member variable.
    // For reconstruction, assume it is a boolean flag (e.g., param_3 or a local state).
    // In the original binary it is likely set from a register or stack offset.
    char unaff_retaddr = 0; // Placeholder; actual value unknown

    void* local_8 = nullptr;   // Output buffer for received data
    uint32_t local_4 = 0;      // Unused initialization

    cVar1 = validatePacketIntegrity(param_2, param_4);
    if (cVar1 != 0) {
        local_4 = 0;
        local_8 = 0;
        // +0x1F8: bool getReceivedPacketData(param_2, &local_8)
        // Returns non-zero on failure (e.g., buffer overflow, sequence mismatch)
        cVar1 = (reinterpret_cast<int (__thiscall*)(TNLConnection*, void*, void**)>
            (*(uintptr_t*)thisPtr + 0x1F8))(thisPtr, param_2, &local_8);
        if (cVar1 == 0) {
            // unaff_retaddr likely indicates whether an acknowledgment is needed
            if (unaff_retaddr != 0) {
                // +0x1E4: int isSequenceStateValid()
                iVar2 = (reinterpret_cast<int (__thiscall*)(TNLConnection*)>
                    (*(uintptr_t*)thisPtr + 0x1E4))(thisPtr);
                if (iVar2 != 0) {
                    return 0; // Sequence state invalid, discard
                }
                // +0x20C: void acknowledgePacket(param_2)
                (reinterpret_cast<void (__thiscall*)(TNLConnection*, void*)>
                    (*(uintptr_t*)thisPtr + 0x20C))(thisPtr, param_2);
            }
            // +0x1EC: void sendAcknowledgment(param_4, param_3)
            (reinterpret_cast<void (__thiscall*)(TNLConnection*, uint32_t, uint32_t)>
                (*(uintptr_t*)thisPtr + 0x1EC))(thisPtr, param_4, param_3);
            // +0x210: void processPacketData(param_2, param_3)
            (reinterpret_cast<void (__thiscall*)(TNLConnection*, void*, uint32_t)>
                (*(uintptr_t*)thisPtr + 0x210))(thisPtr, param_2, param_3);
            return 1;
        }
    }
    return 0;
}