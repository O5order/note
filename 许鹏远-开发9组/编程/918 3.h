#include<stdio.h>
#include <string.h>
#include<stdlib.h>


struct ConfigInfo
{               //������Ҫ���ļ��л�������Ϣ�Ľṹ��
    char key[64];//��������Ҫ��õ�ַ������
    char val[128];
};
    //����ļ���Ч����
    int getLines_ConfigFIle(FILE *file);
    //���������ļ�
    void loadFile_ConfigFile(const char *fliePath, char ***fileData, int *lines);
    //���������ļ�
    void ParseFile_ConfigFile(char **fileData, int lines, struct ConfigInfo **info);    //���ָ��������Ϣ
    //���ָ��������Ϣ
    char *getInfo_ConfigFile(const char *key, struct ConfigInfo *Info);
    //�ͷ������ļ���Ϣ
    void destroInfo_ConfigFile(struct ConfigInfo *Info);
    //�жϵ�ǰ���Ƿ���Ч
    int inValid_ConfigFile(const char *buf);
