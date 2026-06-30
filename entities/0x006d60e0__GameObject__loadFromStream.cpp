// FUNC_NAME: GameObject::loadFromStream
void __thiscall GameObject::loadFromStream(int thisPtr, void* source)
{
    char done;
    int tokenType;
    int value;

    // Initialize XML parser with source
    xmlParserSetSource(source);
    xmlParserSetHash(source, 0xa46b459f);
    done = xmlParserIsDone();
    while (done == '\0') {
        // Advance to next token
        xmlParserAdvance();
        tokenType = xmlParserGetTokenType();
        if (tokenType == 0) {
            // Token type 0: simple value – read and store at offset 0x50
            xmlParserAdvance();
            value = xmlParserGetValue();
            setProperty(thisPtr + 0x50, value);  // +0x50: first property
        }
        else if (tokenType == 1) {
            // Token type 1: nested object – parse into sub-structure at offset 0x58
            int subObjectPtr = thisPtr + 0x58;   // +0x58: sub-object pointer
            xmlParserAdvance(subObjectPtr);
            xmlParserDeserializeSubObject(subObjectPtr);
        }
        else if (tokenType == 2) {
            // Token type 2: attribute – copy value from token data into offset 0x68
            int attrPtr = xmlParserAdvance();    // returns pointer to attribute data
            *(int*)(thisPtr + 0x68) = *(int*)(attrPtr + 8);  // +0x68: third property
        }
        // Pop back to parent element
        xmlParserPopElement();
        done = xmlParserIsDone();
    }
}