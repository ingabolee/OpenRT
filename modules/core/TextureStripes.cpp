#include "TextureStripes.h"
#include "Ray.h"

namespace rt{
	/// @todo Play with the direction of the stripes
	Vec3f CTextureStripes::getTexel(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hit->wcs2ocs(ray.hitPoint());				// Hitpoint in OCS
		
		// Full form
		const Vec3f dir = normalize(Vec3f(1, 0, 0));					// Orintation of the stripes
		const Vec3f proj = hitPoint.mul(dir);							// Projection of the hitpoint to the directional vector
		
		float value = m_period * static_cast<float>(sum(proj)[0]);

		value = 0.5f * (1 + sinf(value * Pif));
		return m_gradient.getColor(value);
	}
}
