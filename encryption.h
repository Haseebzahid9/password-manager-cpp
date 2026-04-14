#ifndef ENCRYPTION_H
#define ENCRYPTION_H

/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: encryption.h
 *  Description: XOR-based encryption & SHA-256 password hashing
 * ============================================================
 */

#include <QString>

namespace Encryption {

// Encrypt plain text using XOR cipher, returns base64-encoded result
QString xor_encrypt(const QString &plain_text, const QString &key);

// Decrypt a base64-encoded XOR cipher back to plain text
QString xor_decrypt(const QString &cipher_text, const QString &key);

// One-way SHA-256 hash of the master password (for verification)
QString hash_master(const QString &password);

} // namespace Encryption

#endif // ENCRYPTION_H
