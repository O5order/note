#include<stdio.h>
#include <string.h>
#include<stdlib.h>


struct ConfigInfo
{               //构建你要从文件中获得相关信息的结构体
    char key[64];//比如这里要获得地址和密码
    char val[128];
};
    //获得文件有效行数
    int getLines_ConfigFIle(FILE *file);
    //加载配置文件
    void loadFile_ConfigFile(const char *fliePath, char ***fileData, int *lines);
    //解析配置文件
    void ParseFile_ConfigFile(char **fileData, int lines, struct ConfigInfo **info);    //获得指定配置信息
    //获得指定配置信息
    char *getInfo_ConfigFile(const char *key, struct ConfigInfo *Info);
    //释放配置文件信息
    void destroInfo_ConfigFile(struct ConfigInfo *Info);
    //判断当前行是否有效
    int inValid_ConfigFile(const char *buf);
