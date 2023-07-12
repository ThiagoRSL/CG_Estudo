#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Vec3.h"
#include "Utils/Pnt2.h"

#include "CameraManager.h"
class CameraManager
{
    private:
        Vec3 CameraAt;
        Vec3 CameraTo;
        Vec3 CameraUp;

    public:
        static CameraManager &shared_instance() {static CameraManager cameraManager; return cameraManager;}
        CameraManager();
        void SetCameraAt(Vec3 At) {this->CameraAt = At;}
        void SetCameraTo(Vec3 To) {this->CameraTo = To;}
        void SetCameraUp(Vec3 Up) {this->CameraUp = Up;}
        Vec3 GetCameraAt() {return CameraAt;}
        Vec3 GetCameraTo() {return CameraTo;}
        Vec3 GetCameraUp() {return CameraUp;}
        //void UpdateCameraOffset();
        //Pnt2* GetCameraOffsetRef() {return &CameraOffset;}
        float DistanceFromCamera(float x, float y, float z);
        float ZDistanceFromCamera(float z)
        {
            return this->CameraAt.z - z;
        }

    protected:

};

#endif // CAMERAMANAGER_H
