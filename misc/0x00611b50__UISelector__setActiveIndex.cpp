// FUNC_NAME: UISelector::setActiveIndex
void __thiscall UISelector::setActiveIndex(int this, int index)
{
    int colorValue; // +0x10, +0x14 stored values

    // Store the index at +0x138
    *(int *)(this + 0x138) = index;

    // Retrieve from array at +0x140 (4-byte entries) and store to +0x14
    colorValue = *(int *)(this + 0x140 + index * 4);
    *(int *)(this + 0x14) = colorValue;

    // Retrieve from array at +0x190 (decimal 400) and store to +0x10
    *(int *)(this + 0x10) = *(int *)(this + 400 + index * 4);

    // If this is the global active instance, also apply the color via external function
    if (DAT_012058e8 == this) {
        FUN_0060a460(colorValue);
    }

    // Refresh the UI display
    FUN_00611500();

    return;
}