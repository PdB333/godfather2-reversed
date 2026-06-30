// FUNC_NAME: AudioDataManager::~AudioDataManager
void __fastcall AudioDataManager::~AudioDataManager(void)
{
  // Set vtable to base class vtable (EARS::Framework::Object)
  *(uint32_t *)this = (uint32_t)&PTR_FUN_00d5ea9c;
  // Set alternative interface vtables
  *(uint32_t *)((uint32_t)this + 0x3C) = (uint32_t)&PTR_LAB_00d5ea8c;
  *(uint32_t *)((uint32_t)this + 0x48) = (uint32_t)&PTR_LAB_00d5ea88;
  *(uint32_t *)((uint32_t)this + 0x50) = (uint32_t)&PTR_LAB_00d5ea70;

  // If child component exists, release it (offset +0xD0 is the child flag/pointer)
  if (*(uint32_t *)((uint32_t)this + 0xD0) != 0) {
    releaseChildComponent((undefined4 *)((uint32_t)this + 0x50));
    *(uint32_t *)((uint32_t)this + 0xD0) = 0;
  }

  // Release audio handles at offsets +0x70 and +0x78
  releaseAudioHandle((undefined4 *)((uint32_t)this + 0x70));
  releaseAudioHandle((undefined4 *)((uint32_t)this + 0x78));
  // Release global static audio resources
  releaseAudioHandle(&DAT_0112a6ac);
  releaseAudioHandle(&DAT_0120e93c);

  // Release stream references at offsets +0x70, +0x78, +0x80 (different function)
  releaseStreamRef((undefined4 *)((uint32_t)this + 0x70));
  releaseStreamRef((undefined4 *)((uint32_t)this + 0x78));
  releaseStreamRef((undefined4 *)((uint32_t)this + 0x80));

  // Final shutdown of audio subsystem
  shutdownAudioSystem();
}