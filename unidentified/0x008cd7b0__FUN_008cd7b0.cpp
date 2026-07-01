// FUNC_NAME: UnknownClass::constructor
// Address: 0x008cd7b0
// Role: Constructor for a derived class – calls base constructor, then sets vtable pointer.

// The base class constructor (FUN_00414970) is expected to be __thiscall
// and takes two additional parameters (param2, param3) beyond the implicit 'this'.
class UnknownClass : public BaseUnknown {
public:
    // Constructor – param2 and param3 are forwarded to base class constructor
    UnknownClass(uint32_t param2, uint32_t param3) : BaseUnknown(param2, param3) {
        // Override vtable pointer to point to this class's vtable
        this->vtablePtr = reinterpret_cast<void**>(0x00d7c978);  // PTR_FUN_00d7c978
    }

private:
    void* vtablePtr;  // +0x00: vtable pointer (first member)
};