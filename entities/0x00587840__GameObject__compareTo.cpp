// FUNC_NAME: GameObject::compareTo
int __thiscall GameObject::compareTo(const GameObject* other) const
{
    // Offsets (relative to this):
    // +0x00: count (mCount)
    // +0x14: base priority (mBasePriority)
    // +0x1C: secondary priority (mSecondaryPriority)
    // +0x2C: flags (bit 0x20: kFlagAdvanced)

    // Determine priority for this object
    int thisPriority;
    if ((mFlags & 0x20) && (mCount >= 2))
    {
        thisPriority = mSecondaryPriority; // +0x1C
    }
    else
    {
        thisPriority = mBasePriority; // +0x14
    }

    // Determine priority for other object
    int otherPriority;
    if ((other->mFlags & 0x20) && (other->mCount >= 2))
    {
        otherPriority = other->mSecondaryPriority; // +0x1C
    }
    else
    {
        otherPriority = other->mBasePriority; // +0x14
    }

    // Primary comparison
    if (thisPriority != otherPriority)
    {
        return (thisPriority < otherPriority) ? -1 : 1;
    }

    // Tie-breaker: if both have advanced flag and count >= 4, compare base priorities
    int thisTie = 0;
    if ((mFlags & 0x20) && (mCount >= 4))
    {
        thisTie = mBasePriority; // +0x14
    }

    int otherTie = 0;
    if ((other->mFlags & 0x20) && (other->mCount >= 4))
    {
        otherTie = other->mBasePriority; // +0x14
    }

    if (thisTie != otherTie)
    {
        return (thisTie < otherTie) ? -1 : 1;
    }

    return 0;
}