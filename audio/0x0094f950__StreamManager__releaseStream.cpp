// FUNC_NAME: StreamManager::releaseStream
void __fastcall StreamManager::releaseStream(int this)
{
    if ((*(byte *)(this + 0x68) & 2) != 0) {
        // +0x60: stream handle/pointer, +0x68: flags byte (bit1 = stream active)
        FUN_00939ba0(*(int *)(this + 0x60));
        *(byte *)(this + 0x68) &= 0xfd;  // clear bit1
    }
}