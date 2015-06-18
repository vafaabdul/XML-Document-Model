///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes             //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
// Modified By: Abdulvafa Choudhary, SUID : 671290061            //
//              aachoudh@syr.edu                                 //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include "XmlDocument.h"
#include "../../XmlElementParts/XmlElementParts/Tokenizer.h"
#include "../../XmlElementParts/XmlElementParts/xmlElementParts.h"
#include <stack>
#include "Utilities.h"
#include <fstream>


using namespace XmlProcessing;

//constructor for creating XML documnt when provided with the root node
XmlProcessing::XmlDocument::XmlDocument(sPtr root){

	if (pDocElement_ == nullptr){

		std::shared_ptr<AbstractXmlElement> pDecl = makeXmlDeclarElement();
		pDecl->addAttrib("version", "1.0");
		pDocElement_ = XmlProcessing::makeDocElement(pDecl);
		pDocElement_->addChild(root);
	}
}
//------< move constructor >--------
XmlProcessing::XmlDocument::XmlDocument(XmlDocument && pdoc)
	: pDocElement_(std::move(pdoc.pDocElement_)), found_(std::move(pdoc.found_)){
	std::cout << "\nInside Move Constructor\n";
	pdoc.pDocElement_ = nullptr;
	pdoc.found_.clear();
	std::cout << "\nMove successful...\n";
};

//------< move Assignment operator >-------
XmlDocument& XmlDocument::operator=(XmlDocument&& pdoc){

	if (this == &pdoc) return *this;
	std::cout << "\nInside Move Assignment operation\n";
	pDocElement_ = pdoc.pDocElement_;
	pdoc.pDocElement_ = nullptr;
	found_.clear();
	std::cout << "\nMove successful...\n";
	return *this;
};

//constructor of the XML Documnet class.Constructs the parse tree from a given xml string or file
XmlProcessing::XmlDocument::XmlDocument(const std::string& src, sourceType srcType)
{
	Toker* toker;
 
	if (srcType==string)
	{
		toker=new Toker(src,false);
		toker->setMode(Toker::xml);
	}
	else{
		toker=new Toker(src);
		toker->setMode(Toker::xml);
	}
	
	XmlParts parts(toker);
	std::stack<XmlDocument::sPtr> s1;
	
	while (parts.get()){
	
		std::string part= parts.show();

		if (XmlProcessing::XMLUtility::isXMLDeclaration(part)){

			if (pDocElement_ == nullptr)
			pDocElement_ = XmlProcessing::makeDocElement();

			std::vector<std::string> vec = XmlProcessing::XMLUtility::split(part, " ");
			std::vector<std::pair<std::string, std::string>> attrbs;
			std::pair<std::string, std::string> attrib;

			for (size_t i = 0; i < vec.size(); i++){

				if (vec[i]=="="){

					std::string first = vec[i - 1];
					vec[i - 1] = "*";
					std::string second = vec[i + 1];
					vec[i + 1] = "*";
					vec[i] = "*";
					second.erase(0, 1);
					second.erase(second.length() - 1, 1);
					attrib= std::make_pair(first,second);
					attrbs.push_back(attrib);
				}

				
			}

			std::string typeName = "";

			for (auto str:vec)
			{
		       if (!(str == "?" || str == "<" || str == ">" || str=="*"))
		       {
			     typeName=typeName+str;
		       }
			
			}
			
			XmlDocument::sPtr declElem = XmlProcessing::makeProcInstrElement(typeName);
			
			for (auto att : attrbs){
				declElem->addAttrib(att.first, att.second);
			}

			pDocElement_->addChild(declElem);
		}
		else if (XmlProcessing::XMLUtility::isCommentElement(part)){

			std::string comment = XmlProcessing::XMLUtility::getCommentText(part);
			XmlDocument::sPtr commElem = XmlProcessing::makeCommentElement(comment);
			
			if (pDocElement_ != nullptr && s1.empty())
				pDocElement_->addChild(commElem);

			else
				s1.top()->addChild(commElem);
		}
		else{
			if (XmlProcessing::XMLUtility::isStartTag(part) && XmlProcessing::XMLUtility::isEndTag(part)){

				std::vector<std::string> myTokens = XmlProcessing::XMLUtility::split(part, " ");
				XmlDocument::sPtr taggedElem = XmlProcessing::makeTaggedElement(myTokens[1]);

				if (myTokens.size() > 4){

					for (size_t i = 2; i < myTokens.size() - 1; i = i + 3)
					{
						std::string val = myTokens[i + 2];
						val.erase(0, 1);
						val.erase(val.length() - 1, 1);

						taggedElem->addAttrib(myTokens[i], val);
					}

				}

				if (!s1.empty()){

					XmlDocument::sPtr elem = s1.top();
					elem->addChild(taggedElem);
				}

			}
			else if (XmlProcessing::XMLUtility::isStartTag(part)){

				std::vector<std::string> myTokens = XmlProcessing::XMLUtility::split(part, " ");
				XmlDocument::sPtr taggedElem = XmlProcessing::makeTaggedElement(myTokens[1]);

				if (myTokens.size() > 3){

					for (size_t i = 2; i < myTokens.size()-1;i=i+3)
					{
						std::string val = myTokens[i + 2];
						val.erase(0, 1);
						val.erase(val.length() - 1, 1);

						taggedElem->addAttrib(myTokens[i],val);
					}

				}

				if (!s1.empty()){

					XmlDocument::sPtr elem = s1.top();
					elem->addChild(taggedElem);	
				}

				s1.push(taggedElem);
			}
			else if (XmlProcessing::XMLUtility::isEndTag(part)){
				if (s1.size() == 1){

					XmlDocument::sPtr root = s1.top();

					if (pDocElement_ !=nullptr)
					pDocElement_->addChild(root);
				}
				s1.pop();
			}
			else{
				XmlDocument::sPtr textElem = XmlProcessing::makeTextElement(part);
				XmlDocument::sPtr elem=s1.top();
				elem->addChild(textElem);
			}
		}
	}
	
	//delete toker;
	//std::cout << pDocElement_->toString() << std::endl;
}


//find the elements  which matches the tag
bool XmlProcessing::XmlDocument::find(const std::string& tag, sPtr pElem, bool findall)
{
	if (pElem->getTag() == tag || tag=="")
	{
		found_.push_back(pElem);
		if (!findall)
			return true;
	}
	for (auto pChild : pElem->getChildren())
		find(tag, pChild,findall);
	return (found_.size() > 0);
}


//find the elements by the name of the attribute
bool XmlProcessing::XmlDocument::findById(const std::string& id, XmlProcessing::XmlDocument::sPtr pElem){

	for(auto attrib : pElem->getAttrib()){

		if (attrib.first == id)
		{
			found_.push_back(pElem);
			return true;
		}
	}

	for (auto pChild : pElem->getChildren())
		findById(id, pChild);

	return (found_.size() > 0);
}


//fetches element matching the given attribute name
XmlProcessing::XmlDocument::sPtr XmlProcessing::XmlDocument::elementById(const std::string& id)
{
	found_.clear();
	if (findById(id, pDocElement_)){
     
		sPtr pElem = found_[0];
		found_.clear();
		return pElem;
	}
	
	return nullptr;
}

//fetches a element which matches the given tag
XmlDocument& XmlProcessing::XmlDocument::element(const std::string& tag){

	found_.clear();
	find(tag,pDocElement_,false);

	if (found_.size() > 1){

		sPtr pElem = found_[0];
		found_.clear();
		found_.push_back(pElem);
	}
	
	return *this;
}

//fetches the elements matching the tag
XmlDocument& XmlProcessing::XmlDocument::elements(const std::string& tag){

	found_.clear();
	find(tag, pDocElement_, true);
	return *this;
}

//returns the results found
std::vector<XmlProcessing::XmlDocument::sPtr> XmlProcessing::XmlDocument::select(){

	return std::move(found_);
}

//fetches the descendants of the element matching the tag
XmlDocument& XmlProcessing::XmlDocument::descendents(const std::string& tag)
{
	if (found_.size() == 0)
		found_.push_back(pDocElement_);
	sPtr pElem = found_[0];
	found_.clear();
	for (auto pChild : pElem->getChildren())
		find(tag, pChild, true);
	return *this;
}

//fetches the chidlren of the element
XmlDocument& XmlProcessing::XmlDocument::children(const std::string& tag)
{
	if (found_.size() == 0)
		return *this;
	sPtr pElem = found_[0];
	found_.clear();
	for (auto pChild : pElem->getChildren())
		found_.push_back(pChild);
	return *this;
}

//add child to a XML element
bool XmlProcessing::XmlDocument::addChild(sPtr child){

	if (found_.size() == 0)
		return false;
	sPtr pElem = found_[0];
	found_.clear();
	return pElem->addChild(child);

}

//remove child from an XML element
bool XmlProcessing::XmlDocument::removeChild(sPtr child){

	if (found_.size() == 0)
		return false;
	sPtr pElem = found_[0];
	found_.clear();
	return pElem->removeChild(child);
}

//add attrib
bool XmlProcessing::XmlDocument::addAttrib(const std::string& name, const std::string& value){

	if (found_.size() == 0)
		//found_.push_back(pDocElement_);
		return false;
	sPtr pElem = found_[0];
	found_.clear();
	return pElem->addAttrib(name, value);
}

//remove attrib
bool XmlProcessing::XmlDocument::removeAttrib(const std::string& name){

	if (found_.size() == 0)
		//found_.push_back(pDocElement_);
		return false;
	sPtr pElem = found_[0];
	found_.clear();
	return pElem->removeAttrib(name);
}

//returns the attributes of a particular element
std::vector<std::pair<std::string, std::string>> XmlProcessing::XmlDocument::getAttributes(){

	std::vector<std::pair<std::string, std::string>> result;
	if (found_.size() == 0)
		return result;
	sPtr pElem = found_[0];
	return pElem->getAttrib();

}

//creates an xml file
void XmlProcessing::XmlDocument::save(const std::string& fileName){

	try{
		std::ofstream myfile;
		myfile.open("..//..//"+fileName);
		myfile << pDocElement_->toString();
		myfile.close();
		
	}
	catch (std::exception ex)
	{
		std::cout << "\n";
		std::cout << "!!! XML write failed  !!! " << std::endl;
		std::cout << "\n  " << ex.what() << "\n\n";
	}
}

//prints the built parse tree
void XmlProcessing::XmlDocument::print(){

	std::cout << pDocElement_->toString()<<"\n ";
}

//adds root to the document if root is not prsent
bool XmlProcessing::XmlDocument::addRoot(sPtr root){

	bool isRootPresent = false;

	if (pDocElement_){

		for(auto child :pDocElement_->getChildren()){

			std::shared_ptr<TaggedElement> sp1 =
				std::dynamic_pointer_cast<TaggedElement>(child);

			if (sp1)
				isRootPresent = true;
		}

		if (root)
		 return pDocElement_->addChild(root);
	}

	else
	{
		pDocElement_ = XmlProcessing::makeDocElement(root);
		std::shared_ptr<AbstractXmlElement> pDecl = makeXmlDeclarElement();
		pDecl->addAttrib("version", "1.0");

		if (root)
		 return pDocElement_->addChild(pDecl);
	}

	return false;
}

//
//----< test stub >--------------------------------------------

#ifdef TEST_XMLDOCUMENT

int main()
{
  title("Testing XmlDocument class");

  try{

	  XmlDocument doc("LectureNote.xml");
	  std::vector<std::shared_ptr<AbstractXmlElement>> vec=doc.children().select();
	  std::vector<std::shared_ptr<AbstractXmlElement>> vecs = doc.elements("LectureNote").children().select();

	  for ( auto child :vec)
	  {
		  std::cout<<child->toString()<<std::endl;
	  }

	  std::cout << "testing functions"<< std::endl;
	  XmlDocument::sPtr myPtr = doc.elementById("Company");
	  if (myPtr){
		 std::cout<< myPtr->toString();
	  }
	 
  }
  catch (std::exception ex)
  {
	  std::cout << "\n  " << ex.what() << "\n\n";
  }

  std::cout << "\n\n";

}

#endif