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

void
print(ys::BinaryHeap<int>* heap)
{
	const size_t l = heap->size();

	for (size_t i(0); i < l; ++i) {
		std::printf("%lu=>%d", i, heap->get(i));
		if (i < l - 1) std::printf(", ");
	}
	std::printf("\n");
}

int
main()
{
	int data[] = {16, 5, 6, 8, 10, 0, 2};
	ys::BinaryHeap<int>* heap = new ys::BinaryHeap<int>();

	heap->prepare(data, sizeof(data)/sizeof(data[0]), compare);
	print(heap);

	int n(3);
	std::printf("PUSH: %d\n", n);
	heap->push(n);
	print(heap);

	n = 7;
	std::printf("UPDATE: %d=>%d\n", 2, n);
	heap->update(2, n);
	print(heap);

	n = heap->pop();
	std::printf("POP: %d\n", n);
	print(heap);

	delete heap;

	return 0;
}
