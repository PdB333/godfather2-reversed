// FUNC_NAME: UIElementBase::applyElementColorFromIndex
void __thiscall UIElementBase::applyElementColorFromIndex(int *thisPtr)
{
    // thisPtr[0x17] at offset 0x5C – likely an index into a color table
    int colorIndex = FUN_00767c20(thisPtr[0x17]);

    // Call virtual function at vtable offset 0x2c (index 11)
    // The function takes:
    //   - a color value from a global array (DAT_00e51b98)
    //   - five additional parameters: 1, 0, 0, 1.0f, 1.0f
    (thisPtr->vtable[11])(*(uint *)(&DAT_00e51b98 + colorIndex * 4), 1, 0, 0, 1.0f, 1.0f);
}