// FUNC_NAME: PhysicsComponent::initFromData
void __fastcall PhysicsComponent::initFromData(PhysicsComponent* this, int* sourcePtr, char* initData)
// Address: 0x005010d0
// This function initializes a PhysicsComponent from a source body and an initData flag.
// param_1 (initData) is a pointer to a struct with a byte at +0x0D controlling initialization.
// sourcePtr (unaff_EDI) is a pointer to a source body (e.g., another rigid body) with velocity at +0x40,0x44,0x48, and flags at +0x18.
// The function sets vtable, copies position, velocity, damping, and resets forces.
{
  FUN_00533cc0(); // likely base class or memory zeroing
  this->vtable = &VTABLE_PHYSICSCOMPONENT; // +0x00
  float thresholdSq = DAT_00e44848; // squared velocity threshold
  float damping = DAT_00e2b1a4; // damping factor

  if (*(char*)(initData + 0x0D) == '\0') // check init flag at offset 0x0D
  {
    this->sourceBody = sourcePtr; // +0x50
    float velX = *(float*)(sourcePtr + 0x40);
    float velY = *(float*)(sourcePtr + 0x44);
    float velZ = *(float*)(sourcePtr + 0x48);

    // If velocity magnitude squared exceeds threshold, compute damping ratio
    if (velX * velX <= thresholdSq)
    {
      this->dampingX = 0.0f;
    }
    else
    {
      this->dampingX = damping / velX;
    }
    if (velY * velY <= thresholdSq)
    {
      this->dampingY = 0.0f;
    }
    else
    {
      this->dampingY = damping / velY;
    }
    if (velZ * velZ <= thresholdSq)
    {
      this->dampingZ = 0.0f;
    }
    else
    {
      this->dampingZ = damping / velZ;
    }

    // Check flag at +0x18 bit 1 (0x02)
    if ((*(char*)(sourcePtr + 0x18) & 2) == 0)
    {
      int* transform = this->transformPtr; // +0x04 (pointer to some transform)
      this->position[0] = *(float*)(transform + 0x60); // +0x30
      this->position[1] = *(float*)(transform + 0x64); // +0x34
      this->position[2] = *(float*)(transform + 0x68); // +0x38
      this->position[3] = *(float*)(transform + 0x6C); // +0x3C
    }
    else
    {
      this->position[0] = 0.0f; // +0x30
      this->position[1] = 0.0f; // +0x34
      this->position[2] = 0.0f; // +0x38
      this->position[3] = damping; // +0x3C (likely w-component or some set to damping)
    }

    // Reset forces and torques
    this->force[0] = 0.0f; // +0x40
    this->force[1] = 0.0f; // +0x44
    this->force[2] = 0.0f; // +0x48
    this->force[3] = 0.0f; // +0x4C (actually set to damping later, but here it's 0? Wait, code sets unaff_ESI[0x10]=0, [0x11]=0, [0x12]=0, [0x15]=0, and [0x13]=fVar5. So [0x13] is at +0x4C set to damping.)
    this->someField[0x15] = 0; // +0x54
    this->someField[0x12] = 0; // +0x48 (force[2] already set)
    this->someField[0x11] = 0; // +0x44 (force[1])
    this->someField[0x10] = 0; // +0x40 (force[0])
    this->someField[0x13] = damping; // +0x4C (fourth force component)
    this->torque[0] = 0.0f; // +0x64
    this->torque[1] = 0.0f; // +0x60 (order? Actually code sets unaff_ESI[0x18]=0 and [0x19]=0, so torque at +0x60 and +0x64)
  }
}