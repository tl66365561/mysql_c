#include<my_global.h>
#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
static const char* host="localhost";
static const char* user="root";
static const char* password="tl8990910";
static const char* database="helloworld";

static void finish_with_error(MYSQL* con)
{
	fprintf(stderr,"MYSQL创建失败:%s",mysql_error(con));
	if(con)
	{
		mysql_close(con);
		
		}
     exit (EXIT_FAILURE);
	
	
	}





int main(int argc ,char* argv[])
{
	if(argc<2)
	{
		fprintf(stderr,"必须指定姓名\n");
		return EXIT_FAILURE;
		
		}
	//创建MySQL结构
	MYSQL* con=mysql_init(NULL);
	if(con==NULL)
	{
		finish_with_error(con);
		}
	
	//连接数据库
	if(mysql_real_connect(con,host,user,password,database,0,NULL,0)==NULL)
	{
		finish_with_error(con);
		}
    //设置客户端字符编码  utf-8
	if(mysql_set_character_set(con,"utf8")!=0){
		
		finish_with_error(con);
		
		}
	//拼接查询query 
	char query[1000];
	sprintf(query,"select * from students where name = '%s'",argv[1]);
	printf("拼接出的 SQL : %s\n",query);

   //获取查询结果       select之类的sql执行完毕后必须获取！！！
   MYSQL_RES* result=mysql_store_result(con);
   if(con==NULL)
   {
	   finish_with_error(con);
	   
	   }
	
  
    //mysql_num_fields :函数返回结果中的字段数
	int num_fields=mysql_num_fields(result);
	printf("一共有%d列",num_fields);
	


	// 分别打印每一行
	//存在问题： 1. while条件是怎么控制变化的？    
	//           2.初始化的lengths表达的意思？
	
	MYSQL_ROW row;
	 while ((row = mysql_fetch_row(result))) {        //检索一个结果集合的下一行，会自动滑向下一行
	 unsigned long *lengths;
	 lengths = mysql_fetch_lengths(result);                 //获得行中字段值的长度
	 for (int i = 0; i < num_fields; ++i) {
	 printf("[%.*s] ", (int)lengths[i], row[i] ? row[i] : "NULL");
	 }
	 printf("\n");
	 }
	 // 释放结果集
	 mysql_free_result(result);
	 // 关闭连接
	 mysql_close(con);
	

	
	return 0;
	}







