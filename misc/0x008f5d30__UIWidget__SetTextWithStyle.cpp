// FUNC_NAME: UIWidget::SetTextWithStyle
void __thiscall UIWidget::SetTextWithStyle(int this, char* text, int styleIndex)
{
    // Temporary variables
    bool visible = false;            // local_809
    wchar_t wideText[1024];         // local_800
    size_t convertedChars = 0;       // local_804
    int result = 0;                  // local_808

    // Step 1: Process style parameter (likely index into style table)
    FUN_008f5990(styleIndex);        // Maybe SetCurrentStyle

    // Step 2: Update internal state (e.g., recalc layout)
    FUN_008f39f0();                  // Maybe RecalcLayout

    // Step 3: Get visibility state from dimensions or position
    int stateVal = FUN_008f23f0(
        *(int*)(this + 0x20a8),      // +0x20A8: width or right coordinate
        *(int*)(this + 0x20ac),      // +0x20AC: height or bottom coordinate
        &visible                     // output: whether widget is visible
    );

    // Step 4: Set some internal state (color? alignment?)
    FUN_008f2320(
        *(int*)(this + 0x20a0),      // +0x20A0: x or left coordinate
        *(int*)(this + 0x20a4),      // +0x20A4: y or top coordinate
        stateVal
    );

    // Step 5: Update visibility flag at +0x10
    if (visible) {
        *(uint*)(this + 0x10) |= 1;    // set visible bit
    } else {
        *(uint*)(this + 0x10) &= ~1;   // clear visible bit
    }

    // Step 6: Convert multibyte string (param_2) to wide string
    mbstowcs_s(&convertedChars, wideText, 1024, text, _TRUNCATE);

    // Step 7: Call virtual function to update displayed text
    // vtable is at +0x2098, virtual function at offset 0x20
    // signature: void (__thiscall?)(wchar_t*, int, int, int, int*)
    int vtablePtr = *(int*)(this + 0x2098);               // +0x2098: pointer to vtable
    void (*setTextFunc)(wchar_t*, int, int, int, int*) = 
        (void (*)(wchar_t*, int, int, int, int*))
            (*(int*)(vtablePtr + 0x20));

    setTextFunc(
        wideText,                 // new text to display
        this + 0x20a0,            // +0x20A0: left/top coordinate?
        this + 0x20a8,            // +0x20A8: right/bottom coordinate?
        *(int*)(this + 0x209c),   // +0x209C: additional parameter (font? alignment?)
        &result                   // out: result code
    );

    return;
}