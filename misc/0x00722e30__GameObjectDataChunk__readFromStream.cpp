// FUNC_NAME: GameObjectDataChunk::readFromStream
void __thiscall GameObjectDataChunk::readFromStream(StreamReader* pStream)
{
    char isEnd;
    int fieldId;
    int temp;
    int nestedOffset;
    int readValInt;
    float readValFloat;

    startStream(pStream);
    readChunkID(pStream, 0xfbed6286);
    isEnd = isEndOfData();
    do {
        if (isEnd != '\0') {
            skipRemainingFields((int*)(this + 0x50), 0x10);
            return;
        }
        advanceStream();
        fieldId = readFieldID();
        switch(fieldId) {
        case 0: // field 0
            temp = readValue();
            *(int*)(this + 0x74) = *(int*)(temp + 8);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8: // fields 1..8 -> array at +0x50
            readValue(); // consume the value? Actually the decompiled shows:
                         // FUN_0043b210(); then again FUN_0043ab70() and FUN_0043b210()
            // This pattern is odd: it calls readValue() twice? Let's re-check decompiled.
            // Original: case 1..8: FUN_0043b210(); iVar4 = FUN_0043ab70(); iVar3 = FUN_0043b210(); *(param_1+0x50+(iVar4-1)*4)=*(iVar3+8);
            // So it reads a field ID again? That would be a nested field ID inside the array element? That doesn't make sense.
            // Actually the decompiled shows that it does another readFieldID() after reading a dummy value. That suggests that for these cases, the first value is a placeholder, then it reads the field ID again (which is the array index), then the actual value.
            // So we need to emulate that.
            // We'll do:
            readValue(); // dummy
            fieldId = readFieldID(); // reuse fieldId variable, but original uses iVar4
            temp = readValue();
            *(int*)(this + 0x50 + (fieldId - 1) * 4) = *(int*)(temp + 8);
            break;
        case 9:
            temp = readValue();
            *(int*)(this + 0x70) = *(int*)(temp + 8);
            break;
        case 10:
            temp = readValue();
            *(int*)(this + 0x88) = *(int*)(temp + 8);
            break;
        case 11: // nested object at +0x154
            nestedOffset = (int)(this + 0x154);
            readValue(); // consume? Actually FUN_0043b210 is called with nestedOffset as argument? No, original: iVar4 = this+0x154; FUN_0043b210(iVar4); That is likely reading into that buffer.
            // Then FUN_0043ad10(iVar4) - reads a sub-object into that buffer.
            // So we call readValueIntoBuffer and then readSubObject.
            readValueIntoBuffer((StreamReader*)nestedOffset);
            readSubObject((StreamReader*)nestedOffset);
            break;
        case 12:
            temp = readValue();
            *(int*)(this + 0x8c) = *(int*)(temp + 8);
            break;
        case 13: // nested object at +0x16c
            nestedOffset = (int)(this + 0x16c);
            goto LAB_00722f23; // same as case 0x2b
        case 14:
            temp = readValue();
            *(int*)(this + 0x90) = *(int*)(temp + 8);
            break;
        case 15:
            temp = readValue();
            *(int*)(this + 0xbc) = *(int*)(temp + 8);
            break;
        case 16:
            temp = readValue();
            *(int*)(this + 0xf4) = *(int*)(temp + 8);
            break;
        case 17:
            temp = readValue();
            *(int*)(this + 0x94) = *(int*)(temp + 8);
            break;
        case 18:
            temp = readValue();
            *(int*)(this + 0xc0) = *(int*)(temp + 8);
            break;
        case 19:
            temp = readValue();
            *(int*)(this + 0xf8) = *(int*)(temp + 8);
            break;
        case 20:
            temp = readValue();
            *(int*)(this + 0x98) = *(int*)(temp + 8);
            break;
        case 21:
            temp = readValue();
            *(int*)(this + 0xc4) = *(int*)(temp + 8);
            break;
        case 22:
            temp = readValue();
            *(int*)(this + 0x9c) = *(int*)(temp + 8);
            break;
        case 23:
            temp = readValue();
            *(int*)(this + 0xc8) = *(int*)(temp + 8);
            break;
        case 24:
            temp = readValue();
            *(int*)(this + 0xfc) = *(int*)(temp + 8);
            break;
        case 25:
            temp = readValue();
            *(int*)(this + 0xa0) = *(int*)(temp + 8);
            break;
        case 26:
            temp = readValue();
            *(int*)(this + 0xcc) = *(int*)(temp + 8);
            break;
        case 27:
            temp = readValue();
            *(int*)(this + 0xa4) = *(int*)(temp + 8);
            break;
        case 28:
            temp = readValue();
            *(int*)(this + 0xd0) = *(int*)(temp + 8);
            break;
        case 29:
            temp = readValue();
            *(int*)(this + 0xa8) = *(int*)(temp + 8);
            break;
        case 30:
            temp = readValue();
            *(int*)(this + 0xd4) = *(int*)(temp + 8);
            break;
        case 31:
            temp = readValue();
            *(int*)(this + 0xac) = *(int*)(temp + 8);
            break;
        case 32:
            temp = readValue();
            *(int*)(this + 0xd8) = *(int*)(temp + 8);
            break;
        case 33:
            temp = readValue();
            *(int*)(this + 0xb0) = *(int*)(temp + 8);
            break;
        case 34:
            temp = readValue();
            *(int*)(this + 0xdc) = *(int*)(temp + 8);
            break;
        case 35:
            temp = readValue();
            *(int*)(this + 0xb4) = *(int*)(temp + 8);
            break;
        case 36:
            temp = readValue();
            *(int*)(this + 0xe0) = *(int*)(temp + 8);
            break;
        case 37:
            temp = readValue();
            *(int*)(this + 0xb8) = *(int*)(temp + 8);
            break;
        case 38:
            temp = readValue();
            *(int*)(this + 0xe4) = *(int*)(temp + 8);
            break;
        case 39:
            temp = readValue();
            *(int*)(this + 0x10c) = *(int*)(temp + 8);
            break;
        case 40:
            temp = readValue();
            *(int*)(this + 0x110) = *(int*)(temp + 8);
            break;
        case 41:
            temp = readValue();
            *(int*)(this + 0x114) = *(int*)(temp + 8);
            break;
        case 42:
            // Convert float to int with scale and round
            temp = readValue();
            readValFloat = *(float*)(temp + 8);
            *(int*)(this + 0x118) = (int)(readValFloat * 100.0f + 0.5f); // Assuming DAT is 100.0
            break;
        case 43: // nested object at +0x184
            nestedOffset = (int)(this + 0x184);
LAB_00722f23:
            readValueIntoBuffer((StreamReader*)nestedOffset);
            readSubObject((StreamReader*)nestedOffset);
            break;
        case 44:
            temp = readValue();
            *(int*)(this + 0x11c) = *(int*)(temp + 8) - 1;
            break;
        case 45:
            temp = readValue();
            readValInt = *(int*)(temp + 8);
            *(int*)(this + 0x11c) = *(int*)(this + 0x11c) - 1;
            *(int*)(this + 0x120) = readValInt;
            break;
        case 46:
            temp = readValue();
            *(int*)(this + 0xe8) = *(int*)(temp + 8);
            break;
        case 47:
            temp = readValue();
            *(int*)(this + 0xec) = *(int*)(temp + 8);
            break;
        case 48:
            temp = readValue();
            *(int*)(this + 0xf0) = *(int*)(temp + 8);
            break;
        case 49:
            temp = readValue();
            *(int*)(this + 0x124) = *(int*)(temp + 8);
            break;
        case 50:
            temp = readValue();
            *(int*)(this + 0x128) = *(int*)(temp + 8);
            break;
        case 51:
            temp = readValue();
            *(int*)(this + 0x12c) = *(int*)(temp + 8);
            break;
        case 52:
            temp = readValue();
            *(int*)(this + 0x130) = *(int*)(temp + 8);
            break;
        case 53:
            temp = readValue();
            *(int*)(this + 0x134) = *(int*)(temp + 8);
            break;
        case 54:
            temp = readValue();
            *(int*)(this + 0x138) = *(int*)(temp + 8);
            break;
        case 55:
            temp = readValue();
            *(int*)(this + 0x13c) = *(int*)(temp + 8);
            break;
        case 56:
            temp = readValue();
            *(int*)(this + 0x140) = *(int*)(temp + 8);
            break;
        case 57:
            temp = readValue();
            *(int*)(this + 0x144) = *(int*)(temp + 8);
            break;
        case 58:
            temp = readValue();
            *(int*)(this + 0x148) = *(int*)(temp + 8);
            break;
        case 59:
            temp = readValue();
            *(int*)(this + 0x100) = *(int*)(temp + 8);
            break;
        case 60:
            temp = readValue();
            *(int*)(this + 0x104) = *(int*)(temp + 8);
            break;
        case 61:
            temp = readValue();
            *(int*)(this + 0x108) = *(int*)(temp + 8);
        }
        nextField();
        isEnd = isEndOfData();
    } while (true);
}