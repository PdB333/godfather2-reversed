// FUNC_NAME: TriggerVolume::testPointWithinDistance
void TriggerVolume::testPointWithinDistance(float *point, float maxDistanceSq)
{
  // Call virtual function at vtable+8 (likely preCheck or beginTest)
  (this->vtable->preCheck)();

  // Check if the volume is active (short at +0x3e)
  if (*(short *)((char *)this + 0x3e) != 0)
  {
    // Call virtual function at vtable+4 (likely isActive or canTrigger)
    if ((this->vtable->isActive)(this))
    {
      // Bounding box stored as 6 floats at +0x48: minX, minY, minZ, maxX, maxY, maxZ
      float *bbox = *(float **)((char *)this + 0x48);
      float dx = 0.0f, dy = 0.0f, dz = 0.0f;

      // Compute squared distance from point to bounding box (closest point on box)
      float px = point[0];
      if (px < bbox[0])
      {
        dx = px - bbox[0];
        dx *= dx;
      }
      else if (px > bbox[3])
      {
        dx = px - bbox[3];
        dx *= dx;
      }
      // else dx stays 0

      float py = point[1];
      if (py < bbox[1])
      {
        dy = py - bbox[1];
        dy *= dy;
      }
      else if (py > bbox[4])
      {
        dy = py - bbox[4];
        dy *= dy;
      }

      float pz = point[2];
      if (pz < bbox[2])
      {
        dz = pz - bbox[2];
        dz *= dz;
      }
      else if (pz > bbox[5])
      {
        dz = pz - bbox[5];
        dz *= dz;
      }

      float distSq = dx + dy + dz;
      if (distSq <= maxDistanceSq)
      {
        // Call the trigger callback (FUN_005fcce0)
        this->onPointWithinDistance();
      }
    }
  }

  // Call virtual function at vtable+0xc (likely postCheck or endTest)
  (this->vtable->postCheck)();

  // Free the point (FUN_006021f0)
  freePoint(point);
}