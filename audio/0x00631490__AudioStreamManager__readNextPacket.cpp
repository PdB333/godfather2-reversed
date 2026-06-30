// FUNC_NAME: AudioStreamManager::readNextPacket
undefined4 AudioStreamManager::readNextPacket(int this)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  float10 fVar4;
  float local_4c;
  int local_48 [17];
  
  piVar3 = *(int **)(this + 0xc);  // +0xC: read pointer (current position in buffer)
  if (*(int **)(this + 8) <= piVar3) goto LAB_0063154b;  // +0x8: end pointer
  if (piVar3 == (int *)0x0) goto LAB_0063154b;
  if (*piVar3 != 3) {  // packet type 3 = audio data
    if (*piVar3 != 4) goto LAB_0063154b;  // packet type 4 = silence/empty
    iVar2 = FUN_00636850();  // check if audio system is active
    if (iVar2 == 0) goto LAB_0063154b;
    local_48[0] = 3;  // convert silence to audio data request
    piVar3 = local_48;
  }
  local_4c = (float)piVar3[1];  // sample value / frequency
  if (local_4c == DAT_00e2b05c) {  // special sentinel value (likely -1.0f or NaN)
    while (((piVar3 = *(int **)(this + 0xc), *(int **)(this + 8) <= piVar3 ||
            (piVar3 == (int *)0x0)) ||
           ((*piVar3 != 3 && ((*piVar3 != 4 || (iVar2 = FUN_00636850(), iVar2 == 0))))))) {
      FUN_00627ac0();  // wait/sleep for next packet
LAB_0063154b:
      local_4c = 0.0;  // default silence
    }
  }
  fVar4 = (float10)FUN_00b9cce0((double)local_4c);  // convert sample to float (likely PCM conversion)
  puVar1 = *(undefined4 **)(this + 8);  // write pointer
  puVar1[1] = (float)fVar4;  // store converted sample
  *puVar1 = 3;  // mark as audio data packet
  *(int *)(this + 8) = *(int *)(this + 8) + 8;  // advance write pointer by 8 bytes
  return 1;
}