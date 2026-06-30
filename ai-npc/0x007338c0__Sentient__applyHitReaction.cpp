// FUNC_NAME: Sentient::applyHitReaction
void __thiscall Sentient::applyHitReaction(Entity* attacker, Vector3* impactPoint) {
  // +0x1fb0: hitReactionActive flag
  *(int*)(this + 0x1fb0) = 1;
  // +0x1f58: flags - clear bit 0x400 (bit 10)
  *(uint*)(this + 0x1f58) &= 0xfffffbff;

  // Scale attacker's velocity by damage multiplier from self
  // +0x2c: attacker velocity (or force)
  *(float*)(attacker + 0x2c) *= *(float*)(this + 0x1fa0); // +0x1fa0: damageMultiplier

  float hitReactionTimer = 0.0f;
  // +0x2004: currentAttacker (Entity*)
  if (*(int*)(this + 0x2004) == 0 || *(int*)(this + 0x2004) == 0x48) {
    // No valid attacker or projectile type (0x48)
    *(float*)(this + 0x2060) = 0.0f; // +0x2060: hitReactionTimer
  } else {
    Entity* currentAttacker = *(Entity**)(this + 0x2004);
    // Check if current attacker has a health component with non-positive health
    if (*(float*)(currentAttacker - 0x48 + 0xe0) <= 0.0f) {
      *(float*)(this + 0x2060) = 0.0f;
    } else {
      // Randomize hit reaction duration
      float randomVal = (float)FUN_007234c0(9); // random in [0,1]?
      float baseDuration = DAT_01205228;
      *(float*)(this + 0x2060) = randomVal + baseDuration;
    }
  }

  // Check if no attacker or projectile, then return early
  if (*(int*)(this + 0x2004) == 0 || *(int*)(this + 0x2004) == 0x48) {
    return;
  }

  // Get current time or something
  float timeDelta = (float)FUN_00722820();
  // Extract impact point components from passed vector
  float impactX = (float)FUN_007235f0(impactPoint);
  float impactZ = (float)FUN_00723570(impactPoint);
  // Apply force/pushback based on impact direction
  FUN_00733680(impactZ, impactX, timeDelta);

  // Check bit 11 (0x800) in flags
  if ((*(uint*)(this + 0x1f58) >> 0xb & 1) == 0) {
    return;
  }

  // Check bit 1 in another flags at +0x2188
  if ((*(uint*)(this + 0x2188) >> 1 & 1) != 0) {
    return;
  }

  if (*(int*)(attacker + 0xc) == 0 || *(int*)(attacker + 0xc) == 0x48) {
    return;
  }

  int entityFromId = *(int*)(attacker + 0xc);
  if (entityFromId == 0) {
    entityFromId = 0;
  } else {
    entityFromId -= 0x48;
  }
  // Look up entity by ID with hash (likely player check)
  int result = FUN_006c9470(entityFromId, 0x383225a1);
  if (result == 0) {
    return;
  }

  // Play hit reaction animation/sound
  FUN_00892af0(0); // set mute flag?
  FUN_00892b40(this, 1); // enable hit reaction on self
  int gameContext = FUN_00806440();
  unsigned int soundOrAnimHash;
  switch (gameContext) {
  case 0:
  case 1:
    soundOrAnimHash = 0x3e42c6a3;
    break;
  case 2:
    soundOrAnimHash = 0x52470d60;
    break;
  case 3:
    if (*(int*)(this + 0x1ed4) == 0x637b907) {
      goto switchD_00733a48_default;
    }
    soundOrAnimHash = 0x6ace47af;
    break;
  default:
    goto switchD_00733a48_default;
  }
  char eventBuffer[20]; // for sound event
  FUN_00894c40(soundOrAnimHash, eventBuffer);
switchD_00733a48_default:
  // Enable some flag
  FUN_0072c050(1);
  // Cleanup if necessary
  if (local_8[0] != 0) {
    FUN_004daf90(local_8);
  }
}