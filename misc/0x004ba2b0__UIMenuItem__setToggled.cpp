// FUNC_NAME: UIMenuItem::setToggled
void __fastcall UIMenuItem::setToggled(int thisPtr, char newState)
{
    char isActive;
    uint *eventBufferPtr;
    undefined **voidRef;
    char storedState;

    storedState = (newState != '\0');
    *(char *)(thisPtr + 0x19c) = newState; // offset +0x19c: toggled/selected flag

    // If event queue is active (offset +0x164 is non-null)
    if (*(int *)(thisPtr + 0x164) != 0) {
        eventBufferPtr = (uint *)(DAT_01206880 + 0x14); // pointer to pointer into global event buffer
        **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_0110ba94; // write vtable-like identifier
        *eventBufferPtr = *eventBufferPtr + 4; // advance
        *(int *)*eventBufferPtr = thisPtr + 0x54; // write pointer to item data (offset +0x54)
        *eventBufferPtr = *eventBufferPtr + 4; // advance
        *(undefined1 *)*eventBufferPtr = storedState; // write boolean state
        *eventBufferPtr = *eventBufferPtr + 4 & 0xfffffffc; // align to 4 bytes
    }
    // If callback function pointer (offset +0x130) is non-null, call it with a static vtable pointer
    if (*(int *)(thisPtr + 0x130) != 0) {
        voidRef = &PTR_LAB_00e35bcc;
        FUN_004a4bd0(&voidRef); // invoke callback (likely dispatches event)
    }
    return;
}