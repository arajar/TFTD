#pragma once

namespace core 
{
	template<class ValueType>
	class Grid 
	{
	public:
		Grid();
		Grid(uint rows, uint cols, const ValueType& initialValue = ValueType());

	public:
		uint GetNumRows() const;
		uint GetNumCols() const;
		bool IsEmpty() const;
		void Clear();
		void Resize(uint rows, uint cols, const ValueType& initialValue = ValueType());

	public:
		ValueType* operator[](uint row);
		const ValueType* operator[](uint row) const;

	private:
		uint m_numRows;
		uint m_numCols;

		std::vector<ValueType> m_array;
	};
}

#include "Grid.inl"