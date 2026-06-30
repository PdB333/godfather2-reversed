// FUNC_NAME: TreeNode::evaluateDecision
undefined4 * __thiscall TreeNode::evaluateDecision(int this, undefined4 *outResult, int parentNode, int keyA, undefined4 keyB)
{
  char comparisonResult;
  int hashResult;
  undefined4 *resultPair;
  int nodeStack[2];
  undefined4 local_8;
  
  // If node has no child (flag at +0x8 is zero), return immediate value
  if (*(int *)(this + 8) == 0) {
    // Set result to type 1, use stored data from +0x4
    helperSetResult(outResult, 1, *(undefined4 *)(this + 4), keyB);
    return outResult;
  }
  
  // Retrieve the underlying data pointer (pointer to pointer)
  hashResult = **(int **)(this + 4);
  
  // Safety check: parentNode must be valid and match this node's parent
  if ((parentNode == 0) || (parentNode != this)) {
    assertionCheck(); // FUN_00b97aea
  }
  
  if (keyA == hashResult) {
    // Compare using second part of key (keyA+0xc)
    hashResult = computeHash(keyA + 0xc); // FUN_004d4b20
    if (hashResult < 0) {
      helperSetResult(outResult, 1, keyA, keyB);
      return outResult;
    }
  }
  else {
    hashResult = *(int *)(this + 4);
    if ((parentNode == 0) || (parentNode != this)) {
      assertionCheck();
    }
    if (keyA == hashResult) {
      hashResult = computeHash(keyB); // FUN_004d4b20 on keyB
      if (hashResult < 0) {
        // Use value from child node (offset +0x8 of stored data)
        helperSetResult(outResult, 0, *(undefined4 *)(*(int *)(this + 4) + 8), keyB);
        return outResult;
      }
    }
    else {
      hashResult = computeHash(keyA + 0xc); // FUN_004d4b20
      if (hashResult < 0) {
        helperBeforeComparison(); // FUN_00694060
        comparisonResult = compareKeys(keyA + 0xc, keyB); // FUN_00693990
        if (comparisonResult != 0) {
          // Check a flag in the structure pointed by keyA+8 (offset 0x25)
          if (*(char *)(*(int *)(keyA + 8) + 0x25) != 0) {
            helperSetResult(outResult, 0, keyA, keyB);
            return outResult;
          }
          helperSetResult(outResult, 1, keyA, keyB);
          return outResult;
        }
      }
      
      comparisonResult = compareKeys(keyA + 0xc, keyB);
      if (comparisonResult != 0) {
        local_8 = *(undefined4 *)(this + 4);
        nodeStack[0] = this;
        helperBeforeRecursion(); // FUN_006940f0
        comparisonResult = checkNodeFlag(&nodeStack); // FUN_00693b80
        if (comparisonResult == 0) {
          comparisonResult = compareKeys(keyB, keyA + 0xc);
          if (comparisonResult == 0) goto fallback;
        }
        if (*(char *)(*(int *)(keyA + 8) + 0x25) != 0) {
          helperSetResult(outResult, 0, keyA, keyB);
          return outResult;
        }
        helperSetResult(outResult, 1, keyA, keyB);
        return outResult;
      }
    }
  }
  
fallback:
  // Fallback: retrieve a pair of values from another node
  resultPair = (undefined4 *)fetchNodeResult(&nodeStack, keyB); // FUN_00696630
  *outResult = *resultPair;
  outResult[1] = resultPair[1];
  return outResult;
}