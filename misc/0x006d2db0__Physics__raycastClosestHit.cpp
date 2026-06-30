// FUNC_NAME: Physics::raycastClosestHit
uint Physics::raycastClosestHit(float *rayStart, float *rayEnd, float *outHitFraction)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  char extraout_AL;
  undefined4 uVar10;
  undefined3 uVar13;
  undefined3 extraout_var;
  uint uVar11;
  undefined1 *puVar12;
  int iVar14;
  int iVar15;
  bool bVar16;
  bool bVar17;
  float local_3b8;
  float local_3b4;
  undefined1 *local_380;
  undefined4 local_37c;
  float *local_378;
  undefined4 local_374;
  undefined1 local_370;
  undefined1 local_36f;
  undefined2 local_36e;
  undefined4 local_36c;
  undefined1 local_368;
  char local_367;
  undefined2 local_366;
  undefined4 local_364;
  undefined4 local_338;
  float local_330;
  float local_32c;
  float local_328;
  float local_324;
  float local_320;
  float local_31c;
  undefined **local_310;
  float local_30c;
  float local_2e4;
  int local_2e0;
  float local_2d0 [6];
  undefined4 local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  undefined4 local_2ac;
  float local_2a8;
  undefined4 local_2a4;
  float local_2a0;
  float local_29c;
  float local_298;
  float local_294;
  undefined1 local_220 [32];
  undefined **local_200;
  float local_1fc;
  undefined1 *local_1f0;
  int local_1ec;
  uint local_1e8;
  undefined1 local_1e0 [384];
  undefined1 local_60 [92];
  
  if (outHitFraction != (float *)0x0) {
    *outHitFraction = _DAT_00d5780c; // 1.0f (default no hit)
  }
  fVar1 = *rayStart;
  fVar2 = rayStart[1];
  fVar3 = rayStart[2];
  fVar4 = rayStart[3];
  fVar5 = *rayEnd;
  fVar6 = rayEnd[1];
  fVar7 = rayEnd[2];
  fVar8 = rayEnd[3];
  FUN_00a64b00(_DAT_00e51108); // physicsWorld->beginRaycast
  local_2d0[1] = 0.0;
  local_2d0[2] = 0.0;
  local_2d0[3] = 0.0;
  local_2d0[4] = 0.0;
  local_2b8 = 0;
  local_2b4 = 0;
  local_2b0 = 0;
  local_2ac = 0;
  local_2a4 = 0;
  local_2d0[0] = _DAT_00d5780c; // 1.0f
  local_2d0[5] = _DAT_00d5780c; // 1.0f
  local_2a8 = _DAT_00d5780c; // 1.0f
  local_378 = local_2d0;
  local_380 = local_220;
  local_374 = 0;
  local_37c = 0xffffffff;
  local_370 = 0;
  local_36c = 0;
  local_368 = 0;
  local_364 = 0;
  local_366 = 0;
  local_367 = 0x7f;
  local_2a0 = fVar1;
  local_29c = fVar2;
  local_298 = fVar3;
  local_294 = fVar4;
  FUN_00a64fd0(); // physicsWorld->setupRaycastQuery
  local_338 = DAT_00d5ccf8;
  local_320 = DAT_00e44598;
  local_31c = DAT_00e44598;
  local_367 = (char)&local_380 - (char)&local_36c;
  local_36f = 0;
  local_36e = 0;
  local_310 = &PTR_LAB_00dc471c; // collision filter
  local_2e0 = 0;
  local_2e4 = DAT_00e445dc;
  local_30c = DAT_00e445dc;
  local_330 = fVar5;
  local_32c = fVar6;
  local_328 = fVar7;
  local_324 = fVar8;
  local_364 = FUN_00540c60(0xc,1,0); // allocate memory
  local_2e0 = 0;
  local_2e4 = DAT_00e445dc;
  local_30c = DAT_00e445dc;
  FUN_009e7fd0(&local_380,&local_330,&local_310,&local_310); // perform raycast
  bVar16 = local_2e0 != 0;
  local_3b4 = 0.0;
  if (bVar16) {
    local_3b4 = local_2e4; // hit fraction from first cast
  }
  local_364 = FUN_00540c60(0xc,0x17,0); // allocate memory
  local_2e0 = 0;
  local_2e4 = DAT_00e445dc;
  local_30c = DAT_00e445dc;
  uVar10 = FUN_009e7fd0(&local_380,&local_330,&local_310,&local_310); // perform second raycast
  bVar17 = local_2e0 == 0;
  uVar13 = (undefined3)((uint)uVar10 >> 8);
  local_3b8 = 0.0;
  if (!bVar17) {
    local_3b8 = local_2e4; // hit fraction from second cast
  }
  if ((!bVar16) || ((!bVar17 && (local_3b8 + DAT_00e44598 < local_3b4)))) {
    if (bVar17) goto LAB_006d3318;
  }
  else {
    uVar10 = FUN_006d11c0(local_60,rayStart,5); // compute swept sphere
    FUN_006d12b0(local_60,uVar10,rayEnd); // check swept sphere collision
    uVar13 = extraout_var;
    if (extraout_AL != '\0') goto LAB_006d3318;
    local_3b8 = local_3b4;
  }
  if ((0.0 <= local_3b8) ||
     (SQRT((rayStart[1] - rayEnd[1]) * (rayStart[1] - rayEnd[1]) +
           (rayStart[2] - rayEnd[2]) * (rayStart[2] - rayEnd[2]) +
           (*rayStart - *rayEnd) * (*rayStart - *rayEnd)) * local_3b8 <=
      DAT_00e44564 - _DAT_00e51108)) {
    if (bVar16) {
      local_1f0 = local_1e0;
      local_200 = &PTR_LAB_00e397fc; // collision results
      local_1e8 = 0x80000008;
      local_1ec = 0;
      local_1fc = DAT_00e445dc;
      FUN_009e7fd0(&local_380,&local_330,&local_200,&local_200); // get collision results
      if ((0 < local_1ec) && (FUN_00a65200(), iVar9 = local_1ec, 0 < local_1ec)) {
        iVar14 = 0;
        iVar15 = 0;
        puVar12 = local_1f0;
        do {
          fVar1 = *(float *)(puVar12 + iVar14 + 0x1c); // hit fraction
          if ((local_3b8 < fVar1) &&
             (uVar11 = FUN_005413f0(*(undefined4 *)(*(int *)(puVar12 + iVar14 + 0x28) + 0x1c)), // check collision flags
             puVar12 = local_1f0, (uVar11 & 2) == 0)) {
            if (outHitFraction != (float *)0x0) {
              *outHitFraction = fVar1;
            }
            uVar11 = FUN_00543d10(); // get hit entity
            return uVar11 & 0xffffff00;
          }
          iVar15 = iVar15 + 1;
          iVar14 = iVar14 + 0x30;
        } while (iVar15 < iVar9);
      }
      local_200 = &PTR_LAB_00e397fc;
      if (-1 < (int)local_1e8) {
        uVar11 = local_1e8 & 0x3fffffff;
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(local_1f0,uVar11 * 0x30,0x17); // free memory
      }
    }
    if (outHitFraction != (float *)0x0) {
      *outHitFraction = local_3b8;
    }
    return (uint)outHitFraction & 0xffffff00;
  }
LAB_006d3318:
  return CONCAT31(uVar13,1);
}