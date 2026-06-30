// FUNC_NAME: AnimationState::samplePoseFromAnimation
// Address: 0x00564470
// This function samples animation data from a global database (DAT_011397d0)
// using an index/timestamp at offset +0x3c, and stores the result as 8
// four-component vectors (x,y,z,w=0) starting at +0x50 (16 bytes each).
// The helper FUN_00c0b080 fills a temporary buffer with six floats (t0..t5)
// which are then distributed into the 8 vectors in a specific pattern,
// likely representing bone transforms or orientations for a skeleton.

void __thiscall AnimationState::samplePoseFromAnimation(void)
{
    float t0, t1, t2, t3, t4, t5; // temporary components from animation sample

    // Call helper to fill temp buffer from global animation data
    // (float)this+0x3c is likely a timestamp or sequence index
    FUN_00c0b080(&DAT_011397d0, *(float*)((char*)this + 0x3c), &t0);

    // First vector at +0x50: (t0, t1, t2, 0)
    *(float*)((char*)this + 0x50) = t0;
    *(float*)((char*)this + 0x54) = t1;
    *(float*)((char*)this + 0x58) = t2;
    *(float*)((char*)this + 0x5C) = 0.0f;

    // Second vector at +0x60: (t0, t1, t5, 0)
    *(float*)((char*)this + 0x60) = t0;
    *(float*)((char*)this + 0x64) = t1;
    *(float*)((char*)this + 0x68) = t5;
    *(float*)((char*)this + 0x6C) = 0.0f;

    // Third vector at +0x70: (t3, t1, t5, 0)
    *(float*)((char*)this + 0x70) = t3;
    *(float*)((char*)this + 0x74) = t1;
    *(float*)((char*)this + 0x78) = t5;
    *(float*)((char*)this + 0x7C) = 0.0f;

    // Fourth vector at +0x80: (t3, t1, t2, 0)
    *(float*)((char*)this + 0x80) = t3;
    *(float*)((char*)this + 0x84) = t1;
    *(float*)((char*)this + 0x88) = t2;
    *(float*)((char*)this + 0x8C) = 0.0f;

    // Fifth vector at +0x90: (t0, t4, t2, 0)
    *(float*)((char*)this + 0x90) = t0;
    *(float*)((char*)this + 0x94) = t4;
    *(float*)((char*)this + 0x98) = t2;
    *(float*)((char*)this + 0x9C) = 0.0f;

    // Sixth vector at +0xA0: (t0, t4, t5, 0)
    *(float*)((char*)this + 0xA0) = t0;
    *(float*)((char*)this + 0xA4) = t4;
    *(float*)((char*)this + 0xA8) = t5;
    *(float*)((char*)this + 0xAC) = 0.0f;

    // Seventh vector at +0xB0: (t3, t4, t5, 0)
    *(float*)((char*)this + 0xB0) = t3;
    *(float*)((char*)this + 0xB4) = t4;
    *(float*)((char*)this + 0xB8) = t5;
    *(float*)((char*)this + 0xBC) = 0.0f;

    // Eighth vector at +0xC0: (t3, t4, t2, 0)
    *(float*)((char*)this + 0xC0) = t3;
    *(float*)((char*)this + 0xC4) = t4;
    *(float*)((char*)this + 0xC8) = t2;
    *(float*)((char*)this + 0xCC) = 0.0f;
}