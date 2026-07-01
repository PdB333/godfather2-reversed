// FUNC_NAME: Entity::`scalar deleting destructor' (size 0x260)
Entity* __thiscall Entity::`scalar deleting destructor'(Entity* this, byte flag)
{
    // Call the base destructor (FUN_008d9490)
    this->~Entity();

    // If the flag's low bit is set, free the memory (operator delete with size 0x260)
    if (flag & 1)
    {
        // FUN_0043b960: operator delete(this, 0x260)
        operator delete(this, 0x260);
    }

    return this;
}