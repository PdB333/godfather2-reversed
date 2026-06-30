// FUNC_NAME: hasAnyActiveDescendant
bool hasAnyActiveDescendant(Node* node)
{
    if (node == nullptr)
    {
        return false;
    }

    // Check if this node's active flag (bit0 of +0x14) is set
    if (node->flags & 0x01)
    {
        return true;
    }

    // Iterate over children: +0x20 = firstChild, +0x28 = nextSibling
    Node* child = node->firstChild;
    while (child != nullptr)
    {
        if (hasAnyActiveDescendant(child))
        {
            return true;
        }
        child = child->nextSibling;
    }

    return false;
}