// FUNC_NAME: NetPacket::getTotalSize
int __fastcall NetPacket::getTotalSize(NetPacket* thisPtr)
{
    uint count = *(uint*)((char*)thisPtr + 0x34); // number of sub-packets/chunks
    int totalSize = 0x18; // base packet header size
    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            totalSize += getChunkSize(); // FUN_008c17a0: returns size of each chunk (no per-item parameter in this loop)
        }
    }
    return totalSize;
}