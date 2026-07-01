// FUNC_NAME: Player::clearCinematicOverride
void __fastcall Player::clearCinematicOverride(Player* this)
{
  if ((*(uint32_t*)((uint8_t*)this + 0x1D0) >> 3 & 1) != 0) {
    int* manager = (int*)FUN_007ab160();
    (**(void (__thiscall**)(int))(*manager + 4))(8);
    (**(void (__thiscall**)(int))(*manager + 4))(2);
    (**(void (__thiscall**)(int))(*manager + 4))(0x20);
    *(uint32_t*)((uint8_t*)this + 0x1D0) &= 0xFFFFFFF7;
  }
}