#ifndef INI_FILE_H
#define INI_FILE_H

#include <vector>
#include <algorithm>
#include <string>

using std::string;
using std::vector;
using namespace std;

namespace Train
{

const static string delim = string("\n");
const static string space = string(" ");

struct IniItem {
    string key;
    string value;
    string comment;
    string rightComment;
};

struct IniSection {
using ItemIterator = vector<IniItem>::iterator;
ItemIterator begin() {
    return itemList.begin(); 
}

ItemIterator end() {
    return itemList.end();
}

string name;
string comment;
string rightComment;
vector<IniItem> itemList;
};

class IniFile
{
public:
    IniFile();
    virtual ~IniFile() { }

public:
    void dump();
    bool load(const string& filePath);
    bool hasSection(const string& name);
    bool getValue(const string& sectionName, const string& key, string& value);
    bool getComment(const string& sectionName, const string& key, string& comment);
    bool getRightComment(const string& sectionName, const string& key, string& rightComment);
    bool hasKey(const string& sectionName, const string& key);
    bool getSectionNames(vector<string>& nameList);
    bool setValue(const string& sectionName, const string& key, const string& value);
    bool setComment(const string& sectionName, const string& key, const string& comment);
    bool setRightComment(const string& sectionName, const string& key, const string& rightComment);
    void save(string filePath = string(""));

protected:
    void trimLeft(string& str, char c = ' ');
    void trimRight(string& str, char c = ' ');
    void trim(string& str);
    bool startWith(const string& str, const string& prefix);
    bool isCommentLine(const string& str);
    bool splitComment(const string &str, const string& sep, string& left, string& right);
    bool parseKeyValue(const string& content, string& key, string& value);
    bool updateSection(const string& content, const string& comment, const string& rightComment);
    bool addKeyValuePair(const string& content, const string& comment, const string& rightComment);
    bool getSection(const string& sectionName, IniSection& section);

 private:
    using SectionIterator = vector<IniSection>::iterator;
    vector<IniSection> mSectionList;
    string mFilePath;
    string mCommentDelimiter;
};

}

#endif

