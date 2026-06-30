// FUNC_NAME: EntityBlender::blendEntities
// This function blends state between two entities (likely an interpolation/blending system)
// Parameters: param_1 = source entity, param_2 = target entity, param_3 = blend flags
// Returns: pointer to blended result entity

int EntityBlender::blendEntities(int sourceEntity, int targetEntity, byte blendFlags)

{
  int resultEntity;
  int entityVar1;
  int entityVar2;
  undefined4 val1;
  undefined4 val2;
  undefined4 val3;
  int loopIndex;
  void *sourceFloatPtr;
  int *sourceIntPtr;
  int *destIntPtr;
  int *tempIntPtr;
  undefined4 *sourceMatrixPtr;
  size_t copySize;
  undefined4 *destMatrixPtr;
  int local48;
  void *sourceVector;
  void *destVector;
  undefined4 *tempVector;
  undefined4 *resultVector;
  void *tempFloat;
  undefined4 *resultMatrix;
  
  // Validate inputs
  if (((sourceEntity == 0) || (targetEntity == 0)) || 
      (resultEntity = FUN_0056fdd0(), resultEntity == 0)) {
    return 0;
  }
  
  // Check for skip flag (0x04)
  if ((blendFlags & 4) != 0) goto LAB_0058595b;
  
  // Calculate minimum component count between source and target
  entityVar1 = *(int *)(*(int *)(sourceEntity + 0x38) + 0xc);  // source +0x38->+0xC = component count
  entityVar2 = *(int *)(*(int *)(targetEntity + 0x38) + 0xc);  // target +0x38->+0xC = component count
  local48 = entityVar1;
  if (entityVar2 <= entityVar1) {
    local48 = entityVar2;
  }
  
  // Sort entities by component count
  FUN_0056f800(targetEntity);
  FUN_0056f800(sourceEntity);
  entityVar2 = targetEntity;
  if (entityVar2 <= entityVar1) {
    entityVar2 = sourceEntity;
  }
  FUN_0056f800(entityVar2);
  
  // Check if this is a standard blend (no skeleton)
  if (*(int *)(resultEntity + 0x3c) == 0) {
    // Standard interpolation blend
    sourceVector = (void *)(*(int *)(sourceEntity + 0x34) + 0x14);  // +0x34->+0x14 = float data
    destVector = (void *)(*(int *)(sourceEntity + 0x38) + 0x10);   // +0x38->+0x10 = matrix data
    tempFloat = (void *)(*(int *)(targetEntity + 0x34) + 0x14);
    tempVector = (undefined4 *)(*(int *)(targetEntity + 0x38) + 0x10);
    resultVector = (void *)(*(int *)(resultEntity + 0x34) + 0x14);
    resultMatrix = (undefined4 *)(*(int *)(resultEntity + 0x38) + 0x10);
    loopIndex = local48;
    
    // Check if interpolation is disabled
    if ((*(char *)(*(int *)(sourceEntity + 0x34) + 0x10) == 0) ||
        (*(char *)(*(int *)(targetEntity + 0x34) + 0x10) == 0)) {
      // Direct copy without interpolation
      for (; resultMatrix = tempVector, 0 < loopIndex; loopIndex = loopIndex + -1) {
        FUN_00585400();  // Single step copy
        destVector = (void *)((int)destVector + 0x20);
        sourceVector = (void *)((int)sourceVector + 1);
        tempFloat = (void *)((int)tempFloat + 1);
        resultVector = (void *)((int)resultVector + 1);
        tempVector = tempVector + 8;
        resultMatrix = resultMatrix + 8;
      }
    }
    else {
      // With interpolation
      resultMatrix = tempVector;
      FUN_0056f620();  // Setup interpolation
      if (0 < local48) {
        sourceVector = (void *)((int)sourceVector + local48);
        resultVector = (void *)((int)resultVector + local48);
        tempFloat = (void *)((int)tempFloat + local48);
        do {
          // Copy 4x4 matrix (8 uint4s) with interpolation
          val1 = tempVector[1];
          val2 = tempVector[2];
          val3 = tempVector[3];
          destVector = (void *)((int)destVector + 0x20);
          *resultMatrix = *tempVector;
          resultMatrix[1] = val1;
          resultMatrix[2] = val2;
          resultMatrix[3] = val3;
          val1 = tempVector[5];
          val2 = tempVector[6];
          val3 = tempVector[7];
          resultMatrix[4] = tempVector[4];
          resultMatrix[5] = val1;
          resultMatrix[6] = val2;
          resultMatrix[7] = val3;
          loopIndex = loopIndex + -1;
          tempVector = tempVector + 8;
          resultMatrix = resultMatrix + 8;
        } while (0 < loopIndex);
      }
    }
    
    // Handle remaining components (from source or target)
    if (local48 < entityVar1) {
      _memcpy(resultVector, sourceVector, entityVar1 - local48);  // Copy remaining floats
      _memcpy(resultMatrix, destVector, (entityVar1 - local48) * 0x20);  // Copy remaining matrices
    }
    else if (local48 < entityVar2) {
      _memcpy(resultVector, tempFloat, entityVar2 - local48);  // Copy remaining floats
      _memcpy(resultMatrix, tempVector, (entityVar2 - local48) * 0x20);  // Copy remaining matrices
    }
  }
  else {
    // Skeletal blend (with bone hierarchy data at +0x3C)
    tempVector = (undefined4 *)(*(int *)(sourceEntity + 0x38) + 0x10);   // Source matrices
    resultVector = (undefined4 *)(*(int *)(sourceEntity + 0x3c) + 0x10); // Source bone data
    sourceVector = (void *)(*(int *)(sourceEntity + 0x34) + 0x14);       // Source floats
    destVector = (void *)(*(int *)(targetEntity + 0x34) + 0x14);         // Target floats
    tempFloat = (undefined4 *)(*(int *)(targetEntity + 0x3c) + 0x10);    // Target bone data
    tempMatrixPtr = (undefined4 *)(*(int *)(targetEntity + 0x38) + 0x10);// Target matrices
    resultVector = (void *)(*(int *)(resultEntity + 0x34) + 0x14);       // Result floats
    resultMatrix = (undefined4 *)(*(int *)(resultEntity + 0x38) + 0x10); // Result matrices
    resultFloat = (undefined4 *)(*(int *)(resultEntity + 0x3c) + 0x10);  // Result bone data
    loopIndex = local48;
    
    // Check if interpolation is disabled for skeletal blend
    if ((*(char *)(*(int *)(sourceEntity + 0x34) + 0x10) == 0) ||
        (*(char *)(*(int *)(targetEntity + 0x34) + 0x10) == 0)) {
      for (; 0 < loopIndex; loopIndex = loopIndex + -1) {
        FUN_00586740(&sourceVector);  // Single step skeletal copy
        tempVector = tempVector + 8;
        sourceVector = (void *)((int)sourceVector + 1);
        destVector = (void *)((int)destVector + 1);
        resultVector = resultVector + 4;
        tempFloat = tempFloat + 4;
        resultFloat = resultFloat + 4;
        tempMatrixPtr = tempMatrixPtr + 8;
        resultVector = (void *)((int)resultVector + 1);
        resultMatrix = resultMatrix + 8;
      }
    }
    else {
      // With interpolation for skeletal blend
      FUN_0056f620();
      if (0 < local48) {
        sourceVector = (void *)((int)sourceVector + local48);
        resultVector = (void *)((int)resultVector + local48);
        destVector = (void *)((int)destVector + local48);
        do {
          // Copy source data with interpolation
          val1 = tempMatrixPtr[1];
          val2 = tempMatrixPtr[2];
          val3 = tempMatrixPtr[3];
          tempVector = tempVector + 8;
          resultVector = resultVector + 4;
          *resultMatrix = *tempMatrixPtr;
          resultMatrix[1] = val1;
          resultMatrix[2] = val2;
          resultMatrix[3] = val3;
          val1 = tempMatrixPtr[5];
          val2 = tempMatrixPtr[6];
          val3 = tempMatrixPtr[7];
          resultMatrix[4] = tempMatrixPtr[4];
          resultMatrix[5] = val1;
          resultMatrix[6] = val2;
          resultMatrix[7] = val3;
          
          // Copy bone hierarchy data
          val1 = tempFloat[1];
          val2 = tempFloat[2];
          val3 = tempFloat[3];
          *resultFloat = *tempFloat;
          resultFloat[1] = val1;
          resultFloat[2] = val2;
          resultFloat[3] = val3;
          
          loopIndex = loopIndex + -1;
          tempFloat = tempFloat + 4;
          resultFloat = resultFloat + 4;
          tempMatrixPtr = tempMatrixPtr + 8;
          resultMatrix = resultMatrix + 8;
        } while (0 < loopIndex);
      }
    }
    
    // Handle remaining components with bone data
    if (local48 < entityVar1) {
      copySize = entityVar1 - local48;
      _memcpy(resultVector, sourceVector, copySize);  // Copy remaining floats
      _memcpy(resultMatrix, tempVector, copySize * 0x20);  // Copy remaining matrices
      tempFloat = resultVector;  // Use source bone data as fallback
    }
    else {
      if (entityVar2 <= local48) goto LAB_0058581c;
      copySize = entityVar2 - local48;
      _memcpy(resultVector, destVector, copySize);  // Copy remaining floats
      _memcpy(resultMatrix, tempMatrixPtr, copySize * 0x20);  // Copy remaining matrices
    }
    _memcpy(resultFloat, tempFloat, copySize * 0x10);  // Copy remaining bone data
  }
  
LAB_0058581c:
  // Handle skin attachment data at +0x44
  if (*(int *)(resultEntity + 0x44) != 0) {
    tempIntPtr = (int *)(*(int *)(sourceEntity + 0x44) + 0x10);   // Source skin data
    sourceIntPtr = (int *)(*(int *)(targetEntity + 0x44) + 0x10);  // Target skin data
    destIntPtr = (int *)(*(int *)(resultEntity + 0x44) + 0x10);    // Result skin data
    loopIndex = local48;
    
    // Process skin attachments with -1 sentinel (means use source data)
    if (3 < local48) {
      entityVar2 = (local48 - 4U >> 2) + 1;
      loopIndex = local48 + entityVar2 * -4;
      do {
        // Process 4 pairs at a time
        if (*sourceIntPtr == -1) {
          *destIntPtr = *tempIntPtr;
          entityVar1 = tempIntPtr[1];
        }
        else {
          *destIntPtr = *sourceIntPtr;
          entityVar1 = sourceIntPtr[1];
        }
        destIntPtr[1] = entityVar1;
        
        if (sourceIntPtr[2] == -1) {
          destIntPtr[2] = tempIntPtr[2];
          entityVar1 = tempIntPtr[3];
        }
        else {
          destIntPtr[2] = sourceIntPtr[2];
          entityVar1 = sourceIntPtr[3];
        }
        destIntPtr[3] = entityVar1;
        
        if (sourceIntPtr[4] == -1) {
          destIntPtr[4] = tempIntPtr[4];
          entityVar1 = tempIntPtr[5];
        }
        else {
          destIntPtr[4] = sourceIntPtr[4];
          entityVar1 = sourceIntPtr[5];
        }
        destIntPtr[5] = entityVar1;
        
        if (sourceIntPtr[6] == -1) {
          destIntPtr[6] = tempIntPtr[6];
          entityVar1 = tempIntPtr[7];
        }
        else {
          destIntPtr[6] = sourceIntPtr[6];
          entityVar1 = sourceIntPtr[7];
        }
        destIntPtr[7] = entityVar1;
        
        tempIntPtr = tempIntPtr + 8;
        sourceIntPtr = sourceIntPtr + 8;
        destIntPtr = destIntPtr + 8;
        entityVar2 = entityVar2 + -1;
      } while (entityVar2 != 0);
    }
    
    for (; 0 < loopIndex; loopIndex = loopIndex + -1) {
      if (*sourceIntPtr == -1) {
        *destIntPtr = *tempIntPtr;
        entityVar2 = tempIntPtr[1];
      }
      else {
        *destIntPtr = *sourceIntPtr;
        entityVar2 = sourceIntPtr[1];
      }
      destIntPtr[1] = entityVar2;
      tempIntPtr = tempIntPtr + 2;
      sourceIntPtr = sourceIntPtr + 2;
      destIntPtr = destIntPtr + 2;
    }
    
    // Copy remaining skin attachment pairs
    if (local48 < entityVar1) {
      entityVar1 = entityVar1 - local48;
      sourceIntPtr = tempIntPtr;
    }
    else {
      if (entityVar2 <= local48) goto LAB_0058595b;
      entityVar1 = entityVar2 - local48;
    }
    _memcpy(destIntPtr, sourceIntPtr, entityVar1 * 8);
  }
  
LAB_0058595b:
  // Handle blend result flags
  if ((blendFlags & 8) != 0) {
    return resultEntity;
  }
  
  bool useSourceBlend = *(char *)(targetEntity + 0x30) != 2;  // +0x30 = blend mode flag
  char sourceBlendMode = *(char *)(sourceEntity + 0x30);
  
  if (sourceBlendMode == 2) {
    // Source is fully blended - use source transformation
    *(char *)(resultEntity + 0x30) = 2;
    if (useSourceBlend) {
      // Copy 8 uint4s (equivalent to transform data at +0x10 to +0x2C)
      val1 = *(undefined4 *)(sourceEntity + 0x14);
      val2 = *(undefined4 *)(sourceEntity + 0x18);
      val3 = *(undefined4 *)(sourceEntity + 0x1c);
      *(undefined4 *)(resultEntity + 0x10) = *(undefined4 *)(sourceEntity + 0x10);
      *(undefined4 *)(resultEntity + 0x14) = val1;
      *(undefined4 *)(resultEntity + 0x18) = val2;
      *(undefined4 *)(resultEntity + 0x1c) = val3;
      val1 = *(undefined4 *)(sourceEntity + 0x24);
      val2 = *(undefined4 *)(sourceEntity + 0x28);
      val3 = *(undefined4 *)(sourceEntity + 0x2c);
      *(undefined4 *)(resultEntity + 0x20) = *(undefined4 *)(sourceEntity + 0x20);
      *(undefined4 *)(resultEntity + 0x24) = val1;
      *(undefined4 *)(resultEntity + 0x28) = val2;
      *(undefined4 *)(resultEntity + 0x2c) = val3;
      return resultEntity;
    }
  }
  else {
    if (useSourceBlend) {
      // Neither is fully blended - reset blend mode
      *(char *)(resultEntity + 0x30) = 0;
      return resultEntity;
    }
    // Target is fully blended
    *(char *)(resultEntity + 0x30) = 2;
  }
  
  // Copy target transformation data
  val1 = *(undefined4 *)(targetEntity + 0x14);
  val2 = *(undefined4 *)(targetEntity + 0x18);
  val3 = *(undefined4 *)(targetEntity + 0x1c);
  *(undefined4 *)(resultEntity + 0x10) = *(undefined4 *)(targetEntity + 0x10);
  *(undefined4 *)(resultEntity + 0x14) = val1;
  *(undefined4 *)(resultEntity + 0x18) = val2;
  *(undefined4 *)(resultEntity + 0x1c) = val3;
  val1 = *(undefined4 *)(targetEntity + 0x24);
  val2 = *(undefined4 *)(targetEntity + 0x28);
  val3 = *(undefined4 *)(targetEntity + 0x2c);
  *(undefined4 *)(resultEntity + 0x20) = *(undefined4 *)(targetEntity + 0x20);
  *(undefined4 *)(resultEntity + 0x24) = val1;
  *(undefined4 *)(resultEntity + 0x28) = val2;
  *(undefined4 *)(resultEntity + 0x2c) = val3;
  
  return resultEntity;
}