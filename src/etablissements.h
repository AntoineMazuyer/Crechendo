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

            std::vector<std::string> listeEtablissements() const;

        private:
            Etablissements() {}
            Etablissements(const Etablissements&) = delete;
            Etablissements& operator=(const Etablissements&) = delete;
        private:
            /// SQLite database
            sqlite3 * db_;

            /// Nom
            std::string name_ {"etablissements"};
    };

};

#endif