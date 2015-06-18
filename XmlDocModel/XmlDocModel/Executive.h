#ifndef EXECUTIVE_H
#define EXECUTIVE_H

///////////////////////////////////////////////////////////////////////////////
// Executive.h - Entry point for Project #2 Demo                             //
// version 1.0                                                               //
// Application:   Project #2, CSE687 - Object Oriented Design, Spring 2015   //
// Platform:      HP Pavillion g6, Win 7 Pro, Visual Studio 2013             //
// Author:        Abdulvafa Choudhary, SUID :671290061				         //
//                aachoudh@syr.edu                                           //
///////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* - Builds an XMlDocument from a XMl string or XML file provided.
* - Displays the internal tree reprsentation.
* - Finds elements based on tag name and id.
* - Adds and removes child element to the XML document.
* - Adds and removes attribute to the XML element.
* - Displays the attrbutes of a given element.
* - Adds root to an empty Document Tree.
*
*
* Required Files:
* ---------------
* Executive.h, Tokenizer.h, Tokenizer.cpp, XmlDocument.h, XmlDocument.cpp, Display.h, Display.cpp,
* xmlElementParts.h, xmlElementParts.cpp, XmlElement.h, XmlElement.cpp, Utilities.h, Utilities.cpp
*
* Build Process:
* --------------
* devenv XmlDocModel.sln /debug rebuild
*
* Maintenance History:
* --------------------
* - Ver 1 : 21 Mar 2015
*   first release
*/

#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../Display/Display.h"
#include <memory>

class Executive{

public :
	Executive(int argc, char** argv);
	Executive(const Executive& ex) = delete;
	Executive& operator=(const Executive& ex) = delete;
	void processCommands(int argc);
private:
	std::unique_ptr<XmlProcessing::XmlDocument> pDoc;
	std::unique_ptr<Display> pDisplay;
};

#endif
