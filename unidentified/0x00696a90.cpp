// FUN_00696a90: EAContainer::findNode
undefined4 * __thiscall EAContainer::findNode(int this, undefined4 *outIterator, int hintNode, int contextCheck, undefined4 key)
{
  char keyMatches;
  int headValue;
  undefined4 *iteratorPtr;
  int localContainer;
  undefined4 localKey;
  
  if (*(int *)(this + 8) == 0) {
    // Container empty – set iterator to end sentinel
    setIteratorSentinel(outIterator, 1, *(undefined4 *)(this + 4), key);
    return outIterator;
  }
  
  headValue = **(int **)(this + 4);
  
  if ((contextCheck == 0) || (contextCheck != this)) {
    assertionFailed();
  }
  
  if (hintNode == headValue) {
    // Hint node matches the head – validate the hint node's right link?
    if (validateNode(hintNode + 0xc) < 0) {
      setIteratorSentinel(outIterator, 1, hintNode, key);
      return outIterator;
    }
  }
  else {
    int thisField = *(int *)(this + 4);
    if ((contextCheck == 0) || (contextCheck != this)) {
      assertionFailed();
    }
    if (hintNode == thisField) {
      if (validateNode(key) < 0) {
        setIteratorSentinel(outIterator, 0, *(undefined4 *)(*(int *)(this + 4) + 8), key);
        return outIterator;
      }
    }
    else {
      if (validateNode(hintNode + 0xc) < 0) {
        updateContext();
        keyMatches = compareKeys(hintNode + 0xc, key);
        if (keyMatches != '\0') {
          if (*(char *)(*(int *)(hintNode + 8) + 0x29) != '\0') {
            setIteratorSentinel(outIterator, 0, hintNode, key);
            return outIterator;
          }
          setIteratorSentinel(outIterator, 1, hintNode, key);
          return outIterator;
        }
      }
      
      keyMatches = compareKeys(hintNode + 0xc, key);
      if (keyMatches != '\0') {
        localKey = *(undefined4 *)(this + 4);
        localContainer = this;
        prepareSearch();
        if (checkSearchState(&localContainer) == '\0') {
          if (compareKeys(key, hintNode + 0xc) == '\0') goto LAB_00696c60;
        }
        if (*(char *)(*(int *)(hintNode + 8) + 0x29) != '\0') {
          setIteratorSentinel(outIterator, 0, hintNode, key);
          return outIterator;
        }
        setIteratorSentinel(outIterator, 1, hintNode, key);
        return outIterator;
      }
    }
  }
  
LAB_00696c60:
  iteratorPtr = (undefined4 *)getNodeFromKey(&localContainer, key);
  *outIterator = *iteratorPtr;
  outIterator[1] = iteratorPtr[1];
  return outIterator;
}