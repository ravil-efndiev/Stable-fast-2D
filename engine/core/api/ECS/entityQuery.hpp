#pragma once
#include "Entity.hpp"

namespace s2f
{
	template <class ...Components>
	struct QueryElement
	{
		Entity entity;
		std::tuple<Components&...> components;
	};

	template <size_t I, class ...Args>
	constexpr auto& get(QueryElement<Args...>&& element)
	{
		if constexpr (I == 0)
			return element.entity;
		else
			return std::get<I - 1>(element.components);
	};

	template <class ...Components>
	inline auto queryEntities(const std::vector<Entity>& entities)
	{
		return entities
			| std::views::filter([](Entity entity) { return (entity.template has<Components>() && ...); })
			| std::views::transform([](Entity entity) {
				return QueryElement<Components...>{
					entity,
					std::tuple<Components&...>(*entity.template get<Components>()...)
				};
			});
	}
}

namespace std
{
	template <class ...Components>
	struct tuple_size<s2f::QueryElement<Components...>>
		: integral_constant<size_t, sizeof...(Components) + 1> {};

	template <class ...Components>
	struct tuple_element<0, s2f::QueryElement<Components...>>
	{
		using type = s2f::Entity;
	};

	template <size_t I, class ...Components>
	struct tuple_element<I, s2f::QueryElement<Components...>>
	{
		using type = tuple_element_t<I - 1, tuple<Components...>>;
	};
}
