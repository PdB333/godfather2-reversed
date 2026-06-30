// FUNC_NAME: NetConnection::dispatchDataBySize
// Address: 0x0068dd10
// Role: Routes incoming data to different processors based on data size.
// Data is first copied into a 24-byte header buffer, then dispatched to one of three
// segment processors (small, medium, large) depending on total size.
// Offsets: +0x14 = small data processor, +0x29c = medium, +0x95c = large.

uint __thiscall NetConnection::dispatchDataBySize(const undefined8 *dataBuffer, uint flags, uint dataSize)
{
    undefined8 header[3]; // 24-byte header copy from the start of dataBuffer
    uint result;

    header[0] = dataBuffer[0];
    header[1] = dataBuffer[1];
    header[2] = dataBuffer[2];

    // default result retains lower 8 bits of flags (upper bits appear to be a mask)
    result = flags & 0xffffff00;

    if (dataSize < 6) {
        // Tiny data: process via small segment handler
        result = processDataSegment(this + 0x14, 6, header);
    } else if (dataSize < 0x10) {
        // Medium data: process via medium segment handler
        result = processDataSegment(this + 0x29c, 0x10, header);
    } else if (dataSize < 0x1f) {
        // Large data: process via large segment handler
        result = processDataSegment(this + 0x95c, 0x1f, header);
    }
    // dataSize >= 0x1f: no processing, result stays as flags & 0xffffff00

    return result;
}