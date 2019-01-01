#pragma once

#pragma once

#include <memory>
#include <vector>

namespace Seed
{
	template<class _Data, class _Key = int>
	class ResourcePool
	{
	public:
		ResourcePool(void) {};
		virtual ~ResourcePool(void) {};

	private:
		std::unordered_map<_Key, std::unique_ptr<_Data>> database_;

	public:
		void Load(const _Key & key, std::unique_ptr<_Data> & data)
		{
			database_[key] = std::forward<std::unique_ptr<_Data>>(data);
		}
		void Unload(const _Key & key)
		{
			database_.erase(key);
		}
		const std::unique_ptr<_Data> & Get(const _Key & key)
		{
			return this->database_[key];
		}
		void UnloadAll(void)
		{
			this->database_.clear();
		}
	};
}