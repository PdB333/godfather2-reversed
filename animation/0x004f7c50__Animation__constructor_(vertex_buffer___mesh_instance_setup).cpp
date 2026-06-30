// FUNC_NAME: Animation::constructor (vertex buffer / mesh instance setup)
undefined4 * Animation_constructor(undefined4 *this, int param_2, int param_3) {
  int *piVar1;
  float *pfVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  char cVar6;
  undefined1 *puVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int unaff_FS_OFFSET;
  float fVar11;
  int local_58;
  undefined4 local_54;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 *local_14;

  // Call base class constructor (likely some framework object)
  EARSObject_constructor();
  // Set vtable pointer (PTR_LAB_00e37940 = Animation vtable)
  *this = &Animation_vtable;
  // If param_2 + 0xd indicates something already processed, skip construction
  if (*(char *)(param_2 + 0xd) != '\0') {
    return this;
  }
  // Store reference to the mesh data (param_3)
  this[9] = param_3;
  // Initialize animation-related fields
  this[0x10] = 0;  // +0x40: unknown animation state
  this[0x11] = 0;  // +0x44: unknown animation state
  this[0xe] = 0;   // +0x38: unknown
  this[0xf] = 0;   // +0x3c: unknown
  this[0xd] = 0;   // +0x34: unknown
  this[0xb] = 0;   // +0x2c: unknown
  // Call some initialization functions (likely for vertices/normals)
  VertexBuffer_init();
  VertexBuffer_init();
  VertexBuffer_init();
  // Get current render context from thread-local storage
  iVar10 = **(int **)(unaff_FS_OFFSET + 0x2c);
  // Compute scale factors and call transform function
  // DAT_00e445c8 is likely a world scale factor
  FUN_0056b8a0(*(float *)(param_3 + 0x68) * DAT_00e445c8,
               *(float *)(param_3 + 0x6c) * DAT_00e445c8,
               *(float *)(param_3 + 0x70) * DAT_00e445c8,
               *(int *)(iVar10 + 8) + 0x10 + this[4]);  // +0x10 = vertex buffer offset
  uVar3 = *(uint *)(param_3 + 0x54);  // Flags from mesh data
  this[10] = uVar3;  // +0x28: store flags
  // If flag 2 is not set, directly copy transformation matrix
  if ((uVar3 & 2) == 0) {
    iVar4 = *(int *)(iVar10 + 8);
    iVar9 = this[4];
    *(undefined4 *)(iVar4 + 0x40 + iVar9) = *(undefined4 *)(param_3 + 0x5c);
    iVar9 = iVar4 + 0x40 + iVar9;
    *(undefined4 *)(iVar9 + 4) = *(undefined4 *)(param_3 + 0x60);
    *(undefined4 *)(iVar9 + 8) = *(undefined4 *)(param_3 + 100);
  } else {
    // Otherwise, add to existing transformation (accumulate)
    pfVar2 = (float *)(*(int *)(iVar10 + 8) + 0x40 + this[4]);
    *pfVar2 = *(float *)(param_3 + 0x5c) + *pfVar2;
    pfVar2[1] = *(float *)(param_3 + 0x60) + pfVar2[1];
    pfVar2[2] = *(float *)(param_3 + 100) + pfVar2[2];
  }
  // Call some post-transform function
  FUN_00533fb0();
  // Get a pointer to some transform data (probably a matrix row)
  pfVar2 = (float *)(*(int *)(iVar10 + 8) + 0x80 + this[4]);
  fVar11 = *pfVar2;
  if ((*(byte *)(this + 10) & 6) == 0) {
    fVar11 = *(float *)(param_3 + 100) + pfVar2[2];
  }
  // Check if there are blend weights (param_3 + 0x10..0x1c)
  if ((*(int *)(param_3 + 0x10) != 0 || *(int *)(param_3 + 0x14) != 0) ||
     (*(int *)(param_3 + 0x18) != 0 || *(int *)(param_3 + 0x1c) != 0)) {
    // Allocate a blend data structure (0x14 bytes)
    puVar7 = (undefined1 *)HeapAlloc(0x14);
    if (puVar7 == (undefined1 *)0x0) {
      puVar7 = (undefined1 *)0x0;
    } else {
      *(undefined4 *)(puVar7 + 8) = 0;
      *(undefined4 *)(puVar7 + 0xc) = 0;
      *(undefined4 *)(puVar7 + 0x10) = 0;
      *puVar7 = 0;
      *(undefined4 *)(puVar7 + 4) = 1;
    }
    this[0xd] = puVar7;  // +0x34: store blend data
    if (puVar7 == (undefined1 *)0x0) goto LAB_004f7ffc;
    // Copy blend weights from mesh data
    this[0xe] = *(undefined4 *)(param_3 + 0x10);  // +0x38
    this[0xf] = *(undefined4 *)(param_3 + 0x14);  // +0x3c
    uVar8 = *(undefined4 *)(param_3 + 0x18);
    this[0x11] = this[1];  // +0x44: copy something from +0x04
    this[0x10] = uVar8;    // +0x40
    // Attempt to set up blend data (DAT_01205510 is likely some global blend buffer)
    cVar6 = FUN_004f85a0(DAT_01205510, this[0xd]);
    if (cVar6 == '\0') {
      *(undefined1 *)(param_2 + 0xc) = 1;
      return this;
    }
  }
  uVar8 = FUN_004f7c10();  // Get skeletal animation interface
  iVar9 = this[1];  // +0x04: some object reference
  // Determine local_58 based on some geometry data
  if (*(int *)(iVar9 + 0xc4) == 0) {
    local_58 = 0;
  } else {
    local_58 = *(int *)(iVar9 + 0xc4) + -0x48;
  }
  local_18 = 0xffffffff;  // default value
  local_14 = (undefined4 *)0x0;
  // Handle special flags
  if ((this[10] & 8) == 0) {  // +0x28 flags
    if ((this[10] & 0x10) != 0) {
      local_18 = *(undefined4 *)(iVar9 + 0xb8);
      local_30 = *(undefined4 *)(param_3 + 0x5c);
      local_2c = *(undefined4 *)(param_3 + 0x60);
      local_28 = *(undefined4 *)(param_3 + 100);
      local_24 = DAT_00e2b1a4;  // Some constant
      local_14 = &local_30;
      fVar11 = DAT_00e2b1a4;
    }
  } else {
    local_58 = 0;
  }
  local_54 = 0;
  if ((*(uint *)(iVar9 + 0xc) & 0x400000) != 0) {
    local_54 = 4;
  }
  local_1c = local_58;
  local_20 = 2;  // Some parameter for skeleton binding
  iVar9 = FUN_004f79b0(uVar8, *(undefined4 *)(iVar9 + 0x84), local_54);
  piVar1 = this + 0xb;  // +0x2c
  *piVar1 = iVar9;  // Store skeleton binding result
  if (iVar9 != 0) {
    *(int **)(iVar9 + 8) = piVar1;
    // Initialize animation data
    AnimationData_init();
    *(undefined4 *)(*piVar1 + 0x84) = *(undefined4 *)(this[1] + 0x84);
    if ((this[0xd] == 0) || (*(int *)(this[0xd] + 0x10) == 0)) {
      // No blend data - use default pose
      Skeleton_init_pose(this[1] + 0x20);
    } else {
      // Set up blended animation
      FUN_004ebc00(this[1], 0);
      uVar5 = *(undefined4 *)(this[0xd] + 0xc);  // Blend data
      iVar9 = *(int *)(this[0xd] + 8);            // Blend index
      uVar8 = *(undefined4 *)(param_3 + 0x50);    // Some mesh data
      iVar10 = *(int *)(iVar10 + 8) + iVar9;
      *(float *)(iVar10 + 0x2c) = fVar11;
      *(undefined4 *)(iVar10 + 0x28) = uVar8;
      // Allocate and set up a vertex animator (0x40 bytes)
      iVar10 = FUN_004e0750(0x40);
      if ((iVar10 != 0) && (iVar10 = VertexAnimator_constructor(), iVar10 != 0)) {
        *(int *)(iVar10 + 0x24) = iVar9;
        *(undefined4 *)(iVar10 + 0x28) = uVar5;
        BoneAnimator_init();
        this[0xc] = *(undefined4 *)(param_3 + 0x58);  // +0x30: store some mesh data
        return this;
      }
    }
    this[0xc] = *(undefined4 *)(param_3 + 0x58);  // +0x30
    return this;
  }
LAB_004f7ffc:
  *(undefined1 *)(param_2 + 0xc) = 1;
  return this;
}