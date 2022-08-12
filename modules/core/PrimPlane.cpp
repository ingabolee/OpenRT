#include "PrimPlane.h"
#include "Ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimPlane::intersect(Ray& ray) const
	{
		float dist = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;

		ray.t = dist;
		ray.hit = shared_from_this();
		return true;
	}

	bool CPrimPlane::if_intersect(const Ray& ray) const
	{
		float t = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (t < Epsilon || isinf(t) || t > ray.t) return false;
		return true;
	}

	Vec2f CPrimPlane::getTextureCoords(const Ray& ray) const
	{
		Vec3f hit = wcs2ocs(ray.hitPoint());
		Vec2f res = norm(hit) > Epsilon ? Vec2f(hit.dot(m_u), hit.dot(m_v)) : Vec2f(0, 0);
	
		return res;
	}

	CBoundingBox CPrimPlane::getBoundingBox(void) const
	{
		Vec3f minPoint = Vec3f::all(-Infty);
		Vec3f maxPoint = Vec3f::all(Infty);
		for (int i = 0; i < 3; i++)
			if (m_normal[i] == 1) {
				minPoint[i] = m_origin[i];
				maxPoint[i] = m_origin[i];
				break;
			}
		return CBoundingBox(minPoint, maxPoint);
	}

	void CPrimPlane::doTransform(const Mat& T)
	{
		// Transform origin
		Vec3f o = Vec3f::all(0);		// point in the WCS origin
		o = CTransform::point(o, T);	// transltion of the point
		m_origin += o;					// update the sphere's origin

		// Transform normals
		Mat T1 = T.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, T1));
	}
}
