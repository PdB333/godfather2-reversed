// FUNC_NAME: GameObject::setFlag20
void __fastcall GameObject::setFlag20(void* thisPtr) {
    // +0x184: flags bitmask (DWORD)
    *(uint32_t*)((uint8_t*)thisPtr + 0x184) |= 0x20;
}