// FUNC_NAME: UIWidget::setText
void __thiscall UIWidget::setText(int this, const TextPair* pair)
{
    // Check if current text buffer exists (offset +0x28 is a buffer pointer or ref count)
    if (*(int*)(this + 0x28) > 0) {
        // Free the existing buffer: first argument 0 likely indicates "use default allocator"
        FUN_004dbe70(0, *(int*)(this + 0x28));
        // Replace buffer pointer with previously stored one (offset +0x1c)
        *(int*)(this + 0x28) = *(int*)(this + 0x1c);
    }

    // Retrieve the string/handle from pair->first; if null, use a global default string
    void* textId = pair->first;
    if (textId == nullptr) {
        textId = &DAT_00e2df14;       // Global default text handle (e.g., empty string or "Missing")
    }

    // Apply the new text: 0 = default channel/context, textId = string ID, pair->second = extra param (e.g., length, style)
    FUN_00989df0(0, textId, pair->second);
}