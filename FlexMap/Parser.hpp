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
    void startElement(const XMLCh* const, AttributeList&);
    void fatalError(const SAXParseException&);
};

ParsedData ParseFile(string path);