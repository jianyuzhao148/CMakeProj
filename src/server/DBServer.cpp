#include "DBServer.h"
#include "stdio.h"
#include <mysql/mysql.h>
#include <hiredis/hiredis.h>
#include <string.h>


DBServer::DBServer() {
}

bool DBServer::connectRedis() {
	rContext = redisConnect(server, redisPort);
	if (rContext->err) {
		printf("Redis Connnect Faild\n");
		return false;
	}
	else {
		printf("Redis Connnect Success\n");
	}
	return true;
}

void DBServer::setString(char* key, char* value) {
	if (!rContext) {
		return;
	}
	redisReply* replay = (redisReply*)redisCommand(rContext, "SET %s %s", key, value);
	if (replay) {
		redisFree(rContext);
		rContext = NULL;
		return;
	}
	freeReplyObject(replay);
	return;
}

void DBServer::excuteSQL(char* sql) {
	if (!connecte) {
		return;
	}
	MYSQL_RES* result;
	MYSQL_ROW sql_row;
	if (!mysql_query(connecte, sql)) {
		int i, j;
		result = mysql_store_result(connecte);
		if (result) {
			while (sql_row = mysql_fetch_row(result)) {
				for (i = 0; i < mysql_num_fields(result); i++) {
					printf("%s\n", sql_row[i]);
				}
			}
		}
	}
	else {
		printf("SQL Query Faild!");
	}
}

bool DBServer::connectMysql() {
	connecte = mysql_init(NULL);
	return  mysql_real_connect(connecte, server, user, password,
		database, 0, NULL, 0);
}