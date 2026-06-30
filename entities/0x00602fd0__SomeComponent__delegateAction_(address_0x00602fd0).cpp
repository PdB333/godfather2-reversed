// FUNC_NAME: SomeComponent::delegateAction (address 0x00602fd0)
// This function reads a pointer from the object at offset +0x20 (likely a sub-component or manager)
// and calls another function with that pointer and the given parameter (param_2).
// It serves as a simple delegation wrapper.

void __thiscall SomeComponent::delegateAction(void* param_2)
{
    // +0x20: pointer to a delegate object (e.g., sub-manager or handler)
    void* delegate = *(void**)((char*)this + 0x20);
    FUN_006052d0(delegate, param_2);
    return;
}