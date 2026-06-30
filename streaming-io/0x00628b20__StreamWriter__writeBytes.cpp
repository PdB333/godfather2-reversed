// FUNC_NAME: StreamWriter::writeBytes
// Address: 0x00628b20
// Role: Buffered byte writer that flushes local 512-byte buffer to dynamic backing buffer when full.
// Structure offsets (relative to 'this' as int*):
//   +0x00: current write pointer (byte*) into local buffer
//   +0x04: number of flushed chunks (uint32)
//   +0x08: pointer to backing buffer descriptor (BackingBuffer*)
//   +0x0C: start of local buffer data (512 bytes)
//   +0x20C: end of local buffer (exclusive)

typedef int32 int32;
typedef uint32 uint32;
typedef uint8 byte;

// Forward declarations of helper functions called in this function
int32 FUN_00627290();                  // Possibly allocate/reserve memory
void FUN_00626f80(void* buffer, int32); // Likely memory management (reset/init)
void FUN_00626fd0(int32);              // Unknown
void FUN_00627010(int32);              // Unknown
void FUN_006270e0();                   // Unknown
int32 FUN_00638920(void* backingBuf, int32* data, int32 size); // Encode data, returns encoded size
void FUN_006289a0();                   // Post-flush callback/notification

class StreamWriter {
public:
    // Write 'count' bytes from 'src' to the stream.
    // Buffers internally and flushes chunks as needed.
    void writeBytes(const byte* src, int32 count) {
        if (count == 0) return;
        
        do {
            count--;
            
            // Check if the local buffer is full (write pointer reached end)
            byte* currentPtr = *(byte**)this;   // this->current
            byte* endPtr = (byte*)((int32*)this + 0x83); // &this[0x83] = base + 0x20C
            if (endPtr <= currentPtr) {
                // Buffer full, compute amount of data currently in the local buffer
                int32 dataSize = currentPtr - (byte*)(this + 3); // bytes between start (this+3) and current
                if (dataSize != 0) {
                    // Flush local buffer to the backing buffer
                    BackingBuffer* backBuf = *(BackingBuffer**)(this + 2); // this->backingBuffer (offset +0x08)
                    
                    // Check if backing buffer needs expansion (e.g., its write pointer reached capacity)
                    int32* backWritePtr = *(int32**)(backBuf + 2); // backBuf->writePtr (offset +0x08)
                    int32* backCapPtr = *(int32**)(backBuf + 4);  // backBuf->capacity? (offset +0x10)
                    if (*(uint32*)(backCapPtr + 0x20) <= *(uint32*)(backCapPtr + 0x24)) {
                        // Need to resize/reallocate the backing buffer
                        int32 reserved = FUN_00627290();
                        FUN_00626f80(backBuf, 0);
                        FUN_00626fd0(0);
                        FUN_00626f80(backBuf, 0);
                        FUN_00627010(reserved);
                        FUN_006270e0();
                    }
                    
                    // Write a 4-byte token (identity, e.g., literal block) and the encoded data size
                    uint32* dst = *(uint32**)(backBuf + 2); // backing buffer's current write position
                    *dst = 4; // literal block marker
                    int32 encodedSize = FUN_00638920(backBuf, this + 3, dataSize); // encode data and get written size
                    dst[1] = encodedSize; // store encoded size (maybe for variable-length encoding)
                    
                    // Advance backing buffer write pointer by 8 bytes (token + size)
                    *(int32**)(backBuf + 2) += 8; // update backBuf->writePtr
                    
                    // Update flush count and reset local buffer pointer to start
                    this[1] = this[1] + 1; // this->chunkCount
                    *(int32**)this = this + 3; // reset current pointer to local buffer start
                    
                    FUN_006289a0(); // post-flush housekeeping
                }
            }
            
            // Copy one byte from source to local buffer
            *(byte*)(*(int32**)this) = *src;
            (*(int32**)this)++; // advance local write pointer
            src++;
        } while (count != 0);
    }
};