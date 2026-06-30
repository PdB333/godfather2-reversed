// FUNC_NAME: ChaseCamera::updateSmoothPosition

void __thiscall ChaseCamera::updateSmoothPosition(ChaseCamera *this, float *outPos)
{
  float *curPosX;
  float factor;
  float clampedFactor;
  float dx, dy, dz;
  float targetX, targetY, targetZ, curX, curY, curZ;
  float distToTarget;
  float t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;
  float springForceX, springForceY, velX, velY, velZ;
  float blendX, blendY, blendZ;
  float tmp1, tmp2, tmp3;
  int stateFlags;
  int obj1, obj2;
  float elapsed; // from caller, stored at +0x28c
  float dt; // assumed delta time
  // Constants (global floats)
  extern float g_cameraMaxFactor; // _DAT_00d5780c
  extern float g_cameraSpringConstant; // DAT_00e51240
  extern float g_cameraDamping; // DAT_00e51238? Actually not clear
  extern float g_cameraParamA; // DAT_00e5123c
  extern float g_cameraParamB; // DAT_00e51214
  extern float g_cameraParamC; // DAT_00e44598 (distance threshold)
  extern float g_cameraParamD; // DAT_00e51248
  extern float g_cameraParamE; // DAT_00e51244
  extern float g_cameraParamF; // DAT_00e51224
  extern float g_cameraParamG; // DAT_00e51220
  extern float g_cameraParamH; // DAT_00e5121c
  extern float g_cameraParamI; // DAT_00e51218
  extern float g_cameraParamJ; // DAT_00e51234
  extern float g_cameraParamK; // DAT_00e51230
  extern float g_cameraParamL; // DAT_00e5122c
  extern float g_cameraParamM; // DAT_00e51228
  extern float g_cameraParamN; // DAT_00e51240 (reused)

  curPosX = (float *)(this + 0x230); // pointer to current position X
  factor = (float)FUN_006c9b00((float *)(this + 0x23c), curPosX, 0, 0); // distance between target and current
  if (*(float *)(this + 0x28c) <= factor) {
    factor = (float)FUN_006c89b0(*(float *)(this + 0x28c), factor, *(undefined4 *)(this + 0x2b0));
    *(float *)(this + 0x28c) = factor;
  } else {
    *(float *)(this + 0x28c) = factor;
  }
  clampedFactor = *(float *)(this + 0x28c);
  if (g_cameraMaxFactor <= clampedFactor) {
    *(undefined4 *)(this + 0x264) = 0;
    *(undefined8 *)outPos = *(undefined8 *)curPosX;
    outPos[2] = *(float *)(this + 0x238);
    *(undefined4 *)(this + 0x268) = 0;
    return;
  }
  curX = *curPosX;
  targetX = *(float *)(this + 0x23c);
  curY = *(float *)(this + 0x234);
  curZ = *(float *)(this + 0x238);
  targetY = *(float *)(this + 0x240);
  targetZ = *(float *)(this + 0x244);
  dt = g_cameraMaxFactor - clampedFactor;
  if (*(int *)(this + 0xc0) == 0) {
    t0 = 0.0f;
  } else {
    t0 = (float)(*(int *)(this + 0xc0) + -0x48);
  }
  if (*(int *)(this + 200) == 0) {
    obj1 = 0;
  } else {
    obj1 = *(int *)(this + 200) + -0x48;
  }
  if ((t0 == 0.0f) || (obj1 == 0)) {
    *(undefined4 *)(this + 0x264) = 0;
    *(undefined8 *)outPos = *(undefined8 *)curPosX;
    outPos[2] = *(float *)(this + 0x238);
    return;
  }
  obj2 = FUN_00471610(); // get object A
  stateFlags = FUN_00471610(); // get object B
  t1 = *(float *)(stateFlags + 0x30) - *(float *)(obj2 + 0x30);
  t2 = *(float *)(stateFlags + 0x34) - *(float *)(obj2 + 0x34);
  t3 = *(float *)(stateFlags + 0x38) - *(float *)(obj2 + 0x38);
  distToTarget = sqrtf(t3*t3 + t2*t2 + t1*t1);
  obj2 = FUN_00471610(); // get another object
  t1 = *(float *)(obj2 + 0x30) - *curPosX;
  t2 = *(float *)(obj2 + 0x34) - *(float *)(this + 0x234);
  t3 = *(float *)(obj2 + 0x38) - *(float *)(this + 0x238);
  if (g_cameraParamC < distToTarget) {
    clampedFactor = (sqrtf(t3*t3 + t2*t2 + t1*t1) / distToTarget) * dt;
    if (clampedFactor <= 0.0f) {
      clampedFactor = 0.0f;
      goto LAB_006ddc37;
    }
    if (clampedFactor < g_cameraMaxFactor) goto LAB_006ddc37;
  }
  clampedFactor = g_cameraMaxFactor;
LAB_006ddc37:
  clampedFactor = g_cameraMaxFactor - clampedFactor;
  t1 = *(float *)(this + 0x100);
  t2 = *(float *)(this + 0x104);
  t3 = 0.0f;
  t4 = 0.0f;
  char state = FUN_006dd3c0(obj1);
  if (state == 1) {
    t3 = g_cameraParamE;
    t4 = g_cameraParamD;
  }
  // spring calculations
  t5 = (*(float *)(this + 0x2c0) * t4 * dt - *(float *)(this + 0x2c4)) * g_cameraParamN + *(float *)(this + 0x2c4);
  t6 = (*(float *)(this + 0x2c0) * *(float *)(this + 0x104) * t3 * dt - *(float *)(this + 0x2c8)) * g_cameraParamN + *(float *)(this + 0x2c8);
  t7 = *(float *)(this + 0x2b4);
  *(float *)(this + 0x2c8) = t6;
  *(float *)(this + 0x2c4) = t5;
  t8 = *(float *)(this + 0xfc);
  t9 = *(float *)(this + 0x110);
  t10 = (g_cameraParamA * clampedFactor + *(float *)(this + 0x130)) * dt;
  // Here t11 = g_cameraParamB - something? Actually DAT_00e51238 - fVar19.
  t11 = g_cameraParamB - *(float *)(this + 0xf8);
  t12 = 0.0f;
  state = FUN_006dd3c0(obj1);
  float tmpSpring, tmpDamp, tmpX, tmpY, tmpVel;
  if (state == 1) {
    t12 = g_cameraParamF;
    t3 = g_cameraParamG;
    t4 = g_cameraParamH;
    float tmp = g_cameraParamI;
  } else if (state == 3) {
    t12 = g_cameraParamJ;
    t3 = g_cameraParamK;
    t4 = g_cameraParamL;
    float tmp = g_cameraParamM;
  } else {
    float tmp = 0.0f;
  }
  // More complex spring calculations
  tmpSpring = *(float *)(this + 0x2c0);
  tmpDamp = *(float *)(this + 0x2b4);
  tmpX = tmpSpring * *(float *)(this + 0xf8) * t4 * dt * dt;
  tmpY = tmpSpring * t3 * dt * dt;
  tmpVel = ((tmpSpring * g_cameraParamB * t12 * dt * dt - tmpX) * tmpDamp + tmpX - *(float *)(this + 0x2c8)) * g_cameraParamN + *(float *)(this + 0x2c8);
  *(float *)(this + 0x2c8) = tmpVel;
  tmpVel = tmpVel + (t11 * t7 + *(float *)(this + 0xf8)) * dt;
  tmpSpring = ((tmpSpring * t12 * dt * dt - tmpY) * tmpDamp + tmpY - *(float *)(this + 0x2c4)) * g_cameraParamN + *(float *)(this + 0x2c4);
  *(float *)(this + 0x2c4) = tmpSpring;
  tmpSpring = tmpSpring + (t9 * dt - t10) * t7 + t10;
  tmpX = ((g_cameraParamB - *(float *)(this + 0xf4)) * t7 + *(float *)(this + 0xf4)) * dt;
  *(float *)(this + 0x264) = (t8 * dt - tmpX) * *(float *)(this + 0x2cc) + tmpX;
  // Final position
  outPos[0] = *(float *)(this + 0x23c) + (curX - targetX) * clampedFactor;
  outPos[1] = *(float *)(this + 0x240) + ((t5 + t1 * dt) - tmpSpring) * *(float *)(this + 0x2cc) + (curY - targetY) * clampedFactor + tmpSpring;
  outPos[2] = *(float *)(this + 0x244) + (curZ - targetZ) * clampedFactor;
  *(float *)(this + 0x268) = ((t6 + t2 * dt) - tmpVel) * *(float *)(this + 0x2cc) + tmpVel;
  return;
}