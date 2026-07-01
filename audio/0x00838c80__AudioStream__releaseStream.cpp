// FUNC_NAME: AudioStream::releaseStream
#include <cstdint>

// Internal audio stream cleanup method
void __thiscall AudioStream::releaseStream(void* this) {
    // Release file/resource handle if valid
    if (*reinterpret_cast<int32_t*>(static_cast<char*>(this) + 0xf8) != -1) {
        // Close the underlying stream resource (e.g., file handle or memory mapping)
        FUN_0090dff0(*reinterpret_cast<int32_t*>(static_cast<char*>(this) + 0xf8));
        *reinterpret_cast<int32_t*>(static_cast<char*>(this) + 0xf8) = -1;
    }

    // Global audio manager cleanup (e.g., decouple from mixer)
    FUN_00838200();

    // Stream-specific shutdown (stop playback, flush buffers)
    FUN_00839c90(this);   // member function call

    // Free an associated memory block (probably audio data buffer)
    // stack structure: { int32_t bufferPtr; int32_t size; int8_t flags; }
    struct BufferInfo {
        int32_t ptr;    // +0x00
        int32_t size;   // +0x04
        int8_t flags;   // +0x08
    } bufInfo;

    bufInfo.ptr  = *reinterpret_cast<int32_t*>(static_cast<char*>(this) + 0x9c);   // buffer pointer stored at +0x9C
    bufInfo.size = 0;   // clear size
    bufInfo.flags= 0;   // clear flags

    // Release the buffer (likely calls free/destroy with size 0 as a signal)
    FUN_00408a00(&bufInfo, 0);
}