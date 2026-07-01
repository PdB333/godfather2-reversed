// FUNC_NAME: InputDevice::updateButtonState
// Function address: 0x007764d0
// Role: Updates button state flags based on manager's condition. Clears a processed flag.

class InputDevice {
public:
    void updateButtonState() {
        // +0x5c: pointer to InputDeviceManager singleton
        InputDeviceManager* mgr = *(InputDeviceManager**)((uintptr_t)this + 0x5c);
        // mgr->flags at +0x1f58: bit2 = isDown, bit1 = processed
        if (mgr->flags & 0x4) { // bit2 set (button is down)
            this->flags &= ~0x40; // clear bit6 (button up flag)
            mgr->flags &= ~0x2;   // clear bit1 (processed flag)
        } else {
            this->flags |= 0x40;  // set bit6 (button up flag)
            mgr->flags &= ~0x2;   // clear bit1 (processed flag)
        }
    }

private:
    // +0x5c: InputDeviceManager* manager
    // +0xac: uint32 flags (bit6 = buttonUp)
    uint32 flags; // placeholder for actual layout
};