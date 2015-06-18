#include "Utilities.h"
#include <iostream>
///////////////////////////////////////////////////////////////////
// Utilities.cpp - a class for detecting XML elements            //
// Ver 1.0                                                       //
// Application: CSE687 Pr#2, Spring 2015                         //
// Platform:    Hp Pavillion g6, Win 7 Pro, Visual Studio 2013   //
// Author:      Abdulvafa Choudhary,SUID:671290061               //
//              aachoudh@syr.edu                                 //
///////////////////////////////////////////////////////////////////

using namespace XmlProcessing;

//get the text from the comment element
std::string XMLUtility::getCommentText(const std::string& part){

	std::string str;
	std::size_t first = part.find_first_of("--");
	std::size_t last = part.find_last_of("--");
	if (first != std::string::npos && last != std::string::npos){

		str = part.substr(first + 2, last - first - 3);
	}

	return str;
}

//splits the string
std::vector<std::string> XMLUtility::split(const std::string& str, const std::string& delimeter){

	std::string part = trim_front_whitepsaces(str);
	part = trim_end_whitespaces(part);

	std::vector<std::string> vec;
	size_t found = part.find(delimeter);
	size_t pos = 0;
	while (found != std::string::npos){

		vec.push_back(part.substr(pos, found - pos));
		pos = found + 1;
		found = part.find(delimeter, pos);
	}
	vec.push_back(part.substr(pos, part.length() - pos));

	return vec;
}

//returns the value of encoding attribute in the  xml dalcaration element
std::string XMLUtility::getEncoding(const std::string& part){

	std::vector<std::string> myTokens = split(part, " ");
	for (size_t i = 0; i < myTokens.size(); i++){

		if (myTokens[i] == "encoding"){

			std::string val = myTokens[i + 2];
			val.erase(0, 1);
			val.erase(val.length() - 1, 1);
			return val;
		}
	}

	return "";
}

//remoe the whitespaces from front of the string
std::string XMLUtility::trim_front_whitepsaces(const std::string& val){

	std::string str = val;
	std::string whitespaces(" \t\f\v\n\r");
	std::size_t found = str.find_last_not_of(whitespaces);

	if (found != std::string::npos)
		str.erase(found + 1);
	else
		str.clear();

	return str;
}

//remove the whitespaces from the end o the string
std::string XMLUtility::trim_end_whitespaces(const std::string& val){

	std::string str = val;
	std::string whitespaces(" \t\f\v\n\r");
	std::size_t found = str.find_first_not_of(whitespaces);
	if (found != std::string::npos)
		str.erase(0, found);
	else
		str.clear();

	return str;
}

//checks whether the xml part is a start of a tag
bool XMLUtility::isStartTag(const std::string& part){

	std::size_t found = part.find("<");
	if (found != std::string::npos){

		found = part.find("/", found + 1);
		if (found == std::string::npos)
			return true;
	}

	return false;
}

// checks whether the part is an ending tag
bool XMLUtility::isEndTag(const std::string & part){

	std::size_t found = part.find("< /");
	if (found != std::string::npos){

		return true;
	}

	return false;
}

//checks wheteher the xml part is a comment element
bool XMLUtility::isCommentElement(const std::string & part){

	std::size_t found = part.find("! --");
	if (found != std::string::npos){

		return true;
	}

	return false;
}

//checks whether the xml part is an declaration element
bool XMLUtility::isXMLDeclaration(const std::string& part){

	std::size_t found = part.find("?");
	if (found != std::string::npos){

			return true;
	}

	return false;

}

//check for processing instruction element
bool XMLUtility::isProcInstrElement(const std::string& part){

	std::size_t found = part.find("?");
	if (found != std::string::npos){
		found = part.find("xml", found + 1);
		if (found != std::string::npos)
			return true;
	}
	return false;

}