// FUNC_NAME: Presentation::renderTintedQuad
void __thiscall Presentation::renderTintedQuad(Presentation* this, uint renderFlags, int alphaModulation)
{
    // +0x00: pointer to vertex/color data block (stored as first member)
    uint8* colorData = (uint8*)*this;

    // Extract first 64-bit color pair
    uint32 colorLow = *(uint32*)(colorData);       // +0x00: color A (low 32-bit)
    uint32 colorHigh = *(uint32*)(colorData + 4);  // +0x04: color B? (high 32-bit of first 64 bits)
    // fStack_c: high dword of first 8 bytes interpreted as float (alpha inverted)
    float invAlpha = 1.0f - (float)(*(uint32*)(colorData + 4)); // actually shift done via cast

    // local_8: second 64-bit color pair
    uint64 colorPair2 = *(uint64*)(colorData + 8); // +0x08: second pair (two 32-bit colors)

    // local_1c: build blended color from first color pair (at offset +4 and +0x24)
    uint32 firstBlendSrc = *(uint32*)(colorData + 4);  // actually offset +4 from colorData?
    uint32 secondBlendSrc = *(uint32*)(colorData + 0x24); // +0x24: third color? (quad vertex)

    // Build blended color: high byte (alpha) multiplied by alphaModulation/255
    uint32 blendedColor = firstBlendSrc & 0x00FFFFFF; // keep RGB
    uint8 newAlpha = ( (firstBlendSrc >> 24) * alphaModulation ) / 0xFF;
    blendedColor |= (newAlpha << 24);

    // Re-apply same alpha modulation to second source (offset 0x24)
    uint32 blendedColor2 = secondBlendSrc & 0x00FFFFFF;
    uint8 newAlpha2 = ( (secondBlendSrc >> 24) * alphaModulation ) / 0xFF;
    blendedColor2 |= (newAlpha2 << 24);

    // Set texture from data block (offset +16 from colorData)
    uint32 textureID = *(uint32*)(colorData + 16); // +0x10
    setTexture(textureID);

    // Set blend mode using the modulated alpha and other parameters
    setBlendMode(&alphaModulation, &blendedColor, &blendedColor2, 0);

    // Set vertex colors from object members
    setVertexColor(*(uint32*)(*this + 0x14));   // +0x14 default color
    setAlphaTest(*(uint32*)(*this + 0x1C));    // +0x1C alpha reference

    // Render the quad with extracted coordinates/colors
    renderQuad(
        colorLow,           // first vertex low color?
        invAlpha,           // inverse alpha
        (uint32)(colorPair2 & 0xFFFFFFFF),      // second vertex low
        (uint32)(colorPair2 >> 32),             // second vertex high
        *(uint32*)(*this + 0x18),               // +0x18 extra param
        renderFlags,                             // flags from param2
        *(uint32*)(*this + 0x30),               // +0x30 transform or position
        *(uint32*)(*this + 0x34),               // +0x34 additional data
        &blendedColor,                          // primary blended color
        0,                                      // unused
        &blendedColor2,                         // secondary blended color
        0, 0, 1                                 // fixed constants
    );
}