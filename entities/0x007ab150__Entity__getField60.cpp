// FUNC_NAME: Entity::getField60
// Returns the pointer stored at offset 0x60 in the entity object.
// This is a fastcall member function (this in ECX).
// Called from many different subsystems, likely a component pointer or state machine.
undefined4 __fastcall Entity::getField60(Entity* this)
{
    return *(undefined4*)((int)this + 0x60);
}