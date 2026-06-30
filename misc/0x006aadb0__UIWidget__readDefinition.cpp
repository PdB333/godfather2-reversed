// FUNC_NAME: UIWidget::readDefinition
void __thiscall UIWidget::readDefinition(int this, void* streamReader) {
    // Open the binary stream for reading
    openStream(streamReader);

    // Check if the widget has a child container at offset +0x3C8 (bool flag)
    bool hasChild = *(byte*)(this + 0x3C8);
    if (hasChild) {
        *(byte*)(this + 0x3C8) = 0;  // Clear flag
        clearChildren(this + 0x64);  // +0x64 = child container pointer
    }

    // Enter reading group with magic hash 0x47e72b38 (likely a section identifier)
    beginReadGroup(streamReader, 0x47e72b38);

    bool isReading = hasNextToken();
    while (!isReading) {
        nextToken();
        int tokenType = getTokenType();
        switch (tokenType) {
        case 0:
            getTokenValue();
            *(int*)(this + 0x50) = getTokenValue(); // +0x50 = flags
            break;
        case 1:
            getTokenValue();
            setStringProperty(this + 0x54, getTokenValue()); // +0x54 = text string
            break;
        case 2:
            getTokenValue();
            setStringProperty(this + 0x5C, getTokenValue()); // +0x5C = subtitle/font string
            break;
        // ... many cases that call setProperty with a value (likely color, position, etc.)
        // Only cases 0,7,0xC,0x11,0x16,0x1B,0x20,0x25,0x2A store integers from the token data
        case 3:
        case 4:
        case 5:
        case 6:
        case 8:
        case 9:
        case 0xA:
        case 0xB:
        case 0xD:
        case 0xE:
        case 0xF:
        case 0x10:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
            getTokenValue();
            setProperty(getTokenValue(), tokenType); // +0x64 child? Actually stores into global property store
            break;
        case 7:
            getTokenValue();
            *(int*)(this + 200) = getTokenValue(); // +0xC8 = some int (e.g., x position)
            break;
        case 0xC:
            getTokenValue();
            *(int*)(this + 0x134) = getTokenValue(); // +0x134 = y position? (offset 308)
            break;
        case 0x11:
            getTokenValue();
            *(int*)(this + 0x1A0) = getTokenValue(); // +0x1A0 = width?
            break;
        case 0x16:
            getTokenValue();
            *(int*)(this + 0x20C) = getTokenValue(); // +0x20C = height?
            break;
        case 0x1B:
            getTokenValue();
            *(int*)(this + 0x278) = getTokenValue(); // +0x278 = another dimension?
            break;
        case 0x20:
            getTokenValue();
            *(int*)(this + 0x2E4) = getTokenValue(); // +0x2E4
            break;
        case 0x25:
            getTokenValue();
            *(int*)(this + 0x350) = getTokenValue(); // +0x350
            break;
        case 0x2A:
            getTokenValue();
            *(int*)(this + 0x3BC) = getTokenValue(); // +0x3BC
            break;
        }
        stepToNextToken(); // Finishes reading this token and advances
        isReading = hasNextToken();
    }

    if (hasChild) {
        // If child container was active, reload it after reading
        *(byte*)(this + 0x3C8) = 1;
        refreshChildDisplay(this + 0x64); // +0x64 = child container
        return;
    } else {
        // If no child, check if we need to load a large data buffer (e.g., font texture)
        if ((*(byte*)(this + 0x50) & 1) && (g_pLargeDataBuffer != 0)) {
            copyLargeBuffer(this + 0x3C, g_pLargeDataBuffer, 0x8000); // +0x3C = buffer address, size 32KB
        }
    }
}