// FUNC_NAME: UIComponent::setTextFromResource
void __thiscall UIComponent::setTextFromResource(int thisPtr, int destParam, int extraParam)
{
    char *textBuffer = nullptr;
    int textLength = 0;
    int textFlags = 0;
    void (*deallocFunc)(char *) = nullptr;

    // Retrieve the localized string from resource ID at offset 0x14
    getLocalizedString(*(int*)(thisPtr + 0x14), &textBuffer, 1);

    char *actualText = textBuffer;
    if (textBuffer == nullptr) {
        actualText = (char*)&DAT_0120546e; // fallback default string
    }

    // Set the UI text (presumably to display)
    setUIText(destParam, actualText, extraParam, textLength);

    // Free the allocated string if it was retrieved
    if (textBuffer != nullptr) {
        deallocFunc(textBuffer);
    }
}