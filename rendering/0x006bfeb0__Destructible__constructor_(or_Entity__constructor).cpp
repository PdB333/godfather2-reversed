// FUNC_NAME: Destructible::constructor (or Entity::constructor)
undefined4 __fastcall Destructible::constructor(uint this)
{
  undefined4 *allocator;
  undefined4 result;
  undefined4 success;
  undefined4 local_10; // alignment struct
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  allocator = (undefined4 *)MemoryManager::getInstance(); // FUN_009c8f80
  local_10 = 2;       // allocation type
  local_c = 0x10;     // alignment
  local_8 = 0;        // flags
  local_4 = 0;
  
  // Allocate 0x280 bytes (640 bytes) for the destructible object
  success = (**(code **)*allocator)(0x280, &local_10);
  if (success == 0) {
    result = 0;
  } else {
    // Call actual constructor on the allocated memory using passed this pointer
    result = Destructible::init(this); // FUN_006bfbd0
  }
  
  // Check state field at +0x90: 0 = idle? 0x48 = playing destruction?
  if (*(int *)(this + 0x90) == 0 || *(int *)(this + 0x90) == 0x48) {
    // Get audio controller from this+0x58 and play destruction sound (hash 0x38523fc3)
    AudioController *audioCtrl = AudioController::getInstance(this + 0x58); // FUN_00445ff0
    AudioController::playSound(audioCtrl, 0x38523fc3, &local_10); // FUN_004480d0
  }
  
  // Initialize sub-object at +0x68 (e.g., physics or child entity)
  SubObject::constructor(this + 0x68); // FUN_006bfa70
  
  return result;
}