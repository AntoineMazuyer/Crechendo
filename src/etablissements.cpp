#include <iostream>

#include <etablissements.h>

namespace Crechendo {
    
    void Etablissements::init( sqlite3 * db ) {
        // Création de la table "etablissements" si elle n'existe pas
        db_ = db;
        std::string sql = "CREATE TABLE IF NOT EXISTS " 
                          + name_ + 
                          " (nom TEXT NOT NULL PRIMARY KEY,"
                          "adresse1 TEXT NOT NULL,"
                          "adresse2 TEXT NOT NULL,"
                          "cp TEXT NOT NULL,"
                          "ville TEXT NOT NULL,"
                          "CHECK(nom <> '')"
                          ");";

        int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
        if (rc != 0)
        {
            fprintf(stderr, "Erreur lors de l'initialisation de la table.\n");
            sqlite3_close(db);
        }
    }
    void Etablissements::creerEtablissement(std::string const &nom,
                                            std::string const &adresse1,
                                            std::string const &adresse2,
                                            std::string const &cp,
                                            std::string const &ville)
    {
        std::string sql = "INSERT INTO "+  name_ + " (nom, adresse1, adresse2, cp, ville) VALUES (?, ?, ?, ?, ?)";
        sqlite3_stmt *stmt;
    
        // Préparation de la requête SQL
        int rc = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de la préparation de la requête : %s\n", sqlite3_errmsg(db_));
        }

        // Liaison des paramètres à la requête SQL
        sqlite3_bind_text(stmt, 1, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, adresse1.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, adresse2.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, cp.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, ville.c_str(), -1, SQLITE_STATIC);
    
        // Exécution de la requête SQL
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Erreur lors de l'exécution de la requête : %s\n", sqlite3_errmsg(db_));
            sqlite3_finalize(stmt);
        }
    
       // Finalisation de la requête
       sqlite3_finalize(stmt);
    }

    int callback(void *data, int argc, char **argv, char **azColName)
    {
        std::vector<std::string> *noms = static_cast<std::vector<std::string> *>(data);

        for (int i = 0; i < argc; i++)
        {
            if (std::string(azColName[i]) == "nom" && argv[i])
            {
                noms->push_back(argv[i]);
            }
        }

        return 0;
    }
    std::vector< std::string > Etablissements::listeEtablissements() const {
        std::vector< std::string > liste;
        std::string sql = "SELECT nom FROM " + name_ + ";";
        std::cout << sql << std::endl;
        int rc = sqlite3_exec(db_, sql.c_str(), callback, &liste, nullptr);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Erreur lors de la récupération des clés primaires : " << sqlite3_errmsg(db_) << std::endl;
        }
        return liste;
    }
};