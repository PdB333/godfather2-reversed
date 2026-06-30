// FUNC_NAME: AudioDataManager::constructor

undefined4 * __thiscall AudioDataManager::constructor(AudioDataManager *this, byte allocFlag)
{
  // Set vtable pointers for multiple inheritance
  this->vtable1 = &_vtable_AudioDataManager_main;      // +0x00
  *(int *)((int)&this->vtable2) = &_vtable_AudioDataManager_iface1;  // +0x3c
  *(int *)((int)&this->vtable3) = &_vtable_AudioDataManager_iface2;  // +0x48

  // Register this instance with the engine (e.g., singleton registration)
  registerManagerClass((int)&gAudioDataManagerClassDesc);

  // Construct sub-object at offset 0x70 (e.g., internal list/reference)
  SUB_OBJECT_CONSTRUCTOR(&this->subObject);  // +0x70

  // If there's a previously stored pointer, release it via function pointer
  if (this->pPrevious != nullptr) {          // +0x60
    (this->releaseCallback)(this->pPrevious); // +0x6c is callback function ptr
  }

  // Increment global instance counter (e.g., g_audioDataManagerCount)
  incrementGlobalManagerCount();

  // If memory was allocated on heap, delete this object with known size
  if (allocFlag & 1) {
    operatorDelete(this, 0x8c);
  }

  return this;
}