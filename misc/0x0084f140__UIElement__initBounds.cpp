// FUNC_NAME: UIElement::initBounds
void __thiscall UIElement::initBounds(int this_ptr, int parent_ptr, float width, float height, int yPos, int flags)
{
    float uVar1;
    int uVar2;
    UIRectStruct rectData;
    // Temp string local variable (size 4 bytes on stack)
    char tempString[4];
    int tempObject;

    if ((width > 0.0f) && (height > 0.0f))
    {
        uVar1 = getSomeGlobalValue(); // FUN_0084ea60
        uVar2 = processValue(uVar1); // FUN_00540cc0
        rectData.field0 = *(ushort *)this_ptr;           // +0x00
        rectData.field1 = *(ushort *)(this_ptr + 4);     // +0x04
        rectData.field2 = *(ushort *)(this_ptr + 8);     // +0x08
        rectData.field3 = g_DefaultColor;               // _DAT_00d5780c
        rectData.field4 = height;                        // +0x10
        rectData.field5 = yPos;                          // +0x14
        rectData.field6 = (int)&g_VTablePtr;             // PTR_LAB_00d74f24
        rectData.field7 = width;                         // +0x1C
        createUIElement(&rectData, width, uVar2, &rectData.field6, flags, 0x100000, 0); // FUN_004b0660
    }
    addToParent(parent_ptr, height, yPos, width, this_ptr); // FUN_0084d9e0
    // Stack cleanup: some string/temp object
    initString(&tempString, 0); // FUN_00408a00
    if (tempObject != 0)
    {
        destroyTempObject(&tempObject); // FUN_004daf90
    }
    return;
}