#include <string.h>
#include "Item.cpp"
#include "vector"

class User {
    Item item;
    int noOfItems, index;
    float spent;
    fstream *file;
    char username[30];
    void open(char*);
    void countNoOfItems();
    void calculateSpent();
    public:
    ~User();
    User(char*);
    void reset();
    void open();
    void close();
    void save();
    void logOut();
    void newItem();
    void readItem();
    void readItemAt(int index);
    void writeItem();
    void writeItem(int index);
    void printItemsForAllYears();
    void printItemsForYear(int year);
    void printItemsForYearAndMonth(int years, int month);
    void printItemsBetweenDates(Date dateRangeStart, Date dateRangeEnd);
    void deleteLastRecord();
    static void createDataSource(char* username);
    static void deleteDataSource(char* username);
    static char* getFilePath(char* username);
    char* getFilePath();
    char* getName();
    int getNoOfItems();
    float getSpent();
    vector<int> getYears();
    bool isOpen();
};
User :: ~User() {
    logOut();
}

User :: User(char username[30]) {
    strcpy(this->username, username);
    file = new fstream();
}

void User::reset() {
    close();
    fstream f(username, ios::out | ios::trunc);
    f.close();
    open();
}

bool User :: isOpen() {
    bool isOpen = file->is_open();
    if(isOpen) {
        printf("file is open");
    } else {
        printf("file is not open");
    }
    getch();
    return isOpen;
}

char* User :: getFilePath(char username[]) {
    char filePath[100] = "Data/";
    strcpy(filePath, strcat(filePath, username));
    return filePath;
}

char* User :: getFilePath() {
    char filePath[100] = "Data/";
    strcpy(filePath, strcat(filePath, this->username));
    return filePath;
}

char* User :: getName() {
    return this->username;
}

void User :: createDataSource(char username[]) {
    string filePath = "Data/" + (string)username;
    fstream file(filePath, ios::out);
    file.close();
}

void User :: deleteDataSource(char username[]) {
    char filePath[100] = "Data/";
    strcat(filePath, username);
    remove((char*)filePath);
}

void User :: open() {
    char filePath[100] = "Data/";
    strcat(filePath, this->username);
    file->open(filePath, ios::in | ios::out | ios::binary | ios::ate);
    calculateSpent();
}

void User :: close() {
    if(!file)
        return;
    if(isOpen())
        file->close();
}

void User::save() {
    User::close();
    User::open();
}

void User::logOut() {
    close();
    delete file;
    file = nullptr;
}

// create a new item to save
void User::newItem() {
    item.askForItem();
    item.print();
}

// read item from <username> file from current cursor position
void User::readItem() {
    file->read((char*)&item, sizeof(Item));
}

// Read item details from <username> file from specified index
void User::readItemAt(int index) {
    file->seekg(index * sizeof(Item));
    file->read((char*)&item, sizeof(Item));
}

void User::writeItem() {
    file->seekp(0, ios::end);
    file->write((char*)&item, sizeof(Item));
    this->save();
}

/* Overwrites the Item details in <username> file at specified index
 * with User->item
*/
void User::writeItem(int index) {
    file->seekp(index * sizeof(Item));
    file->write((char*)&item, sizeof(Item));
    this->save();
}

void User::printItemsForAllYears() {
    vector<int> years = this->getYears();
    Date dateRangeStart, daterangeEnd;
    dateRangeStart.setDate(years.front(), 1, 1);
    daterangeEnd.setDate(years.back(), 12, 31);

    system("cls");

    this->printItemsBetweenDates(dateRangeStart, daterangeEnd);
}

void User::printItemsForYear(int year)
{
    Date DateRangeStart, dateRangeEnd;
    DateRangeStart.setDate(year, 1, 1);
    dateRangeEnd.setDate(year, 12, 31);

    system("cls");

    this->printItemsBetweenDates(DateRangeStart, dateRangeEnd);
}

void User::printItemsForYearAndMonth(int year, int month)
{
    Date dateRangeStart, dateRangeEnd;
    dateRangeStart.setDate(year, month, 1);
    dateRangeEnd = dateRangeStart.getEndOfMonth();

    system("cls");

    this->printItemsBetweenDates(dateRangeStart, dateRangeEnd);
}

void User::printItemsBetweenDates(Date dateRangeStart, Date dateRangeEnd) {
    file->seekg(0, ios::beg);
    for(int i = 0; i < this->getNoOfItems(); ++i) {
        this->readItem();
        if(item.getDate() >= dateRangeStart && item.getDate() <= dateRangeEnd) {
            item.print();
            cout<<endl;
        }
    }
}

void User::deleteLastRecord()
{
    fstream tempUserFile("Data/tempUserFile", ios::out | ios::binary | ios::app);
    Item tempItem;
    char userFilepath[100] = "Data/";
    strcat(userFilepath, this->username);
    file->seekg(0, ios::beg);
    for(int i = 0; i < getNoOfItems() - 1; ++i)
    {
        file->read((char*)&tempItem, sizeof(Item));
        tempUserFile.write((char*)&tempItem, sizeof(Item));
    }
    tempUserFile.close();
    file->close();
    remove(userFilepath);
    rename("Data/tempUserFile", userFilepath);
    this->open();
}

int User::getNoOfItems() {
    return this->noOfItems;
}

vector<int> User::getYears() {
    vector<int> years;
    Item tempItem;
    int year;
    bool isYearNotPresent;
    file->seekg(0, ios::beg);
    for (int i = 0; i < this->getNoOfItems(); ++i ) {
        this->readItem();
        year = item.getDate().getYear();
        isYearNotPresent = true;
        for (int j = 0; j < years.size(); ++j) {
            if(years.at(j) == year) {
                isYearNotPresent = false;
            }
        }
        if(isYearNotPresent) {
            years.emplace_back(year);
        }
    }
    return years;
}

void User::countNoOfItems() {
    file->seekp(0, ios::end);
    int filesize = (int)file->tellp();
    printf("%d", filesize);
    if(filesize < 0)
        filesize = 0;
    this->noOfItems = (filesize / (sizeof(Item)));
}

void User::calculateSpent() {
    float spent = 0;
    this->countNoOfItems();
    file->seekg(0, ios::beg);
    for(int i = 0; i < this->getNoOfItems(); ++i) {
        this->readItem();
        spent += this->item.getPrice();
    }
    this->spent = spent;
}

float User::getSpent() {
    return this->spent;
}