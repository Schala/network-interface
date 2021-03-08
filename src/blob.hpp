#ifndef _BLOB_H
#define _BLOB_H

#include <cstring>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include "common.hpp"

namespace cmm
{
	/// Binary blob that uses an internal string stream
	class blob
	{
	public:
		/// Constructs an empty binary blob
		blob()
		{
		}
		
		/**
		 * Constructs a binary blob
		 * @param data String to initialise the blob with
		 */
		blob(const std::string &data):
			stream_(data)
		{
		}

		/**
		 * Ignores a specified number of bytes when reading from the blob
		 * @param count How many bytes to skip
		 */
		void ignore(sizeint count)
		{
			stream_.ignore(count);
		}

		/**
		 * Zero-pads a specified amount when writing to the blob
		 * @param count How many padded bytes to insert
		 */
		void pad(sizeint count)
		{
			for (int i = 0; i < count; i++)
				stream_.put(0);
		}

		/// Returns the next byte in the blob without advancing the offset
		uint8 peek()
		{
			return static_cast<uint8>(stream_.peek());
		}

		/// Gets the internal storage of the blob
		std::string rdbuf()
		{
			return stream_.str();
		}

		/**
		 * Read a specified number of bytes from the blob.
		 * @param count How many bytes to read
		 * @return Read data as a string
		 */
		template <class String> String&& read(sizeint count)
		{
			String s_(count, 0);
			stream_.read(reinterpret_cast<char *>(s_.data()), count);
			return std::move(s_);
		}

		/// Read a plain old data (POD) value from the blob.
		template <class T> T&& read()
		{
			static_assert(std::is_standard_layout<T>::value, "expected POD type for read");

			T t_;
			stream_.read(reinterpret_cast<char *>(&t_), sizeof(T));
			return std::move(t_);
		}

		/**
		 * Write a plain old data (POD) value to the blob.
		 * @param t Value to write
		 */
		template <class T> void write(T t)
		{
			static_assert(std::is_standard_layout<T>::value, "expected POD type for write_pod");
			stream_.write(reinterpret_cast<const char *>(&t), sizeof(T));
		}

		/**
		 * Write a string container to the blob.
		 * @param data Reference to the string data of an STL container
		 */
		template <class String> void write_str(const String &data)
		{
			stream_.write(reinterpret_cast<const char *>(data.data()), data.size());
		}

		/**
		 * Write an 8-bit value to the blob.
		 * @param b An 8-bit value
		 */
		void write8(uint8 b)
		{
			stream_.put(static_cast<char>(b));
		}

		/**
		 * Write a 16-bit value to the blob.
		 * @param w A 16-bit value
		 */
		void write16(uint16 w)
		{
			write(w);
		}

		/**
		 * Write a 32-bit value to the blob.
		 * @param d A 32-bit value
		 */
		void write32(uint32 d)
		{
			write(d);
		}

		/**
		 * Write a null-terminated string literal to the blob.
		 * @param s Null-terminated string literal
		 */
		void write_cstr(const char *s)
		{
			stream_.write(s, std::strlen(s));
		}

		/** Change the read offset of the blob.
		 * @param position Relative offset
		 * @param direction Relative direction
		 */
		void seekg(sizeint position, std::ios_base::seekdir direction = std::ios_base::cur)
		{
			stream_.seekg(position, direction);
		}

		/** Change the write offset of the blob.
		 * @param position Relative offset
		 * @param direction Relative direction
		 */
		void seekp(sizeint position, std::ios_base::seekdir direction = std::ios_base::cur)
		{
			stream_.seekp(position, direction);
		}

		/// Get the size of the blob.
		sizeint size()
		{
			auto prev = tellg();
			seekg(0, std::ios_base::end);
			auto cur = tellg();
			seekg(prev, std::ios_base::beg);
			return cur;
		}

		/// Get the read offset of the blob.
		sizeint tellg()
		{
			return stream_.tellg();
		}

		/// Get the write offset of the blob.
		sizeint tellp()
		{
			return stream_.tellp();
		}
	protected:
		std::stringstream stream_;
	};
}

#endif // _BLOB_H
