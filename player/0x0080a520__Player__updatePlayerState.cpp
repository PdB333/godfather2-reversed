// FUNC_NAME: Player::updatePlayerState

void __thiscall Player::updatePlayerState(int *this, undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  char cVar7;
  int iStack_364;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_348;
  undefined4 local_344;
  undefined4 local_340;
  undefined4 local_33c;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined4 local_32c;
  undefined4 local_328;
  undefined4 local_324;
  undefined1 *local_318;
  undefined4 local_314;
  undefined4 *local_310;
  undefined4 local_30c;
  undefined1 local_308;
  undefined1 local_307;
  undefined2 local_306;
  undefined4 local_304;
  undefined1 local_300;
  char local_2ff;
  undefined2 local_2fe;
  undefined4 local_2fc;
  undefined4 local_2d0;
  undefined1 local_2c4 [20];
  undefined4 local_2b0;
  undefined4 local_2ac;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  undefined4 local_29c;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined1 local_1fc [12];
  undefined1 local_1f0 [56];
  undefined **ppuStack_1b8;
  undefined **local_1b0;
  undefined4 local_1ac;
  undefined4 uStack_1a8;
  undefined1 *local_1a0;
  int local_19c;
  undefined4 local_198;
  undefined1 local_190 [396];
  
  // Initialize some state from param_2
  FUN_007f4210(&local_358, &local_34c, local_1fc, param_2);
  
  // Check bit 0 of byte at this+0x8e3 (some flag)
  bVar6 = *(byte *)((int)this + 0x8e3) & 1;
  
  // Setup color/lighting values
  local_330 = local_358;
  local_32c = local_354;
  local_340 = local_34c;
  local_328 = local_350;
  local_33c = local_348;
  local_324 = _DAT_00d5780c;
  local_338 = local_344;
  local_334 = _DAT_00d5780c;
  local_35c = _DAT_00d5cf70;
  if (bVar6 != 0) {
    local_35c = DAT_00d5ef90;
  }
  FUN_00a65bb0(&local_330, &local_340, local_35c);
  
  // Initialize some structure for rendering/UI
  local_310 = &local_2b0;
  local_318 = local_1f0;
  local_2ac = 0;
  local_2a8 = 0;
  local_2a4 = 0;
  local_2a0 = 0;
  local_298 = 0;
  local_294 = 0;
  local_290 = 0;
  local_28c = 0;
  local_284 = 0;
  local_2b0 = _DAT_00d5780c;
  local_29c = _DAT_00d5780c;
  local_288 = _DAT_00d5780c;
  local_274 = 0;
  local_278 = 0;
  local_27c = 0;
  local_280 = 0;
  local_30c = 0;
  local_314 = 0xffffffff;
  local_308 = 0;
  local_304 = 0;
  local_300 = 0;
  local_2fc = 0;
  local_2fe = 0;
  local_2ff = 0x7f;
  FUN_00a64fd0();
  local_2ff = (char)&local_318 - (char)&local_304;
  local_2d0 = DAT_00d5ccf8;
  local_307 = 0;
  local_306 = 0;
  uVar2 = 0x230;
  if (bVar6 == 0) {
    uVar2 = 0x40232;
  }
  FUN_00540bc0(uVar2, this[0x20c], 0, 0);
  local_2fc = FUN_00540cc0(local_2c4);
  
  // Setup some rendering/UI callback
  local_1a0 = local_190;
  local_1b0 = &PTR_LAB_00e397fc;
  local_198 = 0x80000008;
  local_19c = 0;
  local_1ac = DAT_00e445dc;
  FUN_009eb730(&local_318, *(undefined4 *)(*(int *)(DAT_01223480 + 0x24) + 0x6c), &local_1b0);
  
  // Loop to clear some data
  iVar5 = 0;
  if (3 < local_19c) {
    iVar4 = (local_19c - 4U >> 2) + 1;
    iVar5 = iVar4 * 4;
    do {
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (iVar5 < local_19c) {
    iVar5 = local_19c - iVar5;
    do {
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  
  // Check some game state via vtable call
  local_35c = 0;
  cVar1 = (**(code **)(*this + 0x10))(0x383225a1, &local_35c);
  cVar7 = (char)((uint)unaff_EBX >> 0x18);
  if ((cVar1 == '\0') || (iStack_364 == 0)) {
    if (cVar7 == '\0') {
      if (((uint)this[0x23a] >> 1 & 1) != 0) {
        (**(code **)(this[0x16] + 0x28))(0x20);
      }
      this[0x23a] = this[0x23a] & 0xfffffffd;
    }
    else {
      if (((uint)this[0x23a] >> 1 & 1) == 0) {
        (**(code **)(this[0x16] + 0x28))(0x20);
      }
      this[0x23a] = this[0x23a] | 2;
    }
  }
  else if (cVar7 == '\0') {
    if ((*(float *)(iStack_364 + 0x2714) <= 0.0) && ((*(uint *)(iStack_364 + 0x24a0) >> 3 & 1) != 0)) {
      FUN_007f6420(0x41);
    }
  }
  else {
    if (((uint)this[0x23a] >> 1 & 1) == 0) {
      (**(code **)(this[0x16] + 0x28))(0x20);
    }
    this[0x23a] = this[0x23a] | 2;
    *(undefined4 *)(iStack_364 + 0x2714) = *(undefined4 *)(iStack_364 + 0x26f4);
    *(uint *)(iStack_364 + 0x24a0) = *(uint *)(iStack_364 + 0x24a0) & 0xfffffff7;
  }
  
  // Cleanup
  ppuStack_1b8 = &PTR_LAB_00e397fc;
  if (-1 < (int)local_1a0) {
    uVar3 = (uint)local_1a0 & 0x3fffffff;
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(uStack_1a8, uVar3 * 0x30, 0x17);
  }
  return;
}