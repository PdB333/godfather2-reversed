// FUNC_NAME: VehicleMemoryPool::deallocate
void __fastcall VehicleMemoryPool::deallocate(int this) {
  // Call destructor-like functions for embedded sub-objects
  // These are likely for memory pool chunks (e.g., two fixed-size allocations)
  FUN_004df600();  // Likely sub-object 1 destructor
  FUN_004df600();  // Likely sub-object 2 destructor

  // If there's a dynamic allocation at +0x26c, free it
  if (*(int *)(this + 0x26c) != 0) {
    FUN_004daf90((undefined4 *)(this + 0x26c));  // Free the allocation
    *(undefined4 *)(this + 0x26c) = 0;
  }
}