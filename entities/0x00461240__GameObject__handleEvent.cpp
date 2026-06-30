// FUNC_NAME: GameObject::handleEvent
void __thiscall GameObject::handleEvent(int param) {
    // This function appears to handle an event/notification for a game object.
    // in_EAX = this (GameObject*)
    // unaff_ESI = some pointer stored in this or globally, possibly m_pEventHandler

    // Dereference this+0x4 to get a pointer to a sub-object (e.g., m_pOwner)
    // Then from that sub-object, get another pointer at its +0x4 (e.g., m_pData)
    int* pData = *(int**)(*(int*)((char*)this + 4) + 4);

    // Get two values from the data structure: at offsets +0x4 and +0xC
    int arg1 = *(int*)((char*)pData + 4);
    int arg2 = *(int*)((char*)pData + 0xC);

    // Call a utility function to obtain a resource/handle
    int handle = FUN_004dafd0(arg1, arg2);  // e.g., GetEventResource(arg1, arg2)

    // Call a virtual method at vtable offset 0x188 on the object pointed by ESI
    // This is likely a callback or notification system
    (*(void(__thiscall**)(int))(*(int*)unaff_ESI + 0x188))(handle);
}