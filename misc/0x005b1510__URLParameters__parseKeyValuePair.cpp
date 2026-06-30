// FUNC_NAME: URLParameters::parseKeyValuePair

char* URLParameters::parseKeyValuePair(char* input, void* keyOut, void* valueOut)
{
    char c;
    char* p = input;
    char* eqPos = nullptr;

    // Initialization of temporary string manager (stack frame?)
    unknownInit1();
    unknownInit2();

    // Clean up any previous temporary strings (likely from a higher-level frame)
    if (localTmpPtr != &localTmpBuf && localTmpPtr != nullptr) {
        g_free(localTmpPtr);
    }

    unknownInit1();
    unknownInit2();

    if (localTmpPtr != &localTmpBuf && localTmpPtr != nullptr) {
        g_free(localTmpPtr);
    }

    // Scan for '=' and track position
    p = input;
    if (input != nullptr) {
        do {
            c = *p;
            if (c == '\0' || c == '&') break;
            if (c == '=') {
                eqPos = p;
            }
            p++;
        } while (p != nullptr); // p never null in practice

        if (eqPos != nullptr) {
            // Extract key
            size_t keyLen = eqPos - input;
            char* keyBuf;
            char stackBuf[16];
            localTmpPtr = &localTmpBuf;
            localTmpBuf = 0;
            localTmpBuf2 = 0;

            if (keyLen > 15) {
                keyBuf = (char*)g_alloc(keyLen + 1, 0);
                localTmpPtr = keyBuf;
            } else {
                keyBuf = stackBuf;
                localTmpPtr = stackBuf; // but localTmpPtr still points to localTmpBuf? Decompiler artifact
            }

            memcpy(localTmpPtr, input, keyLen);
            ((char*)localTmpPtr)[keyLen] = '\0';

            unknownFinalizeString(&keyLen);
            unknownInit2();

            // Free temporary if allocated on heap
            if (puStack_14 != auStack_10 && puStack_14 != nullptr) {
                g_free(puStack_14);
            }
            if (localTmpPtr != &localTmpBuf && localTmpPtr != nullptr) {
                g_free(localTmpPtr);
            }

            storeKeyValue(keyOut); // key stored via internal state

            // Extract value
            size_t valueLen = p - (eqPos + 1);
            char* valueBuf;
            localTmpPtr = &localTmpBuf;
            localTmpBuf = 0;
            localTmpBuf2 = 0;

            if (valueLen > 15) {
                valueBuf = (char*)g_alloc(valueLen + 1, 0);
                localTmpPtr = valueBuf;
            } else {
                valueBuf = stackBuf;
            }

            memcpy(localTmpPtr, eqPos + 1, valueLen);
            ((char*)localTmpPtr)[valueLen] = '\0';

            unknownFinalizeString(&valueLen);
            unknownInit2();

            if (puStack_14 != auStack_10 && puStack_14 != nullptr) {
                g_free(puStack_14);
            }
            if (localTmpPtr != &localTmpBuf && localTmpPtr != nullptr) {
                g_free(localTmpPtr);
            }

            storeKeyValue(valueOut); // value stored via internal state

            // Skip '&' if present
            if (*p == '&') {
                p++;
            }
            return p;
        }
    }

    return nullptr;
}