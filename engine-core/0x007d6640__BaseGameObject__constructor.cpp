// FUNC_NAME: BaseGameObject::constructor
// Address: 0x007d6640
// This is a constructor that calls the base class constructor (0x007d60c0)
// and optionally calls an additional initialization routine (0x00624da0) if the lower bit of flags is set.

extern void __thiscall base_constructor_007d60c0(void* thisPtr);
extern void __thiscall extra_init_00624da0(void* thisPtr);

class BaseGameObject {
public:
    BaseGameObject* __thiscall constructor(byte flags);
};

BaseGameObject* __thiscall BaseGameObject::constructor(byte flags) {
    // Call base class constructor (likely a parent class in the EARS hierarchy)
    base_constructor_007d60c0(this);

    // If the lower bit is set, perform extra initialization (e.g., for placement new)
    if (flags & 1) {
        extra_init_00624da0(this);
    }

    return this;
}