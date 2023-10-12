#pragma once

namespace TwoTune {

	/// <summary>
	/// 'interface' for poolable objects.
	/// </summary>
	struct PoolObject {
	public:
		// ID of the object.
		unsigned int m_ID;
		
		// Resets the poolable object. 
		virtual void Reset() = 0;
	};
}