// FUNC_NAME: SomeComponent::forwardToSubcomponent
void __thiscall SomeComponent::forwardToSubcomponent(uint param_2) {
    // Forward call to sub-object at offset +0x28 (likely a member component)
    // This call delegates to the actual implementation in the sub-component
    FUN_006beb80(reinterpret_cast<uint>(this) + 0x28, param_2);
}