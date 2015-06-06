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