// FUNC_NAME: BaseVehicle::updateWheelGroundContact
void __thiscall BaseVehicle::updateWheelGroundContact(BaseVehicle* this, void* wheelState)
{
    char isGrounded;
    int wheelIndex;
    
    // Initialize wheel state with default values
    BaseVehicle::initWheelState(wheelState);
    
    // Set the wheel contact flag (0x990e4555 likely a contact marker)
    BaseVehicle::setWheelContactFlag(wheelState, 0x990e4555);
    
    // Get initial ground detection state
    isGrounded = BaseVehicle::getWheelGroundState();
    
    while (isGrounded == '\0') {
        // Advance to next wheel slot
        BaseVehicle::incrementWheelIndex();
        
        // Get current wheel index
        wheelIndex = BaseVehicle::getCurrentWheelIndex();
        if (wheelIndex == 0) {
            // If wheel index reset, get the wheel state data
            wheelIndex = BaseVehicle::incrementWheelIndex();
            // Store the ground contact data at offset +0x4C
            // +0x4C = wheelGroundContactData
            this->field_0x4C = *(undefined4*)(wheelIndex + 8);
        }
        
        // Process wheel ground interaction
        BaseVehicle::processWheelInteraction();
        
        // Update ground detection state
        isGrounded = BaseVehicle::getWheelGroundState();
    }
    
    return;
}