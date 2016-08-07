//
//  Bound.cpp
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#include "Bound.h"

Bound3::Bound3()
: m_center(Vec3::zero)
, m_extent(Vec3::zero) {
}

Bound3::Bound3(const Vec3& center, const Vec3& extent)
: m_center(center)
, m_extent(extent) {
    m_cornerMin = center - extent;
    m_cornerMax = center + extent;
}

Bound3::Bound3(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ) {
    m_cornerMin.x = minX;
    m_cornerMin.y = minY;
    m_cornerMin.z = minZ;
    m_cornerMax.x = maxX;
    m_cornerMax.y = maxY;
    m_cornerMax.z = maxZ;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

Bound3::~Bound3() {
}

void Bound3::updateCenter(const Vec3& center) {
    m_center = center;
    m_cornerMin = center - m_extent;
    m_cornerMax = center + m_extent;
}

void Bound3::updateCenterExtent(const Vec3& center, const Vec3& extent) {
    m_center = center;
    m_extent = extent;
    m_cornerMin = center - extent;
    m_cornerMax = center + extent;
}

void Bound3::updateMinMax(const Vec3& cornerMin, const Vec3& cornerMax) {
    m_cornerMin = cornerMin;
    m_cornerMax = cornerMax;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

void Bound3::updateMinMax(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ) {
    m_cornerMin.x = minX;
    m_cornerMin.y = minY;
    m_cornerMin.z = minZ;
    m_cornerMax.x = maxX;
    m_cornerMax.y = maxY;
    m_cornerMax.z = maxZ;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

void Bound3::create(const std::list<Bound3>& boxes) {
    std::list<Vec3> points;
    for (std::list<Bound3>::const_iterator boxPointer = boxes.begin(); boxPointer != boxes.end(); ++boxPointer) {
        points.push_back(boxPointer->getCornerMin());
        points.push_back(boxPointer->getCornerMax());
    }
    create(points);
}

void Bound3::create(const std::list<Vec3>& points) {
    Vec3 cornerMin = Vec3::max;
    Vec3 cornerMax = Vec3::min;
    for (std::list<Vec3>::const_iterator pointPointer = points.begin(); pointPointer != points.end(); ++pointPointer) {
        if (pointPointer->x < cornerMin.x) {
            cornerMin.x = pointPointer->x;
        }

        if (pointPointer->x > cornerMax.x) {
            cornerMax.x = pointPointer->x;
        }

        if (pointPointer->y < cornerMin.y) {
            cornerMin.y = pointPointer->y;
        }

        if (pointPointer->y > cornerMax.y) {
            cornerMax.y = pointPointer->y;
        }

        if (pointPointer->z < cornerMin.z) {
            cornerMin.z = pointPointer->z;
        }

        if (pointPointer->z > cornerMax.z) {
            cornerMax.z = pointPointer->z;
        }
    }
}

bool Bound3::contains(const Vec3& p) const {
    if (p.x > m_cornerMax.x) {
        return false;
    }

    if (p.x < m_cornerMin.x) {
        return false;
    }

    if (p.y > m_cornerMax.y) {
        return false;
    }

    if (p.y < m_cornerMin.y) {
        return false;
    }

    if (p.z > m_cornerMax.z) {
        return false;
    }

    if (p.z < m_cornerMin.z) {
        return false;
    }

    return true;
}

bool Bound3::contains(const Bound3& other) const {
    return (contains(other.m_cornerMin) && contains(other.m_cornerMax));
}

bool Bound3::intersects(const Bound3& other) const {
    // Calculate current and min non intersecting distance between centers.
    // If we are not intersecting at all then return (0, 0).
    Vec3 curDistance = m_center - other.m_center;
    Vec3 minDistance = m_extent + other.m_extent;
    return ((!(fabsf(curDistance.x) >= minDistance.x)) && (!(fabsf(curDistance.y) >= minDistance.y)) && (!(fabsf(curDistance.z) >= minDistance.z)));
}

Bound3 Bound3::transform(const Mat4& m) const {
#if defined UNOPTIMIZED
	Bound boundingBox;
	Vec3 min = Vec3::max;
	Vec3 max = Vec3::min;
	for (unsigned int i = 0; i < 8; ++i) {
		Vec4 p4 = pointVector(m_center + entrywiseProduct(m_extent, getDirection(i))) * m;
		Vec3 p3 = Vec3(p4.x, p4.y, p4.z);
		min = minVec(min, p3);
		max = maxVec(max, p3);
	}
    boundingBox.updateMinMax(min, max);
	return boundingBox;
#else
	Bound3 boundingBox;
	Vec3 xa = m.Right() * m_cornerMin.x;
	Vec3 xb = m.Right() * m_cornerMax.x;
	Vec3 ya = m.Up() * m_cornerMin.y;
	Vec3 yb = m.Up() * m_cornerMax.y;
	Vec3 za = m.Backward() * m_cornerMin.z;
	Vec3 zb = m.Backward() * m_cornerMax.z;
	Vec3 min = minVec(xa, xb) + minVec(ya, yb) + minVec(za, zb) + m.Translation();
	Vec3 max = maxVec(xa, xb) + maxVec(ya, yb) + maxVec(za, zb) + m.Translation();
	boundingBox.updateMinMax(min, max);
	return boundingBox;
#endif
}

Bound3 Bound3::transform(const Transform& t) const {
	return transform(t.getMatrix());
}

bool Bound3::operator==(const Bound3& other) const {
    return (m_center == other.m_center && m_extent == other.m_extent);
}

bool Bound3::operator!=(const Bound3& other) const {
    return (m_center != other.m_center || m_extent != other.m_extent);
}