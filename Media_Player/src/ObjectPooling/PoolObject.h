#pragma once

namespace TwoTune {

	struct PoolObject {
	public:
		unsigned int m_ID;
		virtual void Reset() = 0;
	};
}