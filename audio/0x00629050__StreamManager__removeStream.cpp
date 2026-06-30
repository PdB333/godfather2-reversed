// FUNC_NAME: StreamManager::removeStream
int StreamManager::removeStream(int index)
{
    char *filename;
    int *errorCodePtr;
    char *errorString;
    int elementAddr;
    int *src, *dst;

    filename = (char *)getCurrentFileName();
    errorCodePtr = (int *)getErrorCodePtr();
    errorString = strerror((char *)*errorCodePtr);
    printError("cannot read %s: %s", filename + 1, errorString);

    if (index < 1) {
        elementAddr = getLastIndex();
    } else {
        elementAddr = *(int *)(this + 0xc) + -8 + index * 8;
    }

    src = (int *)(elementAddr + 8);
    dst = (int *)(elementAddr + 8);
    while (dst < *(int **)(this + 0x8)) {
        dst[-2] = *src;
        dst[-1] = src[1];
        dst += 2;
        src += 2;
    }

    *(int *)(this + 0x8) = *(int *)(this + 0x8) + -8;
    return 2;
}