// FUNC_NAME: BaseComponent::delegateToChild
void __thiscall BaseComponent::delegateToChild(int data) {
    // +0x1c offset to child component's this pointer
    FUN_006beb80(reinterpret_cast<int>(this) + 0x1c, data);
}