//FUNC_NAME: UIElement::setTextWithDefault
void __thiscall UIElement::setTextWithDefault(int *this, int param_2, int param_3)
{
    // +0x00: pointer to text string (may be null)
    int *textPtr = (int *)*this;
    if (textPtr == (int *)0x0) {
        // Use default text when no custom text is set
        textPtr = &DAT_0120546e;
    }
    // +0x04: additional parameter (e.g., color, flags)
    FUN_005c4660(param_2, textPtr, param_3, this[1]);
    return;
}