/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EGAMI_H__
#define __EGAMI_H__

#include <etk/types.h>
#include <etk/Vector.h>
#include <etk/math/Vector2D.h>
#include <etk/Color.h>
#include <egami/Image.h>

namespace egami
{
	bool Load(egami::Image& _output, const etk::UString& _fileName, const ivec2& _size=ivec2(-1,-1) );
	bool Scalable(const etk::UString& _fileName);
};

#endif

