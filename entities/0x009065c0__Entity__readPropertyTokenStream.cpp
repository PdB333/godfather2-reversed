// FUNC_NAME: Entity::readPropertyTokenStream
void __thiscall Entity::readPropertyTokenStream(void *this, void *stream) {
    char isDone;
    int tokenType;
    int tokenValue;
    int *tokenPtr;

    pushPropertyStream(stream);
    setPropertyID(stream, 0x4f194024);
    isDone = isPropertyStreamDone();
    while (true) {
        if (isDone != '\0') {
            return;
        }
        nextPropertyToken();
        tokenType = getPropertyTokenType();
        if (tokenType == 0) {
            nextPropertyToken();
            tokenValue = getPropertyTokenValue();
            // offset 0x58: likely a property value field
            writeFieldAtOffset((int)this + 0x58, tokenValue);
        } else if (tokenType == 1) {
            nextPropertyToken();
            tokenValue = getPropertyTokenValue();
            // offset 0x60: another property value field
            writeFieldAtOffset((int)this + 0x60, tokenValue);
        } else if (tokenType == 2) {
            tokenPtr = (int *)nextPropertyToken();
            // offset 0x54: pointer to property block (e.g., a string or sub-object)
            *(int *)((int)this + 0x54) = tokenPtr[2]; // copy value at offset +8 of token
        }
        popPropertyToken();
        isDone = isPropertyStreamDone();
    }
}