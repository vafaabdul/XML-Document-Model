#ifndef DISPLAY_H
#define DISPLAY_H
///////////////////////////////////////////////////////////////////////////////
// Display.h -    Shows results  of the XML Document Operations              //
// version 1.0                                                               //
// Application:   Project #2, CSE687 - Object Oriented Design, Spring 2015   //
// Platform:      HP Pavillion g6, Win 7 Pro, Visual Studio 2013             //
// Author:        Abdulvafa Choudhary, SUID :671290061				         //
//                aachoudh@syr.edu                                           //
///////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* - Demonstrates the functionality of XML Document class.
* - Displays the internal tree reprsentation.
* - Displays elements found based on tag name and id.
* - Demonstrates adding and removing child element to the XML document.
* - Demonstrates adding and removing attribute to the XML element.
* - Displays the attributes of a given element.
* - Adds root to an empty Document Tree.
*
*
* Required Files:
* ---------------
* Tokenizer.h, Tokenizer.cpp, XmlDocument.h, XmlDocument.cpp, Display.h
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
#include <memory>

class Display{

public:
	Display::Display(XmlProcessing::XmlDocument& doc);
	void demoTreeRep();
	void demoElemById();
	void demoElemByTag();
	void demoAddChild();
	void demoRemoveChild();
	void demoAddRoot();
	void demoChildElem();
	void demoFindAttribs();
	void demoAddAttrib();
	void demoRemoveAttrib();
	void demoWriteXML();
	void demoMoveOperations();

private:
	XmlProcessing::XmlDocument& doc_;
};

#endif