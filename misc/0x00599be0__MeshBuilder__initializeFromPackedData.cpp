// FUNC_NAME: MeshBuilder::initializeFromPackedData

// Function at 0x00599be0: Sets up vertex stream descriptors from a packed buffer.
// Takes a packed buffer containing 6 counts (int each) followed by interleaved vertex data (each vertex element is 6 ints).
// Initializes the internal stream descriptors (stride, type, count, usage, data pointer) and returns the total byte size of the packed buffer.
// The internal structure (`this`) has a 8-byte header (flags at +0) and 6 descriptors of 16 bytes each starting at offset 8.

class MeshBuilder {
public:
    // +0x00: flags (bit0 = stream enable, bit1 = usage mode)
    // +0x04: (unused)
    // +0x08: descriptor[0] (16 bytes)
    // +0x18: descriptor[1]
    // +0x28: descriptor[2]
    // +0x38: descriptor[3]
    // +0x48: descriptor[4]
    // +0x58: descriptor[5]
    
    struct VertexStreamDescriptor {
        int stride;      // +0x00 (set to 0)
        short type;      // +0x04 (set to 1)
        short count;     // +0x06
        short usage;     // +0x08 (set to 3)
        short padding;   // +0x0A
        void* data;      // +0x0C
    };
    
    // Sets up vertex streams from packed data. Returns total byte size of the packed buffer.
    int setVertexStreams(int* packedDescriptor);
};

// Global error handler for assertions
extern void assertHandler();

int MeshBuilder::setVertexStreams(int* packedDescriptor) {
    int count0 = packedDescriptor[0];  // first stream vertex count
    int count1 = packedDescriptor[1];  // second stream vertex count
    int count2 = packedDescriptor[2];  // third stream vertex count
    int count3 = packedDescriptor[3];  // fourth stream vertex count
    int count4 = packedDescriptor[4];  // fifth stream vertex count
    int count5 = packedDescriptor[5];  // sixth stream vertex count
    
    int* dataStart = packedDescriptor + 6;  // start of interleaved vertex data
    
    // Compute start pointers for each stream's data
    int* stream0Data = dataStart;
    int* stream1Data = stream0Data + count0 * 6;
    int* stream2Data = stream1Data + count1 * 6;
    int* stream3Data = stream2Data + count2 * 6;
    int* stream4Data = stream3Data + count3 * 6;
    int* stream5Data = stream4Data + count4 * 6;  // used as pointer for stream5
    
    // Get pointer to this's descriptor array
    VertexStreamDescriptor* descriptors = reinterpret_cast<VertexStreamDescriptor*>(reinterpret_cast<char*>(this) + 8);
    
    // Process stream 0
    if (count0 > 0xFFFF) {
        assertHandler();
    }
    if ((short)count0 != 0) {
        descriptors[0].stride = 0;
        descriptors[0].type = 1;
        descriptors[0].count = (short)count0;
        descriptors[0].usage = 3;
        descriptors[0].data = (void*)stream0Data;
    }
    this->flags = (this->flags & 0xfffffffd) | 1;  // set bit0, clear bit1
    
    // Process stream 1
    if (count1 > 0xFFFF) {
        assertHandler();
    }
    if ((short)count1 != 0) {
        descriptors[1].stride = 0;
        descriptors[1].type = 1;
        descriptors[1].count = (short)count1;
        descriptors[1].usage = 3;
        descriptors[1].data = (void*)stream1Data;
    }
    this->flags = (this->flags & 0xfffffffd) | 1;
    
    // Process stream 2
    if (count2 > 0xFFFF) {
        assertHandler();
    }
    if ((short)count2 != 0) {
        descriptors[2].stride = 0;
        descriptors[2].type = 1;
        descriptors[2].count = (short)count2;
        descriptors[2].usage = 3;
        descriptors[2].data = (void*)stream2Data;
    }
    this->flags = (this->flags & 0xfffffffd) | 1;
    
    // Process stream 3
    if (count3 > 0xFFFF) {
        assertHandler();
    }
    if ((short)count3 != 0) {
        descriptors[3].stride = 0;
        descriptors[3].type = 1;
        descriptors[3].count = (short)count3;
        descriptors[3].usage = 3;
        descriptors[3].data = (void*)stream3Data;
    }
    this->flags = (this->flags & 0xfffffffd) | 1;
    
    // Process stream 4 (usage bit set differently)
    if (count4 > 0xFFFF) {
        assertHandler();
    }
    if ((short)count4 != 0) {
        descriptors[4].stride = 0;
        descriptors[4].type = 1;
        descriptors[4].count = (short)count4;
        descriptors[4].usage = 3;
        descriptors[4].data = (void*)stream4Data;
    }
    this->flags = (this->flags & 0xfffffffb) | 1;  // set bit0, clear bit1
    
    // Process stream 5
    if (count5 > 0xFFFF) {
        assertHandler();
    }
    if ((short)count5 != 0) {
        descriptors[5].stride = 0;
        descriptors[5].type = 1;
        descriptors[5].count = (short)count5;
        descriptors[5].usage = 3;
        descriptors[5].data = (void*)(stream5Data);
    }
    this->flags = (this->flags & 0xfffffffb) | 1;
    
    // Return total byte size of the packed buffer (counts + all vertex data)
    return (int)(stream5Data + count5 * 6) - (int)packedDescriptor;
}