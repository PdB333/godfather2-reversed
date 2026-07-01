// FUNC_NAME: SoundDispatcher::dispatchSound
// Function address: 0x0076e5c0
// Role: Dispatches sound events based on sound ID and start/stop flag. Reads sound IDs from an audio manager and triggers playback via a virtual method.

void __thiscall SoundDispatcher::dispatchSound(uint soundId, bool start)
{
    AudioManager* pAudio = reinterpret_cast<AudioManager*>(this->field_0x14);
    bool isSpecial = (pAudio->field_0x1b8c == 1);

    // Group 1: IDs at offsets 0x68c, 0x6b4, 0x674 (shifted right by 2)
    if ((soundId == *(uint*)((char*)pAudio + 0x68c) >> 2) ||
        (soundId == *(uint*)((char*)pAudio + 0x6b4) >> 2) ||
        (soundId == *(uint*)((char*)pAudio + 0x674) >> 2))
    {
        if (start)
        {
            // Hash: if isSpecial then 0xa96a17c9 else 0xf5cf680f
            this->playSound(((-(uint)isSpecial) & 0xa96a17c9) + 0xf5cf680f);
            return;
        }
        this->playSound(
            ((-(uint)isSpecial) & 0x462665f7) + 0xeac4423f,
            1, 1, 0, 1.0f, 1.0f
        );
    }
    // Group 2: IDs at offsets 0x678, 0x67c, 0x680, 0x684, 0x688 (contiguous array)
    else if ((soundId == *(uint*)((char*)pAudio + 0x678) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x67c) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x680) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x684) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x688) >> 2))
    {
        if (start)
        {
            this->playSound(((-(uint)isSpecial) & 0xda82c77) + 0x7b6c9b97);
            return;
        }
        this->playSound(
            ((-(uint)isSpecial) & 0x64b245c9) + 0xcd26ad67,
            1, 1, 0, 1.0f, 1.0f
        );
        return; // Note: extra return in decompiled for this branch
    }
    // Group 3: IDs at offsets 0x6a0, 0x6a4, 0x6a8, 0x6ac, 0x6b0 (contiguous array)
    else if ((soundId == *(uint*)((char*)pAudio + 0x6a0) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x6a4) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x6a8) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x6ac) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x6b0) >> 2))
    {
        if (start)
        {
            this->playSound(((-(uint)isSpecial) & 0x88d9f149) + 0x4d68d42c);
            return;
        }
        this->playSound(
            ((-(uint)isSpecial) & 0xda82c77) + 0x7c03365c,
            1, 1, 0, 1.0f, 1.0f
        );
        return;
    }
    // Group 4: IDs at offsets 0x670, 0x66c, 0x69c, 0x668, 0x698, 0x664, 0x694, 0x660, 0x690
    else if ((soundId == *(uint*)((char*)pAudio + 0x670) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x66c) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x69c) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x668) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x698) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x664) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x694) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x660) >> 2) ||
             (soundId == *(uint*)((char*)pAudio + 0x690) >> 2))
    {
        if (start)
        {
            this->playSound(((-(uint)isSpecial) & 0x2ab10ef7) + 0x1e6846d8);
            return;
        }
        this->playSound(
            ((-(uint)isSpecial) & 0x92db9549) + 0x10aa9ae0,
            1, 1, 0, 1.0f, 1.0f
        );
        return;
    }
}