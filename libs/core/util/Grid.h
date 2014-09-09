#pragma once
#include <detail/type_int.hpp>
#include <vector>

namespace core 
{
	template<class ValueType>
	class Grid 
	{
	public:
		Grid();
		Grid(glm::uint rows, glm::uint cols, const ValueType& initialValue = ValueType());

	public:
		glm::uint GetNumRows() const;
		glm::uint GetNumCols() const;
		bool IsEmpty() const;
		void Clear();
		void Resize(glm::uint rows, glm::uint cols, const ValueType& initialValue = ValueType());

	public:
		ValueType* operator[](glm::uint row);
		const ValueType* operator[](glm::uint row) const;

	private:
		glm::uint m_numRows;
		glm::uint m_numCols;

		std::vector<ValueType> m_array;
	};
}

#include "Grid.inl"