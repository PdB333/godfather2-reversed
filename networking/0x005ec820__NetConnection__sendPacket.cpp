// FUNC_NAME: NetConnection::sendPacket
void __fastcall NetConnection::sendPacket(void* thisPtr, void* data)
{
    // +0x564: pointer to a reliable stream object (likely PacketStream)
    if (*(int*)((char*)thisPtr + 0x564) != 0)
    {
        // Stack-allocated header for the packet
        // type = 2, flags = 0x1000, padding = 0
        struct PacketHeader
        {
            int type;
            int flags;
            int pad;
        } header = { 2, 0x1000, 0 };

        // Call the first virtual method of the reliable stream object,
        // passing the data and the header
        (*(void(__thiscall**)(void*, void*))(**(int**)((char*)thisPtr + 0x564)))(*(void**)((char*)thisPtr + 0x564), &header);
        return;
    }

    // +0x568: pointer to an unreliable stream object (likely PacketStream)
    if ((*(int*)((char*)thisPtr + 0x568) != 0) && (data != 0))
    {
        // Call the second virtual method (vtable offset +4) of the unreliable stream,
        // passing data and zeroed parameters (size 0x20, some flags)
        (*(void(__thiscall**)(void*, void*, int, int, int, int))(**(int**)((char*)thisPtr + 0x568) + 4))(*(void**)((char*)thisPtr + 0x568), data, 0, 0, 0x20, 0);
    }
}