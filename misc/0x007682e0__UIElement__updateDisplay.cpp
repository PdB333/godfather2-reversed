// FUNC_NAME: UIElement::updateDisplay

void __thiscall UIElement::updateDisplay() {
    // Field at offset 0x5c: identifier for the element (e.g., resource ID)
    int elementId = *(int*)((char*)this + 0x5c);
    // Map element ID to index into global array (FUN_00767c20)
    int index = getElementHandleIndex(elementId);
    // vtable[0x2c] is a function to set display properties
    // Signature: void(__thiscall*)(UIElement*, int handle, int flag1, int flag2, int flag3, float scaleX, float scaleY)
    (*(void(__thiscall*)(UIElement*, int, int, int, int, float, float))(**(int**)this + 0x2c))(
        this,
        g_globalHandleArray[index],   // handle from global array based on index
        1,                            // enable flag
        0,                            // unknown flag
        0,                            // unknown flag
        1.0f,                         // scale X
        1.0f                          // scale Y
    );
}