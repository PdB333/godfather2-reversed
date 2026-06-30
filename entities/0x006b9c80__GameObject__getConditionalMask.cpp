// FUNC_NAME: GameObject::getConditionalMask
uint __thiscall GameObject::getConditionalMask(uint flags) {
    // Virtual function at vtable +0x10 (index 4) takes flags and an output pointer,
    // returns char (bool). Output (unused here) may receive additional data.
    int unusedOutput = 0;
    bool conditionMet = (this->vtable[4])(flags, &unusedOutput) != 0;
    return conditionMet ? flags : 0;
}