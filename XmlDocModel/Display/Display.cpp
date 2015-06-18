#include "Display.h"
#include <iostream>
#include "../XmlDocument/XmlElement/XmlElement.h"


Display::Display(XmlProcessing::XmlDocument& doc) : doc_(doc){}

void title(const std::string& title, char underline)
{
	std::cout << "\n  " << title;
	std::cout << "\n " << std::string(title.size() + 2, underline);
}

void Display::demoTreeRep(){

	title("PARSE TREE REPRESNTATION",'=');
	doc_.print();
}

void Display::demoAddRoot(){

	title("ADDING ROOT ELEMENT", '=');
	std::shared_ptr<XmlProcessing::AbstractXmlElement> root=XmlProcessing::makeTaggedElement("Root");
	bool added=doc_.addRoot(root);
    
	if (added){

		std::cout << "Addded Root element "<<std::endl;
	}

	else
	{
		std::cout << "\n";
		std::cout << "!!! Cannot add root element to the document !!!" << std::endl;
	}
}

void Display::demoElemById(){

	title("FINDING ELEMENT BASED ON ID ATTRIBUTE 'Company'", '=');

	std::shared_ptr<XmlProcessing::AbstractXmlElement> elem;
	elem=doc_.elementById("Company");

	if (elem != nullptr){

		std::cout << elem->toString() << std::endl;
	}

	else
	{
		std::cout << "\n";
		std::cout << "!!! No element with given id found  !!! "<<std::endl;
	}
}


void Display::demoElemByTag(){

	title("FINDING ELEMENT BASED ON TAG 'title'", '=');


	bool found = false;
	for (auto elem : doc_.elements("title").select()){

		std::cout << elem->toString() << std::endl;
		found = true;
	}
	if (!found){
		std::cout << "\n";

		std::cout << "!!! No element with given tag found  !!! " << std::endl;
	}
}

void Display::demoAddChild(){

	title("ADDING CHILD ELEMENT", '=');

	std::shared_ptr<XmlProcessing::AbstractXmlElement> child = XmlProcessing::makeTaggedElement("child");
    std::shared_ptr<XmlProcessing::AbstractXmlElement> grandChild = XmlProcessing::makeTextElement("Child Added");
	child->addChild(grandChild);

	bool added=doc_.element("reference").addChild(child);

	if (added){

		title("Tree after adding new child element to 'reference' tag", '-');
		doc_.print();

	}
	else
	{
		std::cout << "\n";
		std::cout << "!!! Child element cannot be added  !!! " << std::endl;

	}

}
void Display::demoRemoveChild(){

	title("REMOVING CHILD ELEMENT", '=');

	std::shared_ptr<XmlProcessing::AbstractXmlElement> child=nullptr;
	if (doc_.element("child").select().size() != 0){
		
		child=doc_.element("child").select().at(0);
	}

	bool removed = doc_.element("reference").removeChild(child);

	if (removed){

		title("XML parse tree after removing child element", '-');
		doc_.print();

	}
	else
	{
		std::cout << "\n";
		std::cout << "!!! Child element cannot be removed  !!! " << std::endl;

	}
}

void Display::demoChildElem(){

	title("FINDING CHILD ELEMENTS OF 'reference' TAG ", '=');

	bool found = false;
	for (auto elem : doc_.element("reference").children().select()){

		std::cout << elem->toString() << std::endl;
		found = true;
	}
	if (!found){

		std::cout << "\n";
		std::cout << "!!! No children found !!! " << std::endl;

	}

}
void Display::demoFindAttribs(){

	title("FINDING ATTRIBUTES OF 'LectureNote' TAG", '=');

	std::vector<std::pair<std::string,std::string>> attrbs=doc_.element("LectureNote").getAttributes();

	if (attrbs.size() == 0){

		std::cout << "\n";
		std::cout << "!!! No attributes found !!! " << std::endl;
	}
	else
	{
		title("Attributes", '-');

		for (auto attrb : attrbs){

			std::cout<<"\n";
			std::cout << " Name : " + attrb.first + "  ";
			std::cout << "Value : " + attrb.second ;
			
		}
		std::cout << "\n";

	}
}

void Display::demoAddAttrib(){

	title("ADDING ATTRIBUTE 'DemoAttrib = Added' to reference tag", '=');

	bool added = doc_.element("reference").addAttrib("DemoAttrib", "Added");
	if (added){

		title("XML Parse Tree after Adding Attribute", '-');
		doc_.print();
	}
	else
	{
		std::cout << "\n";
		std::cout << "!!! Attribute cannot be added  !!! " << std::endl;

	}
}
void Display::demoRemoveAttrib(){

	title("REMOVING ATTRIBUTE 'DemoAttrib' FROM 'reference' TAG", '=');


	bool removed = doc_.element("reference").removeAttrib("DemoAttrib");
	if (removed){

		title("XML Parse tree after remving attribute ",'-');
		doc_.print();
	}
	else
	{
		std::cout << "\n";
		std::cout << "!!! Attribute cannot be removed  !!! " << std::endl;

	}
}
void Display::demoWriteXML(){

	title("SAVING XML TREE TO A FILE", '=');

	std::string path;
	doc_.save("MyXmlFile.xml");
	std::cout << "\n MyXmlFile.xml created in the Project2 directory"<<std::endl;
}

void Display::demoMoveOperations(){

	title("Calling Move Assignment", '=');
	XmlProcessing::XmlDocument doc = std::move(doc_);
	title("Calling Move Constructor", '=');
	XmlProcessing::XmlDocument doc1 = std::move(doc);

}


//
//----< test stub >--------------------------------------------

#ifdef TEST_DISPLAY

int main(){
	
	std::string inputXmlString = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\
								 <!-- Operating Systems -->\
								 <!-- Microsoft -->\
								 <OSes>\
								 <OS name=\"Microsoft-Windows-8.1\">\
								 <SetupLanguage>\
								 <UILang>IN</UILang>\
								 <ShowUI>OnError</ShowUI>\
								 </SetupLanguage>\
								 <SysLocale>US</SysLocale>\
								 <UserLocale>IN</UserLocale>\
								 </OS>\
								 </OSes>";
	using srcType = XmlProcessing::XmlDocument::sourceType;
	XmlProcessing::XmlDocument *pDoc = new XmlProcessing::XmlDocument(inputXmlString, srcType::string);
	Display* pDisplay = new Display(*pDoc);

	pDisplay->demoTreeRep();

	pDisplay->demoElemById();

	pDisplay->demoElemByTag();

	pDisplay->demoAddChild();

	pDisplay->demoRemoveChild();

	pDisplay->demoAddRoot();

	pDisplay->demoChildElem();

	pDisplay->demoFindAttribs();

	pDisplay->demoAddAttrib();

	pDisplay->demoRemoveAttrib();

	pDisplay->demoWriteXML();

	return 0;
}
#endif