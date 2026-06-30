// FUNC_NAME: VFXManager::createEffect
// Address: 0x005929c0
// Role: Creates a visual effect instance (particle/beam) with given flags and transforms.
// Uses EA EARS VFX system, handles scaling, effect type selection based on version field.

int __thiscall VFXManager::createEffect(int this, int effectDef, uint flags)
{
  float scaleFactor;
  int effectObject;
  int versionField;
  bool isEffectDefValid;
  uint bitFlag5;
  float templateValue; // DAT_00e2b1a4 (likely -1.0f or 0.0f)
  // Local arrays for transform data, initialized to zero/template
  int transform1[7]; // +0x00
  int transform2[7]; // +0x1c
  // Actually multiple vector groups, but we'll use named locals
  struct {
    float x, y, z, w;
  } velocityGroup1, velocityGroup2, velocityGroup3, velocityGroup4, velocityGroup5,
    velocityGroup6, velocityGroup7, velocityGroup8;
  // Many more locals...

  // Initialize locals to template constant (likely -1.0f for unused)
  templateValue = DAT_00e2b1a4;
  velocityGroup1.x = templateValue;
  velocityGroup1.y = templateValue;
  velocityGroup1.z = templateValue;
  velocityGroup1.w = templateValue;
  // ... similar for all velocity groups
  
  // Effect type selection based on version field from effect definition
  versionField = *(int *)(effectDef + 4);
  if ((*(uint *)(versionField + 4) & 0xff) < 10) {
    effectObject = *(int *)(versionField + 8);
  } else {
    effectObject = *(int *)(versionField + 0x18);
  }
  // Call to set effect state based on validity
  FUN_00593770(effectDef, effectObject != 0, *(int *)(*(int *)this + 0x10));

  // Initialize transform arrays to zero
  memset(&transform1, 0, sizeof(transform1));
  memset(&transform2, 0, sizeof(transform2));
  // Clear buffer at local_90
  FUN_00593210(&velocityGroup1, 0);

  // Check global flag at this+0x10 bit 0xd
  if ((*(uint *)(*(int *)this + 0x10) >> 0xd & 1) == 0) {
    versionField = *(int *)(effectDef + 4);
    if ((*(uint *)(versionField + 4) & 0xff) < 10) {
      versionField = *(int *)(versionField + 0x10);
    } else {
      versionField = *(int *)(versionField + 0x24);
    }
    if (versionField >= 0) {
      // Get time or some value
      float time = (float)FUN_00593910(effectDef);
      FUN_00593910(time);
      // Check flag bit 5 from input flags
      bitFlag5 = (flags >> 5) & 1;
      if ((bitFlag5 != 0) && (FUN_005934a0(this, &velocityGroup1) == 0)) {
        return 0;
      }
      // Copy transforms from default to local
      if (FUN_005934f0(&velocityGroup5, &velocityGroup2) == 0) return 0;
      if (FUN_005934f0(&velocityGroup7, &transform1) == 0) return 0;
    }
  }

  // Create the actual effect via main factory function
  int effectHandle = FUN_00593cb0(*(int *)this, *(int *)(this + 0x10), &velocityGroup3, flags, &velocityGroup1);
  if (effectHandle == 0) return 0;

  // Post-creation adjustments if global flag not set
  if ((*(uint *)(*(int *)this + 0x10) >> 0xd & 1) == 0) {
    versionField = *(int *)(effectDef + 4);
    if ((*(uint *)(versionField + 4) & 0xff) < 10) {
      versionField = *(int *)(versionField + 0x10);
    } else {
      versionField = *(int *)(versionField + 0x24);
    }
    if (versionField >= 0) {
      // Apply transform effect
      FUN_00586fa0(effectHandle + 0x10, &transform2, bitFlag5);
      *(char *)(effectHandle + 0x30) = 2; // Set some type to 2
      // Scale if global scale factor present
      if ((*(int *)this != 0) && 
          (scaleFactor = *(float *)(*(int *)this + 0x104), scaleFactor != DAT_00e2b1a4)) {
        *(float *)(effectHandle + 0x20) *= scaleFactor;
        *(float *)(effectHandle + 0x24) *= scaleFactor;
        *(float *)(effectHandle + 0x28) *= scaleFactor;
      }
    }
  }
  return effectHandle;
}