// FUNC_NAME: AudioDataManager::processAudioData
int AudioDataManager::processAudioData(int *audioData, int *streamInfo, undefined4 *outputBuffer, int flags)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  undefined8 uVar11;
  int sampleCount;
  int local_54 [2];
  int local_4c;
  int local_48;
  int local_44 [2];
  undefined4 local_3c;
  int local_38;
  undefined4 local_34 [3];
  undefined4 *local_28;
  int local_24;
  int local_18;
  undefined4 local_14;
  undefined4 *local_8;
  
  if (*streamInfo == 0) {
    return -3; // Stream not initialized
  }
  iVar5 = checkAudioFormat(); // FUN_00665c30
  if (iVar5 == -1) {
    if (flags == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = initAudioOutput(); // FUN_00665ce0
    }
    if (outputBuffer != (undefined4 *)0x0) {
      outputBuffer[2] = 0;
      *outputBuffer = 0;
      _memset((void *)outputBuffer[3],0,outputBuffer[1] * 4);
    }
    return iVar5;
  }
  iVar5 = checkAudioLock(); // FUN_006678c0
  if (iVar5 != 0) {
    return iVar5;
  }
  local_24 = *audioData + 2; // +0x00 offset
  iVar5 = acquireAudioBuffer(); // FUN_006677b0
  if (iVar5 != 0) goto LAB_00666227;
  iVar5 = acquireAudioBuffer(); // FUN_006677b0
  if (iVar5 == 0) {
    iVar5 = processAudioBlock(); // FUN_006677e0
    if (iVar5 == 0) {
      iVar5 = processAudioBlock(); // FUN_006677e0
      if (iVar5 == 0) {
        iVar3 = audioData[2]; // +0x08 offset
        iVar2 = streamInfo[2]; // +0x08 offset
        local_3c = 0;
        local_4c = 0;
        iVar5 = getSampleRate(); // FUN_00665d40
        if (iVar5 % 0x1c < 0x1b) {
          sampleCount = 0x1b - iVar5 % 0x1c;
          iVar5 = allocateSampleBuffer(sampleCount); // FUN_00668e40
          if ((iVar5 == 0) && (iVar5 = allocateSampleBuffer(sampleCount), iVar5 == 0)) goto LAB_00665ed6;
        }
        else {
          sampleCount = 0;
LAB_00665ed6:
          iVar6 = local_44[0] + -1;
          iVar9 = local_54[0] + -1;
          iVar10 = iVar9 - iVar6;
          iVar5 = allocateChannelBuffer(iVar10); // FUN_006687e0
          if (iVar5 == 0) {
            iVar5 = getNextSample(); // FUN_00665bd0
            while (iVar5 != -1) {
              piVar1 = (int *)(local_18 + iVar10 * 4);
              *piVar1 = *piVar1 + 1;
              iVar5 = processSamplePair(local_54,local_44); // FUN_0066a780
              if (iVar5 != 0) goto LAB_00666203;
              iVar5 = getNextSample(); // FUN_00665bd0
            }
            freeChannelBuffer(iVar10); // FUN_0066a4d0
            for (; local_44[0] <= iVar9; iVar9 = iVar9 + -1) {
              if (iVar9 <= local_54[0]) {
                uVar7 = *(uint *)(local_48 + iVar9 * 4);
                uVar4 = *(uint *)(local_38 + iVar6 * 4);
                if (uVar7 == uVar4) {
                  iVar10 = iVar9 - iVar6;
                  *(undefined4 *)(local_18 + -4 + iVar10 * 4) = 0xfffffff;
                }
                else {
                  uVar11 = __aulldiv(uVar7 << 0x1c | *(uint *)(local_48 + -4 + iVar9 * 4),uVar7 >> 4
                                     ,uVar4,0);
                  uVar7 = (uint)uVar11;
                  if (((int)((ulonglong)uVar11 >> 0x20) != 0) || (0xfffffff < uVar7)) {
                    uVar7 = 0xfffffff;
                  }
                  iVar10 = iVar9 - iVar6;
                  *(uint *)(local_18 + -4 + iVar10 * 4) = uVar7 & 0xfffffff;
                }
                *(uint *)(local_18 + -4 + iVar10 * 4) =
                     *(int *)(local_18 + -4 + iVar10 * 4) + 1U & 0xfffffff;
                do {
                  *(uint *)(local_18 + -4 + iVar10 * 4) =
                       *(int *)(local_18 + -4 + iVar10 * 4) - 1U & 0xfffffff;
                  processAudioFrame(); // FUN_0066baa0
                  if (local_44[0] + -2 < 0) {
                    uVar8 = 0;
                  }
                  else {
                    uVar8 = *(undefined4 *)(local_38 + -4 + iVar6 * 4);
                  }
                  *local_28 = uVar8;
                  local_28[1] = *(undefined4 *)(local_38 + iVar6 * 4);
                  local_34[0] = 2;
                  iVar5 = mixAudioChannels(local_34,*(undefined4 *)(local_18 + -4 + iVar10 * 4),local_34
                                      ); // FUN_00668f50
                  if (iVar5 != 0) goto LAB_00666203;
                  if (iVar9 + -2 < 0) {
                    uVar8 = 0;
                  }
                  else {
                    uVar8 = *(undefined4 *)(local_48 + (iVar9 + -2) * 4);
                  }
                  *local_8 = uVar8;
                  if (iVar9 + -1 < 0) {
                    uVar8 = 0;
                  }
                  else {
                    uVar8 = *(undefined4 *)(local_48 + -4 + iVar9 * 4);
                  }
                  local_8[1] = uVar8;
                  local_8[2] = *(undefined4 *)(local_48 + iVar9 * 4);
                  local_14 = 3;
                  iVar5 = checkAudioFormat(); // FUN_00665c30
                } while (iVar5 == 1);
                iVar5 = mixAudioChannels(local_44,*(undefined4 *)(local_18 + -4 + iVar10 * 4),local_34); // FUN_00668f50
                if ((iVar5 != 0) || (iVar5 = allocateChannelBuffer(iVar10 + -1), iVar5 != 0))
                goto LAB_00666203;
                iVar5 = processSamplePair(local_54,local_34); // FUN_0066a780
                if (iVar5 != 0) goto LAB_00666203;
                if (local_4c == 1) {
                  iVar5 = initAudioOutput(); // FUN_00665ce0
                  if (((iVar5 != 0) || (iVar5 = allocateChannelBuffer(iVar10 + -1), iVar5 != 0)) ||
                     (iVar5 = processAudioStream(local_54), iVar5 != 0)) goto LAB_00666203; // FUN_006657c0
                  *(uint *)(local_18 + -4 + iVar10 * 4) =
                       *(int *)(local_18 + -4 + iVar10 * 4) - 1U & 0xfffffff;
                }
              }
            }
            local_4c = audioData[2]; // +0x08 offset
            if (outputBuffer != (undefined4 *)0x0) {
              copyAudioData(); // FUN_00665b10
              updateAudioState(); // FUN_00666970
              outputBuffer[2] = (uint)(iVar3 != iVar2);
            }
            if (flags != 0) {
              processAudioOutput(local_54,sampleCount,local_54,0); // FUN_00666300
              updateAudioState(); // FUN_00666970
            }
            iVar5 = 0;
          }
        }
LAB_00666203:
        releaseAudioBuffer(); // FUN_00665b40
      }
      releaseAudioBuffer(); // FUN_00665b40
    }
    releaseAudioBuffer(); // FUN_00665b40
  }
  releaseAudioBuffer(); // FUN_00665b40
LAB_00666227:
  releaseAudioBuffer(); // FUN_00665b40
  return iVar5;
}