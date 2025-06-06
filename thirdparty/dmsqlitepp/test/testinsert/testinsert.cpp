#include <iostream>
#include "sqlite3pp.h"

using namespace std;

int main()
{
  try {
    sqlite3pp::database db("test.db");
    {
		db.execute(R"""(
    CREATE TABLE contacts (
      id INTEGER PRIMARY KEY,
      name TEXT NOT NULL,
      phone TEXT NOT NULL,
      address TEXT,
      UNIQUE(name, phone)
    );
  )""");
    }
    {
      db.execute("INSERT INTO contacts (name, phone) VALUES ('AAAA', '1234')");
    }
    
    {
      sqlite3pp::transaction xct(db);

      sqlite3pp::command cmd(db, "INSERT INTO contacts (name, phone) VALUES (?, ?)");

      cout << cmd.bind(1, "BBBB", sqlite3pp::copy) << endl;
      cout << cmd.bind(2, "1234", sqlite3pp::copy) << endl;
      cout << cmd.execute() << endl;

      cout << cmd.reset() << endl;

      cmd.binder() << "CCCC" << "1234";

      cout << cmd.execute() << endl;

      xct.commit();
    }

    {
      sqlite3pp::transaction xct(db, true);

      sqlite3pp::command cmd(db, "INSERT INTO contacts (name, phone) VALUES (:name, :name)");

      cout << cmd.bind(":name", "DDDD", sqlite3pp::copy) << endl;

      cout << cmd.execute() << endl;
    }
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
  }

}
