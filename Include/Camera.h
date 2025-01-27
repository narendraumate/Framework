//
//  Camera.h
//  Framework
//
//  Created by Narendra Umate on 11/29/15.
//
//

#ifndef Camera_h
#define Camera_h

#include "Bound.h"
#include "Matrix.h"
#include "Vector.h"

#define UNOPTIMIZED

class Camera {
public:
    enum Type {
        Orthographic,
        Perspective
    };

    Camera(const Type& type);
    virtual ~Camera();

    void setType(const Type& type);
    void setFrame(const Vec3& position, const Vec3& right, const Vec3& up, const Vec3& front);
    void setPosition(const Vec3& position);
    void setAxes(const Vec3& right, const Vec3& up, const Vec3& front);
	void setFrustum(const float& rightMin, const float& rightMax, const float& upMin, const float& upMax, const float& frontMin, const float& frontMax);
    void setFrustum(const float& upFovDegrees, const float& aspectRatio, const float& frontMin, const float& frontMax);
	void setSize(const int& screenWidth, const int& screenHeight);
    void setPreViewMatrix(const Mat4& preViewMatrix);
    void setPostProjectionMatrix(const Mat4& postProjectionMatrix);

    void getFrame(Vec3& position, Vec3& right, Vec3& up, Vec3& front);
    void getAxes(Vec3& right, Vec3& up, Vec3& front);
	void getFrustum(float& rightMin, float& rightMax, float& upMin, float& upMax, float& frontMin, float& frontMax);
    void getFrustum(float& upFovDegrees, float& aspectRatio, float& frontMin, float& frontMax);
	void getSize(int& screenWidth, int& screenHeight);

	Type getType();
	Vec3 getPosition();
	Mat4 getPreViewMatrix();
	Mat4 getPostProjectionMatrix();

    Mat4 getViewMatrix();
	Mat3 getViewNormMatrix();
    Mat4 getViewProjectionMatrix();
	Mat4 getProjectionMatrix();

	bool boundInFrustum(const Bound3& bound) const;

private:
    void updateViewMatrix();
    void updateProjectionMatrix();
    void updateViewProjectionMatrix();
	void updateFrustumPlanesAndPoints();

    Type m_type;
    Vec3 m_position;
    Vec3 m_right;
    Vec3 m_up;
    Vec3 m_front;

    float m_upFovDegrees;
    float m_aspectRatio;

    float m_rightMin;
    float m_rightMax;
    float m_upMin;
    float m_upMax;
    float m_frontMin;
    float m_frontMax;

    Mat4 m_preViewMatrix;
    Mat4 m_viewMatrix;
    Mat4 m_orthographicProjectionMatrix;
    Mat4 m_perspectiveProjectionMatrix;
    Mat4 m_viewOrthographicProjectionMatrix;
    Mat4 m_viewPerspectiveProjectionMatrix;
    Mat4 m_postProjectionMatrix;

	Vec4 m_planes[6];
#if defined UNOPTIMIZED
	Vec3 m_points[8];
#endif // defined UNOPTIMIZED
};

#endif /* Camera_h */
