echo off
cls
echo Demonstrating Xml Document Model with File
echo ------------------------------------------ 
cd ./XmlDocModel/Debug 
XmlDocModel /f ../../LectureNote.xml
cd ../../
cls
echo Demonstrating Xml Document Model with String
echo ------------------------------------------ 
cd ./XmlDocModel/Debug 
XmlDocModel /s "<?xml version=\"1.0\" encoding=\"utf-8\"?><?xml-stylesheet type=\"text/css\" href=\"style.css\"?><!-- XML test case --><LectureNote course=\"CSE681\"><title>XML Example #1</title><reference><title>Programming Microsoft .Net</title><author>Jeff Prosise <note Company=\"Wintellect\"></note></author><publisher>Microsoft Press</publisher><date>2002</date><page>608</page></reference><comment>Description of PCDATA</comment></LectureNote>"
cd ../../
cls
echo Demonstrating Xml Document Model by Programmatically adding Root
echo ------------------------------------------------------------- 
cd ./XmlDocModel/Debug 
XmlDocModel
