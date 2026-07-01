// FUNC_NAME: UIElement::addChild
void __thiscall UIElement::addChild(UIElement* this, UIElementNode* parentNodeRef)
{
  int* pChildListHead;
  char isValidChar;
  int* pNewNode;
  int newNodeBase;
  
  // Clear and set flags at +0x5C (bit 17 clear, bit 18 set, bit 16 clear)
  *(uint*)(this + 0x5C) &= 0xFFFDFFFF; // clear 0x20000
  *(uint*)(this + 0x5C) |= 0x40000;    // set 0x40000
  *(uint*)(this + 0x5C) &= 0xFFFEFFFF; // clear 0x10000

  // Retrieve the child list head pointer (pointer-to-pointer) stored at +0x9C
  pChildListHead = (int*)(this + 0x9C);

  // Obtain the embedded node from the parent reference.
  // parentNodeRef+4 holds a pointer to a UIElement; the node is at that element + 0x48.
  if (*(int*)(parentNodeRef + 4) == 0) {
    newNodeBase = 0;
  } else {
    newNodeBase = *(int*)(parentNodeRef + 4) + 0x48;
  }

  // Insert the new node into the child list head.
  // The list uses a pointer-to-pointer scheme for O(1) removal.
  if (*pChildListHead != newNodeBase) {
    if (*pChildListHead != 0) {
      unlinkChildNode((int*)pChildListHead); // FUN_004daf90
    }
    *pChildListHead = newNodeBase;
    if (newNodeBase != 0) {
      // Save previous head pointer at +0xA0, then set node->next to point to the head pointer itself.
      *(int*)(this + 0xA0) = *(int*)(newNodeBase + 4);
      *(int**)(newNodeBase + 4) = pChildListHead;
    }
  }

  // Update internal state (likely recalculates layout or flags)
  updateInternal(this); // FUN_00731e90

  // Obtain the child object base from the new node (node - 0x48)
  if (*pChildListHead == 0) {
    pNewNode = (int*)0x0;
  } else {
    pNewNode = (int*)(*pChildListHead - 0x48);
  }

  // Call virtual function at vtable+0x1DC with argument at +0xD0 (e.g., render context)
  (*(code**)(*pNewNode + 0x1DC))(*(undefined4*)(this + 0xD0));

  // Call virtual function at vtable+0x1C with argument at +0x50 (e.g., transform data)
  if (*pChildListHead == 0) {
    pNewNode = (int*)0x0;
  } else {
    pNewNode = (int*)(*pChildListHead - 0x48);
  }
  (*(code**)(*pNewNode + 0x1C))(this + 0x50);

  // Get the UI manager singleton and call its virtual at vtable+0x1C with the child object
  // FUN_0043b870 returns a manager from a global pointer (DAT_01131010)
  pNewNode = (int*)getUIManager(DAT_01131010); // FUN_0043b870
  if (*pChildListHead == 0) {
    newNodeBase = 0;
  } else {
    newNodeBase = *pChildListHead - 0x48;
  }
  (*(code**)(*pNewNode + 0x1C))(newNodeBase);

  // Handle an additional visual property at +0xA4 (e.g., color or intensity)
  if ((*(int*)(this + 0xA4) != 0) && (*(int*)(this + 0xA4) != 0x48)) {
    newNodeBase = *(int*)(this + 0xA4);
    if ((newNodeBase == 0) || (newNodeBase == 0x48)) {
      newNodeBase = 0;
    } else {
      newNodeBase = newNodeBase - 0xC;
    }
    setWidgetColorIntensity(parentNodeRef, newNodeBase, 0); // FUN_00408bf0
  }

  // Global UI update (e.g., event dispatch)
  updateGlobalUI(); // FUN_00790a50

  // Special handling for a specific widget type identified by magic number 0x637B907 at offset +0xC8
  if ((*(int*)(this + 200) == 0x637B907) &&
      (newNodeBase = getWidgetAnimationIndex(this), newNodeBase != -1) && // FUN_0090b0a0
      (isValidChar = isAnimationValid(newNodeBase), isValidChar != '\0')) // FUN_009bca20
  {
    if (*pChildListHead != 0) {
      applyAnimationToWidget(newNodeBase, *pChildListHead - 0x48); // FUN_009bf2f0
      return;
    }
    applyAnimationToWidget(newNodeBase, 0); // FUN_009bf2f0
  }
}