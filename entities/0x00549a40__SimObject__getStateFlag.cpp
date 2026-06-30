// FUNC_NAME: SimObject::getStateFlag
void __thiscall SimObject::getStateFlag(unsigned char *outFlag) {
    // Read byte at offset 0x11 from the sub-object pointed to by this+0x18 (likely a state or data block)
    *outFlag = *(unsigned char *)(*(int *)(this + 0x18) + 0x11);
}