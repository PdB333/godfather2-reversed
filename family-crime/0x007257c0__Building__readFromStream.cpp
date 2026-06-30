// FUNC_NAME: Building::readFromStream
void __thiscall Building::readFromStream(Building *this, Stream *stream) {
    char done;
    int tokenType;
    int *childList;
    int *foundChild;
    char *strPtr;
    char *strTemp;
    int hashValue;
    double floatVal;
    TransformMatrix localMatrix;
    int *tokenData;
    int i;

    // Start reading group with CRC 0xb390b11a
    Stream::beginRead(stream);
    Stream::beginGroup(stream, 0xb390b11a);
    Stream::setGroupVersion(stream, 1);
    done = Stream::isGroupDone(stream);
    if (!done) {
        // Read initial transform matrix and combine
        Stream::readTransform(stream, &localMatrix);
        TransformMatrix::combine(&localMatrix, &localMatrix);

        // Store matrix components into object offsets
        // Offsets: +0x80, +0x90, +0xa0, +0x88, +0x98, +0xa8, +0xc0, +0xc8
        this->transformMatrix00 = localMatrix.c0;   // +0x80
        this->transformMatrix04 = localMatrix.b0;   // +0x90
        this->transformMatrix08 = localMatrix.a0;   // +0xa0
        this->transformMatrix10 = localMatrix.b8;   // +0x88
        this->transformMatrix14 = localMatrix.a8;   // +0x98
        this->transformMatrix18 = localMatrix.a0;   // +0xa0 (duplicated? actually local_a0)
        this->transformMatrix20 = localMatrix.c8;   // +0xc8
        this->transformMatrix24 = localMatrix.88;   // +0x88? confusion
        // Note: The decompiler shows scattered assignments; actual structure likely holds 12 floats.
    }

    // End the initial group and check for done again? Actually the code ends the group and then checks done again.
    Stream::endGroup(stream, 0x8bd0e0eb);
    done = Stream::isGroupDone(stream);

    do {
        if (done) {
            // If stream ended, set default if hash is zero
            if (this->hash4 == 0) {
                this->hash4 = 0x46f5c7b4;
            }
            Building::validateAfterLoad(this);
            return;
        }

        // Read next token
        Stream::readNextToken(stream);
        tokenType = Stream::getTokenType(stream);
        switch (tokenType) {
        case 0: // Euler angle X
            Stream::readNextToken(stream);
            this->eulerX = Stream::readFloat(stream);
            break;
        case 1: // Euler angle Y
            Stream::readNextToken(stream);
            this->eulerY = Stream::readFloat(stream);
            break;
        case 2: // Euler angle Z
            Stream::readNextToken(stream);
            this->eulerZ = Stream::readFloat(stream);
            break;
        case 3: // Another angle or quaternion component? Stored at +0xec
            i = (int)&this->eulerW; // +0xec
            goto readSubStructure;
        case 4: // Model name hash
            Stream::readNextToken(stream);
            strPtr = (char *)Stream::readString(stream);
            if (strPtr != NULL) {
                strTemp = strPtr;
                while (*strTemp != '\0') {
                    strTemp++;
                }
                if (strTemp != strPtr + 1) { // non-empty string
                    hashValue = StringUtils::hashString(strPtr);
                    this->modelHash1 = hashValue; // +0x68
                }
            }
            break;
        case 5: // Another name hash
            Stream::readNextToken(stream);
            strPtr = (char *)Stream::readString(stream);
            if (strPtr != NULL) {
                strTemp = strPtr;
                while (*strTemp != '\0') {
                    strTemp++;
                }
                if (strTemp != strPtr + 1) {
                    hashValue = StringUtils::hashString(strPtr);
                    this->modelHash2 = hashValue; // +0x6c
                }
            }
            break;
        case 6: // Another name hash
            Stream::readNextToken(stream);
            strPtr = (char *)Stream::readString(stream);
            if (strPtr != NULL) {
                strTemp = strPtr;
                while (*strTemp != '\0') {
                    strTemp++;
                }
                if (strTemp != strPtr + 1) {
                    hashValue = StringUtils::hashString(strPtr);
                    this->modelHash3 = hashValue; // +0x70
                }
            }
            break;
        case 7: // Another name hash (possibly type ID)
            Stream::readNextToken(stream);
            strPtr = (char *)Stream::readString(stream);
            if (strPtr != NULL) {
                strTemp = strPtr;
                while (*strTemp != '\0') {
                    strTemp++;
                }
                if (strTemp != strPtr + 1) {
                    hashValue = StringUtils::hashString(strPtr);
                    this->typeHash = hashValue; // +0x74
                }
            }
            break;
        case 8: // Integer flag
            tokenData = (int *)Stream::readNextToken(stream);
            this->flags = *(tokenData + 2); // +0x134 (assuming token data offset 8)
            break;
        case 9: // Bitmask
            tokenData = (int *)Stream::readNextToken(stream);
            this->bitmask = 1 << (*(tokenData + 2) & 0x1f); // +0x11c
            break;
        case 10: // Another sub-structure at +0xfc
            i = (int)&this->extraData; // +0xfc
            goto readSubStructure;
        case 11: // Integer value
            tokenData = (int *)Stream::readNextToken(stream);
            this->someInt = *(tokenData + 2); // +0x120
            break;
        case 12: // Another integer
            tokenData = (int *)Stream::readNextToken(stream);
            this->anotherInt = *(tokenData + 2); // +0xe4
            break;
        case 13: // Sub-structure at +0x10c
            i = (int)&this->subData; // +0x10c
            goto readSubStructure;
        case 14: // Child list at +0x54
            i = (int)&this->children; // +0x54
readSubStructure:
            Stream::readNextToken(i);
            Stream::readSubObject(i);
            break;
        case 15: // Child object with specific hash
            Stream::readNextToken(stream);
            hashValue = Stream::readInt(stream);
            childList = (int *)EntityManager::findChild(this->children, 0); // +0x54
            if (childList != NULL) {
                int *resultArray[27] = {0};
                char success = (**(code **)(*childList + 0x10))(0x38523fc3, &resultArray);
                if (success && resultArray[0] != NULL) {
                    (**(code **)(*resultArray[0] + 0x94))(this + 100, hashValue);
                }
            }
            break;
        case 16: // Float value multiplied by global
            tokenData = (int *)Stream::readNextToken(stream);
            floatVal = (double)(*(float *)(tokenData + 2) * this->someGlobalMultiplier); // _DAT_00e445c8
            MathUtils::unusedFunction(); // FUN_00b99e20
            this->someFloat = (float)floatVal; // +0x124
            break;
        }

        Stream::nextToken(stream);
        done = Stream::isGroupDone(stream);
    } while (true);
}