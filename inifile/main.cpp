#include <iostream>
#include "inifile.h"


int main(int argc, char **agv)
{
    char filepath[] = "test_save.ini";
    FILE *fp = fopen(filepath, "w");
    char content[] = "[DEFINE] \nname = cxy # SDF\nsex=sd # test2\n  [COMMON] \n DB=sys      \n PASSWD = tt   \n#commit  \n    #--------- \n";
    fwrite(content, sizeof(char), sizeof(content), fp);
    fclose(fp);

    Train::IniFile ini;
    ini.load(filepath);
    ini.dump();

    ini.load(filepath);
    ini.dump();

    ini.setValue("COMMON", "PASSWD", "123456");
    ini.setRightComment("COMMON", "", "common");
    ini.setComment("COMMON", "", "this is common configure");
    ini.setComment("COMMON", "DB", "database");
    ini.setRightComment("COMMON", "DB", "database");
    ini.setComment("COMMON", "PASSWD", "user code");
    ini.setRightComment("COMMON", "PASSWD", "password");
    ini.setComment("DEFINE", "", "this is user define");
    ini.setComment("DEFINE", "name", "user name");
    ini.setRightComment("DEFINE", "", "define");
    ini.setValue("DEFINE", "test1", "11111");
    ini.setValue("DEFINE", "test2", "22222");
    ini.setValue("DEFINE", "test3", "33333");
    char saveas_path[] = "test_save.ini";

    ini.dump();
    ini.save(saveas_path);

    return 0;
}

