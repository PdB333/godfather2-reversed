// FUNC_NAME: NetSession::computeTripleDataHash
// Reconstructed from 0x00655000: Computes a truncated 32-bit hash from three data blocks (20, 8, 12 bytes).
// The third block is read from the object at offset +0x70 (e.g., a session key or seed).

// Forward declarations of the underlying hash API (size 208 bytes for context)
// These functions are defined elsewhere in the binary.
#define HASH_CONTEXT_SIZE 208
#define HASH_OUTPUT_SIZE  32

void __cdecl hashInit(void* context);
void __cdecl hashUpdate(void* context, const void* data, uint32_t size);
void __cdecl hashFinal(void* context, void* output);

// ----------------------------------------------------------------------------
// This function likely belongs to the NetSession class or a related networking
// component. It combines user-provided data blocks with an internal secret
// field (object+0x70) to produce a compact authentication token.
// ----------------------------------------------------------------------------

uint32_t NetSession::computeTripleDataHash(void* thisPtr, const void* param2, const void* param3) {
    // 208-byte hash context (stack allocation)
    uint8_t hashContext[HASH_CONTEXT_SIZE];

    // 32-byte output buffer (only first 4 bytes are returned)
    uint32_t hashOutput[8];

    // Initialize the hash algorithm (MD5/SHA-like)
    hashInit(hashContext);

    // Feed first block: 20 bytes (e.g., packet header or player ID)
    hashUpdate(hashContext, param2, 0x14);

    // Feed second block: 8 bytes (e.g., sequence number or timestamp)
    hashUpdate(hashContext, param3, 8);

    // Feed third block: 12 bytes from this+0x70 (likely a secret key or session data)
    hashUpdate(hashContext, (const uint8_t*)thisPtr + 0x70, 0xC);

    // Finalize hash and produce output
    hashFinal(hashContext, hashOutput);

    // Return only the first 32 bits as the truncated authentication value
    return hashOutput[0];
}