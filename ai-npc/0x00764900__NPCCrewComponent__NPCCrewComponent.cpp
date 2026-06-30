// FUNC_NAME: NPCCrewComponent::NPCCrewComponent
undefined4* __thiscall NPCCrewComponent::NPCCrewComponent(undefined4* this, undefined4 param_2, undefined4 param_3)
{
    undefined4 uVar1;
    int iVar2;

    // Base class constructor call
    FUN_004ac120(param_2, param_3);  // likely some base class initialization

    // Set vtable pointer for this class
    *this = &PTR_LAB_00d655f8; // vtable for NPCCrewComponent

    uVar1 = DAT_00d5ccf8; // some global singleton or constant

    // Adjust pointer based on whether m_pOwner is valid
    if (this[0x12] == 0) { // m_pOwner at +0x48
        iVar2 = 0;
    } else {
        iVar2 = this[0x12] - 0x48; // subtract offset to get base pointer
    }
    this[0x14] = iVar2; // m_pBase at +0x50

    // Initialize various member fields
    this[0x19] = uVar1;      // m_globalData at +0x64
    this[0x18] = 0;          // flags/state at +0x60
    this[0x1a] = 0;          // another flag at +0x68
    this[0x1f] = 0;          // something at +0x7C
    this[0x20] = DAT_00d65680; // another global pointer at +0x80
    *(undefined1*)(this + 0x21) = 0; // byte flag at +0x84
    this[0x17] = 0;          // at +0x5C
    this[0x16] = 0;          // at +0x58
    this[0x15] = 0;          // at +0x54

    return this;
}