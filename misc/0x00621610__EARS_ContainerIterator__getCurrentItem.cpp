// FUNC_NAME: EARS_ContainerIterator::getCurrentItem
undefined4 FUN_00621610(void)

{
  int iVar1;
  int in_EAX;
  int local_10;
  int local_c;
  
  // Save the this pointer and container pointer? 
  FUN_00621d50(&stack0x00000004);
  // Get the current version/sequence number from the container (+0x1c)
  iVar1 = *(int *)(*(int *)(in_EAX + 0xc) + 0x1c);
  // Verify the iterator (+0x10) is valid and matches the container (+0xc)
  if ((local_10 == 0) || (local_10 != *(int *)(in_EAX + 0xc))) {
    FUN_00b97aea(); // Assert/validation failure
  }
  // If the saved version (+0x1c) doesn't match the current version
  if (local_c != iVar1) {
    // Re-validate before accessing
    if (local_10 == 0) {
      FUN_00b97aea(); // Assert
    }
    // Check if the saved version matches the container's version 
    if (local_c == *(int *)(local_10 + 0x1c)) {
      FUN_00b97aea(); // Assert
    }
    // Return the item at the current iterator position (+0x10)
    return *(undefined4 *)(local_c + 0x10);
  }
  // If versions match, iterator has reached end
  return 0;
}