// FUN_004abd90: SceneNode::computeAggregatedFlags
uint __thiscall SceneNode::computeAggregatedFlags() {
    uint ownFlags = *(uint *)(this + 0x3C); // base flags at +0x3C
    if (*(char *)(this + 0x44) != '\0') { // dirty flag at +0x44
        SceneNode *child = *(SceneNode **)(this + 0x20); // first child at +0x20
        *(char *)(this + 0x44) = 0;                       // clear dirty
        *(uint *)(this + 0x40) = 0;                       // reset aggregated flags at +0x40
        for (; child != nullptr; child = *(SceneNode **)(child + 0x28)) { // next sibling at +0x28
            uint childFlags = child->computeAggregatedFlags(); // recursive call
            *(uint *)(this + 0x40) |= childFlags;
        }
    }
    return *(uint *)(this + 0x40) | ownFlags;
}