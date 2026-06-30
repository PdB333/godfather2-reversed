// FUNC_NAME: TextSpan::render
void __thiscall TextSpan::render(int style, const char* text)
{
    ushort startIndex;                 // offset +0x04: starting character index
    uint endIndex;                     // offset +0x12: ending character index (inclusive)
    int fontHandle;                    // offset +0x00: font handle/id

    // Map style 13 to style 6 (font size / weight remapping)
    if (style == 0xD) {
        style = 6;
    }

    fontHandle = *(int*)this;                              // +0x00
    startIndex = *(ushort*)((char*)this + 4);              // +0x04
    endIndex = (uint)*(ushort*)((char*)this + 0x12);      // +0x12

    // Check if the active font needs to be changed
    if (g_activeFontHandle != fontHandle) {
        // vtable +0x1A0: FontManager::setActiveFont
        g_pFontManager->setActiveFont(fontHandle);
        g_activeFontHandle = fontHandle;
    }

    // Prepare the renderer (e.g., enable texturing, set blending)
    FUN_006102c0();

    // Retrieve the current render color from the engine
    uint currentColor = FUN_0060c9d0();

    // Draw the substring: from startIndex to endIndex inclusive
    // vtable +0x148: FontManager::drawString (style, y, x, length, text, color)
    // Note: y is hardcoded to 0 in this call
    g_pFontManager->drawString(style, 0, (uint)startIndex,
                               (endIndex - (uint)startIndex) + 1,
                               text, currentColor);
}