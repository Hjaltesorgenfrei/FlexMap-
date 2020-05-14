#include "Parser.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
using namespace xercesc;



int ParseThatShit() {
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n"
            << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    char* xmlFile = (char*)"lejr.osm";
    SAXParser* parser = new SAXParser();
    parser->setDoNamespaces(true);    // optional

    OSMHandler* docHandler = new OSMHandler();
    ErrorHandler* errHandler = (ErrorHandler*)docHandler;
    parser->setDocumentHandler(docHandler);
    parser->setErrorHandler(errHandler);

    try {
        parser->parse(xmlFile);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (...) {
        std::cout << "Unexpected Exception \n";
        return -1;
    }
    for (auto k : docHandler->count) {
        std::cout << XMLString::transcode(k.first) << ":" << k.second << "\n";
    }
    delete parser;
    delete docHandler;
    return 0;
}


void OSMHandler::startElement(const XMLCh* const name,
    AttributeList& attributes)
{
    char* message = XMLString::transcode(name);
    //std::cout << "I saw element: " << message << "\n";
    for (unsigned int i = 0; i < attributes.getLength(); i++){
        count[attributes.getName(i)]++;
        //std::cout << "    " << attributes.getName(i) << ":" << attributes.getValue(i) << "\n";
    }
    XMLString::release(&message);
}

void OSMHandler::fatalError(const SAXParseException& exception)
{
    char* message = XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Error: " << message
        << " at line: " << exception.getLineNumber()
        << "\n";
    XMLString::release(&message);
}

ParsedData ParseFile(string path)
{
    ParseThatShit();
    return ParsedData();
}
