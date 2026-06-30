// FUNC_NAME: NetPacket::initializeFromStream
undefined4 * __fastcall NetPacket::initializeFromStream(undefined4 param_1, undefined4 param_2, undefined4 *packet, undefined8 *streamData)
{
    int i;
    undefined4 *tempBuffer; // actually local_10a4, but used as pointer
    undefined4 *dest;
    undefined4 *src;

    // Allocate a large temporary buffer on stack (1064 * 4 = 4256 bytes)
    // This is used to hold intermediate data during construction.
    tempBuffer = (undefined4 *)__alloca(0x10A0); // 0x10A0 = 4256 bytes

    // Initialize the packet object: set vtable pointer and zero flags
    packet[1] = 0; // +0x04: some flag/state
    packet[2] = 0; // +0x08: another flag
    *packet = &PTR_LAB_00e433dc; // +0x00: vtable pointer

    // Fill the temporary buffer with data derived from param_2 (likely a key or hash)
    // FUN_00660a10: generates a 0x10-byte? based buffer? Actually it fills 1064 words.
    FUN_00660a10(param_2, 0x10, 0, tempBuffer);

    // Copy 0x81 (129) words from tempBuffer into packet at offset 0x1b (0x6c bytes)
    // This is likely a data block such as a hash or sequence numbers.
    dest = packet + 0x1b; // +0x6c
    src = tempBuffer;
    for (i = 0x81; i != 0; i = i - 1) {
        *dest = *src;
        src++;
        dest++;
    }

    // Duplicate the 8-byte stream data into two different locations in the packet
    // Offsets: +0x1c (7*4) and +0x0c (3*4) for first 8 bytes
    // Offsets: +0x24 (9*4) and +0x14 (5*4) for second 8 bytes
    // This suggests the stream data (e.g., a 64-bit ID or timestamp) is stored redundantly.
    *(undefined8 *)(packet + 7) = *streamData;      // +0x1c
    *(undefined8 *)(packet + 9) = streamData[1];     // +0x24
    *(undefined8 *)(packet + 3) = *streamData;       // +0x0c
    *(undefined8 *)(packet + 5) = streamData[1];     // +0x14

    // Perform some transformation or update using the object's fields and the temp buffer
    // FUN_00661210: likely combines or computes checksums, sequence numbers, etc.
    // Arguments: packet+3 (offset 0x0c), packet+0x17 (offset 0x5c), and tempBuffer.
    FUN_00661210(packet + 3, packet + 0x17, tempBuffer);

    // Set a final field to zero (likely a counter or flags)
    packet[0x9c] = 0; // +0x270

    return packet;
}