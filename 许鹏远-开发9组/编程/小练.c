#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_DATA 128
#define MAX_save 2048

struct Address {                 //ÿ���˵Ļ������ݴ洢
    char name[MAX_DATA];
    char key[MAX_DATA];
    char account[MAX_DATA];
    char character[MAX_DATA];
    int age;
    int classroom;
    int studentID;
    int set;  //��֤�Ƿ�ע���
};

struct Database {               //���ݿ�
    struct Address rows[MAX_save];
};

struct  Total{                 //�ṹ��Ƕ�ף���ͬ���ļ������ֲ�ͬ��ݵ����ݱ�
    FILE *file;
    struct Database *db;
};

void die(const char *message, struct Total *conn){      //���ִ���ֹͣ����
    if(errno) {
        perror(message);
    } else {
    	printf("ERROR: %s\n", message);
    }if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
    exit(1);
}

void Database_write(struct Total *conn){             //д�����ݿ�
    rewind(conn->file);
    int wr=fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(wr!=1) die("Failed to write database.", conn);
    wr=fflush(conn->file);              //��֤���ݳ��д��
    if(wr==-1) die("Cannot flush database.", conn);
}

void Database_str(struct Total *conn, int age, int classroom,int studentID, const char *name, const char *key, const char *account,const char *character){
    struct Address *add=&conn->db->rows[studentID];             //ע��д������
    if(add->set) die("Already had,please register", conn);     //��ֹ�ظ�ע��
    add->set=1;                  //�����ݱ�ע���
    char *res=strncpy(add->name, name, MAX_DATA);
    if(!res) die("Error��copy failed", conn);

    res=strncpy(add->key, key, MAX_DATA);
    if(!res) die("Error��copy failed", conn);

    res=strncpy(add->account, account, MAX_DATA);
    if(!res) die("Error��copy failed", conn);

    res=strncpy(add->character, character, MAX_DATA);
    if(!res) die("Error��copy failed", conn);

    add->studentID=studentID;
    add->age=age;
    add->classroom=classroom;         //�������ݸ�ֵ���
}

struct Total *Database_open(const char *filename, char mode){
    struct Total *conn=malloc(sizeof(struct Total));
    if(!conn) die("Error: failed to open database", conn);
    conn->db=malloc(sizeof(struct Database));         //�򿪴洢�ռ�
    if(!conn->db) die("Error: failed to open database", conn);
    if(mode=='s') {                       //���ݵ�½����ע����ļ�
        conn->file=fopen(filename, "w");
    } else {
        conn->file=fopen(filename, "r+");
        if(conn->file) {
            int r=fread(conn->db, sizeof(struct Database), 1, conn->file);
            if(r!=1) die("Failed to load database.", conn);          //�������뵽db��
        }
    }
    if(!conn->file) die("Failed to open the file", conn);
    return conn;
}
void Database_find(struct Total *conn){        //�г����п��Ե�½���˻�
        int i;
        struct Database *db=conn->db;
        for(i=0;i<MAX_save;i++) {
            struct Address *prt=&db->rows[i];

            if(prt->set) {
                printf("%s %d %d %d\n",
                    prt->name, prt->classroom, prt->age, prt->studentID);
            }
        }
    }

void Database_register(struct Total *conn, int studentID){
    struct Address *add = &conn->db->rows[studentID];
    if(add->set==1) {
        printf("%s %d %d %d\n",
                    add->name, add->classroom, add->age, add->studentID);
    } else {
        die("please sigh in first", conn);
    }
}

int main(){
    scan:
    printf("\n===============================\n");
    printf("if you first use this database, please enter 's' to set(only one time)\n");
    printf("enter 'r' to sigh in\nenter 'w' to register\nenter 'f' to konw accont");
    char mode='0';
    printf("\n===============================\n");
    scanf(" %c", &mode);                                 //ȷ��ע�ỹ�ǵ�¼���ǲ���
    getchar();
    //if (mode=='f')goto find;
    printf("\nwhat`s the character(student,teacher,manager)\n");
    char filename[8];
    fgets(filename,8,stdin);                 //ȷ�����
    if(strcmp(filename,"student")==0)
        printf("student: \n");
    else if(strcmp(filename,"teacher")==0)
        printf("teacher: \n");
    else if(strcmp(filename,"manager")==0)
        printf("headmaster: \n");                       //��ֹ����������
    else {printf("didn`t find this character");goto scan;}
    if(mode=='0'){
    	printf("please enter the correct word");
    	goto scan;                  //��ֹע���¼�������
    }
    struct Total *conn=Database_open(filename, mode);           //�����ڴ�ռ䲢���ļ�
    int i=0;			        //�������
    char name[MAX_DATA];
    int classroom;
    int age;
    int studentID;
    char key[MAX_DATA];
    char account[MAX_DATA];
    switch(mode) {
        case 'w':			//register only to read
            printf("please enter your studentID\n");
            scanf("%d", &studentID);
            Database_register(conn, studentID);
            break;
        case 'r': 			//sigh in only to write
            printf("please enter your information(name classroom age studentID key account)\n");
            if((scanf("%s %d %d %d %s %s", name, &classroom, &age, &studentID, key, account))==0)   //��������
                {
                printf("please enter right words");
                break;
                }

            Database_str(conn, age, classroom, studentID, name, key, account, filename);
            Database_write(conn);
            printf("\nsigh in succeed\n");
            printf("Now return original page\n");
            break;
        case 'f':

            Database_find(conn);
            break;
        case 's':
            for(i=0; i < MAX_save; i++) {
                struct Address first={.name="NULL", .studentID=0, .classroom=0, .age=0, .set=0, .key="NULL", .account="NULL"};
                conn->db->rows[i]=first;
            }
            Database_write(conn);       //��֤��ʼ������
            break;
        default:
            printf("Invalid action, only: r=sigh in, w=register");
            goto scan;
    }
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
    return 0;
}
