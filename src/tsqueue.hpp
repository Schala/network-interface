#ifndef _TSQUEUE_H
#define _TSQUEUE_H

#include <deque>
#include <mutex>
#include <utility>

#include "common.hpp"

namespace cmm
{
	/// Thread-safe queue
	template <class T> class tsqueue
	{
	public:
		/// Constructs a new, empty queue
		tsqueue() = default;

		/// Queue cannot be copy-constructed
		tsqueue(const tsqueue<T>&) = delete;

		/// Clears the queue before deallocation
		virtual ~tsqueue()
		{
			clear();
		}

		/// Reference to the front element of the queue
		const T& front()
		{
			std::scoped_lock lock_(mutex_);
			return queue_.front();
		}

		/// Reference to the last element of the queue
		const T& back()
		{
			std::scoped_lock lock_(mutex_);
			return queue_.back();
		}

		/**
		 * Appends an element to the end of the queue
		 * @param item Item to append
		 */
		void push_back(const T &item)
		{
			std::scoped_lock lock_(mutex_);
			queue_.emplace_back(std::move(item));
		}

		/**
		 * Appends an element to the front of the queue
		 * @param item Item to append
		 */
		void push_front(const T &item)
		{
			std::scoped_lock lock_(mutex_);
			queue_.emplace_front(std::move(item));
		}

		/// Is the queue empty?
		bool empty()
		{
			std::scoped_lock lock_(mutex_);
			return queue_.empty();
		}

		/// Number of elements in the queue
		sizeint size()
		{
			std::scoped_lock lock_(mutex_);
			return queue_.size();
		}

		/// Clears the queue of all elements
		void clear()
		{
			std::scoped_lock lock_(mutex_);
			queue_.clear();
		}

		/// Removes and returns the frontmost element
		T pop_front()
		{
			std::scoped_lock lock_(mutex_);
			auto t_ = std::move(queue_.front());
			queue_.pop_front();
			return t_;
		}

		/// Removes and returns the last element
		T pop_back()
		{
			std::scoped_lock lock_(mutex_);
			auto t_ = std::move(queue_.back());
			queue_.pop_back();
			return t_;
		}
	private:
		std::mutex mutex_;
		std::deque<T> queue_;
	};
}

#endif // _TSQUEUE_H
