#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>



static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
bool isPrime(long what);

const char* createTable = "CREATE TABLE PRIME(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, AVGNOW REAL NOT NULL);";
bool insert(sqlite3* db, float avg) {
   char *zErrMsg = 0;
   std::ostringstream o;
   o <<  "INSERT INTO PRIME(AVGNOW) VALUES (" << avg << ");";
   std::string sql = o.str();

   int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   return rc == SQLITE_OK;


} 

int main() {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   rc = sqlite3_exec(db, createTable, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   long sum = 2;
   long n = 1;
   float currentAvg = 2.0;
   long index = 3;
   int oldPrime = 2;
   insert(db, 2);
   while(true) {
      if(isPrime(index)) {
         n++;
         int gap = index - oldPrime;
         sum = sum + gap;
         oldPrime = index;
         currentAvg = sum / (float)n;
         insert(db, currentAvg);
         std::cout << n << " " << gap << " " << currentAvg << std::endl;
      }
      index++;
   }


   sqlite3_close(db);
   return 0;
}

bool isPrime(long what) {
   int square = ceil(sqrt(what));
   for(int j = 2; j <= square; j++) {
      if(what % j == 0) {
         return false;
      }
   }
   return true;
}
