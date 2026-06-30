// FUNC_NAME: Delegate::invoke
// Function at 0x004d9b60: Calls a stored delegate with a given parameter and returns it.
// The object stores two values (likely a function pointer and a context pointer) at offsets 0x00 and 0x04.
// The external function FUN_004d9080 performs the actual invocation.
// The method returns the same parameter to allow chaining or assignment-style usage.

extern void __cdecl FUN_004d9080(uint32 param, uint32 arg1, uint32 arg2);

class Delegate {
public:
    uint32 field_0x00; // +0x00: First stored argument (e.g., object/context)
    uint32 field_0x04; // +0x04: Second stored argument (e.g., function pointer)

    uint32 __thiscall invoke(uint32 param) {
        FUN_004d9080(param, this->field_0x00, this->field_0x04);
        return param;
    }
};