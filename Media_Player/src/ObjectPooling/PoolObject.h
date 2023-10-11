#pragma once

namespace TwoTune {

	/// <summary>
	/// 'interface' for poolable objects.
	/// </summary>
	struct PoolObject {
	public:
		unsigned int m_ID;
		virtual void Reset() = 0;
	};
}