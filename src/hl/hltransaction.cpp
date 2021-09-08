#include <boost/endian/conversion.hpp>
#include <utility>

#include "hltransaction.hpp"

namespace be = boost::endian;

HLParameter::HLParameter(HLParamID type, HLParamData &data):
	m_data(data)
{
	m_header.type = type;
	
	switch (type)
	{
		// strings
		case HLParamID::Error: [[fallthrough]];
		case HLParamID::UserName: [[fallthrough]];
		case HLParamID::UserLogin: [[fallthrough]];
		case HLParamID::UserAlias: [[fallthrough]];
		case HLParamID::ChatTopic: [[fallthrough]];
		case HLParamID::UserAliasChange: [[fallthrough]];
		case HLParamID::ServerAgreement: [[fallthrough]];
		case HLParamID::ServerName: [[fallthrough]];
		case HLParamID::FileName: [[fallthrough]];
		case HLParamID::FileTypeString: [[fallthrough]];
		case HLParamID::FileCreatorString: [[fallthrough]];
		case HLParamID::FileComment: [[fallthrough]];
		case HLParamID::FileNameNew: [[fallthrough]];
		case HLParamID::MessageQuote: [[fallthrough]];
		case HLParamID::AutoReply: [[fallthrough]];
		case HLParamID::NewsCategoryName: [[fallthrough]];
		case HLParamID::NewsArticleDataFlavor: [[fallthrough]];
		case HLParamID::NewsArticleTitle: [[fallthrough]];
		case HLParamID::NewsArticlePoster: [[fallthrough]];
		case HLParamID::ServerCipherAlgorithm: [[fallthrough]];
		case HLParamID::ClientCipherAlgorithm: [[fallthrough]];
		case HLParamID::ServerCipherMode: [[fallthrough]];
		case HLParamID::ClientCipherMode: [[fallthrough]];
		case HLParamID::ServerChecksumAlgorithm: [[fallthrough]];
		case HLParamID::ClientChecksumAlgorithm: [[fallthrough]];
		case HLParamID::ServerCompressionAlgorithm: [[fallthrough]];
		case HLParamID::ClientCompressionAlgorithm:
			m_header.size = static_cast<uint16_t>(std::get<std::string>(m_data).size());
			break;
		
		// var binary
		case HLParamID::Data: [[fallthrough]];
		case HLParamID::UserPassword: [[fallthrough]];
		case HLParamID::NewsArticleData: [[fallthrough]];
		case HLParamID::GIFIcon: [[fallthrough]];
		case HLParamID::SessionKey: [[fallthrough]];
		case HLParamID::ServerCipherInitVector: [[fallthrough]];
		case HLParamID::ClientCipherInitVector:
			m_header.size = static_cast<uint16_t>(std::get<ByteString>(m_data).size());
			break;

		// 2 bytes
		case HLParamID::UserID: [[fallthrough]];
		case HLParamID::UserIconID: [[fallthrough]];
		case HLParamID::Reference: [[fallthrough]];
		case HLParamID::ChatOptions: [[fallthrough]];
		case HLParamID::ChatID: [[fallthrough]];
		case HLParamID::WaitingCount: [[fallthrough]];
		case HLParamID::UserIconChange: [[fallthrough]];
		case HLParamID::Version: [[fallthrough]];
		case HLParamID::UserFlags: [[fallthrough]];
		case HLParamID::Options:
			m_header.size = 2;
			break;

		// 4 bytes
		case HLParamID::TransferSize: [[fallthrough]];
		case HLParamID::FileSize: [[fallthrough]];
		case HLParamID::FileType:
			m_header.size = 4;
			break;
		
		// 8 bytes
		case HLParamID::UserAccess: [[fallthrough]];
		case HLParamID::FileCreateDate: [[fallthrough]];
		case HLParamID::FileEditDate: [[fallthrough]];
		case HLParamID::NewsArticleDate:
			m_header.size = 8;
			break;
		
		// 16 bytes
		case HLParamID::NewsCategoryGUID: [[fallthrough]];
		case HLParamID::MD5: [[fallthrough]];
		case HLParamID::HAVAL:
			m_header.size = 16;
			break;
		
		// 20 bytes
		case HLParamID::SHA1:
			m_header.size = 20;
			break;
		
		case HLParamID::UserInfo:
			m_header.size = 8 + std::get<HLUserInfo>(m_data).GetNameSize();
		
		// unknown/unsupported
		[[unlikely]] default:
			m_header.size = 0;
	}
}

HLParameter::HLParameter(HLParamHeader &header, std::istream &buf):
	m_header(std::move(header))
{
	switch (m_header.type)
	{
		// strings
		case HLParamID::Error: [[fallthrough]];
		case HLParamID::UserName: [[fallthrough]];
		case HLParamID::UserLogin: [[fallthrough]];
		case HLParamID::UserAlias: [[fallthrough]];
		case HLParamID::ChatTopic: [[fallthrough]];
		case HLParamID::UserAliasChange: [[fallthrough]];
		case HLParamID::ServerAgreement: [[fallthrough]];
		case HLParamID::ServerName: [[fallthrough]];
		case HLParamID::FileName: [[fallthrough]];
		case HLParamID::FileTypeString: [[fallthrough]];
		case HLParamID::FileCreatorString: [[fallthrough]];
		case HLParamID::FileComment: [[fallthrough]];
		case HLParamID::FileNameNew: [[fallthrough]];
		case HLParamID::MessageQuote: [[fallthrough]];
		case HLParamID::AutoReply: [[fallthrough]];
		case HLParamID::NewsCategoryName: [[fallthrough]];
		case HLParamID::NewsArticleDataFlavor: [[fallthrough]];
		case HLParamID::NewsArticleTitle: [[fallthrough]];
		case HLParamID::NewsArticlePoster: [[fallthrough]];
		case HLParamID::ServerCipherAlgorithm: [[fallthrough]];
		case HLParamID::ClientCipherAlgorithm: [[fallthrough]];
		case HLParamID::ServerCipherMode: [[fallthrough]];
		case HLParamID::ClientCipherMode: [[fallthrough]];
		case HLParamID::ServerChecksumAlgorithm: [[fallthrough]];
		case HLParamID::ClientChecksumAlgorithm: [[fallthrough]];
		case HLParamID::ServerCompressionAlgorithm:
		{
			std::string tmp(m_header.size, 0);
			buf.read(reinterpret_cast<char *>(&tmp[0]), m_header.size);
			m_data = tmp;
		}
			break;
		
		// binary
		case HLParamID::Data: [[fallthrough]];
		case HLParamID::UserPassword: [[fallthrough]];
		case HLParamID::NewsArticleData: [[fallthrough]];
		case HLParamID::GIFIcon: [[fallthrough]];
		case HLParamID::SessionKey: [[fallthrough]];
		case HLParamID::ServerCipherInitVector: [[fallthrough]];
		case HLParamID::ClientCipherInitVector:
		{
			ByteString tmp(m_header.size, 0);
			buf.read(reinterpret_cast<char *>(&tmp[0]), m_header.size);
			m_data = tmp;
		}
			break;

		// 16-bit integer
		case HLParamID::UserID: [[fallthrough]];
		case HLParamID::UserIconID: [[fallthrough]];
		case HLParamID::Reference: [[fallthrough]];
		case HLParamID::ChatID: [[fallthrough]];
		case HLParamID::WaitingCount: [[fallthrough]];
		case HLParamID::UserIconChange: [[fallthrough]];
		case HLParamID::Version:
		{
			uint16_t tmp = 0;
			buf.read(reinterpret_cast<char *>(&tmp), 2);
			be::big_to_native_inplace(tmp);
			m_data = tmp;
		}
			break;

		// 32-bit integer
		case HLParamID::TransferSize: [[fallthrough]];
		case HLParamID::FileSize: [[fallthrough]];
		case HLParamID::FileType:
		{
			uint32_t tmp = 0;
			buf.read(reinterpret_cast<char *>(&tmp), 4);
			be::big_to_native_inplace(tmp);
			m_data = tmp;
		}
			break;
		
		// date time
		case HLParamID::FileCreateDate: [[fallthrough]];
		case HLParamID::FileEditDate: [[fallthrough]];
		case HLParamID::NewsArticleDate:
			//m_data = HLDateTime(buf);
			break;
		
		// 16-byte hashes
		case HLParamID::MD5: [[fallthrough]];
		case HLParamID::HAVAL:
		{
			Bytes16 tmp;
			buf.read(reinterpret_cast<char *>(&tmp[0]), 16);
			m_data = tmp;
		}
			break;
		
		// misc.
		case HLParamID::UserAccess:
			m_data = HLUserAccess(buf);
			break;
		case HLParamID::UserFlags:
			m_data = HLSessionFlags(buf);
			break;
		case HLParamID::ChatOptions:
			m_data = HLMessageFlags(buf);
			break;
		case HLParamID::NewsCategoryGUID:
		{
			boost::uuids::uuid tmp;
			buf.read(reinterpret_cast<char *>(&tmp.data), 16);
			m_data = tmp;
		}
			break;
		case HLParamID::SHA1:
		{
			Bytes20 tmp;
			buf.read(reinterpret_cast<char *>(&tmp[0]), 20);
			m_data = tmp;
		}
			break;
		case HLParamID::UserInfo:
			m_data = HLUserInfo(buf);
			break;
		
		// unknown/unsupported
		default:
			m_data = nullptr;
	}
}
	
HLParamID HLParameter::GetID() const
{
	return m_header.type;
}

uint16_t HLParameter::GetSize() const
{
	return m_header.size;
}

const HLParamData& HLParameter::GetData() const
{
	return m_data;
}

HLTransaction::HLTransaction(HLOpcode opcode, uint32_t id, uint32_t error)
{
	m_header.flags = 0;
	m_header.isReply = opcode == HLOpcode::Reply;
	m_header.opcode = opcode;
	m_header.id = id;
	m_header.error = error;
	m_header.chunkSize = m_header.totalSize = 2;
}

HLTransaction::HLTransaction(HLTransactionHeader &header):
	m_header(std::move(header))
{
	FixHeaderEndianness();
}

HLTransaction::HLTransaction(HLTransactionHeader &header, std::istream &buf):
	m_header(std::move(header))
{
	uint16_t numParams;

	buf.read(reinterpret_cast<char *>(&numParams), 2);
	be::big_to_native_inplace(numParams);
	FixHeaderEndianness();

	for (uint16_t i = 0; i < numParams; i++)
	{
		HLParamHeader pHead;
		
		// header
		buf.read(reinterpret_cast<char *>(&pHead), 4);
		pHead.type = static_cast<HLParamID>(be::big_to_native(static_cast<uint16_t>(pHead.type)));
		be::big_to_native_inplace(pHead.size);

		m_params->emplace_back(pHead, buf);
	}
}

bool HLTransaction::IsReply() const
{
	return m_header.isReply;
}

HLOpcode HLTransaction::GetOpcode() const
{
	return m_header.opcode;
}

uint32_t HLTransaction::GetTotalSize() const
{
	return m_header.totalSize;
}

uint16_t HLTransaction::GetParamCount() const
{
	return static_cast<uint16_t>(m_params->size());
}

const HLParameter& HLTransaction::operator[](size_t index) const
{
	return m_params->at(index);
}

void HLTransaction::AddParam(HLParamID type, HLParamData &data)
{
	auto &p = m_params->emplace_back(type, data);
	m_header.chunkSize = m_header.totalSize += 4 + p.GetSize();
}

void HLTransaction::FixHeaderEndianness()
{
	m_header.opcode = static_cast<HLOpcode>(be::big_to_native(static_cast<uint16_t>(m_header.opcode)));
	be::big_to_native_inplace(m_header.id);
	be::big_to_native_inplace(m_header.error);
	be::big_to_native_inplace(m_header.totalSize);
	be::big_to_native_inplace(m_header.chunkSize);
}

std::ostream& operator<<(std::ostream &buf, const HLParameter &param)
{
	HLParamHeader tmp;

	tmp.type = static_cast<HLParamID>(be::native_to_big(static_cast<uint16_t>(param.m_header.type)));
	tmp.size = be::native_to_big(param.m_header.size);

	buf.write(reinterpret_cast<const char *>(&tmp), 4);

	switch (param.m_header.type)
	{
		// strings
		case HLParamID::Error: [[fallthrough]];
		case HLParamID::UserName: [[fallthrough]];
		case HLParamID::UserLogin: [[fallthrough]];
		case HLParamID::UserAlias: [[fallthrough]];
		case HLParamID::ChatTopic: [[fallthrough]];
		case HLParamID::UserAliasChange: [[fallthrough]];
		case HLParamID::ServerAgreement: [[fallthrough]];
		case HLParamID::ServerName: [[fallthrough]];
		case HLParamID::FileName: [[fallthrough]];
		case HLParamID::FileTypeString: [[fallthrough]];
		case HLParamID::FileCreatorString: [[fallthrough]];
		case HLParamID::FileComment: [[fallthrough]];
		case HLParamID::FileNameNew: [[fallthrough]];
		case HLParamID::MessageQuote: [[fallthrough]];
		case HLParamID::AutoReply: [[fallthrough]];
		case HLParamID::NewsCategoryName: [[fallthrough]];
		case HLParamID::NewsArticleDataFlavor: [[fallthrough]];
		case HLParamID::NewsArticleTitle: [[fallthrough]];
		case HLParamID::NewsArticlePoster: [[fallthrough]];
		case HLParamID::ServerCipherAlgorithm: [[fallthrough]];
		case HLParamID::ClientCipherAlgorithm: [[fallthrough]];
		case HLParamID::ServerCipherMode: [[fallthrough]];
		case HLParamID::ClientCipherMode: [[fallthrough]];
		case HLParamID::ServerChecksumAlgorithm: [[fallthrough]];
		case HLParamID::ClientChecksumAlgorithm: [[fallthrough]];
		case HLParamID::ServerCompressionAlgorithm:
			buf << std::get<std::string>(param.m_data);
			break;
		
		// binary
		case HLParamID::Data: [[fallthrough]];
		case HLParamID::UserPassword: [[fallthrough]];
		case HLParamID::NewsArticleData: [[fallthrough]];
		case HLParamID::GIFIcon: [[fallthrough]];
		case HLParamID::SessionKey: [[fallthrough]];
		case HLParamID::ServerCipherInitVector: [[fallthrough]];
		case HLParamID::ClientCipherInitVector:
		{
			std::vector<uint8_t> bin = std::get<ByteString>(param.m_data);
			buf.write(reinterpret_cast<const char *>(&bin[0]), param.m_header.size);
		}
			break;

		// 16-bit integer
		case HLParamID::UserID: [[fallthrough]];
		case HLParamID::UserIconID: [[fallthrough]];
		case HLParamID::Reference: [[fallthrough]];
		case HLParamID::ChatID: [[fallthrough]];
		case HLParamID::WaitingCount: [[fallthrough]];
		case HLParamID::UserIconChange: [[fallthrough]];
		case HLParamID::Version:
		{
			uint16_t u = be::native_to_big(std::get<uint16_t>(param.m_data));
			buf.write(reinterpret_cast<const char *>(&u), 2);
		}
			break;

		// 32-bit integer
		case HLParamID::TransferSize: [[fallthrough]];
		case HLParamID::FileSize: [[fallthrough]];
		case HLParamID::FileType:
		{
			uint32_t u = be::native_to_big(std::get<uint32_t>(param.m_data));
			buf.write(reinterpret_cast<const char *>(&u), 4);
		}
			break;
		
		// date time
		case HLParamID::FileCreateDate: [[fallthrough]];
		case HLParamID::FileEditDate: [[fallthrough]];
		case HLParamID::NewsArticleDate:
			//m_data = HLDateTime(buf);
			break;
		
		// 16-byte hashes
		case HLParamID::MD5: [[fallthrough]];
		case HLParamID::HAVAL:
		{
			Bytes16 b = std::get<Bytes16>(param.m_data);
			buf.write(reinterpret_cast<const char *>(&b[0]), 16);
		}
			break;
		
		// misc.
		case HLParamID::UserAccess:
			buf << std::get<HLUserAccess>(param.m_data);
			break;
		case HLParamID::UserFlags:
			buf << std::get<HLSessionFlags>(param.m_data);
			break;
		case HLParamID::ChatOptions:
			buf << std::get<HLMessageFlags>(param.m_data);
			break;
		case HLParamID::NewsCategoryGUID:
		{
			boost::uuids::uuid guid = std::get<boost::uuids::uuid>(param.m_data);
			buf.write(reinterpret_cast<const char *>(&guid.data), 16);
		}
			break;
		case HLParamID::SHA1:
		{
			Bytes20 b = std::get<Bytes20>(param.m_data);
			buf.write(reinterpret_cast<const char *>(&b[0]), 20);
		}
			break;
		case HLParamID::UserInfo:
			buf << std::get<HLUserInfo>(param.m_data);
			break;
		
		// unknown/unsupported
		[[unlikely]] default: ;
	}
}

std::ostream& operator<<(std::ostream &buf, const HLTransaction &trans)
{
	HLTransactionHeader tmp;

	tmp.opcode = static_cast<HLOpcode>(be::native_to_big(static_cast<uint16_t>(trans.m_header.opcode)));
	tmp.id = be::native_to_big(trans.m_header.id);
	tmp.error = be::native_to_big(trans.m_header.error);
	tmp.totalSize = be::native_to_big(trans.m_header.totalSize);
	tmp.chunkSize = be::native_to_big(trans.m_header.chunkSize);
	uint16_t numParams = be::native_to_big(trans.GetParamCount());

	buf.write(reinterpret_cast<const char *>(&tmp), 20);
	buf.write(reinterpret_cast<const char *>(&numParams), 2);
	for (auto &p : *trans.m_params) buf << p;

	return buf;
}
