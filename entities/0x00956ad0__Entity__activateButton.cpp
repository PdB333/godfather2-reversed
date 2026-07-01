// FUNC_NAME: Entity::activateButton
void __fastcall Entity::activateButton(int this)
{
  undefined2 local_4;
  undefined2 uStack_2;
  
  *(undefined1 *)(this + 0x7c) = 0; // +0x7c: m_activateButtonState
  _local_4 = CONCAT22((short)((uint)this >> 0x10),0x30); // Build entity ID (type 0x30 = Entity)
  FUN_005a04a0("ActivateButton",0,&DAT_00d8c174,1,&local_4); // Trigger button activation event
  return;
}