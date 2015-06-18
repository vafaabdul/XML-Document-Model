#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
// Modified By: Abdulvafa Choudhary,SUID:671290061               //
//              aachoudh@syr.edu                                 //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to help students in CSE687 - Object Oriented Design
* get started with Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with 
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*
* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp, 
*     XmlElement.h, XmlElement.cpp
*     Tokenizer.h, Tokenizer.cpp
*	  Utilities.h, Utilities.cpp
*     xmlElementParts.h,xmlElementParts.cpp     
*
* Build Process:
* --------------
*   devenv XmlDocument.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.3 : 17 Mar 15 
* - added the functionalities for XML Document model
* ver 1.2 : 21 Feb 15
* - modified these comments
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
*
*/

#include <memory>
#include <string>
#include "../XmlElement/XmlElement.h"

namespace XmlProcessing
{
  class XmlDocument
  {
  public:
	  using sPtr = std::shared_ptr < XmlProcessing::AbstractXmlElement >;

    enum sourceType { string, filename };

    XmlDocument(const std::string& src, sourceType srcType=string);
	XmlDocument(sPtr root);
	XmlDocument(XmlDocument && pdoc);
	XmlDocument& operator=(XmlDocument&& pdoc);
	
    // queries return XmlDocument references so they can be chained, e.g., doc.element("foobar").descendents();
	bool find(const std::string& tag, sPtr pElem, bool findall);
	bool findById(const std::string& tag, sPtr pElem);
    XmlDocument& element(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
    XmlDocument& elements(const std::string& tag);          // found_ contains all elements with tag
    XmlDocument& children(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
    XmlDocument& descendents(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
    std::vector<sPtr> select();								// return reference to found_.  Use std::move(found_) to clear found_
	bool addChild(sPtr child);								//returns true if  new child is added
	bool removeChild(sPtr child);							//returns true if child element is removed
	bool addAttrib(const std::string& name,const std::string& value);	//reruns true if attribute is added
	bool removeAttrib(const std::string& name);							//returns true if the attribute is removed
	std::vector<std::pair<std::string, std::string>> getAttributes();	//returns a vector containing the attributes of the element
	sPtr elementById(const std::string& id);						 //returns a pointer to element maching the given id
	void save(const std::string& fileName);							//writes the document object to an xml file
	void print();													//prints the tree structure
	bool addRoot(sPtr root);										//add root element to the document


  private:
    sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
    std::vector<sPtr> found_;  // query results
  };
}
#endif
