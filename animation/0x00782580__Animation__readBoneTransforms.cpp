// FUNC_NAME: Animation::readBoneTransforms
// File: 0x00782580 - Reads bone transformation data from a serialization stream and stores pointers to bone-specific data structures.

#include <cstdint>

class Animation {
public:
    // Offset fields for bone data (each is a pointer to a bone info block)
    // +0x54: bone0 - 0x54
    // +0x58: bone1
    // +0x5C: bone2
    // +0x60: bone3
    // +0x64: bone4
    // +0x68: bone5
    // +0x6C: bone6
    // +0x70: bone7
    // +0x74: bone8
    // +0x78: bone9
    // +0x7C: bone10
    // +0x80: bone11
    // +0x84: bone12
    // +0x88: bone13
    // +0x8C: bone14
    // +0x90: bone15

    void __thiscall readBoneTransforms(SerializationStream* stream) {
        stream->reset();
        stream->begin(0xd20b51cd); // Type hash for bone transform data (likely CRC of "BonePose")

        while (!stream->isFinished()) {
            uint32_t boneIndex = stream->readTag(); // Returns 0..15 for bone index
            void* boneData = stream->readPointer(); // Reads a pointer from the stream (at offset +8)
            switch (boneIndex) {
            case 0:
                m_bone7 = boneData; // +0x70
                break;
            case 1:
                m_bone0 = boneData; // +0x54
                break;
            case 2:
                m_bone1 = boneData; // +0x58
                break;
            case 3:
                m_bone2 = boneData; // +0x5C
                break;
            case 4:
                m_bone3 = boneData; // +0x60
                break;
            case 5:
                m_bone4 = boneData; // +0x64 (100 decimal)
                break;
            case 6:
                m_bone5 = boneData; // +0x68
                break;
            case 7:
                m_bone6 = boneData; // +0x6C
                break;
            case 8:
                m_bone8 = boneData; // +0x74
                break;
            case 9:
                m_bone10 = boneData; // +0x7C
                break;
            case 10:
                m_bone12 = boneData; // +0x84
                break;
            case 11:
                m_bone14 = boneData; // +0x8C
                break;
            case 12:
                m_bone9 = boneData; // +0x78
                break;
            case 13:
                m_bone11 = boneData; // +0x80
                break;
            case 14:
                m_bone13 = boneData; // +0x88
                break;
            case 15:
                m_bone15 = boneData; // +0x90
                break;
            }
            stream->advance();
        }
    }

private:
    // Bone data pointers in order of offset
    void* m_bone0;      // +0x54
    void* m_bone1;      // +0x58
    void* m_bone2;      // +0x5C
    void* m_bone3;      // +0x60
    void* m_bone4;      // +0x64
    void* m_bone5;      // +0x68
    void* m_bone6;      // +0x6C
    void* m_bone7;      // +0x70
    void* m_bone8;      // +0x74
    void* m_bone9;      // +0x78
    void* m_bone10;     // +0x7C
    void* m_bone11;     // +0x80
    void* m_bone12;     // +0x84
    void* m_bone13;     // +0x88
    void* m_bone14;     // +0x8C
    void* m_bone15;     // +0x90
};