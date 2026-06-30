// FUNC_NAME: PostEffectManager::initializeShaderHandles
// Address: 0x0053d040
// This function initializes a set of post-processing effects and their shader parameter indices.
// It stores 14 effect objects (32 bytes each: 7 parameter indices + effect pointer).
// The first effect pointer is taken from a global, the rest are loaded via getEffect().
// For each effect, it queries parameter handles for common post-processing uniforms.

void __thiscall PostEffectManager::initializeShaderHandles(void)
{
  int effectIndex;
  int* paramIndices;

  // Call base initialization (likely parent class or common init)
  baseInit();

  // Store the global default effect pointer at offset 0x104 (index 0 effect)
  // +0x104 : effect pointer for first effect (array of 14 effects, each 32 bytes)
  effectPointers[0] = g_pDefaultEffect;

  // Load the remaining 13 effect pointers from global resource pointers
  // Offsets: +0x124 (index 1), +0x144 (index 2), ..., +0x2a4 (index 13)
  effectPointers[1] = getEffect(&PTR_DAT_010be140);
  effectPointers[2] = getEffect(&PTR_DAT_010be160);
  effectPointers[3] = getEffect(&PTR_DAT_010be150);
  effectPointers[4] = getEffect(&PTR_DAT_010be0a0);
  effectPointers[5] = getEffect(&PTR_DAT_010be0b0);
  effectPointers[6] = getEffect(&PTR_DAT_010be0c0);
  effectPointers[7] = getEffect(&PTR_DAT_010be0d0);
  effectPointers[8] = getEffect(&PTR_DAT_010be0e0);
  effectPointers[9] = getEffect(&PTR_DAT_010be0f0);
  effectPointers[10] = getEffect(&PTR_DAT_010be100);
  effectPointers[11] = getEffect(&PTR_DAT_010be110);
  effectPointers[12] = getEffect(&PTR_DAT_010be120);
  effectPointers[13] = getEffect(&PTR_DAT_010be130);

  // For each of the 14 effects, look up parameter indices (stored before effect pointer)
  // Each effect block: 7 ints (parameter indices) + 1 pointer (effect) = 32 bytes
  paramIndices = &effectPointers[0]; // Actually point to the start of the block (effect pointer at +0x104)
  effectIndex = 0xe; // 14 effects
  do {
    // Query parameter handles using the effect pointer (*paramIndices)
    // Store at negative offsets from paramIndices (i.e., before the effect pointer)
    // Indices: -7 = kDelta, -6 = screenTexture, -5 = depthTexture, -4 = screenColor, -3 = lodFade, -2 = dofParams, -1 = halfPixelOffset
    paramIndices[-7] = getParameterIndex(*paramIndices, "kDelta");
    paramIndices[-6] = getParameterIndex(*paramIndices, "screen_texture");

    // Fallback: if screen_texture not found, try "bb_texture"
    if (paramIndices[-6] == 0) {
      paramIndices[-6] = getParameterIndex(*paramIndices, "bb_texture");
    }

    paramIndices[-5] = getParameterIndex(*paramIndices, "depth_texture");
    paramIndices[-4] = getParameterIndex(*paramIndices, "screen_color");
    paramIndices[-3] = getParameterIndex(*paramIndices, "lod_fade");
    paramIndices[-2] = getParameterIndex(*paramIndices, "dof_params");
    paramIndices[-1] = getParameterIndex(*paramIndices, "halfPixelOffsetXY");

    // Advance to next effect block (32 bytes = 8 ints)
    paramIndices = paramIndices + 8;
    effectIndex = effectIndex - 1;
  } while (effectIndex != 0);
}