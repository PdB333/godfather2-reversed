// FUNC_NAME: AnimationTrackDecoder::decompressFrames
// Function at 0x00589ef0: Decompresses a compressed animation track.
// Reads a stream of ushort deltas (interleaved) and produces float vectors.
// Uses a 2-bit code (from a bitstream via __aullshr) to determine which components are delta-coded.
// State stored at offsets: +0x38 (ushort* mCompressedDeltaPtr), +0x3c (float* mBaseFramePtr), +0x44 (int mFrameIndex).

extern float kScaleFactor; // DAT_00e445cc - scaling factor for ushort delta values

class AnimationTrackDecoder {
public:
    // +0x38: pointer to compressed delta data (ushort array)
    unsigned short* mCompressedDeltaPtr;
    // +0x3c: pointer to base frame float data (3 floats per frame)
    float* mBaseFramePtr;
    // +0x44: current frame index
    int mFrameIndex;

    // Process frames from startIndex to endIndex.
    // outBuffer must be pre-allocated for (endIndex - startIndex) * 3 floats.
    void __thiscall decompressFrames(int startIndex, int endIndex, float* outBuffer) {
        int tempIndex;

        // Advance state to startIndex
        tempIndex = this->mFrameIndex;
        while (tempIndex < startIndex) {
            tempIndex = this->mFrameIndex;
            // Read 2-bit code from bitstream (intrinsic)
            unsigned int code = __aullshr() & 3;
            if ((code - 1) < 3) {
                // Code 1,2,3: skip 1 ushort delta
                this->mCompressedDeltaPtr += 2; // 2 bytes per ushort? Actually increment by 2 bytes means one ushort
                // But the decompiler shows +2, so it's increment by 2 (sizeof(short)? Wait, pointer is ushort*, +2 adds 2 ushorts? No, pointer arithmetic: adding 2 to a ushort* adds 4 bytes.
                // In the decompiled code: int offset addition: *(int *)(+0x38) = *(int *)(+0x38) + 2; That's adding 2 to the raw address, not to the pointer as a ushort*.
                // So it's a byte offset addition of 2 bytes, which is one ushort.
                // We'll simulate by casting to char* and adding bytes.
                // In C++, to match the byte offset, we can do:
                this->mCompressedDeltaPtr = (unsigned short*)((char*)this->mCompressedDeltaPtr + 2);
            } else {
                // Code 0: skip 3 ushorts (6 bytes)
                this->mCompressedDeltaPtr = (unsigned short*)((char*)this->mCompressedDeltaPtr + 6);
            }
            this->mBaseFramePtr += 3; // 3 floats = 12 bytes
            tempIndex++;
            this->mFrameIndex = tempIndex;
        }

        // Process frames from current to endIndex
        tempIndex = this->mFrameIndex;
        do {
            if (endIndex <= tempIndex) {
                return;
            }
            tempIndex = this->mFrameIndex;
            unsigned int code = __aullshr() & 3;
            unsigned short* delta = this->mCompressedDeltaPtr;
            float* base = this->mBaseFramePtr;

            switch (code) {
            case 1:
                // Only first component changed
                outBuffer[0] = (float)*delta * kScaleFactor + base[0];
                outBuffer[1] = base[1];
                outBuffer[2] = base[2];
                delta++;
                break;
            case 2:
                // Only second component changed
                outBuffer[0] = base[0];
                outBuffer[1] = (float)*delta * kScaleFactor + base[1];
                outBuffer[2] = base[2];
                delta++;
                break;
            case 3:
                // Only third component changed
                outBuffer[0] = base[0];
                outBuffer[1] = base[1];
                outBuffer[2] = (float)*delta * kScaleFactor + base[2];
                delta++;
                break;
            default: // case 0
                // All components changed (three deltas)
                outBuffer[0] = (float)*delta * kScaleFactor + base[0];
                outBuffer[1] = (float)*(delta + 1) * kScaleFactor + base[1];
                outBuffer[2] = (float)*(delta + 2) * kScaleFactor + base[2];
                delta += 3;
                break;
            }
            this->mBaseFramePtr = base + 3; // advance by 3 floats (12 bytes)
            this->mCompressedDeltaPtr = delta; // ushort pointer advanced appropriately
            outBuffer += 3;
            tempIndex++;
            this->mFrameIndex = tempIndex;
        } while (true);
    }
};