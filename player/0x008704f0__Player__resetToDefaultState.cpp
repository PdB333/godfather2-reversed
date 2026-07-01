// FUNC_NAME: Player::resetToDefaultState
void Player::resetToDefaultState(void *this)
{
    // Set health to 0 (dead state)
    FUN_0086b830(0);
    // Set some float value to 1.0f (possibly speed multiplier or damage scale)
    FUN_0086b7d0(0x3f800000);
    // Set some boolean to true (e.g., enable ragdoll, or disable input)
    FUN_0086b7f0(1);
    // Set some boolean to false (e.g., disable invincibility)
    FUN_0086b7b0(0);
    // Call a more specific reset function with the player object
    FUN_0086eb20(this);
    return;
}