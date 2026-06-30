// FUNC_NAME: GameObject::getContext
int __thiscall GameObject::getContext() {
    // Returns the pointer stored at offset +0x2e8 (likely a component or context object)
    return *(int*)((char*)this + 0x2e8);
}