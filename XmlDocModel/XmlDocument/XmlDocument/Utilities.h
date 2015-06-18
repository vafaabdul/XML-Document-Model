#ifndef UTILITIES_H
#define UTILITIES_H
///////////////////////////////////////////////////////////////////
// Utilities.h - a class for detecting XML elements              //
// Ver 1.0                                                       //
// Application: CSE687 Pr#2, Spring 2015                         //
// Platform:    Hp Pavillion g6, Win 7 Pro, Visual Studio 2013   //
// Author:      Abdulvafa Choudhary,SUID:671290061               //
//              aachoudh@syr.edu                                 //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to to be used to determine what is the type of the  
* XML element.It detects wheteher the XMl part provided is starting tag,ending tag,comment element,
* Text element,preprocessing instruction or Xml declaration element.It also provides faciltiy to 
* perform operations on a string
*
* Required Files:
* ---------------
*	  Utilities.h, Utilities.cpp
*
* Build Process:
* --------------
*   devenv XmlDocument.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1.0 : 20 Mar 15
* - first release
*
*/

#include <string>
#include <vector>

namespace XmlProcessing{
	
	class XMLUtility{

	public:
		static std::string getCommentText(const std::string& part);         //returns the text part of the comment element
		static std::string trim_front_whitepsaces(const std::string& val);  //removes the leading spaces from the string
		static std::string trim_end_whitespaces(const std::string& val);	//removes the trailing spaces from the string
		static std::vector<std::string> split(const std::string& str, const std::string& delimeter); //splits the given string based on the delimeter
		static bool isStartTag(const std::string& part);					//detects the start tag
		static bool isEndTag(const std::string & part);						//detects end tag	
		static bool isCommentElement(const std::string & part);				//detects the comment element
		static bool isXMLDeclaration(const std::string& part);				//detects the declaration element
		static bool isProcInstrElement(const std::string& part);			//detects the processing instruction element
		static std::string getEncoding(const std::string& part);			//retuns the encoding value for the xml declartion
	};
}
#endif 