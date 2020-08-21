#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include "inifile.h"

namespace Train
{

IniFile::IniFile()
    : mCommentDelimiter("#")
{

}

void IniFile::trimLeft(string &str, char c) {
    int len = str.length();
    int i = 0;

    while (str[i] == c && str[i] != '\0') {
        i++;
    }

    if (i != 0) {
        str = string(str, i, len - i);
    }
}

void IniFile::trimRight(string &str, char c) {
    int i = 0;
    int len = str.length();

    for (i = len - 1; i >= 0; --i) {
        if (str[i] != c) {
            break;
        }
    }

    str = string(str, 0, i + 1);
}


void IniFile::trim(string &str) {
    int len = str.length();

    int i = 0;

    while ((i < len) && isspace(str[i]) && (str[i] != '\0')) {
        i++;
    }

    if (i != 0) {
        str = string(str, i, len - i);
    }

    len = str.length();

    for (i = len - 1; i >= 0; --i) {
        if (!isspace(str[i])) {
            break;
        }
    }

    str = string(str, 0, i + 1);
}


bool IniFile::isCommentLine(const string &str) {
    return startWith(str, mCommentDelimiter);
}

bool IniFile::startWith(const string &str, const string &prefix) {
    if (str.find(prefix) == 0) {
        return true;
    }

    return false;
}

bool IniFile::parseKeyValue(const string& content, string& key, string& value) {
    size_t pos = content.find('=');
    if (pos != string::npos) {
        key = string(content, 0, pos);
        value = string(content, pos+1);
        trim(key);
        trim(value);
        return true;
    } else {
        key = content;
        value = string("");
        trim(key);
        return false;
    }
}

bool IniFile::splitComment(const string &str, const string& sep, string& left, string& right) {
    size_t pos = str.find(sep);
    if (pos != string::npos) {
        left = string(str, 0, pos);
        right = string(str, pos);
        trim(left);
        trim(right);
        return true;
    } else {
        left = str;
        right = string("");
        trim(left);
        return false;
    }
}


bool IniFile::load(const string &filePath) {
    mFilePath = filePath;
    std::ifstream ifs(mFilePath);
    if (!ifs.is_open()) {
        cout << string("IniFile::load open ") << string(mFilePath) <<  string(" file failed\n");
        return false;
    }

    mSectionList.clear();

    bool ret = true;
    string line, comment, content, rightComment;
    while (std::getline(ifs, line)) {
        trim(line);

        if (line.length() <= 0) {
            comment += delim;
            continue;
        }

        if (isCommentLine(line)) {
            comment += line;
            comment += delim;
            continue;
        }

        splitComment(line, mCommentDelimiter, content, rightComment);

        std::cout << string("IniFile::parseKeyValue line = ") << line << std::endl;
        std::cout << string("IniFile::parseKeyValue content = ") << content << std::endl;
        if (content[0] == '[') {
            ret = updateSection(content, comment, rightComment);
        } else {
            ret = addKeyValuePair(content, comment, rightComment);
        }

        if (!ret) {
            ifs.close();
            return false;
        }

        comment.clear();
        rightComment.clear();
    }

    ifs.close();

    return true;
}

bool IniFile::updateSection(const string& content, const string& comment, const string& rightComment) {
    size_t index = content.find_first_of(']');
    if (index == string::npos) {
        std::cout << string("IniFile::updateSection don not find ]\n");
        return false;
    }

    int len = index - 1;
    if (len <= 0) {
        std::cout << string("IniFile::updateSection section name is empty\n");
        return false;
    }

    string s(content, 1, len);
    trim(s);

    IniSection section;
    if (getSection(s, section)) {
        std::cout << string("IniFile::updateSection section: ") << s << string(" exist.\n");
        return false;
    }

    section.name = s;
    section.comment = comment;
    section.rightComment = rightComment;
    mSectionList.push_back(section);

    return true;
}

bool IniFile::getSection(const string& sectionName, IniSection& section) {
    for (auto& sec :  mSectionList) {
        if (sec.name == sectionName) {
            section = sec;
            return true;
        }
    }
    return false;
}

bool IniFile::addKeyValuePair(const string& content, const string& comment, const string& rightComment) {
    string key, value;
    if (!parseKeyValue(content, key, value)) {
        std::cout << string("IniFile::addKeyValuePair parse line failed.\n");
        return false;
    }

    IniItem item;
    item.key = key;
    item.value = value;
    item.comment = comment;
    item.rightComment = rightComment;

    if (mSectionList.empty()) {
        std::cerr << string("IniFile::addKeyValuePair section is empty.\n");
        std::cerr << string("IniFile::addKeyValuePair ignore comment: ") << comment 
            << string(", ") << content << string(", ") << rightComment << std::endl;
        return false;
    }

    mSectionList.back().itemList.push_back(item);
    return true;
}

bool IniFile::getValue(const string& sectionName, const string& key, string& value) {
    IniSection section;
    if (!getSection(sectionName, section)) {
        cout << string("IniFile::getValue not find the section: ") << sectionName << std::endl;
        return false;
    }

    for (IniSection::ItemIterator it = section.begin(); it != section.end(); ++it) {
        if (it->key == key) {
            value = it->value;
            return true;
        }
    }

    cout << string("IniFile::getValue not find the key: ") << key << std::endl;
    return false;
}

bool IniFile::getComment(const string& sectionName, const string& key, string& comment) {
    IniSection section;
    if (!getSection(sectionName, section)) {
        cout << string("IniFile::getValue not find the section: ") << sectionName << std::endl;
        return false;
    }

    if (key == string("")) {
        comment = section.comment;
        return true;
    }

    for (IniSection::ItemIterator it = section.begin(); it != section.end(); ++it) {
        if (it->key == key) {
            comment = it->comment;
            return true;
        }
    }

    cout << string("IniFile::getComment not find the key: ") << sectionName << std::endl;
    return false;
}

bool IniFile::getRightComment(const string& sectionName, const string& key, string& comment) {
    IniSection section;
    if (!getSection(sectionName, section)) {
        cout << string("IniFile::getValue not find the section: ") << sectionName << std::endl;
        return false;
    }

    if (key == string("")) {
        comment = section.rightComment;
        return true;
    }

    for (IniSection::ItemIterator it = section.begin(); it != section.end(); ++it) {
        if (it->key == key) {
            comment = it->rightComment;
            return true;
        }
    }

    cout << string("IniFile::getRightComment not find the key: ") << key << std::endl;
    return false;
}

bool IniFile::hasKey(const string& sectionName, const string& key) {
    IniSection section;
    if (!getSection(sectionName, section)) {
        cout << string("IniFile::getValue not find the section: ") << sectionName << std::endl;
        return false;
    }

    for (IniSection::ItemIterator it = section.begin(); it != section.end(); ++it) {
        if (it->key == key) {
            return true;
        }
    }

    return false;
}

bool IniFile::getSectionNames(vector<string>& nameList) {
    for (SectionIterator it = mSectionList.begin(); it != mSectionList.end(); ++it) {
        nameList.push_back(it->name);
    }

    return nameList.size() > 0;
}

bool IniFile::setValue(const string& sectionName, const string& key, const string& value) {
    for(auto& section : mSectionList) {
        for(auto& item : section.itemList) {
            if (item.key == key) {
                item.value = value;
                return true;
            }
        }
    }
    return false;
}

bool IniFile::setComment(const string& sectionName, const string& key, const string& comment) {
    for(auto& section : mSectionList) {
        if (sectionName == section.name) {
            if (key == string("")) {
                section.comment = mCommentDelimiter +  comment;
                return true;
            }

            for (auto& item : section.itemList) {
                if (item.key == key) {
                    item.comment = mCommentDelimiter + comment;
                    return true;
                }
            }
            break;
        }
    }

    return false;
}

bool IniFile::setRightComment(const string& sectionName, const string& key, const string& comment) {
    for(auto& section : mSectionList) {
        if (sectionName == section.name) {
            if (key == string("")) {
                section.rightComment = space + mCommentDelimiter + comment;
                return true;
            }

            for (auto& item : section.itemList) {
                if (item.key == key) {
                    item.rightComment = space + mCommentDelimiter + comment;
                    return true;
                }
            }
        }
    }

    return false;
}

void IniFile::save(string filePath) {
    string path(filePath);
    if (path.empty()) {
        path = mFilePath;
    }
    string data = string("");

    for (const auto& section : mSectionList) {
        if (!section.comment.empty()) {
            data += section.comment;
            if (data[data.length()-1] != '\n') {
                data += delim;
            }
        }

        if (!section.name.empty()) {
            data += string("[") + section.name + string("]");
        }

        if (!section.rightComment.empty()) {
            data += section.rightComment;
        }

        if (data[data.length()-1] != '\n') {
            data += delim;
        }

        for (const auto& item : section.itemList) {
            if (!item.comment.empty()) {
                data += item.comment;
                if (data[data.length()-1] != '\n') {
                    data += delim;
                }
            }

            data += item.key + string("=") + item.value;

            if (!item.rightComment.empty()) {
                data += item.rightComment;
            }

            if (data[data.length()-1] != '\n') {
                data += delim;
            }
        }
        data += delim;

    }

    std::ofstream ofs(path);
    ofs << data;
    ofs.close();
}

void IniFile::dump()
{
    printf("############ dump start ############\n");
    printf("filePath:[%s]\n", mFilePath.c_str());
    printf("commentDelimiter:[%s]\n\n", mCommentDelimiter.c_str());

    for (SectionIterator it = mSectionList.begin(); it != mSectionList.end(); ++it) {
        printf("comment :[%s]\n", it->comment.c_str());
        printf("section :[%s]\n", it->name.c_str());
        printf("rightComment: %s\n", it->rightComment.c_str());

        for (IniSection::ItemIterator i = it->itemList.begin(); i != it->itemList.end(); ++i) {
            printf("    comment :[%s]\n", i->comment.c_str());
            printf("    parm    :%s=%s\n", i->key.c_str(), i->value.c_str());
            printf("    rcomment:[%s]\n", i->rightComment.c_str());
        }
    }

    printf("############ dump end ############\n");
    return;
}

}
