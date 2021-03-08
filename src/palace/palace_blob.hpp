#ifndef _PALACE_BLOB_H
#define _PALACE_BLOB_H

#include "../blob.hpp"

namespace cmm
{
	/// Blob extensions for the Palace protocol
	class palace_blob : public blob
	{
	public:
		/// Constructs an empty blob
		palace_blob()
		{
		}

		/**
		 * Constructs a new blob
		 * @param data Data to initialise the blob with
		 */
		palace_blob(const std::string &data):
			stream_(data)
		{
		}

		/// Reads a Pascal-style string from the blob
		template <class String> String&& read_pstr()
		{
			uint8 count = read();
			String s = read(count);
			return std::move(s);
		}

		/// Reads a Pascal-style string up to 31 bytes from the blob
		template <class String> String&& read_str31()
		{
			uint8 count = read();
			String s = read(count);
			ignore(31 - count);
		}

		/// Reads a Pascal-style string up to 63 bytes from the blob
		template <class String> String&& read_str63()
		{
			uint8 count = read();
			String s = read(count);
			ignore(63 - count);
		}

		/// Reads a null-terminated string from the blob
		template <class String> String&& read_zstr()
		{
			String s;
			char c = ' ';

			while (c != 0)
			{
				c = stream_.get();
				s.push_back(c);
			}
			return std::move(s);
		}

		template <class String> void write_pstr(const String &data)
		{
			write8(data.size());
			write_str(data);
		}

		template <class String> void write_str31(const String &data)
		{
			auto len_ = data.size()
			if (len_ > 31) data.resize(31);
			write8(len_);
			write_str(data);
			pad(31 - len_);
		}

		template <class String> void write_zstr(const String &data)
		{
			auto len_ = data.size()
			if (len_ > 63) data.resize(31);
			write8(len_);
			write_str(data);
			pad(63 - len_);
		}
	}
}

#endif // _PALACE_BLOB_H
