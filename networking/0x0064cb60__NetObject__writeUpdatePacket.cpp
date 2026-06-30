// FUNC_NAME: NetObject::writeUpdatePacket
void __fastcall NetObject::writeUpdatePacket(int this, undefined4 param2, undefined4 param3)
{
    // +0x138: bitstream buffer
    // +0x18:  dirty mask (bit field, size in bits)
    FUN_00658230(param3, this + 0x138, *(int *)(this + 0x18) + 7U >> 3, param2);
    return;
}