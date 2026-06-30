// FUNC_NAME: BaseVehicle::readNetworkState
// Function address: 0x0067bc80
// Reads a compressed physics state from network packet and unpacks into local fields.
// Fields at offsets +0xe0..+0xec represent orientation (quaternion) and +0xf0, +0xf4 represent linear velocity (delta encoded).
// Uses predictive delta compression for velocity (accumulate read deltas), absolute assignment for orientation.

void BaseVehicle::readNetworkState() {
    int deltaVel1 = readPackedInt();     // read from network stream
    int deltaVel2 = readPackedInt();
    this->velocityX += deltaVel1 + deltaVel2;   // +0xf0: accumulated linear velocity X

    int deltaVel3 = readPackedInt();
    int deltaVel4 = readPackedInt();
    this->velocityY += deltaVel3 + deltaVel4;   // +0xf4: accumulated linear velocity Y

    int orientX = readPackedInt();              // +0xe0: quaternion X
    this->orientationX = orientX;

    int orientZ = readPackedInt();              // +0xe8: quaternion Z (note order: X, Z, Y, W)
    this->orientationZ = orientZ;

    int orientY = readPackedInt();              // +0xe4: quaternion Y
    this->orientationY = orientY;

    int orientW = readPackedInt();              // +0xec: quaternion W
    this->orientationW = orientW;
}