// FUNC_NAME: MeshSlice::setupStreams
// Address: 0x00599be0
// Description: Sets up vertex stream descriptors for a mesh slice with up to 6 streams.
// Takes a pointer to a structure containing 6 element counts followed by interleaved vertex data.
// Fills in this object's stream descriptors (each 24 bytes) and returns total data size.
// Stream layout: [flags(4), pad(4?), count(2), stride(2), type(2), pad(2), dataPtr(4)] per stream.

#include <cstdint>

// Forward declaration of error handler (if needed)
extern int* DAT_01205590; // global for error handling function

struct StreamDescriptor {
    uint32_t flags;        // +0x00: combined flags (bit0 set, bits 1/2 cleared depending on stream index)
    uint32_t pad0;         // +0x04: padding
    uint32_t flags2;       // +0x08: set to 0
    uint16_t stride;       // +0x0C: set to 1 (bytes per vertex per stream? )
    uint16_t count;        // +0x0E: number of elements in this stream
    uint16_t type;         // +0x10: set to 3 (maybe D3D vertex buffer type)
    uint16_t pad1;         // +0x12: padding
    uint32_t dataPtr;      // +0x14: pointer to vertex data for this stream
} __attribute__((packed));

struct StreamInput {
    int counts[6];          // [0]..[5] element counts for each stream
    // followed by interleaved vertex data (each element is 6 ints = 24 bytes)
    int buffer[0];          // Flexible array member
};

int __thiscall MeshSlice::setupStreams(void* thisObj, int* input) {
    StreamDescriptor* desc = static_cast<StreamDescriptor*>(thisObj);
    StreamInput* in = reinterpret_cast<StreamInput*>(input);

    int count0 = in->counts[0];
    int count1 = in->counts[1];
    int count2 = in->counts[2];
    int count3 = in->counts[3];
    int count4 = in->counts[4];
    int count5 = in->counts[5];

    int* baseData = in->buffer; // start of vertex data

    // Compute offsets into the interleaved buffer for each stream
    int* stream0Data = baseData;
    int* stream1Data = stream0Data + count0 * 6;
    int* stream2Data = stream1Data + count1 * 6;
    int* stream3Data = stream2Data + count2 * 6;
    int* stream4Data = stream3Data + count3 * 6;
    int* stream5Data = stream4Data + count4 * 6; // used for the last stream's base pointer

    // Set up stream 0 (index 0)
    if (count0 > 0xFFFF) {
        // error: count too large
        (**(code**)(*DAT_01205590 + 4))();  // likely crash/assert handler
    }
    if (count0 != 0) {
        desc[0].count = count0;
        desc[0].flags2 = 0;
        desc[0].stride = 1;
        desc[0].dataPtr = reinterpret_cast<uint32_t>(stream0Data);
        desc[0].type = 3;
    }
    // Set flags: bit0 = 1, bit1 = 0
    desc[0].flags = (desc[0].flags & 0xFFFFFFFD) | 1;

    // Stream 1
    if (count1 > 0xFFFF) {
        (**(code**)(*DAT_01205590 + 4))();
    }
    if (count1 != 0) {
        desc[1].flags2 = 0;
        desc[1].stride = 1;
        desc[1].count = count1;
        desc[1].dataPtr = reinterpret_cast<uint32_t>(stream1Data);
        desc[1].type = 3;
    }
    desc[0].flags = (desc[0].flags & 0xFFFFFFFD) | 1; // note: still modifying first descriptor? Possibly a bug in decompilation or intentional? Actually repeated pattern.

    // Stream 2
    if (count2 > 0xFFFF) {
        (**(code**)(*DAT_01205590 + 4))();
    }
    if (count2 != 0) {
        desc[2].flags2 = 0;
        desc[2].stride = 1;
        desc[2].count = count2;
        desc[2].dataPtr = reinterpret_cast<uint32_t>(stream2Data);
        desc[2].type = 3;
    }
    desc[0].flags = (desc[0].flags & 0xFFFFFFFD) | 1;

    // Stream 3
    if (count3 > 0xFFFF) {
        (**(code**)(*DAT_01205590 + 4))();
    }
    if (count3 != 0) {
        desc[3].flags2 = 0;
        desc[3].stride = 1;
        desc[3].count = count3;
        desc[3].dataPtr = reinterpret_cast<uint32_t>(stream3Data);
        desc[3].type = 3;
    }
    // For streams 3-5, clear bit2 instead of bit1, set bit0
    desc[0].flags = (desc[0].flags & 0xFFFFFFFB) | 1;

    // Stream 4
    if (count4 > 0xFFFF) {
        (**(code**)(*DAT_01205590 + 4))();
    }
    if (count4 != 0) {
        desc[4].flags2 = 0;
        desc[4].stride = 1;
        desc[4].count = count4;
        desc[4].dataPtr = reinterpret_cast<uint32_t>(stream4Data);
        desc[4].type = 3;
    }
    // Note: second time using 0xFFFFFFFB? Decompiled shows 0xFFFFFFFB for the fourth? Actually pattern: first three use &0xFFFFFFFD|1, next three use &0xFFFFFFFB|1.
    desc[0].flags = (desc[0].flags & 0xFFFFFFFB) | 1;

    // Stream 5
    if (count5 > 0xFFFF) {
        (**(code**)(*DAT_01205590 + 4))();
    }
    if (count5 != 0) {
        desc[5].flags2 = 0;
        desc[5].stride = 1;
        desc[5].count = count5;
        // For stream5, data pointer is relative to stream4Data + count4*6, not directly stream5Data? Actually decompiled: piVar4 + iVar8 * 6, where piVar4 = stream4Data, iVar8 = count4, so pointer = stream4Data + count4*6 = stream5Data. So same.
        desc[5].dataPtr = reinterpret_cast<uint32_t>(stream5Data);
        desc[5].type = 3;
    }
    desc[0].flags = (desc[0].flags & 0xFFFFFFFB) | 1;

    // Return total size of vertex data in bytes? 
    // (count5 * 0x18) - (int)input + (int)(stream5Data)
    // int* arithmetic: (count5 * 0x18) is 24*count5 (size of last stream data in bytes)
    // minus input (pointer to struct) plus stream5Data (address of last stream data)
    // = (stream5Data - input) + count5*24 = offset from input to end of all data?
    // Possibly returns the total allocated memory offset or size.
    return (count5 * 24 - reinterpret_cast<int>(input)) + reinterpret_cast<int>(stream5Data);
}