#ifndef __MYSTRING__
#define __MYSTRING__
class MyString {
private:
	char* str;
public:
	MyString(const char* str);
	//��������
	MyString(const MyString& str);
	//������ֵ
	MyString& operator=(const MyString& str);
	//����
	~MyString();
	char* GetCString()const;
};
#endif // !__MYSTRING__