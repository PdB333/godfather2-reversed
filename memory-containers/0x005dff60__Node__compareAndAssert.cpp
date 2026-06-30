// FUNC_NAME: Node::compareAndAssert
bool Node::compareAndAssert(const Node* other) const
{
    // +0x00: id (must be non-zero and equal)
    // +0x04: value (compared for equality only if ids match)
    if (id == 0 || id != other->id) {
        AssertFail(); // 0x00b97aea - debug assert
    }
    return value == other->value;
}