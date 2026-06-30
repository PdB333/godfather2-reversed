// FUNC_NAME: CGameObject::setAnimationFlag
// Address: 0x00605770 - Wrapper that initializes a local flag structure and calls a virtual function
// The structure likely contains: (flag, mask, unk) - values 2, 0x10, 0
void CGameObject::setAnimationFlag(void)
{
    struct FlagData {
        uint32_t flag;   // +0x00: e.g., 2
        uint32_t mask;   // +0x04: e.g., 0x10
        uint32_t unknown; // +0x08: 0
    } data;

    data.flag = 2;
    data.mask = 0x10;
    data.unknown = 0;

    // Call virtual function through vtable (offset 0)
    // this pointer is in EAX? Ghidra shows *in_EAX, so likely this is passed via EAX
    (this->vtable[0])(this, &data);
}