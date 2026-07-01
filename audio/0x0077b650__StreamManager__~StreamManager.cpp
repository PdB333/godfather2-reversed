// FUNC_NAME: StreamManager::~StreamManager
void __fastcall StreamManager::~StreamManager(StreamManager* this)
{
    // Set vtable to derived class vtable (destructor step)
    this->vtable = &Vtable_Derived;

    // Destroy member at offset +0x28 (param_1[10])
    if (this->member28 != 0) {
        destroyMember(this->member28);
    }

    // Destroy member at offset +0x1C (param_1[7])
    if (this->member1C != 0) {
        destroyMember(this->member1C);
    }

    // Destroy member at offset +0x10 (param_1[4])
    if (this->member10 != 0) {
        destroyMember(this->member10);
    }

    // Destroy member at offset +0x04 (param_1[1])
    if (this->member04 != 0) {
        destroyMember(this->member04);
    }

    // Set vtable to base class vtable (after destruction)
    this->vtable = &Vtable_Base;

    // Clear global active flag
    g_streamManagerActive = 0;
}