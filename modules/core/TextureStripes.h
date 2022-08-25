#pragma once

#include"Texture.h"

namespace rt {
	/**
	 * @brief Stripes Procedural Texture class
	 * @ingroup moduleTexture
	 * @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	 */
	class CTextureStripes : public CTexture {
	public:
		/**
		 * @brief Constructor
		 * @note This class is an experimental class
		 * @ingroup moduleTexture
		 * @param period The number of stripes per 1 unit of WCS
		 */
		DllExport CTextureStripes(float period) : m_period(period) {}
		DllExport virtual ~CTextureStripes(void) = default;
    
		DllExport Vec3f	getTexel(const Vec3f& uvw) const override;
		DllExport bool	isProcedural(void) const override { return true; }


	private:
		float m_period;		///< The number of stripes per 1 unit of WCS
	};
}
