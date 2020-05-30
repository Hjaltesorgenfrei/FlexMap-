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
    auto* parser = new SAXParser();
    parser->setDoNamespaces(true);    // optional

    auto* docHandler = new OSMHandler();
    auto* errHandler = static_cast<ErrorHandler*>(docHandler);
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
        char* name = XMLString::transcode(k.first);
        std::cout <<  name << ":" << k.second << "\n";
        XMLString::release(&name);
    }
    delete parser;
    delete docHandler;
    return 0;
}


void OSMHandler::handleNode(std::map<string, string> values)
{
    std::cout << "node-" << values["id"]  <<  ": (" << values["lat"] << ", " << values["lon"] << ")\n";
}

void OSMHandler::startElement(const XMLCh* const name,
                              AttributeList& attributes)
{
    char* message = XMLString::transcode(name);
    std::map<string, string> values;
    for (unsigned int i = 0; i < attributes.getLength(); i++){
        string name = stringFromXMLCh(attributes.getName(i));
        string value = stringFromXMLCh(attributes.getValue(i));
        values[name] = value;
    }
	if (strcmp(message, "node") == 0)
	{
        this->handleNode(values);
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

void OSMHandler::endElement(const XMLCh* const name)
{
    char* message = XMLString::transcode(name);
    XMLString::release(&message);
}

ParsedData ParseFile(string path)
{
    ParseThatShit();
    return ParsedData();
}
