// Xbox PDB: EARS::Audio::SoundProviderRWAC2::Play2
// FUNC_NAME: AudioManager::playSound
int __thiscall AudioManager::playSound(int *thisPtr, int soundIndex, char *soundName, int startTimeMs, int audioDataHandle)
{
  int *destString;
  int *slotPtr;
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  int *piVar8;
  undefined1 *puVar9;
  double *pdVar10;
  int *local_2c;         // stack storage
  int local_28;          // stack storage
  undefined1 local_24[4];
  undefined1 local_20[4];
  double local_1c[2];

  // Get pointer to sound slot array? (offset 0x206f + soundIndex*4)
  slotPtr = thisPtr + soundIndex * 4 + 0x206f;

  // Call vtable function at +0xa0 (likely stop previous sound on this virtual channel)
  (**(code **)(*thisPtr + 0xa0))(soundIndex);

  // If the main audio manager is active (thisPtr[0x160] != 0) and the slot is not already used (value != 10)
  if ((thisPtr[0x160] != 0) && (*slotPtr != 10)) {
    iVar6 = thisPtr[0x241c];           // current slot index in pool (0-9)
    iVar5 = 0;
    do {
      // Check if this slot is free (marked with -1 at offset 0x20ab)
      if (thisPtr[iVar6 * 0x5c + 0x20ab] == -1) {
        // Free slot found; prepare to fill it
        destString = thisPtr + iVar6 * 0x5c + 0x2084;   // pointer to string buffer (128 bytes)
        thisPtr[0x241c] = (iVar6 + 1) % 10;               // move to next slot (circular)
        bVar1 = *(byte *)(thisPtr + iVar6 * 0x5c + 0x20d0); // read flags byte
        LOCK();                                          // enter critical section
        (*local_2c)++;                                    // increment global lock counter (stack hack)
        UNLOCK();
        // Assign a unique ID for this sound instance
        iVar5 = thisPtr[0x241d];
        thisPtr[0x241d] = iVar5 + 1;
        thisPtr[iVar6 * 0x5c + 0x20ac] = iVar5;           // store unique ID in slot
        thisPtr[iVar6 * 0x5c + 0x20ab] = soundIndex;      // store the virtual channel index
        _strncpy((char *)destString, soundName, 0x80);     // copy name (max 128 bytes)
        // Set default volumes (0x1000 = 1.0 in fixed point?)
        thisPtr[iVar6 * 0x5c + 0x20a6] = 0x1000;
        thisPtr[iVar6 * 0x5c + 0x20a7] = 0x1000;
        // Clear flag bit 0
        thisPtr[iVar6 * 0x5c + 0x20d0] = thisPtr[iVar6 * 0x5c + 0x20d0] & 0xfffffffe;
        // Set configuration bytes
        *(undefined1 *)(thisPtr + iVar6 * 0x5c + 0x20c3) = 3;
        *(undefined1 *)((int)thisPtr + iVar6 * 0x170 + 0x830d) = 0;  // another array? (size 0x170)
        *(undefined1 *)((int)thisPtr + iVar6 * 0x170 + 0x830e) = 0;
        *(undefined1 *)((int)thisPtr + iVar6 * 0x170 + 0x830f) = 0;
        thisPtr[iVar6 * 0x5c + 0x20c4] = 0;                // pan? start
        thisPtr[iVar6 * 0x5c + 0x20c5] = 0x20;             // pan? end
        thisPtr[iVar6 * 0x5c + 0x20c6] = 0;                // something else
        // Clear two 16-bit pairs (offset 0x20c7 and 0x20c9)
        *(undefined4 *)(thisPtr + iVar6 * 0x5c + 0x20c7) = 0;
        *(undefined4 *)(thisPtr + iVar6 * 0x5c + 0x20c9) = 0;
        // Handle start time: if negative, use a default global constant
        if (startTimeMs < 0) {
          *(undefined8 *)(thisPtr + iVar6 * 0x5c + 0x20a4) = DAT_00e2af58; // default double
        }
        // Store audioDataHandle on stack for later use
        local_2c[1] = audioDataHandle;
        local_28 = 0;

        // Determine audio bus based on audioDataHandle
        iVar2 = getAudioDataFromHandle(audioDataHandle);   // FUN_005dc670
        iVar3 = local_28;
        if (iVar2 != 0) {
          iVar3 = *(int *)(iVar2 + 0x2b8);               // some type field
        }
        if (iVar3 == thisPtr[100]) {                      // compare to known type
          iVar3 = soundIndex * 0x30 + 0x1a4;              // offset for this type
LAB_005f40c5:
          local_2c[2] = iVar3 + (int)thisPtr;
        }
        else if (iVar3 == thisPtr[0xa5]) {
          local_2c[2] = (int)(thisPtr + soundIndex * 0xc + 0xaa);
        }
        else {
          if (iVar3 != thisPtr[0x116]) {
            iVar3 = soundIndex * 0x30 + 0xa0;
            goto LAB_005f40c5;
          }
          local_2c[2] = (int)(thisPtr + soundIndex * 0xc + 0x11b);
        }
        iVar3 = local_2c[2];
        if (iVar3 == 0) {
          return iVar5;                                   // return unique ID even without bus
        }
        // If the bus has no existing handle (offset +4 == 0), set up without routing
        if (*(int *)(iVar3 + 4) == 0) {
          if (*(int *)(iVar3 + 0x18) != 0) {
            *(undefined4 *)(iVar3 + 0x18) = 0;            // clear something
          }
          if (startTimeMs >= 0) goto LAB_005f42e6;
          audioBegin();                                    // FUN_00c9eac0
          local_1c[0] = *(double *)(thisPtr[0x160] + 8);  // some audio master time?
          audioEnd();                                      // FUN_00c9eae0
        }
        else {
          // Bus already has a handle; set up auxiliary sends
          iVar2 = allocateAudioHandle();                   // FUN_005e9d10
          if (iVar2 != 0) {
            thisPtr[iVar6 * 0x5c + 0x20de] = iVar2;       // store handle
          }
          audioBegin();
          iVar2 = allocateAudioHandle();
          if (iVar2 != 0) {
            setVolume(0, 1.0f);                            // FUN_00ca4e90
          }
          iVar2 = allocateAudioHandle();
          if (iVar2 != 0) {
            setVolume(0, 1.0f);
          }
          iVar2 = allocateAudioHandle();
          if (iVar2 != 0) {
            setVolume(0, *DAT_00e4459c);                   // some float constant
          }
          // Set up auxiliary sends 1,2,3 and master send
          piVar8 = &local_28;
          uVar4 = findAudioBusByName("AuxSend1", piVar8); // FUN_004dafd0
          iVar2 = getAudioBusFromHandle(uVar4, piVar8);   // FUN_005e9d90
          if (iVar2 != 0) {
            setVolume(0, 0.0f);
          }
          puVar9 = local_24;
          uVar4 = findAudioBusByName("AuxSend2", puVar9);
          iVar2 = getAudioBusFromHandle(uVar4, puVar9);
          if (iVar2 != 0) {
            setVolume(0, 0.0f);
          }
          puVar9 = local_20;
          uVar4 = findAudioBusByName("AuxSend3", puVar9);
          iVar2 = getAudioBusFromHandle(uVar4, puVar9);
          if (iVar2 != 0) {
            setVolume(0, 0.0f);
          }
          pdVar10 = local_1c;
          uVar4 = findAudioBusByName("SendToMaster", pdVar10);
          iVar2 = getAudioBusFromHandle(uVar4, pdVar10);
          if (iVar2 != 0) {
            setVolume(0, 0.0f);
          }
          iVar2 = allocateAudioHandle();
          if (iVar2 != 0) {
            setVolume(0, 0.0f);
            setVolume(1, 0.0f);
            setVolume(2, 1.0f);
            setVolume(3, 0.0f);
            setVolume(4, 1.0f);
          }
          local_1c[0] = *(double *)(slotPtr[0x160] + 8);  // potentially bug: should be thisPtr?
          audioEnd();
          setupAudioRouting(slotPtr, local_2c[1], iVar3); // FUN_005ebfa0
        }
        if (startTimeMs >= 0) {
          // Set start time: convert ms to seconds and add to current audio time
          *(double *)(thisPtr + iVar6 * 0x5c + 0x20a4) =
               (double)startTimeMs * DAT_00e446c8 + local_1c[0];
        }
LAB_005f42e6:
        // If flag bit 0 was not set, trigger some global event
        if ((bVar1 & 1) == 0) {
          triggerGlobalEvent(&DAT_00e2aea0);               // FUN_00ac2870
        }
        thisPtr[iVar6 * 0x5c + 0x20ad] = 1;               // mark as active? (offset +0x20ad)
        // Set a callback on completion (function FUN_005f37f0)
        setCallback(destString, 0, onSoundFinished, destString, 0); // FUN_00ac41a0
        return iVar5;                                      // return unique ID
      }
      iVar6 = (iVar6 + 1) % 10;                           // circular search
      iVar5 = iVar5 + 1;
    } while (iVar5 < 10);
  }
  return -1;                                               // no free slot or audio inactive
}