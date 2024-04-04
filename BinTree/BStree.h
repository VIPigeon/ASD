#pragma once

//  Фрагменты для реализации сбалансированных деревьев поиска - заготовка, не рабочая, доделать

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <string>
#include <iterator>
#include <memory>
#include <memory_resource>
#include <initializer_list>
#include <functional>
#include <exception>

template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class BinarySearchTree
{
	//using node_allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

public:
	using key_type        = T;
	using key_compare     = Compare;
	using value_type      = T;
	using value_compare   = Compare;
	using allocator_type  = Allocator;
	using size_type       = size_t;
	using difference_type = ptrdiff_t;
	using pointer         = value_type*;
	using const_pointer   = const value_type*;
	using reference       = value_type&;
	using const_reference = const value_type&;

	class iterator 
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type        = BinarySearchTree::value_type;
		using difference_type   = BinarySearchTree::difference_type;
		using pointer           = BinarySearchTree::const_pointer;
		using reference         = BinarySearchTree::const_reference;

		reference operator*()  const noexcept;
		pointer   operator->() const noexcept;
		iterator& operator++() noexcept;
		iterator& operator--() noexcept;
		iterator& operator++(int) noexcept;
		iterator& operator--(int) noexcept;
		bool      operator!=(const iterator& other) const;
		bool      operator==(const iterator& other) const;
	};

	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	

	template <class InputIterator>
	BinarySearchTree(InputIterator first, InputIterator last, Compare comparator = Compare(), allocator_type alloc = allocator_type());
	BinarySearchTree(Compare comparator = Compare(), allocator_type alloc = allocator_type());
	BinarySearchTree(std::initializer_list<T> il);
	BinarySearchTree(const BinarySearchTree& tree);

	const BinarySearchTree& operator=(const BinarySearchTree& other);
	const BinarySearchTree& operator=(BinarySearchTree&& other);

	iterator begin() const noexcept;
	iterator end() const noexcept;

	reverse_iterator rbegin() const	noexcept;
	reverse_iterator rend() const noexcept;


	allocator_type get_allocator() const noexcept;
	key_compare key_comp() const noexcept;
	value_compare value_comp() const noexcept;
	inline bool empty() const noexcept;

	size_type size() const;
	void swap(BinarySearchTree& other) noexcept;

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last);
	std::pair<iterator, bool> insert(const T& value);
	iterator insert(const_iterator position, const value_type& x);

	iterator find(const value_type& value) const;
	iterator lower_bound(const value_type& key);
	const_iterator lower_bound(const value_type& key) const;
	iterator upper_bound(const value_type& key);
	const_iterator upper_bound(const value_type& key) const;
	size_type count(const value_type& key) const;
	std::pair<const_iterator, const_iterator> equal_range(const value_type& key) const;
	iterator erase(iterator elem);
	size_type erase(const value_type& elem);
	iterator erase(const_iterator first, const_iterator last);

	bool operator==(const BinarySearchTree<T>& other);
	bool operator!=(const BinarySearchTree<T>& other);
	bool operator>=(const BinarySearchTree<T>& other);
	bool operator<=(const BinarySearchTree<T>& other);
	bool operator> (const BinarySearchTree<T>& other);
	bool operator< (const BinarySearchTree<T>& other);

	void clear();
	~BinarySearchTree();
};
