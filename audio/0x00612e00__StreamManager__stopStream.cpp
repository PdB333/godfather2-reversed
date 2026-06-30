// FUNC_NAME: StreamManager::stopStream
void __fastcall StreamManager::stopStream(StreamManager* this) {
    uint uVar1;
    if (this->field_0xa0 != 0) {
        uVar1 = this->field_0xa0 & 0xff;
        if (gStreamTypeActive[this->field_0x14 * 0x10] != '\0') {
            uVar1 = uVar1 + 0x10;
        }
        FUN_00618d40(); // likely releaseStreamHandle
        gStreamActiveTable[uVar1] = 0;
    }
    gStreamGlobalFlag1 = 0;
    gStreamGlobalFlag2 = 0;
}