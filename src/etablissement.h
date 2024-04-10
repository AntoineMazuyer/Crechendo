#include <string>
#include <sqlite3.h>

namespace Crechendo {
    int creerEtablissement( char* nom,
                            char* adresse1,
                            char* adresse2,
                            char* cp,
                            char* ville,
                            sqlite3 * db);
};