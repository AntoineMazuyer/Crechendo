#include <etablissement.h>

namespace Crechendo {
    int creerEtablissement( char* nom,
                            char* adresse1,
                            char* adresse2,
                            char* cp,
                            char* ville,
                            sqlite3 * db) {
        char const *sql = "INSERT INTO etablissements (nom, adresse1, adresse2, cp, ville) VALUES (?, ?, ?, ?, ?)";
        sqlite3_stmt *stmt;
    
        // Préparation de la requête SQL
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de la préparation de la requête : %s\n", sqlite3_errmsg(db));
            return 1;
        }

        // Liaison des paramètres à la requête SQL
        sqlite3_bind_text(stmt, 1, nom, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, adresse1, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, adresse2, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, cp, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, ville, -1, SQLITE_STATIC);
    
        // Exécution de la requête SQL
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Erreur lors de l'exécution de la requête : %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return 1;
        }
    
       // Finalisation de la requête
       sqlite3_finalize(stmt);
       return 0;
    }
};