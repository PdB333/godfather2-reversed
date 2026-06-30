// FUNC_NAME: CameraController::adjustCameraAngle
undefined4 CameraController::adjustCameraAngle(int param_1)

{
  float *in_EAX;
  float *unaff_ESI;
  float in_XMM0_Da;
  float fVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  
  fVar2 = DAT_00e2cd54; // some global camera constant
  if (param_1 == 1) {
    *unaff_ESI = 0.0;
    if (fVar2 < in_XMM0_Da) {
      fVar1 = DAT_00e44564 - *in_EAX * (DAT_00e2b1a4 / in_XMM0_Da);
      fVar4 = in_EAX[2] * (DAT_00e2b1a4 / in_XMM0_Da);
      fVar2 = DAT_00e2eff4;
      if ((DAT_00e2eff4 < fVar1) && (fVar2 = fVar1, DAT_00e2b1a4 <= fVar1)) {
        fVar2 = DAT_00e2b1a4;
      }
      if ((fVar4 <= DAT_00e2eff4) || ((fVar4 < DAT_00e2b1a4 && (fVar4 <= 0.0)))) {
        dVar3 = (double)fVar2;
        FUN_00b9c766(); // likely a math helper or clamp function
        *unaff_ESI = DAT_00e2afac - (float)dVar3;
        return 1;
      }
      dVar3 = (double)fVar2;
      FUN_00b9c766();
      fVar2 = (float)dVar3;
      *unaff_ESI = fVar2;
      if (fVar2 < 0.0) {
        *unaff_ESI = fVar2 + DAT_00e2a848;
        return 1;
      }
    }
  }
  else {
    *unaff_ESI = 0.0;
  }
  return 1;
}