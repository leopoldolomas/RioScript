//--------------------------------------------------------------- @License begins
// 2015 Leopoldo Lomas Flores. Torreon, Coahuila. MEXICO
// leopoldolomas [at] gmail
// www.leolomas.com
// 
// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
// software, either in source code form or as a compiled binary, for any purpose,
// commercial or non-commercial, and by any means.
// 
// In jurisdictions that recognize copyright laws, the author or authors of this
// software dedicate any and all copyright interest in the software to the public
// domain. We make this dedication for the benefit of the public at large and to
// the detriment of our heirs and successors. We intend this dedication to be
// an overt act of relinquishment in perpetuity of all present and future
// rights to this software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//--------------------------------------------------------------- @License ends

#ifndef _HELPERFUNCS_HPP_
#define _HELPERFUNCS_HPP_

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>

//-----------------------------------------------------------------------------

static inline std::string& leftTrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

//-----------------------------------------------------------------------------

static inline std::string& rightTrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

//-----------------------------------------------------------------------------

static inline std::string& trim(std::string &s) {
	return leftTrim(rightTrim(s));
}

//-----------------------------------------------------------------------------

static inline std::string& replaceChar(std::string& s, char original, char replace_with) {
	std::replace(s.begin(), s.end(), original, replace_with);
	return s;
}

//-----------------------------------------------------------------------------

static inline std::string& replaceSubstring(
	std::string& s, 
	const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = s.find(search, pos)) != std::string::npos) {
		s.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return s;
}

//-----------------------------------------------------------------------------

static inline bool bothAreSpaces(char left_char, char right_char) {
	return (left_char == right_char) && (left_char == ' ');
}

//-----------------------------------------------------------------------------

static inline std::string& removeDuplicateSpaces(std::string& s) {
	std::string::iterator new_end = std::unique(s.begin(), s.end(), bothAreSpaces);
	s.erase(new_end, s.end());
	return s;
}

#endif _HELPERFUNCS_HPP_