/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	binary_heap.hpp
 * @brief	binary heapのテンプレート
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	アルゴリズムイントロダクション第1巻を参考に実装した。
 */

#ifndef	__BINARY_HEAP_HPP__
#define __BINARY_HEAP_HPP__	"binary_heap.hpp"

#include <cstddef>
#include <cassert>
#include <vector>

namespace ys
{
	/**
	 * @class	binary heapのテンプレート・クラス
	 */
	template<typename TYPE>
	class BinaryHeap
	{
	private:

		std::vector<TYPE> data_;	///< ヒープ本体

		/**
		 * ヒープ条件の比較用関数
		 * @note	第1引数を親にしたい場合は0以下の整数を返却する。
		 * @note	第2引数を親にしたい場合は1以上の整数を返却する。
		 */
		int (* compare_)(const TYPE&, const TYPE&);

		/**
		 * 指定位置の要素から親に向かってヒープ条件を成立させる
		 * @param[in]	i	ヒープのインデックス
		 * @note	不正な引数 @a i を用いた際の動作は不定。
		 * @note	最悪計算量はΘ(log n)。
		 */
		void
		heapify_up(size_t i)
			{
				size_t j;
				TYPE tmp;

				while (0 < i) {
					j = (i - 1) / 2;
					if (0 >= compare_(data_[j], data_[i])) break;
					tmp = data_[j];
					data_[j] = data_[i];
					data_[i] = tmp;
					i = j;
				}
			}

		/**
		 * 指定位置の要素から子に向かってヒープ条件を成立させる
		 * @param[in]	i	ヒープのインデックス
		 * @note	不正な引数 @a i を用いた際の動作は不定。
		 * @note	最悪計算量はΘ(log n)。
		 */
		void
		heapify_down(size_t i)
			{
				size_t j, k;
				const size_t l = data_.size();
				TYPE tmp;

				while (i < l) {
					j = i * 2 + 1;
					if (l <= j) break;
					k = j + 1;
					if (k < l && 0 < compare_(data_[j], data_[k])) j = k;
					if (0 >= compare_(data_[i], data_[j])) break;
					tmp = data_[j];
					data_[j] = data_[i];
					data_[i] = tmp;
					i = j;
				}
			}

	public:

		/**
		 * コンストラクタ
		 */
		BinaryHeap()
			: compare_(0)
			{
				;
			}

		/**
		 * ヒープの準備
		 * @param[in]	data	ヒープに入力するデータ列
		 * @param[in]	length	引数 @a data の長さ
		 * @param[in]	compare	ヒープ条件の比較用関数
		 * @note	最悪計算量はΘ(n log n)。
		 */
		void
		prepare(const TYPE* data,
				size_t length,
				int (* compare)(const TYPE&, const TYPE&))
			{
				compare_ = compare;
				data_.reserve(length);

				for (size_t i(0); i < length; ++i) {
					data_.push_back(data[i]);
					heapify_up(i);
				}
			}

		/**
		 * ヒープ内の要素数を取得
		 * @return	ヒープ内の要素数
		 * @note	最悪計算量はΘ(1)。
		 */
		size_t
		size() const
			{
				return data_.size();
			}

		/**
		 * ヒープにデータを追加
		 * @param[in]	data	追加するデータ
		 * @note	最悪計算量はΘ(log n)。
					ただし、 @a data_ のメモリ領域が伸びた場合はΘ(n)。
		 */
		void
		push(const TYPE& data)
			{
				const size_t l = data_.size();
				data_.push_back(data);
				heapify_up(l);
			}

		/**
		 * ヒープのルートを取得しヒープから削除
		 * @return	ヒープのルートのデータ
		 * @note	1つ以上の要素を含む時に使用すること。
		 * @note	最悪計算量はΘ(log n)。
		 */
		TYPE
		pop()
			{
				const size_t l = data_.size();

				assert(l);

				TYPE value = data_[0];

				if (1 < l) {
					TYPE tmp = data_[l-1];
					data_.pop_back();
					data_[0] = tmp;
					heapify_down(0);
				}

				return value;
			}

		/**
		 * ヒープ内のデータを書き換え
		 * @param[in]	i	ヒープのインデックス
		 * @param[in]	data	書き換える値
		 * @note	不正な引数 @a i を用いた際の動作は不定。
		 * @note	最悪計算量はΘ(log n)。
		 */
		void
		update(size_t i,
			   const TYPE& data)
			{
				data_[i] = data;

				if (0 < i) {
					size_t j = (i - 1) / 2;
					if (0 < compare_(data_[j], data)) {
						heapify_up(i);
						return;
					}
				}

				heapify_down(i);
			}

		/**
		 * ヒープ内のデータを直接取得
		 * @param[in]	i	ヒープのインデックス
		 * @return	ヒープ内の指定した位置のデータ
		 * @note	不正な引数 @a i を用いた際の動作は不定。
		 * @note	最悪計算量はΘ(1)。
		 */
		TYPE
		get(size_t i = 0) const
			{
				return data_[i];
			}
	};
};

#endif	// __BINARY_HEAP_HPP__
