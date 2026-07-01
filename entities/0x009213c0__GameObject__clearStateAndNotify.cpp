// FUNC_NAME: GameObject::clearStateAndNotify
void __thiscall GameObject::clearStateAndNotify()
{
    int *pParentMember; // pointer stored at +0x5c, pointing to a member inside parent
    int parentBase;     // base address of parent object after container_of adjustment

    this->stateFlag74 = 0;                                        // +0x74: some flag
    pParentMember = (int *)this->parentPointer;                   // +0x5c: pointer to parent's member (e.g., a field)
    if (pParentMember == (int *)0) {
        parentBase = 0;
    } else {
        parentBase = *pParentMember - 0x48;                      // container_of: get parent object base
    }
    this->stateFlag58 = 0;                                        // +0x58: another state variable
    FUN_00976ac0(*(undefined4 *)(parentBase + 0x164), FUN_00950b20()); // call parent method with its field +0x164 and a timestamp/global value
    return;
}