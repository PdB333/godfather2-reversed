// FUNC_NAME: EARSGameObject::EARSGameObject

undefined4 * __thiscall EARSGameObject::EARSGameObject(undefined4 *this, undefined4 *sourceData)
{
  float *pfVar1;
  float *pfVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 *puVar13;
  int *piVar14;
  undefined4 *puVar15;
  int iVar16;
  int unaff_FS_OFFSET;
  double dVar17;
  undefined1 local_18[20];

  // Initialize base fields
  this[1] = 0;                                  // +0x04
  this[2] = &PTR_LAB_00e32854;                  // +0x08, secondary vtable?
  this[3] = 0;                                  // +0x0C
  this[4] = 0;                                  // +0x10
  *this = &PTR_FUN_00e3566c;                    // +0x00, primary vtable
  this[2] = &PTR_LAB_00e35670;                  // +0x08, update vtable
  this[6] = 0;                                  // +0x18, instance index/offset
  this[7] = 0;                                  // +0x1C

  // Allocate data block via engine allocator
  puVar13 = (undefined4 *)FUN_004ab6d0(local_18);
  this[6] = *puVar13;                           // +0x18, offset into buffer
  this[7] = puVar13[1];                         // +0x1C, size?

  // Magic/sentinel values for debugging
  puVar13 = this + 9;                           // +0x24
  *puVar13 = 0xbadbadba;
  this[10] = 0xbeefbeef;                        // +0x28
  this[11] = 0xeac15a55;                        // +0x2C
  this[12] = 0x91100911;                        // +0x30

  // Clear flag bit 0x40 (maybe "alive" flag)
  *(byte *)(this + 0xe) = *(byte *)(this + 0xe) & 0xbf; // +0x38 byte flags

  if (this[6] == 0) {
    // Allocation failed
    *(byte *)(this + 0xe) = *(byte *)(this + 0xe) | 0x40; // set failure flag
    return this;
  }

  // Clear bits 0x40 and 0x80, keep others? Actually clear 0xc2 = 11000010
  *(byte *)(this + 0xe) = *(byte *)(this + 0xe) & 0xc2;

  iVar16 = DAT_01206880;                        // Global object manager pointer
  // Push this onto a global stack/list (custom allocator)
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_0112449c; // push marker
  *(int *)(iVar16 + 0x14) = *(int *)(iVar16 + 0x14) + 4; // increment stack pointer
  piVar14 = (int *)(iVar16 + 0x14);
  puVar15 = (undefined4 *)(*(int *)(iVar16 + 0x14) + 3U & 0xfffffffc); // align
  *piVar14 = (int)puVar15;
  *puVar15 = this;
  *piVar14 = *piVar14 + 4;

  // Get thread-local storage context (FS segment)
  iVar16 = **(int **)(unaff_FS_OFFSET + 0x2c); // TEB + 0x2c -> some thread local data
  puVar15 = (undefined4 *)(*(int *)(iVar16 + 8) + this[6]); // base + offset

  // Copy source data into allocated buffer (128 bytes? 4 sets of 4 ints)
  uVar9 = sourceData[5];
  uVar10 = sourceData[6];
  uVar11 = sourceData[7];
  *puVar15 = sourceData[4];
  puVar15[1] = uVar9;
  puVar15[2] = uVar10;
  puVar15[3] = uVar11;

  uVar9 = sourceData[9];
  uVar10 = sourceData[10];
  uVar11 = sourceData[11];
  puVar15[4] = sourceData[8];
  puVar15[5] = uVar9;
  puVar15[6] = uVar10;
  puVar15[7] = uVar11;

  uVar9 = sourceData[13];
  uVar10 = sourceData[14];
  uVar11 = sourceData[15];
  puVar15[8] = sourceData[12];
  puVar15[9] = uVar9;
  puVar15[10] = uVar10;
  puVar15[11] = uVar11;

  uVar9 = sourceData[0x11];
  uVar10 = sourceData[0x12];
  uVar11 = sourceData[0x13];
  puVar15[12] = sourceData[0x10];
  puVar15[13] = uVar9;
  puVar15[14] = uVar10;
  puVar15[15] = uVar11;

  // Copy source flags byte
  this[8] = (uint)*(byte *)(sourceData + 0x15); // +0x20, flags from source

  // Copy source header (first 4 ints) into this
  *puVar13 = *sourceData;                        // this[9] = sourceData[0]
  this[10] = sourceData[1];                      // this[10] = sourceData[1]
  this[11] = sourceData[2];                      // this[11] = sourceData[2]
  this[12] = sourceData[3];                      // this[12] = sourceData[3]

  // Set pointer to either internal copy or external pointer
  if (sourceData[0x14] == 0) {
    this[13] = puVar13;                          // +0x34, point to internal copy
  } else {
    this[13] = sourceData[0x14];                 // external pointer
  }

  // Set various fields in the allocated buffer (using offset this[6])
  *(uint *)(*(int *)(iVar16 + 8) + 0x7c + this[6]) = (uint)*(ushort *)((int)sourceData + 0x56);
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x90 + this[6]) = sourceData[0x19];
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x60 + this[6]) = sourceData[0x19];
  *(undefined4 *)(*(int *)(iVar16 + 8) + 100 + this[6]) = sourceData[0x18];
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x70 + this[6]) = sourceData[0x1b];
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x6c + this[6]) = sourceData[0x1c];
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x78 + this[6]) = sourceData[0x1d];

  // Convert and set a float value
  dVar17 = (double)(float)sourceData[0x1e];
  FUN_00b99e20(); // Unknown, maybe convert or store
  *(float *)(*(int *)(iVar16 + 8) + 0x74 + this[6]) = (float)dVar17;

  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x68 + this[6]) = sourceData[0x1a];
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x8c + this[6]) = sourceData[0x1f];
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x98 + this[6]) = sourceData[0x20];

  // Scale color/lighting values
  bVar3 = *(byte *)((int)sourceData + 0x5f);
  bVar4 = *(byte *)((int)sourceData + 0x5e);
  pfVar1 = (float *)(*(int *)(iVar16 + 8) + 0x50 + this[6]);
  bVar5 = *(byte *)(sourceData + 0x17);
  pfVar1[1] = (float)*(byte *)((int)sourceData + 0x5d);
  fVar12 = DAT_00e44640;                         // Global scale factor
  pfVar1[2] = (float)bVar4;
  pfVar1[3] = (float)bVar3;
  *pfVar1 = (float)bVar5;

  // Multiply all four floats by the global scale
  pfVar1 = (float *)(*(int *)(iVar16 + 8) + 0x50 + this[6]);
  fVar6 = pfVar1[1];
  fVar7 = pfVar1[2];
  fVar8 = pfVar1[3];
  pfVar2 = (float *)(*(int *)(iVar16 + 8) + 0x50 + this[6]);
  *pfVar2 = fVar12 * *pfVar1;
  pfVar2[1] = fVar12 * fVar6;
  pfVar2[2] = fVar12 * fVar7;
  pfVar2[3] = fVar12 * fVar8;

  FUN_004aa8f0();                                // Post-initialization (physics/spawn?)
  this[5] = 1;                                   // +0x14, mark as active

  // Clear additional fields in allocated buffer
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x94 + this[6]) = 0;
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x84 + this[6]) = 0;
  *(undefined4 *)(*(int *)(iVar16 + 8) + 0x88 + this[6]) = 0;

  // Check flag bit 0x20 in allocated data
  if ((*(byte *)(*(int *)(iVar16 + 8) + 0x7c + this[6]) & 0x20) != 0) {
    // Push another marker onto global stack
    piVar14 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011244d8;
    *piVar14 = *piVar14 + 4;
    puVar13 = (undefined4 *)(*piVar14 + 3U & 0xfffffffc);
    *piVar14 = (int)puVar13;
    *puVar13 = this;
    *piVar14 = *piVar14 + 4;
  }

  iVar16 = sourceData[0x16];
  if (sourceData[0x16] == 0) {
    iVar16 = DAT_0110ac04;                       // Default value
  }
  FUN_004aa7b0(iVar16);                          // Finalize/setup with id

  return this;
}