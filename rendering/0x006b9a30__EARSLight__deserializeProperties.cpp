// FUNC_NAME: EARSLight::deserializeProperties
void __thiscall EARSLight::deserializeProperties(int thisPtr, Stream& stream) {
    char isDone;
    int propertyId;
    int* propertyValuePtr;

    stream.beginRead();
    stream.readAndCheckMagic(0x91f69a72);

    isDone = stream.isEnd();
    while (isDone == 0) {
        stream.readPropertyValue(); // consume property header
        propertyId = stream.readPropertyId();

        switch (propertyId) {
        case 0: {
            // String property -> field at offset 0x98
            stream.readPropertyValue();
            int stringId = stream.readStringId(); // returns string table index
            setString(thisPtr + 0x98, stringId); // sets string reference
            break;
        }
        case 1: {
            // Int/float property -> field at 0x84
            propertyValuePtr = (int*)stream.readPropertyValue();
            *(int*)(thisPtr + 0x84) = propertyValuePtr[2]; // offset 8 in property struct
            break;
        }
        case 2: {
            // Int/float property -> field at 0x88
            propertyValuePtr = (int*)stream.readPropertyValue();
            *(int*)(thisPtr + 0x88) = propertyValuePtr[2];
            break;
        }
        case 3: {
            // Int/float property -> field at 0x8C
            propertyValuePtr = (int*)stream.readPropertyValue();
            *(int*)(thisPtr + 0x8C) = propertyValuePtr[2];
            break;
        }
        case 4: {
            // Int/float property -> field at 0x90
            propertyValuePtr = (int*)stream.readPropertyValue();
            *(int*)(thisPtr + 0x90) = propertyValuePtr[2];
            break;
        }
        case 5: {
            // Int/float property -> field at 0x94
            propertyValuePtr = (int*)stream.readPropertyValue();
            *(int*)(thisPtr + 0x94) = propertyValuePtr[2];
            break;
        }
        case 6: {
            // 4-float vector property -> field at 0xA0 through 0xAC
            stream.readPropertyValue();
            float* vecPtr = stream.readVec4();
            *(float*)(thisPtr + 0xA0) = vecPtr[0];
            *(float*)(thisPtr + 0xA4) = vecPtr[1];
            *(float*)(thisPtr + 0xA8) = vecPtr[2];
            *(float*)(thisPtr + 0xAC) = vecPtr[3];
            break;
        }
        case 7: {
            // 4-float vector property -> field at 0xB0 through 0xBC
            stream.readPropertyValue();
            float* vecPtr = stream.readVec4();
            *(float*)(thisPtr + 0xB0) = vecPtr[0];
            *(float*)(thisPtr + 0xB4) = vecPtr[1];
            *(float*)(thisPtr + 0xB8) = vecPtr[2];
            *(float*)(thisPtr + 0xBC) = vecPtr[3];
            break;
        }
        case 8: {
            // Bit flags property -> OR into field at 0x80
            propertyValuePtr = (int*)stream.readPropertyValue();
            *(uint*)(thisPtr + 0x80) |= (uint)propertyValuePtr[2];
            break;
        }
        }

        stream.endProperty();
        isDone = stream.isEnd();
    }
}