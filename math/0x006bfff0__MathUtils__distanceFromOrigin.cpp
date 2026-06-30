// FUNC_NAME: MathUtils::distanceFromOrigin
float MathUtils::distanceFromOrigin(float* vec3)
{
  float originX;
  float originY;
  float originZ;

  FUN_00424fb0(&originX, 0); // Get origin X coordinate
  return SQRT(((vec3[2] - originZ) * (vec3[2] - originZ) +
               (vec3[1] - originY) * (vec3[1] - originY) +
               (vec3[0] - originX) * (vec3[0] - originX)));
}