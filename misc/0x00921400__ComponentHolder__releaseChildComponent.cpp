// FUNC_NAME: ComponentHolder::releaseChildComponent
void __thiscall ComponentHolder::releaseChildComponent() {
    // +0xA4: pointer to a child component's interface
    if (*(int*)(this + 0xA4) != 0) {
        // Subtract 0x48 to get the parent object (child interface is at offset 0x48 inside parent)
        FUN_0097b8c0(*(int*)(this + 0xA4) - 0x48);
        return;
    }
    FUN_0097b8c0(0);
}