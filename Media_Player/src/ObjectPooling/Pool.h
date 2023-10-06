#include "pch.h"
#include "PoolObject.h"
#pragma once

namespace TwoTune {

	template<typename T>
	class Pool {
		static_assert(std::is_base_of<PoolObject, T>::value, "T must be derived from PoolObject");

	private:
		std::vector<T*> m_Pool;
		std::vector<unsigned int> m_ActivePool;
		std::queue<unsigned int> m_PassivePool;

	public:
		Pool(unsigned int amountOfObjects) {
			for (unsigned int i = 0; i < amountOfObjects; ++i) {
				AddObjectToPool();
			}
		}

		T* Get() { 
			if (m_PassivePool.empty()) {
				AddObjectToPool();
			}
			
			unsigned int index = m_PassivePool.front();
			m_PassivePool.pop();
			m_ActivePool.push_back(index);
			return m_Pool[index];
		}

		void Release(T* object) {
			object->Reset();
			m_PassivePool.push(object->m_ID);
			std::vector<unsigned int>::iterator it = std::find(m_ActivePool.begin(), m_ActivePool.end(), object->m_ID);
			m_ActivePool.erase(it);
		}

	private:
		void AddObjectToPool() {
			T* object = new T;
			m_Pool.push_back(object);
			object->m_ID = m_Pool.size() - 1;
			m_PassivePool.push(object->m_ID);
		}

		T* GetPoolObject(unsigned int id) {
			if (id >= m_Pool.size()) {
				TWOTUNE_LOG_WARNING("ID exceeds pool boundaries.");
				return nullptr;
			}
			return m_Pool[id];
		}
	};
}