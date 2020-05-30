#pragma once
#include <vector>
#include <string>
#include <map>
#include <xercesc/sax/HandlerBase.hpp>

using namespace xercesc;
using std::string;
using std::vector;

struct ParsedData {
	vector<string> data;
};



class OSMHandler : public HandlerBase {
private:
    
public:
    std::map<const XMLCh* const, int> count;
    void handleNode(std::map<string, string> map);
    void startElement(const XMLCh* const, AttributeList&);
    void fatalError(const SAXParseException&);
    void endElement(const XMLCh* const);
};

inline string stringFromXMLCh(const XMLCh* const val)
{
    char* transcoded = XMLString::transcode(val);
    string v(transcoded);
    XMLString::release(&transcoded);
    return v;
}

ParsedData ParseFile(string path);