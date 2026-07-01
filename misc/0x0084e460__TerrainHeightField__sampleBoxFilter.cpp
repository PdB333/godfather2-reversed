// FUNC_NAME: TerrainHeightField::sampleBoxFilter
float10 __thiscall TerrainHeightField::sampleBoxFilter(int *this, uint timeThreshold)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float accumulatedHeight;
  int sampleCount;
  int unk1;
  int unk2;
  
  iVar1 = this[3]; // +0x0C: number of samples (height field size)
  accumulatedHeight = 0.0;
  sampleCount = 0;
  if (3 < iVar1) {
    iVar8 = this[1]; // +0x04: start index (row/column offset)
    iVar4 = *this; // +0x00: base pointer to height data array
    iVar5 = this[2]; // +0x08: current index (row/column)
    unk2 = iVar5 + 3; // end of block + 3
    unk1 = iVar5 * 8 + 0x10; // offset into array (stride 8, +0x10 for header)
    iVar5 = (iVar5 - iVar8) + 2; // number of elements to process
    do {
      iVar6 = unk1 + -0x10; // previous element offset
      if (iVar8 <= iVar8 + -2 + iVar5) { // wraparound check
        iVar6 = iVar6 + iVar8 * -8;
      }
      uVar2 = *(uint *)(iVar6 + 4 + iVar4); // time stamp at offset +4
      uVar3 = DAT_01205224 - uVar2; // global time delta
      if (DAT_01205224 < uVar2) {
        uVar3 = uVar3 - 1;
      }
      if (timeThreshold < uVar3) goto LAB_0084e65a; // skip if too old
      iVar7 = unk1 + -8; // next element
      accumulatedHeight = *(float *)(iVar6 + iVar4) + accumulatedHeight; // +0x00: height value
      if (iVar8 <= iVar8 + -1 + iVar5) {
        iVar7 = iVar7 + iVar8 * -8;
      }
      uVar2 = *(uint *)(iVar7 + 4 + iVar4);
      uVar3 = DAT_01205224 - uVar2;
      if (DAT_01205224 < uVar2) {
        uVar3 = uVar3 - 1;
      }
      if (timeThreshold < uVar3) goto LAB_0084e65a;
      accumulatedHeight = *(float *)(iVar7 + iVar4) + accumulatedHeight;
      iVar6 = unk1;
      if (iVar8 <= iVar8 + iVar5) {
        iVar6 = unk1 + iVar8 * -8;
      }
      uVar2 = *(uint *)(iVar6 + 4 + iVar4);
      uVar3 = DAT_01205224 - uVar2;
      if (DAT_01205224 < uVar2) {
        uVar3 = uVar3 - 1;
      }
      if (timeThreshold < uVar3) goto LAB_0084e65a;
      iVar7 = unk1 + 8;
      accumulatedHeight = *(float *)(iVar6 + iVar4) + accumulatedHeight;
      if (iVar8 <= unk2) {
        iVar7 = iVar7 + iVar8 * -8;
      }
      uVar2 = *(uint *)(iVar7 + 4 + iVar4);
      uVar3 = DAT_01205224 - uVar2;
      if (DAT_01205224 < uVar2) {
        uVar3 = uVar3 - 1;
      }
      if (timeThreshold < uVar3) goto LAB_0084e65a;
      unk1 = unk1 + 0x20;
      unk2 = unk2 + 4;
      sampleCount = sampleCount + 4;
      iVar5 = iVar5 + 4;
      accumulatedHeight = *(float *)(iVar7 + iVar4) + accumulatedHeight;
    } while (sampleCount < iVar1 + -3);
  }
  if (sampleCount < iVar1) {
    iVar8 = this[2] + sampleCount; // +0x08: current index + sample count
    iVar4 = iVar8 * 8;
    do {
      iVar5 = iVar4;
      if (this[1] <= iVar8) { // +0x04: wraparound at start index
        iVar5 = iVar4 + this[1] * -8;
      }
      uVar2 = *(uint *)(iVar5 + 4 + *this); // +0x04: time stamp
      uVar3 = DAT_01205224 - uVar2;
      if (DAT_01205224 < uVar2) {
        uVar3 = uVar3 - 1;
      }
      if (timeThreshold < uVar3) break;
      sampleCount = sampleCount + 1;
      accumulatedHeight = *(float *)(iVar5 + *this) + accumulatedHeight; // +0x00: height
      iVar4 = iVar4 + 8;
      iVar8 = iVar8 + 1;
    } while (sampleCount < iVar1);
  }
LAB_0084e65a:
  return (float10)accumulatedHeight;
}