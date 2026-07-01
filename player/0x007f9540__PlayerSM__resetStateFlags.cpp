// FUNC_NAME: PlayerSM::resetStateFlags
void __fastcall PlayerSM::resetStateFlags(int thisPtr)
{
  *(undefined4 *)(thisPtr + 0x86c) = 0; // +0x86c: stateFlag1
  *(undefined4 *)(thisPtr + 0x868) = 0; // +0x868: stateFlag0
  *(undefined4 *)(thisPtr + 0x874) = 0; // +0x874: stateFlag3
  *(undefined4 *)(thisPtr + 0x870) = 0; // +0x870: stateFlag2
  *(undefined4 *)(thisPtr + 0x87c) = 0; // +0x87c: stateFlag5
  *(undefined4 *)(thisPtr + 0x878) = 0; // +0x878: stateFlag4
  *(undefined4 *)(thisPtr + 0x884) = 0; // +0x884: stateFlag7
  *(undefined4 *)(thisPtr + 0x880) = 0; // +0x880: stateFlag6
  *(undefined4 *)(thisPtr + 0x88c) = 0; // +0x88c: stateFlag9
  *(undefined4 *)(thisPtr + 0x888) = 0; // +0x888: stateFlag8
  *(undefined4 *)(thisPtr + 0x890) = 0; // +0x890: stateFlag10
  return;
}