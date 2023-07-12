#include "CameraManager.h"

CameraManager::CameraManager()
{
    CameraAt = Vec3(0,0,0);
    CameraTo = Vec3(0,0,0);
    CameraUp = Vec3(0,1,0);
}

float CameraManager::DistanceFromCamera(float x, float y, float z)
{
    float dx = this->CameraAt.x - x;
    float dy = this->CameraAt.y - y;
    float dz = this->CameraAt.z - z;
    if(dx*dx + dy*dy + dz*dz < 0) printf("RAIZ QUADRADA DE NEGATIVO.");
    return sqrtf(dx*dx + dy*dy + dz*dz);
}
