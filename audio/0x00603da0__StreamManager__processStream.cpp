// FUNC_NAME: StreamManager::processStream
void __thiscall StreamManager::processStream(void* this, float deltaTime, undefined4 buffer, undefined4 context, undefined4 callbackData)
{
    char cVar1;
    int pData;
    int dataSize;
    undefined4 someInt;
    code* funcPtr1;
    int handleArray[3];
    code* funcPtr2;

    // Check if stream channels are initialized (bit 1 of flags at +0x4c)
    if ((*(uint*)((int)this + 0x4c) >> 1 & 1) == 0) {
        sub_603c50();
        sub_603c50();
        sub_603c50();
        *(uint*)((int)this + 0x4c) = *(uint*)((int)this + 0x4c) | 2;
    }

    sub_4d3fe0();
    sub_4d4ad0(context, &DAT_00e3ab7c, (double)deltaTime);
    handleArray[0] = 0;
    handleArray[1] = 0;
    handleArray[2] = 0;
    funcPtr2 = (code*)0x0;
    pData = 0;
    dataSize = 0;
    someInt = 0;
    funcPtr1 = (code*)0x0;
    cVar1 = sub_4d5210(&DAT_00e40868, handleArray, &pData);
    if (cVar1 == '\0') {
        sub_603ec0(this, callbackData);
    }
    else {
        sub_603ec0(this, callbackData);
        sub_4d3e20();
        sub_4d4060(buffer, 0x30);
        if (dataSize != 0) {
            sub_4d4300();
            sub_4d43f0(pData, 0, dataSize);
        }
    }
    if (pData != 0) {
        (*funcPtr1)();
    }
    if (handleArray[0] != 0) {
        (*funcPtr2)();
    }
    return;
}