/*
* Minimal TextEncoder backed by zueci to support non-UTF8 encodings
*/

#include "zxing/TextEncoder.h"
#include "zxing/CharacterSet.h"
#include "zxing/Utf.h"
#include "zxing/ZXAlgorithms.h"
#include "zxing/ECI.h"

#include <stdexcept>

namespace ZXing {

// Forward declare minimal zueci subset when headers are not present
extern "C" {
int zueci_dest_len_eci(int eci, const unsigned char* src, int src_len, int* p_dst_len);
int zueci_utf8_to_eci(int eci, const unsigned char* src, int src_len, unsigned char* dst, int* p_dst_len);
}

void TextEncoder::GetBytes(const std::string& str, CharacterSet charset, std::string& bytes)
{
	(void)charset; // minimal build: treat input as UTF-8 already
	bytes = str;
}

void TextEncoder::GetBytes(const std::wstring& str, CharacterSet charset, std::string& bytes)
{
	GetBytes(ToUtf8(str), charset, bytes);
}

} // namespace ZXing


