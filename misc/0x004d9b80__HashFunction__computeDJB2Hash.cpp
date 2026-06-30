// FUNC_NAME: HashFunction::computeDJB2Hash
// Address: 0x004d9b80
// Purpose: Computes a 32-bit rolling hash (djb2 style with base 0x21 = 33) from 4 bytes loaded by an internal helper.
// The helper (FUN_004d9500) likely reads 4 bytes from an input string pointer passed via EAX, storing them on stack.
void __thiscall HashFunction::computeDJB2Hash(int *this) {
    uint32_t byte0; // local_18 - first byte of input segment
    uint32_t byte1; // local_14 - second byte
    uint32_t byte2; // local_10 - third byte
    uint32_t byte3; // local_c  - fourth byte

    // Internal helper reads 4 bytes from the input source (e.g., a string pointed to by EAX)
    // and writes them into the above locals.
    // The helper's exact signature is unknown; it modifies stack variables.
    FUN_004d9500(/* in_EAX = pointer to source data */);

    // Combine the four bytes into a hash: hash = (((b0*33 + b1)*33 + b2)*33 + b3)
    *this = ((byte0 * 0x21 + byte1) * 0x21 + byte2) * 0x21 + byte3;
}