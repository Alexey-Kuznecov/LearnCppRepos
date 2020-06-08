#include <iostream>
#include <fstream>
#include <string>
#include "libs/rapidjson/include/rapidjson/Writer.h"
#include "libs/rapidjson/include/rapidjson/Document.h"
#include "libs/rapidjson/include/rapidjson/StringBuffer.h"
#include "libs/rapidjson/include/rapidjson/istreamwrapper.h"

using namespace std;
using namespace rapidjson;

class ParseJson 
{
public:
    ParseJson() 
    {
        std::ifstream ifs("Param.json");
        IStreamWrapper isw(ifs);      
        documentFromFile.ParseStream(isw);
    };

    void InterapOverElements()
    {
        std::string json = "{\"type\":\"test\",\"number\":1}";
        Document document;
        document.Parse(json.c_str());

        // Example 1: Json modification, writing Json to console
        Value& s = document["number"];
        s.SetInt(s.GetInt() + 1);

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);

        std::cout << buffer.GetString() << std::endl;

        //Example 2: Getting json from a file
        if (documentFromFile.IsNull()) {
            std::cout << "Unable to read document" << std::endl;
        }

        // Example 3: Iterating over elements
        Value::ConstMemberIterator iter = documentFromFile.MemberBegin();
        for (;iter != documentFromFile.MemberEnd(); ++iter) {
        std::cout   << "Element name:" 
                    << iter->name.GetString() 
                    << "; element value: " 
                    << GetElementValue(iter->value) 
                    << std::endl;
        }
    }

    std::string GetElementValue(const Value& val) 
    {
        if (val.GetType() == Type::kNumberType)
            return std::to_string(val.GetInt());
        else if (val.GetType() == Type::kStringType)
            return val.GetString();
        else if (val.IsArray())
        {
            GetSearchOption(val);
            return "Array";
        }
        else if (val.GetType() == Type::kObjectType)
            return "Object";
        else if (val.IsBool())
            return "Booleam";
        return "Unknown";
    }

    void GetSearchOption(const Value& arr)
    {
        const rapidjson::Value& item = documentFromFile["searchOption"];

        for (rapidjson::Value::ConstMemberIterator itr = item.MemberBegin();
        itr != item.MemberEnd(); ++itr)
        {
            rapidjson::StringBuffer sb;
            rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
            itr->value.Accept(writer);

            std::cout << sb[0].GetString();
        }
    }

private:
    Document documentFromFile;
};
