// FUNC_NAME: EARSObject::destroy
void EARSObject::destroy(EARSObject *this)
{
  // Guard against null pointer
  if (this != 0) {
    // Retrieve global vtable table pointer (contains function pointers for base operations)
    void **vtableTable = (void **)FUN_009c8f80();
    
    // Call virtual destructor through vtable at offset 4 (scalar deleting destructor pattern)
    // The second parameter (0) indicates the memory should be freed
    (*(void (**)(EARSObject *, int))(*(int *)vtableTable + 4))(this, 0);
  }
}