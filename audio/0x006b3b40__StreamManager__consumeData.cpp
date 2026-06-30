// FUNC_NAME: StreamManager::consumeData
// Address: 0x006b3b40
// Role: Reduces the available count at +0x6c by up to 'count' and triggers an update

void __thiscall StreamManager::consumeData(uint count)
{
    uint available = *(uint *)(this + 0x6c); // +0x6c: number of bytes/items available
    if (available < count) {
        count = available;
    }
    *(uint *)(this + 0x6c) = available - count;
    onDataConsumed(); // FUN_006b2f70 – notification after consumption
}