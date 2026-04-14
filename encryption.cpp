/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: encryption.cpp
 * ============================================================
 */

#include "encryption.h"
#include <QCryptographicHash>

namespace Encryption {

QString xor_encrypt(const QString &plain_text, const QString &key) {
    if (key.isEmpty() || plain_text.isEmpty())
        return plain_text;

    QByteArray data     = plain_text.toUtf8();
    QByteArray key_data = key.toUtf8();

    for (int i = 0; i < data.size(); i++) {
        data[i] = static_cast<char>(
            static_cast<unsigned char>(data[i]) ^
            static_cast<unsigned char>(key_data[i % key_data.size()])
        );
    }

    // Base64-encode so the result is always printable ASCII
    return QString::fromLatin1(data.toBase64());
}

QString xor_decrypt(const QString &cipher_text, const QString &key) {
    if (key.isEmpty() || cipher_text.isEmpty())
        return cipher_text;

    QByteArray data     = QByteArray::fromBase64(cipher_text.toLatin1());
    QByteArray key_data = key.toUtf8();

    for (int i = 0; i < data.size(); i++) {
        data[i] = static_cast<char>(
            static_cast<unsigned char>(data[i]) ^
            static_cast<unsigned char>(key_data[i % key_data.size()])
        );
    }

    return QString::fromUtf8(data);
}

QString hash_master(const QString &password) {
    QByteArray raw  = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(raw, QCryptographicHash::Sha256);
    return QString::fromLatin1(hash.toHex());
}

} // namespace Encryption
