#pragma once
#include "Grid.h"

namespace core 
{
	//////////////////////////////////////////////////////////////////////////

	template<class ValueType>
	Grid<ValueType>::Grid()
		: m_numRows(0)
		, m_numCols(0)
		, m_array(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	template<class ValueType>
	Grid<ValueType>::Grid(glm::uint rows, glm::uint cols, const ValueType& initialValue)
		: m_numRows(rows)
		, m_numCols(cols)
		, m_array(0)
	{
		Resize(rows, cols, initialValue);
	}

	//////////////////////////////////////////////////////////////////////////

	template<class ValueType>
	glm::uint Grid<ValueType>::GetNumCols() const 
	{
		return m_numCols;
	}

	//////////////////////////////////////////////////////////////////////////

	template<class ValueType>
	glm::uint Grid<ValueType>::GetNumRows() const 
	{
		return m_numRows;
	}
	
	//////////////////////////////////////////////////////////////////////////

	template<class ValueType>
	bool Grid<ValueType>::IsEmpty() const 
	{
		return m_array.empty();
	}

	//////////////////////////////////////////////////////////////////////////
	
	template<class ValueType>
	void Grid<ValueType>::Clear() 
	{
		m_array.clear();
		m_numRows = 0;
		m_numCols = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	template<class ValueType>
	void Grid<ValueType>::Resize(glm::uint rows, glm::uint cols, const ValueType& initialValue) 
	{
		m_numRows = rows;
		m_numCols = cols;
		if (m_numRows == 0) 
		{
			m_numCols = 0;
		}

		m_array.resize(m_numRows * m_numCols, initialValue);
	}

	//////////////////////////////////////////////////////////////////////////
	
	template<class ValueType>
	ValueType* Grid<ValueType>::operator[](glm::uint row)
	{
		return &m_array[row * m_numCols];
	}

	//////////////////////////////////////////////////////////////////////////
	
	template<class ValueType>
	const ValueType* Grid<ValueType>::operator[](glm::uint row) const
	{
		return &m_array[row * m_numCols];
	}

	//////////////////////////////////////////////////////////////////////////
}
