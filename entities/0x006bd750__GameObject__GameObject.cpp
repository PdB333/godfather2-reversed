// FUNC_NAME: GameObject::GameObject
void __fastcall GameObject::GameObject(int thisPtr)
{
    int subObjPtr;
    if (thisPtr == 0) {
        subObjPtr = 0;
    }
    else {
        subObjPtr = thisPtr + 0x50; // +0x50: pointer to sub-object (e.g., base class or component)
    }
    // Initialize sub-object (likely constructor of base/component)
    FUN_00791350(subObjPtr);
    // Set member at +0xD0 to zero (e.g., m_pParent, m_pNext, or flag)
    *(int *)(thisPtr + 0xD0) = 0;
}