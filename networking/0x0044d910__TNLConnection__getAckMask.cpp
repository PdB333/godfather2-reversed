// FUNC_NAME: TNLConnection::getAckMask
// Address: 0x0044d910
// Role: Retrieves a bitmask from a global acknowledgment table based on an offset stored in this connection object.
// The mask is shifted right by 5 and then bits 1-7 are cleared (keeps bit0 and bits8-31).
// This is likely used to extract a specific status field from a 32-bit slot window (packet acknowledgments).
// TLS access via FS:[0x2C] points to thread-local game state; double indirection yields a pointer to a network manager,
// from which a base address is read at offset +8, then a uint is read at 0x7C + per-connection offset.

#include <cstdint>

// Assuming __readfsdword is defined as intrinsic elsewhere; for reconstruction we declare it.
extern "C" uint32_t __readfsdword(unsigned long offset);

class TNLConnection {
public:
    // Retrieves a bitmask for this connection's packet slots.
    // param_1 is the 'this' pointer (passed as first int parameter).
    uint32_t getAckMask(int32_t thisPtr) const
    {
        // Thread-Local Storage: pointer at FS:[0x2C] (usually the thread's game state)
        uint32_t tlsPtr = __readfsdword(0x2C);
        
        // Dereference twice: get a pointer to the network manager object
        // First dereference: the pointer at the TLS data
        uint32_t* pNetworkManager = *(uint32_t**)tlsPtr;
        // Second dereference: the pointer at pNetworkManager + 0x08 (some global array base)
        uint32_t baseAddr = *(uint32_t*)((uintptr_t)pNetworkManager + 8);
        
        // The connection object stores an offset at +0x18 (e.g., its index into a global state table)
        uint32_t connectionOff = *(uint32_t*)(thisPtr + 0x18);
        
        // Read the 32-bit value from the global table at offset 0x7C + connectionOff
        uint32_t rawValue = *(uint32_t*)(baseAddr + 0x7C + connectionOff);
        
        // Extract bits: shift right by 5, then clear bits 1-7 (retain bit0 and bits8-31)
        // This operation is likely converting slot indices into a bitmask or extracting a specific field.
        return (rawValue >> 5) & 0xFFFFFF01;
    }
};