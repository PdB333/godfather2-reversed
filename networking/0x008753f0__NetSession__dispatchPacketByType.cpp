// FUNC_NAME: NetSession::dispatchPacketByType
int __thiscall NetSession::dispatchPacketByType(NetSession* this, uint* packetType, undefined4 param_3)
{
    uint type = *packetType;
    if (type > 9 && type < 14) {
        // Packet types 10 and 12 use virtual at vtable+0x1c0 (e.g. processUnreliablePacket)
        // Packet types 11 and 13 use virtual at vtable+0x1c4 (e.g. processReliablePacket)
        if (type != 10 && type != 12) {
            (*(void (__thiscall**)(NetSession*, uint*, undefined4))(*(int*)this + 0x1c4))(this, packetType, param_3);
            return 1;
        }
        (*(void (__thiscall**)(NetSession*, uint*, undefined4))(*(int*)this + 0x1c0))(this, packetType, param_3);
        return 1;
    }
    return 0;
}