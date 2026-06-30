// FUNC_NAME: Presentation::loadFromXML
void __thiscall Presentation::loadFromXML(Presentation* this, const char* filename) {
    char hasMoreElements;
    int elementHandle;
    int elementType;
    int scaledInt;
    int resourceId;

    // Initialize file parser
    xmlBeginParse(filename);
    xmlOpenFile(filename, 0x2017e685); // likely a key/hash for the file
    hasMoreElements = xmlHasMoreElements();
    while (hasMoreElements == 0) {
        elementHandle = xmlNextElement();
        elementType = xmlGetElementType(elementHandle);
        switch (elementType) {
            case 0: {
                // Read a string value, convert to ID
                xmlNextElement(); // consume sub-element? Actually need to check
                resourceId = xmlGetElementValue();
                this->m_id = hashStringToInt(resourceId);
                break;
            }
            case 1: {
                // Read float, apply scaling and offset
                elementHandle = xmlNextElement();
                this->m_scaledInt = (int)(*(float*)(elementHandle + 8) * g_scaleFactor + g_offsetFactor);
                break;
            }
            case 2: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x68) = *(float*)(elementHandle + 8);
                break;
            }
            case 3: {
                elementHandle = xmlNextElement();
                *(short*)(this + 0x5c) = *(short*)(elementHandle + 8);
                break;
            }
            case 4: {
                // Read sub-struct (GUID) at offset 0x8c
                int guidPtr = (int)(this + 0x8c);
                xmlReadElementIntoBuffer(guidPtr);
                xmlProcessSubElement(guidPtr);
                break;
            }
            case 5: {
                elementHandle = xmlNextElement();
                *(int*)(this + 0x54) = *(int*)(elementHandle + 8);
                break;
            }
            case 6: {
                elementHandle = xmlNextElement();
                *(int*)(this + 0x58) = *(int*)(elementHandle + 8);
                break;
            }
            case 7: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x60) = *(float*)(elementHandle + 8) * *(float*)(elementHandle + 8);
                break;
            }
            case 8: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x6c) = *(float*)(elementHandle + 8);
                break;
            }
            case 9: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x70) = *(float*)(elementHandle + 8);
                break;
            }
            case 10: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x74) = *(float*)(elementHandle + 8);
                break;
            }
            case 11: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x78) = *(float*)(elementHandle + 8);
                break;
            }
            case 12: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x7c) = *(float*)(elementHandle + 8);
                break;
            }
            case 13: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x80) = *(float*)(elementHandle + 8);
                break;
            }
            case 14: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x84) = *(float*)(elementHandle + 8);
                break;
            }
            case 15: {
                elementHandle = xmlNextElement();
                *(float*)(this + 0x88) = *(float*)(elementHandle + 8);
                break;
            }
        }
        xmlAdvanceElement();
        hasMoreElements = xmlHasMoreElements();
    }

    // Initialize if not already done
    if ((*(short*)(this + 0x5e) & 1) == 0) {
        initResourceData(this);
        *(short*)(this + 0x5e) |= 1;
    }

    // Check if the resource GUID is not a known default and not all zeros, and if there is a global texture data
    if (
        (*(int*)(this + 0x8c) != 0xBABDBDBA || *(int*)(this + 0x90) != 0xBEEFBEEF || 
         *(int*)(this + 0x94) != 0xEAC15A55 || *(int*)(this + 0x98) != 0x91100911) &&
        (
            *(int*)(this + 0x8c) != 0 || *(int*)(this + 0x90) != 0 ||
            *(int*)(this + 0x94) != 0 || *(int*)(this + 0x98) != 0
        ) &&
        g_pTextureData != 0
    ) {
        // Copy texture data into the object's buffer
        memcpy(this + 0x3c, g_pTextureData, 0x8000);
    }
}