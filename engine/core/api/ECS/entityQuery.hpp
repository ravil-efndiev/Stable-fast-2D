#pragma once
#include "Entity.hpp"

namespace s2f
{
	/*
	* @brief Allows to efficiently filter entities based on component type list
	* and get those components in place
	* @tparam ...Components searched component types
	* @param entities original entities vector
	* @return view into original entities vector, filtered and made of unpackable tuples
	* containing entity as first element and its component references as the rest
	*/
	template <class ...Components>
	inline auto queryEntities(const std::vector<Entity>& entities)
	{
		return entities
			| std::views::filter([](Entity entity) { return (entity.has<Components>() && ...); })
			| std::views::transform([](Entity entity) {
				return std::tuple<Entity, Components&...>(entity, *entity.get<Components>()...);
			});
	}
}
