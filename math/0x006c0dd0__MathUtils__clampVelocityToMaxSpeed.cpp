// FUNC_NAME: MathUtils::clampVelocityToMaxSpeed
void __thiscall clampVelocityToMaxSpeed(float *velocity, int param2, int *param3)
{
  float fVar1;
  float fVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *unaff_retaddr;
  float fStack_10;
  undefined1 local_c [4];
  float fStack_8;
  
  // Call virtual function at vtable offset 0x4c on param3 (likely a physics object)
  (**(code **)(*param3 + 0x4c))(local_c);
  
  // Compute horizontal speed (sqrt of x^2 + y^2)
  fVar6 = SQRT(fStack_8 * fStack_8 + fStack_10 * fStack_10);
  
  // If speed is below a threshold, just copy velocity as-is
  if (fVar6 <= DAT_00e50de4) {
    *(undefined8 *)unaff_retaddr = *(undefined8 *)velocity;
    unaff_retaddr[2] = velocity[2];
    return;
  }
  
 