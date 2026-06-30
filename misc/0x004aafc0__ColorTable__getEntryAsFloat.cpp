// FUNC_NAME: ColorTable::getEntryAsFloat
void ColorTable::getEntryAsFloat(int colorEntryId, float outColor[4]) {
    // Get thread-local storage base (FS segment selector 0x2c)
    void* tlsBase = *reinterpret_cast<void**>(__readfsdword(0x2c));
    // Dereference twice: first to a structure, then +8 yields the color table base address
    char* tableBase = *reinterpret_cast<char**>(*reinterpret_cast<int*>(tlsBase) + 8);
    // The color entry’s data offset is stored at colorEntryId + 0x18
    char* colorData = tableBase + *reinterpret_cast<int*>(reinterpret_cast<char*>(colorEntryId) + 0x18);
    // Read three bytes (R, G, B) from offsets 0x98, 0x99, 0x9a
    outColor[0] = static_cast<float>(static_cast<unsigned char>(colorData[0x98]));
    outColor[1] = static_cast<float>(static_cast<unsigned char>(colorData[0x99]));
    outColor[2] = static_cast<float>(static_cast<unsigned char>(colorData[0x9a]));
    outColor[3] = 0.0f; // Alpha set to zero

    // Scale factor: typically 1.0f / 255.0f to convert [0,255] to [0,1]
    extern const float DAT_00e4477c; // Value about 0.00392156886f
    outColor[0] *= DAT_00e4477c;
    outColor[1] *= DAT_00e4477c;
    outColor[2] *= DAT_00e4477c;
    outColor[3] *= DAT_00e4477c;
}