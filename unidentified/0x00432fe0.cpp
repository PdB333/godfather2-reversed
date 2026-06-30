// FUN_NAME: FUN_00432fe0 (possibly SomeGameObject::checkFlagAndCall)
// Address: 0x00432fe0
// Role: Checks a flag at offset +0x8 (bit 3) and if clear, calls a delegate function
// Note: The delegate function receives an implicit parameter in eax (likely a related object)

// Class name is unknown; assume a base game object
class SomeGameObject {
public:
    // Offset +0x0: vtable pointer (if any)
    // Offset +0x4: unknown
    // Offset +0x8: flags byte (bit 3 = e.g., something like "isActive" or "isDisabled")
    byte flags; // actually at +0x8

    // __fastcall: param_1 in ecx (this), and the delegate function receives something in eax
    // We interpret this as a method that takes an implicit second argument in eax
    // The callee (FUN_00432e30) likely expects that value as its first parameter (possibly another object)
    void __fastcall checkFlagAndCall(int param_1 /* this */, int /* in_EAX */) {
        // In actual assembly, eax is not a parameter but a register value set by the caller.
        // For reconstruction, we document that eax is passed to the delegate.
        if ((*(byte*)(param_1 + 8) & 8) == 0) {
            // Call delegate with the value that was in eax when this function was entered
            // This implies the caller placed an object pointer in eax before calling this function
            FUN_00432e30(eaxValue);
        }
    }
};