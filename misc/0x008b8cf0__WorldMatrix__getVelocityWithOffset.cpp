// FUNC_NAME: WorldMatrix::getVelocityWithOffset
void getVelocityWithOffset(int obj, float *velocity)
{
  // Stack locals for transformed velocity (pos from offset, quat rotation, etc.)
  // obj likely a physics/transform object with position/rotation data
  // +0x28C: float z velocity component
  // +0x284: vec3 (x,y) velocity components packed as double for alignment?
  // _DAT_00d5780c: probably identity quaternion or zero vector constant
  undefined8 transformedVel;
  float velZ;
  undefined1 local_50[12]; // quaternion or rotation matrix temp
  undefined4 local_44; // quaternion/reference frame
  undefined4 local_34;
  undefined4 local_24;
  undefined4 local_14 = _DAT_00d5780c; // identity quat (w=1?)

  if (obj != 0) {
    // Initialize rotation to identity
    local_44 = 0; // x=0
    local_34 = 0; // y=0
    local_24 = 0; // z=0
    local_14 = _DAT_00d5780c; // w=1 (likely)
    FUN_00470f80(local_50); // Probably returns view/inverse camera rotation
    velZ = *(float *)(obj + 0x28c); // velocity.z
    transformedVel = *(undefined8 *)(obj + 0x284); // velocity.xy
    // Rotate velocity into some other space (camera? local?)
    FUN_006cb9d0(&transformedVel, &transformedVel, local_50);
    // Add transformed velocity to output (camera-relative offset velocity)
    *velocity = *velocity + (float)transformedVel;
    velocity[1] = velocity[1] + transformedVel._4_4_;
    velocity[2] = velocity[2] + velZ;
  }
}