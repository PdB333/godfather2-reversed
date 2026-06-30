// FUNC_ADDR: 0x004958a0 - Simple accessor returning field at offset +0x4, likely object type ID or next pointer in linked list.
// This function is used by multiple networking and game object management functions.
uint32_t __fastcall EARSBaseObject::getObjectTypeId(void* this) {
    // Return the 32-bit value stored at offset 4 from the object base.
    return *reinterpret_cast<uint32_t*>(static_cast<char*>(this) + 0x4);
}