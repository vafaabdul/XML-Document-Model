#include "Executive.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// Executive.cpp - Entry point for Project #2 Demo                           //
// version 1.0                                                               //
// Application:   Project #2, CSE687 - Object Oriented Design, Spring 2015   //
// Platform:      HP Pavillion g6, Win 7 Pro, Visual Studio 2013             //
// Author:        Abdulvafa Choudhary, SUID :671290061				         //
//                aachoudh@syr.edu                                           //
///////////////////////////////////////////////////////////////////////////////


Executive::Executive(int argc,char** argv)
{

	using srcType=XmlProcessing::XmlDocument::sourceType ;

	if (argc <2){

		std::shared_ptr<XmlProcessing::AbstractXmlElement> root = XmlProcessing::makeTaggedElement("OSes");
		std::shared_ptr<XmlProcessing::AbstractXmlElement> child = XmlProcessing::makeTaggedElement("OS");
		child->addAttrib("name","Micrsoft-Windows-8.1");
		root->addChild(child);
		pDoc = std::unique_ptr<XmlProcessing::XmlDocument>(new XmlProcessing::XmlDocument(root));
	}
	else {


		if (argv[1][0] == '/' && argv[1][1]=='f'){

			pDoc = std::unique_ptr<XmlProcessing::XmlDocument>(new XmlProcessing::XmlDocument(argv[2], srcType::filename));
		}

		else if (argv[1][0] == '/' && argv[1][1] == 's')
		{
			pDoc = std::unique_ptr<XmlProcessing::XmlDocument>(new XmlProcessing::XmlDocument(argv[2], srcType::string));
		}

	}

	pDisplay = std::unique_ptr<Display>(new Display(*pDoc));
}

//demonstrates the requirements
void Executive::processCommands(int argc){

	try{

		if (argc < 2){

			pDoc->print();
			std::cout << "\n";
		}
		else
		{

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

			pDisplay->demoMoveOperations();
		}
	}

	catch (std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
	}
}

//
//----< starting point >--------------------------------------------

int main(int argc, char** argv){

	
		Executive exec(argc, argv);
		exec.processCommands(argc);
		std::cout << "\n";
		system("pause");

}