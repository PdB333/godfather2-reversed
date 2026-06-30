// FUNC_NAME: Entity::getComponentAndCall
void __thiscall Entity::getComponentAndCall(void* thisPtr, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    void* componentPtr;
    if (thisPtr == 0) {
        componentPtr = 0;
    } else {
        // +0x54 is likely a pointer to a sub-component (e.g., m_pComponent)
        componentPtr = (void*)((char*)thisPtr + 0x54);
    }
    // Call the target function with the component pointer as the third argument
    FUN_00525970(arg2, arg3, componentPtr, arg4, arg5, arg1);
}