// FUNC_NAME: Base::Base
// Address: 0x0067e120
// Role: Constructor with optional destruction flag (for placement new or error handling)

// Reconstructed C++ for a base class constructor.
// param_1 is the 'this' pointer (__thiscall).
// param_2 is a flags byte: if bit 0 is set, the function will call a cleanup/destroy function
// on the already constructed object (possibly for deallocation on failure or placement delete).
// FUN_009823b0 appears to be a base class default constructor (no arguments).
// FUN_009c8eb0 appears to be a destroy/free function taking the object pointer.

void * __thiscall Base::Base(byte flags) {
    // Call base class default constructor (initialization)
    baseInit();                                           // +0x0: FUN_009823b0

    if ((flags & 1) != 0) {
        // If bit 0 set, perform cleanup/destroy (e.g., free allocated memory)
        destroy(this);                                    // +0x0: FUN_009c8eb0
    }

    return this;
}