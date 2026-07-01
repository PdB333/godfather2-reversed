// FUNC_NAME: Node::reset
void __fastcall Node::reset(Node* this)
{
  this[1].someField = 0; // +0x4 - likely node state or flags
  FUN_009c8f10(this[0].someField); // +0x0 - clear/reset some resource (maybe socket, handle or pointer)
  this[0].someField = 0; // +0x0
  this[2].someField = 0; // +0x8 - third field reset
}