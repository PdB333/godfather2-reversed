// FUNC_NAME: Entity::GetStatusByte
byte Entity::GetStatusByte() {
    byte outByte;
    byte outBuffer[4];
    int result = GetDataByHandle(this, &outByte, outBuffer);
    if (result != 0) {
        return *(byte *)(result + 0x22); // +0x22 status byte field
    }
    return 0;
}