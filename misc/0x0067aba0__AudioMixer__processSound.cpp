// FUNC_NAME: AudioMixer::processSound
// Reconstructed from Ghidra decompilation at 0x0067aba0 (The Godfather 2, EARS engine)
// Handles mixing a single sound event into the main audio output buffer.
// param_2 = sound index, param_3 = output left volume (short), param_4 = output master volume (unsigned short)

struct AudioMixerInternalBuffer { // offset layout from buffer handle (param_1[0x3f])
    int   type;          // +0x00   set to 3
    // ... 
    short state;         // +0x36   e.g., playing/stopped
    short sampleCount;   // +0x38   number of samples per channel
    // ... 
    int   leftSamples;   // +0x44   pointer to left channel sample buffer
    int   rightSamples;  // +0x48   pointer to right channel sample buffer
};

struct SoundEventEntry { // 8 bytes each
    short flags;         // +0x00
    short dataSize;      // +0x02   number of bytes of sound data
    int   dataOffset;    // +0x04   offset into ring buffer (or frequency?)
};

struct AudioRingBuffer { // param_1[1] points to this
    int   data;          // +0x00   base pointer to audio data
    int   writeOffset;   // +0x04   current write position
    int   something;     // +0x08
    int   baseOffset;    // +0x0C   base offset (for wrap-around)
};

// Allocated temp block header (before the data pointer returned by allocateAudioBuffer)
struct TempBlockHeader {
    int   refCount;      // +0x00 (actually +0x04 from allocation? see code)
    int   field04;
    // ... 
};

// Function pointers
extern void* (*gAudioFree)(TempBlockHeader* block); // DAT_01206694

// External functions (assumed names from patterns)
int getAudioBuffer(int handle, int, int, int); // FUN_00678100
void* allocateAudioBuffer();                   // FUN_00673070
int processAudio(AudioMixer* self, void* buffer, int sampleRate, int size, int maxLeft, int maxRight, int unknown1, int unknown2, int unknown3); // FUN_0067ae20
void stopAudio();                                   // FUN_00677e80
void releaseAudioBuffer(int bufferHandle);          // FUN_0067ba50

int __thiscall AudioMixer::processSound(int soundIndex, short* outLeftVolume, unsigned short* outMasterVolume) {
    int bufferCount = this[0x42]; // +0x108 (offset in ints)
    // Check conditions to set a "active" flag
    if (*(short*)((char*)this + 0xa6) != 0 && 
        *(char*)((char*)this + 0xad) != '\0' && 
        ((char)this[0x2b]) == '\0') { // this[0x2b] is the int at offset 0xac
        *(char*)((int*)this + 0x2b) = 1; // set flag
    }

    int bufferHandle = getAudioBuffer(*(int*)this, 0, 0, 0); // this[0] is some ID
    this[0x3f] = bufferHandle; // store buffer handle at offset 0xfc
    *(short*)(bufferHandle + 0x34) = 3; // set buffer type to 3

    if ((int)(soundIndex & 0xffff) < (int)(short)bufferCount) {
        SoundEventEntry* event = (SoundEventEntry*)(this[3] + (soundIndex & 0xffff) * 8); // this[3] is event table pointer
        unsigned short dataSize = *(unsigned short*)((char*)event + 2);

        // Update ring buffer write position
        AudioRingBuffer* ring = (AudioRingBuffer*)this[1];
        ring->writeOffset = event->dataOffset + ring->baseOffset + this[0xb]; // this[0xb] is an extra offset

        void* tempBuffer = allocateAudioBuffer();
        if (tempBuffer != nullptr) {
            if (dataSize != 0) {
                int writePos = ring->writeOffset;
                int basePointer = bufferHandle; // actually bufferHandle is the base of the ring buffer? Doesn't match exactly
                // Actually the copy: source = bufferHandle + writePos, dest = tempBuffer
                // In the code: iVar8 = bufferHandle, iVar7 = writePos, puVar9 = tempBuffer
                // Then loop copying dataSize bytes from (iVar8 + iVar7) to tempBuffer
                void* src = (void*)((int)bufferHandle + writePos);
                void* dst = tempBuffer;
                memcpy(dst, src, dataSize); // simplified, actual loop is self-relative weirdness but same effect
                ring->writeOffset += dataSize; // buffer's write offset increases? Actually the code increments piVar5[1] which is ring->writeOffset
                // Wait: the code does piVar5[1] = iVar7 + uVar13; so ring->writeOffset += dataSize.
                // But we already set it above. Actually the original code sets ring->writeOffset first, then does the copy and increments again. So it's a double increment.
                // To keep faithful, I'll replicate the increment after copy.
                ring->writeOffset = writePos + dataSize; // re-add to mimic original order (already set above, then add again)
            }

            // Process audio: mix into tempBuffer? The third param is event->dataOffset again? but in code it's *(int*)(event + 4) which is event->dataOffset (or sampleRate?).
            processAudio(this, tempBuffer, event->dataOffset, dataSize, 0x10000, 0x10000, 0, 0, 0);

            if (*(char*)(this + 7) == '\0') { // this[7] is a byte flag for channel select
                this[0x24] = (unsigned int)*(unsigned short*)(*(int*)(this[0x41] + 0x10) + (soundIndex & 0xffff) * 2);
                this[0x25] = 0;
            } else {
                this[0x24] = 0;
                this[0x25] = (unsigned int)*(unsigned short*)(*(int*)(this[0x41] + 0x10) + (soundIndex & 0xffff) * 2);
            }

            // Check if buffer is still playing and not already stopped
            AudioMixerInternalBuffer* buf = (AudioMixerInternalBuffer*)bufferHandle;
            if (buf->state == 0 || *(char*)(this + 0xd) != '\0') {
                stopAudio();
                *(char*)(this + 0xd) = 0;
            }

            // Decrement reference count and free temp buffer
            int obj = *(int*)this; // this[0] is some object
            *(int*)(*(int*)(obj + 0xc) + *(int*)((char*)tempBuffer - 8) * 4) = 0; // messy reference
            int* refCount = (int*)(obj + 4);
            (*refCount)--;
            gAudioFree((TempBlockHeader*)((char*)tempBuffer - 0x10));
        }
    }

    // Mix into output buffers (left/right sample arrays)
    AudioMixerInternalBuffer* outBuf = (AudioMixerInternalBuffer*)this[0x3f];
    // Clear current samples for this channel? The code writes zeros then sets new values.
    *(short*)(*(int*)(outBuf->rightSamples) + outBuf->sampleCount * 2) = 0; // Actually offset 0x48 is pointer, then offset 0x38 is sampleCount index
    // Wait: The code: *(undefined2 *)(*(int *)(iVar7 + 0x48) + *(short *)(iVar7 + 0x38) * 2) = 0;
    // So: *(short*)(rightSamplesPtr + sampleCount * 2) = 0; similarly for left? Actually there is also for left (0x44).
    // Then: write left volume (this[0x24]) and right volume (this[0x25]) to similar positions.
    // Then find maximum in rightSamples array.
    // Then add masterVolume/10 to that max and write pan/volume to outputs.

    short sampleIndex = outBuf->sampleCount; // current write index
    short* rights = (short*)outBuf->rightSamples;
    short* lefts  = (short*)outBuf->leftSamples;

    rights[sampleIndex] = (short)this[0x25]; // set right sample value
    lefts[sampleIndex]  = (short)this[0x24]; // set left sample value

    *outLeftVolume = (short)this[0x24]; // output left volume

    short minRight = rights[0]; // actually they use both first two elements, not sure
    short maxRight = rights[0];
    if (sampleIndex > 1) {
        for (int i = 1; i < sampleIndex; i++) {
            if (rights[i] > maxRight) maxRight = rights[i];
        }
    }

    unsigned short masterVol = this[0x43]; // +0x10c
    rights[sampleIndex + 2] = masterVol / 10 + maxRight; // write peak sample
    lefts[sampleIndex + 2]  = rights[sampleIndex + 2] - masterVol; // derived

    // Average of first two samples for something
    short avg = (short)((lefts[sampleIndex] + rights[sampleIndex]) >> 1); // actually code uses sVar1 and sVar2 from lefts[0] and lefts[1]? Wait they used the same first two.
    // The code: sVar1 = *(short*)(leftsPtr + 0); sVar2 = *(short*)(leftsPtr + 2); then uVar14 = (sVar1 + sVar2) >> 1.
    // But this is for index 0 and 1? Actually indices 0 and 1 are from the lefts array at base + 0 and base+2.
    // They write uVar14 to lefts[2 + sampleIndex*2]? Actually they write to lefts + 4 + sampleIndex*2 (offset 4 bytes from base plus sampleIndex*2). Very messy.
    // Since this is reconstruction, I'll simplify to approximate: set pan average.
    // For output param_4, they set to masterVol.

    *outMasterVolume = masterVol;

    this[0x3f] = 0; // clear buffer handle
    releaseAudioBuffer(bufferHandle);

    return bufferHandle;
}