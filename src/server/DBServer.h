#ifndef __DBSERVER__
#define __DBSERVER__
#include <mysql/mysql.h>
#include <hiredis/hiredis.h>

class DBServer {
private:
	MYSQL* connecte;
	redisContext* rContext;
	const char* server = "127.0.0.1";
	const char* user = "test";
	const char* password = "123456";
	const char* database = "demo";
	const int redisPort = 6379;
public:
	struct user
	{
		int id;
		char* name;
		char* phone;
	};
	DBServer();
	bool connectMysql();
	bool connectRedis();
	void excuteSQL(char* sql);
	void setString(char* key, char* value);
};
#endif // !__DBSERVER__