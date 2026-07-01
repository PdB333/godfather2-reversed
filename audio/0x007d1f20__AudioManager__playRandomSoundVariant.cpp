// FUNC_NAME: AudioManager::playRandomSoundVariant
void __thiscall AudioManager::playRandomSoundVariant(void* thisPtr, int soundId)
{
    float variantScale;        // local_8
    float randomVal;            // fVar1
    float scaledFactor;         // fVar2
    uint8_t tempBuffer[4];      // local_10
    uint8_t randomOutput[4];    // local_c

    // Get a random value from a table at global offset 0x2494 based on this->variantIndex (offset 0x58)
    // Writes two floats/bytes into randomOutput (first 4 bytes) and variantScale (next 4 bytes?)
    getRandomVariantPair(randomOutput, *(uint32_t*)((uint8_t*)DAT_00002494 + *(int*)((uint8_t*)thisPtr + 0x58)));

    // Scale the variant by global volume multiplier
    scaledFactor = variantScale * DAT_00e44748;  // DAT_00e44748 = gVolumeScale

    // Generate a random number [0,1)
    randomVal = randomFloat0(0, 0);  // FUN_0079eb40

    // Compare with a probability threshold stored at global +0x1694
    if ((float)*(float*)((uint8_t*)DAT_01223464 + 0x1694) < randomVal) {
        // Generate another random and blend with the scaled variant
        randomVal = randomFloat1(0, 0);  // FUN_0079eb90
        randomVal = clampToRange(randomVal * DAT_00e44748 + scaledFactor);  // FUN_006d6350
        // Play the sound with computed volume, system handle, sound ID, and output buffer
        playSoundInternal(randomVal, DAT_00e53034, soundId, tempBuffer, 0);  // FUN_007992a0
    }
}