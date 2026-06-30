// FUNC_NAME: InputDeviceManager::initialize
// Function address: 0x00610c40
// Initializes the input device manager: allocates a memory pool for controller data (0x44 bytes per slot)
// and a separate control block for the manager state.

void InputDeviceManager::initialize(void)
{
  // Allocate a large block for controller slot data (0x44000 bytes = 0x44 * 0x1000 = 4096 slots?),
  // using a function pointer from the engine's memory manager.
  // local_c, local_8, local_4 are likely out parameters for heap handle/statistics.
  int local_c = 0;
  int local_8 = 0;
  int local_4 = 0;
  void* pool = (**(code **)*DAT_01205868)(0x44000, &local_c);
  DAT_012058e4 = pool;  // Global pointer to the raw memory pool

  // Allocate a manager control block (0x4024 bytes) from a different allocator.
  // This block contains an array region and a tail field.
  void* manager = (void *)FUN_009c8e50(0x4024);
  if (manager != (void *)0x0) {
    // Set field at offset 0x4000 (likely a count or flag) to 0.
    *(int *)((int)manager + 0x4000) = 0;
    // Zero the first 0x4000 bytes (the main array/state region).
    _memset(manager, 0, 0x4000);
    // Initialize the large pool: base, total size, element size (0x44), and alignment (4).
    // This may set up a fixed-size allocator for controller data.
    FUN_004abe90(DAT_012058e4, 0x44000, 0x44, 4);
    DAT_012058e0 = manager;  // Store manager pointer globally
    return;
  }
  DAT_012058e0 = (void *)0x0;
  return;
}