// FUNC_NAME: EARSObject::onType9Check
// Address: 0x004a83d0
// Reconstructed from Ghidra decompilation. Checks if the object's type field (offset +0x04) equals 9.
// If so, calls a global function with (globalContext, this, 0) and returns its result.
// Otherwise returns the default EAX value (masked) that was set by the caller.

class EARSObject {
    // Vtable pointer typically at +0x00, not directly used here
    // +0x04: Type identifier (int32)
    // +0x08 ... other data
};

// Global context pointer (likely singleton/game state)
extern void* gGlobalContext; // DAT_0122345c

// Function called when type is 9 (address 0x00462410)
extern DWORD __fastcall CallType9Handler(void* context, EARSObject* obj, int zero); // FUN_00462410

DWORD __thiscall EARSObject::onType9Check(void)
{
    DWORD result;

    // Default return value: preserves the lower 8 bits by masking them out
    // This may be a return value already in EAX from a previous call in the caller
    result = (DWORD)(EAX & 0xFFFFFF00);

    // Check if object is valid and of the specific type (9)
    if ((this != NULL) && (*(int*)((int)this + 4) == 9)) {
        // Type matches, delegate to global handler
        result = CallType9Handler(gGlobalContext, this, 0);
    }

    return result;
}