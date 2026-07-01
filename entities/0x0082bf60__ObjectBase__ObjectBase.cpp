// FUNC_NAME: ObjectBase::ObjectBase
undefined4 __thiscall ObjectBase::ObjectBase(undefined4 this, byte flags) {
    Base::Base(); // Call base class constructor (FUN_0082b1c0)
    if ((flags & 1) != 0) {
        CustomInit(this); // Optional initialization (FUN_009c8eb0)
    }
    return this;
}