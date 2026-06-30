// FUNC_NAME: EngineObjectContainer::releaseChildren
// This function appears to release two child objects paired with two parent-style objects.
// Structure offsets:
//   +0x00: parent1 (pointer to an object with vtable)
//   +0x04: firstChild (pointer to a child object, may be released by parent1)
//   +0x08: parent2 (pointer to another object with vtable)
//   +0x0C: secondChild (pointer to a child object, released by parent2)
void EngineObjectContainer::releaseChildren()
{
    // Release second child using parent2
    if (this->secondChild != 0)
    {
        // Call virtual function at vtable+0x04 (likely Release) on parent2
        // Second argument 0 may indicate "no additional flags" or "do not delete now"
        this->parent2->Release(this->secondChild, 0);
        this->secondChild = 0;
    }
    // Call virtual function at vtable+0x0C (likely Delete/Shutdown) on parent2
    this->parent2->Delete();
    // Release first child using parent1
    if (this->firstChild != 0)
    {
        this->parent1->Release(this->firstChild, 0);
        this->firstChild = 0;
    }
    // Call virtual function at vtable+0x0C on parent1
    this->parent1->Delete();
}