// FUNC_NAME: StreamManager::~StreamManager
void StreamManager::__thiscall ~StreamManager(void) {
  LPCRITICAL_SECTION lpCriticalSection;
  int *piVar2;
  int iVar1;
  
  // Set up vtable pointers to this class's vtable (destructor stage 1)
  this->m_vtable = &StreamManager_vtable;
  this->m_secondVtable = &StreamManager_secondVtable;
  
  // Lock the stream access critical section
  lpCriticalSection = &this->m_streamCriticalSection;
  EnterCriticalSection(lpCriticalSection);
  
  // Get the global audio/memory manager and call its shutdown procedure
  piVar2 = GetGlobalAudioManager();
  if (piVar2 != NULL) {
    piVar2 = (int *)(*piVar2->vfptr->GetStreamingObject)(piVar2);
    if (piVar2 != NULL) {
      (*piVar2->vfptr->StopStreaming)();
    }
  }
  
  // If we have an active stream, call its shutdown
  if (this->m_activeStream != NULL) {
    (*(this->m_activeStream)->vfptr->DestroyStream)();
  }
  this->m_activeStream = NULL;
  
  LeaveCriticalSection(lpCriticalSection);
  
  // Release audio debug resources
  ReleaseAudioDebugResources();
  MemoryFree(this->m_streamBuffer); // +0x68
  iVar1 = this->m_audioMemoryRegion1; // +0x54
  if (iVar1 != 0) {
    MemoryFree(*(void **)(iVar1 + 8));
    MemoryFreeBlock(iVar1);
  }
  
  // Release second audio memory region
  ReleaseAudioDebugResources();
  MemoryFree(this->m_streamDecompressionBuffer); // +0x50
  iVar1 = this->m_audioMemoryRegion2; // +0x3C
  if (iVar1 != 0) {
    MemoryFree(*(void **)(iVar1 + 8));
    MemoryFreeBlock(iVar1);
  }
  
  // Delete critical sections
  DeleteCriticalSection(&this->m_packetCriticalSection); // +0x24 (9 dwords)
  DeleteCriticalSection(&this->m_streamCriticalSection); // +0xC (3 dwords)
  
  // Set second vtable to a stub (destructor completed)
  this->m_secondVtable = &StreamManager_FreedSecondVtable;
  
  // Set global active flag to 0 and vtable to purecall
  g_InstanceActive = 0;
  this->m_vtable = &_purecall_vtable;
  
  return;
}