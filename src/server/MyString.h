#ifndef __MYSTRING__
#define __MYSTRING__
class MyString {
private:
	char* str;
public:
	MyString(const char* str);
	//拷贝构造
	MyString(const MyString& str);
	//拷贝赋值
	MyString& operator=(const MyString& str);
	//析构
	~MyString();
	char* GetCString()const;
};
#endif // !__MYSTRING__