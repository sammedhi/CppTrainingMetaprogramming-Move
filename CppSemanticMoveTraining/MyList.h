#pragma once
#include <iostream>

template <typename T>
struct is_pointer { static constexpr bool value = false; };

template <typename T>
struct is_pointer<T*> { static constexpr bool value = true; };

template <typename T>
struct Node
{
	template <typename UR = T>
	Node(UR&& elem , Node<T>* prev = nullptr , Node<T>* next = nullptr):
		content( std::forward<UR>(elem) ),
		next(next),
		prev(prev)
	{
		if (prev != nullptr)
			prev->next = this;
	}

	friend void swap(Node<T>*& elem1, Node<T>*& elem2)
	{
		Node<T>* tmp = std::move(elem1);
		elem1 = std::move(elem2);
		elem2 = std::move(tmp);
	}

	T content;

	Node<T>* next;
	Node<T>* prev;
};

template <typename T>
class List
{
public:
	List();
	template <typename UR = T, class TypeMustBeT = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, T>::value>>
	void push(UR&& elem)
	{
		if (m_list_start == nullptr)
		{
			m_list_start = new Node<T>(std::forward<UR>(elem));
			m_list_end = m_list_start;
		}
		else
		{
			m_list_end = new Node<T>(std::forward<UR>(elem), m_list_end);
		}
	}

	T& get(int index)
	{
		Node<T>* curr = m_list_start;
		for (auto i = 0; i < index; i++)
		{
			curr = curr->next;
		}
		return curr->content;
	}

	template <typename TT = T>
	friend std::ostream & pick_value_stream(std::ostream & os,
		const List<T> & list,
		typename std::enable_if < is_pointer<TT>::value == true >::type * = nullptr)
	{
		for (Node<T>* node = list.m_list_start; node != nullptr; node = node->next)
		{
			os << *(node->content) << " ";
		}
		os << std::endl;
		return os;
	}

	template <typename TT = T>
	friend std::ostream & pick_value_stream(std::ostream & os,
		const List<T> & list,
		typename std::enable_if < is_pointer<TT>::value == false >::type * = nullptr)
	{
		for (Node<T>* node = list.m_list_start; node != nullptr; node = node->next)
		{
			os << node->content << " ";
		}
		os << std::endl;
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, const List<T>& list)
	{
		return pick_value_stream(os, list);
	}

private:
	Node<T>* m_list_start;
	Node<T>* m_list_end;

};

template<typename T>
inline List<T>::List()
{
	m_list_start = nullptr;
	m_list_end = nullptr;
}
