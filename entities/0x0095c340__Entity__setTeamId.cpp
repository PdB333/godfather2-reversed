// FUNC_NAME: Entity::setTeamId
void __thiscall Entity::setTeamId(int this,undefined4 teamId)
{
  // Writes a 32-bit team ID into the entity's team field at offset +0x4d (byte/short?)
  // Uses a memset-like or copy function to set 0x80 bytes? Actually it's FUN_005c4660 which likely
  // copies the teamId parameter into a buffer at this+0x4d with size 0x80 and a flag (0).
  // This appears to store the team ID into an array or structure member.
  FUN_005c4660(teamId,this + 0x4d,0x80,0);
  return;
}