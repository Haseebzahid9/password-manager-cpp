/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: file_handler.cpp
 * ============================================================
 */

#include "file_handler.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStandardPaths>

namespace File_Handler {

// Store data in the user's AppData / home directory
static QString data_dir() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    return path + "/";
}

QString load_master_hash() {
    QFile file(data_dir() + HASH_FILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    QTextStream in(&file);
    return in.readLine().trimmed();
}

void save_master_hash(const QString &hash) {
    QFile file(data_dir() + HASH_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    out << hash << "\n";
}

QVector<QStringList> load_passwords() {
    QVector<QStringList> rows;

    QFile file(data_dir() + VAULT_FILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return rows;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) continue;

        // Format: website<TAB>username<TAB>encrypted_password
        QStringList parts = line.split('\t');
        if (parts.size() == 3)
            rows.append(parts);
    }

    return rows;
}

void save_passwords(const QVector<QStringList> &rows) {
    QFile file(data_dir() + VAULT_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    for (const QStringList &row : rows) {
        if (row.size() < 3) continue;
        out << row[0] << '\t' << row[1] << '\t' << row[2] << '\n';
    }
}

} // namespace File_Handler
