#include <sqlite3.h>

namespace Crechendo {
   int init(sqlite3* db) {
        // Création de la table "etablissements" si elle n'existe pas
        char const *sql = "CREATE TABLE IF NOT EXISTS etablissements ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nom TEXT NOT NULL,"
                    "adresse1 TEXT NOT NULL,"
                    "adresse2 TEXT NOT NULL,"
                    "cp TEXT NOT NULL,"
                    "ville TEXT NOT NULL"
                     ");";

           return sqlite3_exec(db, sql, NULL, 0, NULL);
   }
};