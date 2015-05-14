/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	main.cpp
 * @brief	binary_heap.hppの動作確認用コマンド
 * @author	Yasutaka SHINDOH / 新堂 安孝
 */

#include <cstdio>
#include "binary_heap.hpp"

int
compare(const int& parent,
		const int& child)
{
	if (parent <= child) return -1;
	return 1;
}

int print(ys::BinaryHeap<int>* heap)
{
	const size_t l = heap->size();

	for (size_t i(0); i < l; ++i) {
		std::printf("[%lu]\t%d\n", i, heap->get(i));
	}
}

int
main()
{
	int data[] = {16, 5, 6, 8, 10, 0, 2};
	ys::BinaryHeap<int>* heap = new ys::BinaryHeap<int>();

	heap->prepare(data, sizeof(data)/sizeof(data[0]), compare);
	print(heap);

	std::printf(">>>> PUSH: 3\n");
	heap->push(3);
	print(heap);

	std::printf(">>>> UPDATE: [0] 4\n");
	heap->update(0, 4);
	print(heap);

	std::printf(">>>> POP: %d\n", heap->pop());
	print(heap);

	delete heap;

	return 0;
}
