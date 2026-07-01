// FUNC_NAME: ResourceHandle::release
void __fastcall ResourceHandle::release(int *this) {
    // +0x04: second field (probably aux data)
    this[1] = 0;
    // Release the resource pointed to by the first field (offset 0)
    FUN_009c8f10(this[0]);
    // +0x00: primary handle/pointer
    this[0] = 0;
    // +0x08: third field (likely another resource or state)
    this[2] = 0;
}