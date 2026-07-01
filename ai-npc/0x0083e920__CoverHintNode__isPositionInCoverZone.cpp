// FUNC_NAME: CoverHintNode::isPositionInCoverZone
undefined4 __thiscall CoverHintNode::isPositionInCoverZone(int this, float *position)

{
  char cVar1;
  bool bVar2;
  float fVar3;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  undefined1 local_c [12];
  
  // Get cover zone bounds from the node (likely min/max distances, inner/outer radii)
  FUN_0083d270(&local_28,&local_24,&local_20,&local_1c,&local_18,local_c);
  
  // Calculate squared distance from position to cover node's reference point (local_18, local_14, local_10)
  fVar3 = (position[2] - local_10) * (position[2] - local_10) +
          (position[1] - local_14) * (position[1] - local_14) +
          (*position - local_18) * (*position - local_18);
  
  // Check if distance is within the inner radius (local_28) - too close, not in zone
  if (fVar3 < local_28) {
    return 0;
  }
  // Check if distance exceeds the outer radius (local_24) - too far, not in zone
  if (local_24 < fVar3) {
    return 0;
  }
  
  // Check cover node flags at +0xA8 (bit 2: maybe "ignore line of sight" or "always valid")
  if ((*(uint *)(this + 0xa8) >> 2 & 1) == 0) {
    // Perform line-of-sight check from position to cover node
    local_24 = (float)(CONCAT31(local_24._1_3_,(char)(*(uint *)(this + 0xa8) >> 0x12)) &
                      0xffffff01);
    cVar1 = FUN_006c0050(position,1,local_24); // likely line-of-sight test
    if (cVar1 == '\\0') {
      bVar2 = local_20 < fVar3; // check if distance is beyond some threshold
      goto LAB_0083e9ec;
    }
  }
  // If line-of-sight check passed or flag set, use inner threshold (local_1c)
  bVar2 = fVar3 < local_1c;
  local_20 = local_1c;
LAB_0083e9ec:
  // Final validation: must satisfy either the threshold check or exact distance match
  if (!bVar2 && local_20 != fVar3) {
    return 0;
  }
  return 1;
}