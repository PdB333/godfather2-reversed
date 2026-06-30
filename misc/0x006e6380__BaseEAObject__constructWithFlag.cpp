// FUNC_NAME: BaseEAObject::constructWithFlag
// Function at 0x006e6380: Constructor / initializer with optional self-deallocation flag
// Pattern seen in EA EARS engine: if ownershipFlag bit0 set, calls cleanup on this after base init
BaseEAObject* __thiscall BaseEAObject::constructWithFlag(byte ownershipFlag)
{
    // Call base class initialization (likely zeroing fields or setting defaults)
    this->init(); // FUN_006e5af0

    // If ownershipFlag bit0 is set, perform deallocation/cleanup on self
    if ((ownershipFlag & 1) != 0) {
        this->deallocate(); // FUN_009c8eb0 (likely a custom operator delete or destructor)
    }

    return this;
}