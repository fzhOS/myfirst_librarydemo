#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define ENDL "\n"
class Time
{ //时间类
private:
    int year;
    int month;
    int day;

public:
    Time(int year = 0, int month = 0, int day = 0) : year(year), month(month), day(day) {}

    void setYear(int year)
    {
        this->year = year;
    }
    void setMonth(int month)
    {
        this->month = month;
    }
    void setDay(int day)
    {
        this->day = day;
    }
    int getYear()
    {
        return year;
    }
    int getMonth()
    {
        return month;
    }
    int getDay()
    {
        return day;
    }
    //
    // bool operator<(Time &t)
    // {
    //     return year < t.year ? true : month < t.month ? true
    //                               : day < t.day       ? true
    //                                                   : false;
    // }
    bool operator<(const Time&t1)const
    {
        return year!=t1.year?year<=t1.year:month!=t1.month?month<=t1.month:day<=t1.day;
    }
    friend istream &operator>>(istream &in, Time &t);
    friend ostream &operator<<(ostream &out, Time &t);
};
istream &operator>>(istream &in, Time &t)
{
    in >> t.year >> t.month >> t.day;
    return in;
}
ostream &operator<<(ostream &out, Time &t)
{
    out << t.year << "  "
        << t.month << "  "
        << t.day;
    return out;
}
class Record
{ //借阅记录类
private:
    int student_num; //学号
    int isbn;        //书号ISBN
    Time start;
    Time end;
    int xujie;  // 续借
    int status; //借阅状态 1: 在借  0：在还
public:
    Record()
    {
    }

    Record(int id, Time t, int isbn) : student_num(id), start(t), isbn(isbn)
    {
        if (t.getMonth() + 2 > 12)
        { //自动生成还书日期
            end = Time(t.getYear() + 1, t.getMonth() + 2 - 12, t.getDay());
        }
        else
        {
            end = Time(t.getYear(), t.getMonth() + 2, t.getDay());
        }
        xujie = 0;
        status = 0;
    }
    friend istream &operator>>(istream &in, Record &r);
    friend ostream &operator<<(ostream &out, Record &r);
    void setStudent_num(int id)
    {
        this->student_num = id;
    }
    void setIsbn(int isbn)
    {
        this->isbn = isbn;
    }
    void setStart(Time &t)
    {
        this->start = t;
    }
    void setEnd(); //续借则更改最迟归还时间

    void setXujie()
    {
        xujie =1;
    }
    void setStatus(int status)
    {
        this->status = status;
    }
    bool getXujie()
    {
        return xujie;
    }
    int getStatus()
    {
        return status;
    }
    int getIsbn()
    {
        return isbn;
    }
    int getStudent_num()
    {
        return student_num;
    }
    Time getEnd()
    {
        return end;
    }
    Time getStart()
    {
        return start;
    }
};
void Record::setEnd()
{
    if (end.getMonth() + 1 > 12)
    {
        end = Time(end.getYear() + 1, end.getMonth() + 1 - 12, end.getDay());
    }
    else
    {
        end = Time(end.getYear(), end.getMonth() + 1, end.getDay());
    }
}
istream &operator>>(istream &in, Record &r)
{
    in >> r.student_num;
    in >> r.isbn;
    in >> r.start;
    in >> r.end;
    in >> r.xujie;
    in >> r.status;
    return in;
}
ostream &operator<<(ostream &out, Record &r)
{
    out << r.student_num << "  "
        << r.isbn << "  "
        << r.start << "  "
        << r.end << "  "
        << r.xujie << "  "
        << r.status <<"  ";
    return out;
}
class Book
{
private:
    int isbn;       //isbn
    string name;    //书名
    string press;   //出版社
    Time press_out; //出版时间
    int count;      //图书总数量
    int lend;       //借出去的数量
    int records;    //借阅记录条数。
    vector<Record> vector1;
    vector<Record>::iterator iter1;
    multimap<int, int> map1;
    multimap<int, int>::iterator iter2;

public:
    Book()
    {
        count = 0;
    }
    vector<Record> getRecord()
    {
        return vector1;
    }
    multimap<int, int> getmap()
    {
        return map1;
    }
    void addR(Record r1); //只增加记录，但不牵扯到书的借阅状态。
    void displayRecord(); //显示记录信息
    void addRecord(Record r);
    void return_book(int student_num); //根据学号来还书
    void display();
    int search(int student_num);
    void xujie(int student_num);
    void clear();
    friend istream &operator>>(istream &in, Book &book);
    friend ostream &operator<<(ostream &out, Book &Book);

    Time GetPress_out() const
    {
        return press_out;
    }

    void SetPress_out(Time press_out)
    {
        this->press_out = press_out;
    }

    int GetLend() const
    {
        return lend;
    }

    void SetLend(int lend)
    {
        this->lend = lend;
    }

    int GetRecords() const
    {
        return records;
    }

    void SetRecords(int records)
    {
        this->records = records;
    }

    int GetCount() const
    {
        return count;
    }

    void SetCount(int count)
    {
        this->count = count;
    }

    string GetPress() const
    {
        return press;
    }

    void SetPress(string press)
    {
        this->press = press;
    }

    string GetName() const
    {
        return name;
    }

    void SetName(string name)
    {
        this->name = name;
    }

    int GetIsbn() const
    {
        return isbn;
    }

    void SetIsbn(int isbn)
    {
        this->isbn = isbn;
    }
};
istream &operator>>(istream &in, Book &book)
{ //输入不需要输入借阅记录
    //cout << "请输入isbn：,输入-1结束输入";
    in >> book.isbn;
    if (book.isbn == -1) //多次输入的小技巧
        return in;
    //cout << "输入书名：";
    in >> book.name;
    //cout << "输入出版社";
    in >> book.press;
   // cout << "输入出版时间";
    in >> book.press_out;
   // cout << "输入书籍数量";
    in >> book.count;
    //cout << "输入已借出数量";
    in >> book.lend;
   // cout << "输入借阅记录条数";
    in >> book.records;
    return in;
}
ostream &operator<<(ostream &out, Book &book)
{ //输出需要输出里面包含的借阅记录。
    out << book.isbn << "  " << book.name << "  "
        << book.press << "  " << book.press_out << "  "
        << book.count << "  " << book.lend << "  "
        << book.records <<"   ";
    if (book.records != 0)
    {
        for (int i = 0; i < book.records; i++)
        {
            out << book.vector1[i]; //向文件里写入records。
        }
    }
    out << ENDL;
    return out;
}
void Book::display()
{ //显示书的基本信息
    cout << isbn << ENDL;
    cout << name << ENDL;
    cout << press << ENDL;
    cout << press_out << ENDL;
}
void Book::addR(Record r1)
{
    vector1.push_back(r1);
    int size = vector1.size();
    map1.insert(make_pair(r1.getStudent_num(), size - 1));
}
void Book::addRecord(Record r1)
{
    r1.setStatus(1);
    vector1.push_back(r1);
    int size = vector1.size();
    map1.insert(make_pair(r1.getStudent_num(), size - 1));
}
void Book::displayRecord()
{
    if (vector1.size() != 0)
    {
        for (iter1 = vector1.begin(); iter1 != vector1.end(); iter1++)
            cout << *iter1;
    }
    else
        cout << "No Record!" << ENDL;
}
void Book::clear()
{
    vector1.clear();
}
int Book::search(int stu_num)
{
    iter2 = map1.find(stu_num);
    if (iter2 != map1.end())
        return iter2->second;
    return -1;
}
void Book::xujie(int stu_num)
{
    int top = search(stu_num);
    if (top != -1&&vector1[top+records-1].getXujie()==0)
    {
        vector1[top+records-1].setXujie(); //将状态改为续借true
        vector1[top+records-1].setEnd();   //修改还书时间
    }
    else
        cout << "no record now ,can't xujie" << ENDL;
}
void Book::return_book(int stu_num)
{
    int top = search(stu_num);
    if (top != -1)
    {
        vector1[top+records-1].setStatus(0); //修改书状态为归还
    }
}
class User
{
private:
    int stu_num;
    string name;
    int max;         //最大借阅量
    int cur;         //当前借阅量
    int delay;      //是否有书未按时归还
    int cur_records; //当前借阅记录条数
    vector<Record> vector2;
    vector<Record>::iterator iter1;
    multimap<int, int> map2;
    multimap<int, int>::iterator iter2;

public:
    User()
    {
        delay = 0;
        cur_records = 0;
    }
    vector<Record> getRecord() const
    {
        return vector2;
    }
    multimap<int, int> getMap() const
    {
        return map2;
    }
    void setVector(vector<Record> v)
    {
        vector2 = v;
    }
    void setMap(multimap<int, int> map)
    {
        map2 = map;
    }

    int GetCur_records() const
    {
        return cur_records;
    }

    void SetCur_records(int cur_records)
    {
        this->cur_records = cur_records;
    }

    int GetDelay() const
    {
        return delay;
    }

    void SetDelay(int delay)
    {
        this->delay = delay;
    }

    int GetCur() const
    {
        return cur;
    }

    void SetCur(int cur)
    {
        this->cur = cur;
    }

    int GetMax() const
    {
        return max;
    }

    void SetMax(int max)
    {
        this->max = max;
    }

    string GetName() const
    {
        return name;
    }

    void SetName(string name)
    {
        this->name = name;
    }

    int GetStu_num() const
    {
        return stu_num;
    }

    void SetStu_num(int stu_num)
    {
        this->stu_num = stu_num;
    }
    void clear();
    void addRecord(Record r1);
    void displayRecord();
    int search(int stu_num);
    void xujie(int stu_num);
    void return_book(int stu_num);
    friend istream &operator>>(istream &in, User &User);
    friend ostream &operator<<(ostream &out, User &user);
    void delayjudge(Time &t);
    void addR(Record r);
    void operator=(const User &user)
    { //重载赋值运算符
        stu_num = user.GetStu_num();
        name = user.GetName();
        max = user.GetMax();
        cur = user.GetCur();
        delay = user.GetDelay();
        cur_records = user.GetCur_records();
        vector2 = user.getRecord();
        map2 = user.getMap();
    }
    bool operator==(User &user)
    { //重载等于运算符
        return this->stu_num == user.GetStu_num() ? 1 : 0;
    }
};
istream &operator>>(istream &in, User &user)
{
    //cout << "请输入学号：，输入-1结束输入";
    in >> user.stu_num;
    if (user.stu_num == -1)
        return in;
    //cout << "依此输入姓名，最大借阅量，当前借阅数，违规状态，借阅记录条数:" << ENDL;
    in >> user.name >> user.max >> user.cur >> user.delay >> user.cur_records;
    return in;
}

// for (user.iter1 = user.vector2.begin(); user.iter1 != user.vector2.end();user.iter1++){
//             cout << *user.iter1;
//         }

ostream &operator<<(ostream &out, User &user)
{
    out << user.stu_num << "  "
        << user.name << "  "
        << user.max << "  "
        << user.cur << "  "
        << user.delay << "  "
        << user.cur_records<<"   " ;
    if (user.cur_records != 0)
    {
        for (int i = 0; i < user.cur_records; i++)
            out << user.vector2[i];
    }
    out << ENDL;
    return out;
}
void User::clear()
{
    vector2.clear();
}
void User::addR(Record r)
{ //不涉及书籍的借还状态
    vector2.push_back(r);
    int size = vector2.size();
    map2.insert(make_pair(r.getIsbn(), size - 1));
}
void User::addRecord(Record r)
{
    r.setStatus(1);
    vector2.push_back(r);
    int size = vector2.size();
    map2.insert(make_pair(r.getIsbn(), size - 1));
}
void User::displayRecord()
{
    if (vector2.size() != 0)
        for (iter1 = vector2.begin(); iter1 != vector2.end(); iter1++)
        {
            cout << *iter1;
        }
    else
        cout << "No Record!" << ENDL;
}
int User::search(int isbn)
{
    iter2 = map2.find(isbn);
    if (iter2 != map2.end())
    {
        return iter2->second;
    }
    else
        return -1;
}
void User::xujie(int isbn)
{
    int top = search(isbn);
        
        if (top != -1&&delay!=1)
        {
            int temp;
            for (int i = 0; i < vector2.size(); i++)
            {
                if (vector2[i].getIsbn() == isbn)
                {
                    top = i;
                    temp = vector2[i].getXujie();
                }
            }
            if(!temp){
            vector2[top].setXujie();
            vector2[top].setEnd();
            }
            else
                cout << "Can't xujie!" << ENDL;

        }
        else
        {
            cout << "Can't xujie!" << ENDL;
        }
}
void User::return_book(int isbn)
{
    int top = search(isbn);
    if (top != -1)
    {
        int temp;
        for (int i = 0; i < vector2.size(); i++)
        {
            if (vector2[i].getIsbn() == isbn)
            {
                top = i;
            }
        }
        vector2[top].setStatus(0);
    }
}
void User::delayjudge(Time &t)
{
    for (iter1 = vector2.begin(); iter1 != vector2.end(); iter1++)
    {
        if ((iter1->getEnd() < t )&& iter1->getStatus() == 1)
        {
            delay = 1;
            cout << "FBI Warning！ ：你尚有未还书籍，不能继续借阅，请尽快归还" << ENDL;
            break;
        }
    }
}
class Manager
{ //管理员类（增删改查）
private:
    vector<Book> v1;
    vector<Book>::iterator iter1;
    multimap<int, int> map2; //按照书的ISBN查找
    multimap<int, int>::iterator iter2;
    vector<User> v3;
    vector<User>::iterator iter3;
    multimap<int, int> map4; //按照学号查找
    multimap<int, int>::iterator iter4;

public:
    Manager()
    {
        cout << "welcome to the Manager Page!\n";
        cout << "___________________________ 图书馆管理系统____________________________\n";
        cout << "                  ┏━━━━━━━━━━━━━━┓                      \n";
        cout << "                  ┃ [0]退出系统。  ┃                      \n";
        cout << "                  ┃ [1]增加图书。  ┃                      \n";
        cout << "                  ┃ [2]查询图书。  ┃                      \n";
        cout << "                  ┃ [3]删除图书。  ┃                      \n";
        cout << "                  ┃ [4]显示图书信息。  ┃                      \n";
        cout << "                  ┃ [5]修改图书信息┃                    \n";
        cout << "                  ┃ [6]增加用户。  ┃                      \n";
        cout << "                  ┃ [7]查询用户。  ┃                      \n";
        cout << "                  ┃ [8]删除用户。  ┃                      \n";
        cout << "                  ┃ [9]显示用户信息。  ┃                      \n";
        cout << "                  ┃ [10]修改用户信息。  ┃                      \n";
        cout << "                  ┗━━━━━━━━━━━━━━┛                      \n";
        cout << "输入要进行的操作：\n";
    }
    void addBook();
    void displayBook();
    void deleteBook();
    void modifyBook();
    int search1(int isbn);
    void queryByIsbn();
    void addUser();
    void deleteUser();
    void displayUser();
    void modifyUser();
    int search2(int stu_num);
    void queryByStunum();
    void save1();
    void save2();
    ~Manager()
    {
        save1();
        save2();
    }
};
void Manager::save1()
{ //写文件
    ofstream of("books.txt", ios::out);
    if (!of)
    {
        return;
    }
    for (iter1 = v1.begin(); iter1 != v1.end(); iter1++)
        of << *iter1;
    of.close();
}
void Manager::save2()
{
    ofstream of("students.txt", ios::out);
    if (!of)
        return;
    for (iter3 = v3.begin(); iter3 != v3.end(); iter3++)
        of << *iter3;
}
void Manager::addBook()
{
    cout << "请输入书籍信息:" << ENDL;
    Book b;
    int top;
    while (cin >> b)
    {
        if (b.GetIsbn() == -1)
            break;
        v1.push_back(b);
        top = v1.size();
        map2.insert(make_pair(b.GetIsbn(), top - 1));
        b.clear();
    }
}
int Manager::search1(int isbn)
{
    iter2 = map2.find(isbn);
    if (iter2 != map2.end())
    {
        return iter2->second;
    }
    return -1;
}
void Manager::queryByIsbn()
{
    cout << "请输入你要查询的isbn号：";
    int isbn;
    cin >> isbn;
    int result = search1(isbn);
    if (result != -1)
        cout << v1[result];
    else
        cout << "not found!" << ENDL;
}
void Manager::deleteBook()
{
    cout << "请输入你要删除的isbn号：";
    int isbn;
    cin >> isbn;
    int result = search1(isbn);
    if (result != -1)
    {
        iter1 = v1.begin();
        map2.erase(map2.find(isbn));
        v1.erase(iter1 + result);
    }
}
void Manager::displayBook()
{
    for (iter1 = v1.begin(); iter1 != v1.end(); iter1++)
        cout << *iter1;
}
void Manager::modifyBook()
{
    cout << "请输入你要修改的isbn号：";
    int isbn;
    cin >> isbn;
    int top = search1(isbn);
    if (top != -1)
    {
        cout << "请输入你要修改图书总数量为：" << ENDL;
        int num;
        cin >> num;
        v1[top].SetCount(num);
    }
}
void Manager::addUser()
{
    User user;
    while (cin >> user)
    {
        if (user.GetStu_num() == -1)
            break;
        v3.push_back(user);
        int top = v3.size();
        map4.insert(make_pair(user.GetStu_num(), top - 1));
        user.clear(); //清空原因还未搞懂
    }
}
int Manager::search2(int stu_num)
{
    iter4 = map4.find(stu_num);
    if (iter4 != map4.end())
        return iter4->second;
    return -1;
}
void Manager::queryByStunum()
{
    cout << "请输入你要查找的学号：";
    int stu_num;
    cin >> stu_num;
    int result = search2(stu_num);
    if (result != -1)
    {
        cout << v3[result];
    }
}
void Manager::deleteUser()
{

    cout << "请输入你要删除的学号：";
    int stu_num;
    cin >> stu_num;
    int result1 = search2(stu_num);
    if (result1 != -1)
    {
        v3.erase(v3.begin() + result1);

        map4.erase(map4.find(stu_num));
        //通过调用stl的erase(*iter)来删除
    }
}
void Manager::modifyUser()
{
    cout << "请输入你要修改的学生信息学号：";
    int stu_num;
    cin >> stu_num;
    int top = search2(stu_num);
    if (top != -1)
    {
        cout << "请输入你要修改" << v3[top].GetName() << "的最大借阅量为：" << ENDL;
        int num;
        cin >> num;
        v3[top].SetMax(num);
    }
}
void Manager::displayUser()
{
    for (iter3 = v3.begin(); iter3 != v3.end(); iter3++)
        cout << *iter3;
}
class Client
{ //客户端（用户操作类）

private:
    vector<Book> v1;
    vector<Book>::iterator iter1;
    multimap<int, int> map2;
    multimap<int, int>::iterator iter2;
    User user;
    Time time;

public:
    Client(int id) //重要；必须带着形参
    {
        load3();
        load4(id);
        cout << "welcome to the Student Page!\n";
        cout << "___________________________ 图书馆借阅系统____________________________\n";
        cout << "                  ┏━━━━━━━━━━━━━━┓                      \n";
        cout << "                  ┃ [0]退出系统。  ┃                      \n";
        cout << "                  ┃ [1]查询图书。  ┃                      \n";
        cout << "                  ┃ [2]借阅图书。  ┃                      \n";
        cout << "                  ┃ [3]归还图书。  ┃                      \n";
        cout << "                  ┃ [4]续借图书。  ┃                      \n";
        cout << "                  ┗━━━━━━━━━━━━━━┛                      \n";
        cout << "输入要进行的操作：\n";
    }
    ~Client()
    {
        save3();
        save4();
    }
    void load3();
    void save3();
    void load4(int id);
    void save4();
    int search5(int h);
    void queryBook(); //查询书；
    void borrow();    //借书；
    void back();      //还书；
    void renew();     //续借；
};
void Client::load3()
{
    Book book;
    ifstream infile("books.txt", ios::in);
    if (!infile)
    {
        cout << "error!" << ENDL;
        return;
    }
    v1.clear();
    map2.clear();
    while (infile >> book)
    {
        if (book.GetRecords() != 0)
        {
            for (int i = 0; i < book.GetRecords(); i++)
            {
                Record r;
                infile >> r;
                book.addR(r);
            }
        }
        v1.push_back(book);
        int size = v1.size();
        map2.insert(make_pair(book.GetIsbn(), size - 1));
        book.clear();
        cout << "read one book successfully"<<ENDL;
    }
    infile.close();
}
void Client::save3()
{
    ofstream of("books.txt", ios::out);
    if (!of)
    {
        return;
    }
    for (iter1 = v1.begin(); iter1 != v1.end(); iter1++)
    {
        of << *iter1;
    }
    of.close();
}
void Client::load4(int num)
{
    cout << "请输入当前时间:" << ENDL;
    cin >> time;
    User user;
    ifstream infile("students.txt", ios::in);
    if (!infile){
        cout << "error!" << ENDL;
        return;
    }
    while (infile >> user)
    {
        if (user.GetCur_records() != 0)
        {
            for (int i = 0; i < user.GetCur_records(); i++)
            {
                Record r;
                infile >> r;
                user.addR(r);
            }
        }
        if (user.GetStu_num() == num)
        {
            this->user = user;
        }
        user.clear();
        cout << "read one user successfully"<<ENDL;
    }
    infile.close();
}
void Client::save4()
{
    vector<User> v1;
    vector<User>::iterator iter1;
    User user;
    ifstream infile("students.txt", ios::in);
    if (!infile)
    {
        return;
    }
    while (infile >> user)
    {
        if (user.GetCur_records() != 0)
        {
            for (int i = 0; i < user.GetCur_records(); i++)
            {
                Record r;
                infile >> r;
                user.addR(r);
            }
        }
        if (user == this->user)
            user = this->user; //若当前user发生变化，则替换原来txt中的user。妙啊！
        v1.push_back(user);
        user.clear();
    }
    infile.close();
    ofstream of("students.txt", ios::out);
    if (!of)
        return;
    for (iter1 = v1.begin(); iter1 != v1.end(); iter1++)
    {
        cout << "hell java" << endl;
        of << *iter1;
    }
}
int Client::search5(int isbn)
{
    iter2 = map2.find(isbn);
    if (iter2 != map2.end())
    {
        return iter2->second;
    }
    return -1;
}
void Client::queryBook()
{
    cout << "请输入图书isbn号：";
    int isbn;
    cin >> isbn;
    int top = search5(isbn);
    if (top != -1)
        v1[top].display();
    else
        cout << "Not found!" << ENDL;
}
void Client::borrow()
{
    cout << "请输入图书isbn号：";
    int isbn;
    cin >> isbn;
    int top = search5(isbn);
    user.delayjudge(time);
    if (top != -1)
    {
        if (!user.GetDelay() && user.GetCur() < user.GetMax())
        {
            v1[top].SetLend(v1[top].GetLend() + 1);
            v1[top].SetRecords(v1[top].GetRecords() + 1);   //借阅记录条数
            user.SetCur(user.GetCur() + 1);
            user.SetCur_records(user.GetCur_records() + 1);
            Record r1(user.GetStu_num(), time, isbn);
            v1[top].addRecord(r1);
            user.addRecord(r1);
        }
    }
    else
        cout << "Not found!" << ENDL;
}
void Client::back()
{
    cout << "请输入图书isbn号：";
    int isbn;
    cin >> isbn;
    int top = search5(isbn);
    if (top != -1)
    {
        v1[top].SetLend(v1[top].GetLend() - 1);
        v1[top].return_book(user.GetStu_num());
        user.SetCur(user.GetCur() - 1);
        user.return_book(isbn);
    }
    else
        cout << "Not found!" << ENDL;
}
void Client::renew()
{
    if(user.GetCur()!=0){
    cout << "请输入图书isbn号：";
    int isbn;
    cin >> isbn;
    int top = search5(isbn);
    if (top != -1)
    {
        v1[top].xujie(user.GetStu_num());
        user.xujie(isbn);
    }
    else
        cout << "Not found!" << ENDL;

    }
    else{
        cout << "You have not borrow any book,can't renew one" << ENDL;
    }
}

int main(int argc, char *argv[])
{
    
    // system(clear);  //清屏未成功
    string identity;
    cout << "请输入你的身份：学生 or 管理员" << ENDL;
    cin >> identity;
    if (identity == "学生")
    {
        cout << "请输入你的学号：" << ENDL;
        int num;
        cin >> num;
        Client stu(num);
        bool flag = true;
        while (flag)
        {
            cout << "输入序号进行操作：";
            int ch;
            cin >> ch;
            switch (ch)
            {
            case 1:
                stu.queryBook();
                break;
            case 2:
                stu.borrow();
                break;
            case 3:
                stu.back();
                break;
            case 4:
                stu.renew();
                break;
            case 0:
                flag = false;
                break;
            }
        }
    }
    else if(identity=="管理员")
    {
        Manager manager1;
        bool flag = true;
        while (flag)
        {
            cout << "输入序号进行操作：";
            int ch;
            cin >> ch;
            switch (ch)
            {
            case 1:
                manager1.addBook();
                break;
            case 2:
                manager1.queryByIsbn();
                break;
            case 3:
                manager1.deleteBook();
                break;
            case 4:
                manager1.displayBook();
                break;
            case 5:
                manager1.modifyBook();
                break;
            case 6:
                manager1.addUser();
                break;
            case 7:
                manager1.queryByStunum();
                break;
            case 8:
                manager1.deleteUser();
                break;
            case 9:
                manager1.displayUser();
                break;
            case 10:
                manager1.modifyUser();
                break;
            case 0:
                flag = false;
                break;
            }
        }
    }
    else
        cout << "你输入的身份有误，系统自动退出！" << ENDL;
    
    return 0;
}