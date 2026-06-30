// FUNC_NAME: SoundManager::setSoundVolume
int __fastcall SoundManager::setSoundVolume(uint index, float volume)
{
    // this pointer in ECX, stored in in_EAX by decompiler
    // Offset 0x603c: pointer to array of sound instance structures (0x74 bytes each, 512 max)
    if (*(int *)(this + 0x603c) == 0 || index >= 0x200)
        return 0;

    int *instance = (int *)(index * 0x74 + *(int *)(this + 0x603c));
    if (instance == nullptr || *instance == 0)
        return 0;

    int *linkedObject = (int *)instance[2]; // offset +8: pointer to another object (e.g., sound source)
    instance[0x18] = (int)volume;           // offset +0x60: store volume as int (fixed-point?)
    FUN_005dbc10(index, (double)volume);    // propagate to audio system

    if (linkedObject != nullptr)
    {
        *(float *)(linkedObject + 0x4c / 4) = volume; // offset +0x4c: set float volume on linked object
        return 1;
    }
    return 0;
}