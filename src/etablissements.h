#ifndef __CRECHENDO__ETABLISSEMENTS__
#define __CRECHENDO__ETABLISSEMENTS__

#include <sqlite3.h>

#include <vector>
#include <string>

namespace Crechendo {
    
    class Etablissements {
        public:
            static Etablissements & getInstance()
            {
                static Etablissements instance;
                return instance;
            }
            void init( sqlite3 * db );
            void creerEtablissement(std::string const & nom,
                                    std::string const & adresse1,
                                    std::string const& adresse2,
                                    std::string const& cp,
                                    std::string const & ville);

            void supprimerEtablissement( std::string const & nom);

            std::vector<std::string> listeEtablissements();

        private:
            Etablissements() {}
            Etablissements(const Etablissements&) = delete;
            Etablissements& operator=(const Etablissements&) = delete;

            std::vector<std::string> listeEtablissementsSQL();
        private:
            /// SQLite database
            sqlite3 * db_;

            /// Nom
            std::string name_ {"etablissements"};

            bool to_update_ {true};
            std::vector< std::string > listeEtablissements_;

    };

};

#endif