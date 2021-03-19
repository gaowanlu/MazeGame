#include"../headfile/DataBaseMode.h"
#include"../headfile/database-hfile/Database.h"
DataBaseMode::DataBaseMode() {
	//�������ݿ��ļ�
    // ��Ϊִ���ַ�������ΪUTF8�������ֶ����ô���ҳ�Է�ֹ������ Windows ��ӡ�����룬���ֱ��ʹ�ñ�׼������Ϊ������Դ����ô����Ҳ�ᱻת����UTF8
    system("chcp 65001");
    // ��ʼ��һ������ʵ����ָ�������ݿ��ļ�·�����������Ѿ����ڵ��ļ���
    this->db=new Database("./maze.db");
}
DataBaseMode::~DataBaseMode() {
    delete this->db;
}
void DataBaseMode::AddUser(std::string &id, std::string &password) {
    this->db->add_user(User(id, password));
}
void DataBaseMode::DelUser(std::string& id) {
    this->db->delete_user(id);
}
void DataBaseMode::PrintAllUser(void) {
    // ��ѯ�����û�
    struct UserData* headNode = beauty(db->select_all_users());
    PrintUserList(headNode);
    if (!headNode) {
        return;
    }
    if (headNode->next == NULL) {
        free(headNode);
        return;
    }
    struct UserData* temp = headNode->next;
    free(headNode);
    while (temp) {
        delete (temp->id);
        delete (temp->password);
        struct UserData* freeNode = temp;
        temp = temp->next;
        free(freeNode);
    }
}
struct UserData* DataBaseMode::beauty(const std::vector<std::vector<std::string>>& vector)
{
    struct UserData* headNode = (struct UserData*)malloc(sizeof(struct UserData) * 1);
    headNode->next = NULL;
    for (auto row : vector) {
        struct UserData* newNode = (struct UserData*)malloc(sizeof(struct UserData) * 1);
        newNode->id = new std::string(row[0]);
        newNode->password = new std::string(row[1]);
        newNode->next = headNode->next;
        headNode->next = newNode;
    }
    return headNode;
}

void DataBaseMode::PrintUserList(struct UserData* headNode) {
    if (!headNode || !headNode->next) {
        return;
    }
    struct UserData* temp = headNode->next;
    std::cout << "All Users:\n";
    while (temp) {
        std::cout << "\t{id:" << *(temp->id) << ",password:" << *(temp->password) << "}\n";
        temp = temp->next;
    }
}

void DataBaseMode::AddRecord(std::string&id,int level,int timeCost,int score) {
    db->add_record(Record(id, level, timeCost, score));
}
void DataBaseMode::DelRecord(std::string&id,int level,size_t index) {
    db->delete_record(id, level, index);
}
void DataBaseMode::PrintAllRecord() {
    PrintRecordList(db->select_all_records());
}
void DataBaseMode::PrintRecordList(const std::vector<std::vector<std::string>>& vector) {
    struct RecordData* headNode = (struct RecordData*)malloc(sizeof(struct RecordData) * 1);
    headNode->next = NULL;
    for (auto row : vector) {
        struct RecordData* newNode = (struct RecordData*)malloc(sizeof(struct RecordData) * 1);
        newNode->id = new std::string(row[0]);
        newNode->level = new std::string(row[1]);
        newNode->frequency = new std::string(row[2]);
        newNode->cost = new std::string(row[3]);
        newNode->score = new std::string(row[4]);
        newNode->next = headNode->next;
        headNode->next = newNode;
    }
    if (!headNode || !headNode->next) {
        return;
    }
    struct RecordData* temp = headNode->next;
    std::cout << "All Records:\n";
    while (temp) {
        std::cout << "\t{id:" << *(temp->id) << ",level:" << *(temp->level)<<",frequency:"<<*(temp->frequency) << ",cost:" << *(temp->cost)<<",score:"<<*(temp->score)<< "}\n";
        temp = temp->next;
    }
    //free
    if (!headNode) {
        return;
    }
    if (headNode->next == NULL) {
        free(headNode);
        return;
    }
    temp = headNode->next;
    free(headNode);
    while (temp) {
        delete (temp->id);
        delete (temp->level);
        delete (temp->frequency);
        delete (temp->score);
        delete(temp->cost);
        struct RecordData* freeNode = temp;
        temp = temp->next;
        free(freeNode);
    }

}