// FUNC_NAME: StreamManager::setOption
void __thiscall StreamManager::setOption(int this, int optionId, uint value)
{
  LPCRITICAL_SECTION criticalSection;
  uint alignedSize;
  uint minSize;
  
  switch(optionId) {
  case 1: // Initialize/Shutdown stream manager
    if (value == 0) {
      // Shutdown: delete critical section
      criticalSection = *(LPCRITICAL_SECTION *)(this + 0x4e8);
      if (criticalSection != (LPCRITICAL_SECTION)0x0) {
        EnterCriticalSection(criticalSection);
        // Decrement reference count (stored in DebugInfo field)
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
        criticalSection = *(LPCRITICAL_SECTION *)(this + 0x4e8);
        *(undefined4 *)(this + 0x4e8) = 0;
        FUN_00643ee0(); // StreamManager::shutdown
        DeleteCriticalSection(criticalSection);
        return;
      }
    }
    else if (*(int *)(this + 0x4e8) == 0) {
      // Initialize: create critical section
      *(undefined4 *)(this + 0x4e8) = FUN_00643e90(); // CreateCriticalSection
      return;
    }
    break;
  case 2: // No-op
    break;
  case 3: // Set streaming enabled flag
    *(bool *)(this + 0x46d) = value != 0;
    return;
  case 4: // Set buffer size (alignment)
    if (value != 0) {
      minSize = *(uint *)(this + 0x4d4); // +0x4D4: minimum buffer size
      if (value <= minSize) {
        value = minSize;
      }
      // Align to next multiple of minSize
      *(uint *)(this + 0x4dc) = (value - 1) + minSize & ~(minSize - 1); // +0x4DC: buffer size
      return;
    }
    *(undefined4 *)(this + 0x4dc) = 0x1000000; // Default 16MB buffer
    return;
  case 5: // Set max buffer size
    if (value == 0) {
      *(undefined4 *)(this + 0x4e0) = 0x400000; // Default 4MB max
      return;
    }
    minSize = *(uint *)(this + 0x4d4); // +0x4D4: minimum buffer size
    if (value <= minSize) {
      value = minSize;
    }
    alignedSize = (value - 1) + minSize & ~(minSize - 1);
    *(uint *)(this + 0x4e0) = alignedSize; // +0x4E0: max buffer size
    // Clamp to buffer size
    if (*(uint *)(this + 0x4dc) < alignedSize) {
      *(uint *)(this + 0x4e0) = *(uint *)(this + 0x4dc);
      return;
    }
    break;
  case 6: // Flush/reset stream
    criticalSection = *(LPCRITICAL_SECTION *)(this + 0x4e8);
    if (criticalSection != (LPCRITICAL_SECTION)0x0) {
      EnterCriticalSection(criticalSection);
      criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }
    FUN_00647b20(this); // StreamManager::flush
    if (value == 0) {
      *(uint *)(this + 4) = *(uint *)(this + 4) & 1; // Clear flags except bit 0
    }
    else {
      FUN_00643e00(); // StreamManager::reset
    }
    if (criticalSection != (LPCRITICAL_SECTION)0x0) {
      criticalSection[1].DebugInfo =
           (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
      LeaveCriticalSection(criticalSection);
      return;
    }
    break;
  case 7: // Set stream priority
    *(uint *)(this + 0x4c8) = value; // +0x4C8: priority
    return;
  case 8: // Set stream type
    *(uint *)(this + 0x4cc) = value; // +0x4CC: stream type
    return;
  case 9: // Set something (likely read ahead size)
    *(uint *)(this + 0x494) = value; // +0x494: read ahead size
    return;
  case 10: // Set something (likely prefetch size)
    *(uint *)(this + 0x490) = value; // +0x490: prefetch size
    return;
  case 0xb: // Set async flag
    *(bool *)(this + 0x498) = value != 0; // +0x498: async flag
    return;
  case 0xc: // Set something (likely streaming flag)
    *(bool *)(this + 0x4e4) = value != 0; // +0x4E4: streaming flag
    return;
  case 0xd: // Set something (likely buffer count)
    *(uint *)(this + 0x4b4) = value; // +0x4B4: buffer count
    return;
  case 0xe: // Set something (likely enable flag)
    *(bool *)(this + 0x46e) = value != 0; // +0x46E: enable flag
    break;
  default:
    goto switchD_006444d4_default;
  }
switchD_006444d4_default:
  return;
}