#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: file_handler.h
 *  Description: All file read/write operations live here
 * ============================================================
 */

#include <QString>
#include <QStringList>
#include <QVector>

namespace File_Handler {

// Returns the SHA-256 hash stored on disk (empty if no file found)
QString load_master_hash();

// Persists the SHA-256 hash to disk
void save_master_hash(const QString &hash);

// Returns raw rows: each row is [website, username, encrypted_password]
QVector<QStringList> load_passwords();

// Writes rows back to the vault file
void save_passwords(const QVector<QStringList> &rows);

// Paths to data files (relative to the executable)
const QString HASH_FILE    = "master.dat";
const QString VAULT_FILE   = "vault.dat";

} // namespace File_Handler

#endif // FILE_HANDLER_H
