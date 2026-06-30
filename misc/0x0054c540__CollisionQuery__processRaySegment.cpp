// FUNC_NAME: CollisionQuery::processRaySegment

void __thiscall CollisionQuery::processRaySegment(CollisionQuery *this, RaySegmentData *rayData)
{
  // TLS profiling variables (simplified)
  // Use rdtsc for profiling calls

  // Get the last node in the static body list (param_2[9] is head, walk to tail via +0x0C)
  int staticBody = rayData->staticBodies; // param_2[9]
  for (int node = *(int *)(staticBody + 0xC); node != 0; node = *(int *)(node + 0xC))
  {
    staticBody = node;
  }

  // TLS profiling (LtaddCdPoint and StGetMaterial)
  // ... (profile markers omitted for clarity)

  // Check collision with the static body
  int hitNode = FUN_005566a0(staticBody, *(undefined4 *)(rayData->staticBodies + 4));
  if (hitNode != 0)
  {
    // Compute dot product of this->rayDirection (offset 0x1b0,0x1b4,0x1b8) with rayData->direction (components [4],[5],[6])
    float dotResult = this->rayDirectionX * (float)rayData->direction[0] +
                      this->rayDirectionY * (float)rayData->direction[1] +
                      (float)rayData->direction[2] * this->rayDirectionZ;

    // Check if this hit is closer than previous best
    if (this->bestDistance <= dotResult && dotResult != this->bestDistance)
    {
      this->hitNodeIndex = hitNode;
      this->bestDistance = dotResult;

      // Get material ID
      int material = FUN_004afca0(staticBody);
      if (material == 0)
      {
        // Fallback to another material retrieval
        undefined4 *materialPtr = (undefined4 *)FUN_0054c0e0(&localStackVar, staticBody);
        this->hitMaterial = *materialPtr;
      }
      else
      {
        undefined4 *materialPtr = (undefined4 *)FUN_00421430(); // likely get default material
        this->hitMaterial = *materialPtr;
      }
    }
  }

  // TLS profiling (StTouch)
  // ...

  // Now process dynamic bodies (param_2[8] list)
  int bodyType = *(char *)(staticBody + 0x18); // Flag from static body, used below

  char collisionResult = '\0';
  if (*(char *)(staticBody + 0x10) + staticBody != 0) // Check if static body has children
  {
    // Get collision collector from static body (via FUN_004af8c0(0x2001))
    int *collector = 0;
    FUN_004af8c0(&collector, 0x2001); // Some kind of collection query
    if (collector != 0)
      ; // collector assigned

    if (collector != 0)
    {
      // Get last node in dynamic body list
      int dynamicBody = rayData->dynamicBodies; // param_2[8]
      for (int node = *(int *)(dynamicBody + 0xC); node != 0; node = *(int *)(node + 0xC))
      {
        dynamicBody = node;
      }

      int *dynamicCollector = 0;
      if (*(char *)(dynamicBody + 0x10) + dynamicBody != 0) // Check dynamic body children
      {
        FUN_004af8c0(&dynamicCollector, 0x2001);
        if (dynamicCollector == 0)
          dynamicCollector = collector; // fallback to static collector
      }

      // Build collision input structure on stack
      CollisionInput input;
      input.originX = rayData->originX; // param_2[0]
      input.originY = rayData->originY; // param_2[1]
      input.originZ = rayData->originZ; // param_2[2]
      input.originW = rayData->originW; // param_2[3]
      input.directionX = rayData->direction[0]; // param_2[4]
      input.directionY = rayData->direction[1]; // param_2[5]
      input.directionZ = rayData->direction[2]; // param_2[6]
      input.unk7 = rayData->unk7; // param_2[7]
      input.staticBodyTransform = *(undefined4 *)(rayData->staticBodies + 4); // rayData->staticBodies->transform
      input.dynamicBodyTransform = *(undefined4 *)(rayData->dynamicBodies + 4); // rayData->dynamicBodies->transform
      input.dynamicBodyIndex = dynamicBody;
      input.staticBodyIndex = staticBody;

      // Call collision detection on the collector (vtable+200 = testRay)
      collisionResult = (**(code (__thiscall **)(int, int, CollisionInput *))(*(int *)collector + 200))(
                          dynamicCollector, *(char *)(dynamicBody + 0x18), &input);
      if (collisionResult == '\0')
      {
        // Fallback to static collector
        collisionResult = (**(code (__thiscall **)(int, int, CollisionInput *))(*(int *)dynamicCollector + 200))(
                            collector, bodyType, &input);
      }
    }
  }

  // TLS profiling (StaddCdPoint)
  // ...

  if (collisionResult == '\0')
  {
    // No collision found, call default handler
    FUN_00a65150(rayData);
  }

  // TLS profiling end
  // ...
}