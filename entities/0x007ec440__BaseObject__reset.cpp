// FUNC_NAME: BaseObject::reset
void __thiscall BaseObject::reset(BaseObject* this) {
    // +0x20: some integer field (set to 0)
    *(int*)((char*)this + 0x20) = 0;
    // +0x24: some handle/ID field (set to -1)
    *(int*)((char*)this + 0x24) = -1;
}