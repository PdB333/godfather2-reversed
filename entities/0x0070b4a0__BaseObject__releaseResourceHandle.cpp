// FUNC_NAME: BaseObject::releaseResourceHandle
void __fastcall BaseObject::releaseResourceHandle(int thisPtr)
{
    // +0x398: handle to some resource (audio/asset handle), -1 indicates invalid
    if (*(int*)(thisPtr + 0x398) != -1) {
        ReleaseResource(*(int*)(thisPtr + 0x398));
        *(int*)(thisPtr + 0x398) = -1;
    }
}