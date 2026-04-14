/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: password_manager.cpp
 * ============================================================
 */

#include "password_manager.h"
#include "encryption.h"
#include "file_handler.h"

Password_Manager::Password_Manager()
    : m_unlocked(false), m_next_id(1)
{
    m_master_hash = File_Handler::load_master_hash();
}

bool Password_Manager::is_first_run() const {
    return m_master_hash.isEmpty();
}

bool Password_Manager::setup_master(const QString &password, const QString &confirm) {
    if (password != confirm || password.isEmpty())
        return false;

    m_master_hash = Encryption::hash_master(password);
    m_master_key  = password;
    m_unlocked    = true;

    File_Handler::save_master_hash(m_master_hash);
    save_data();
    return true;
}

bool Password_Manager::verify_master(const QString &password) {
    if (Encryption::hash_master(password) != m_master_hash)
        return false;

    m_master_key = password;
    m_unlocked   = true;
    load_data();
    return true;
}

void Password_Manager::lock() {
    m_master_key.clear();
    m_unlocked = false;
    m_entries.clear();
}

void Password_Manager::add_entry(const QString &website,
                                  const QString &username,
                                  const QString &plain_password)
{
    if (!m_unlocked) return;

    Password_Entry entry;
    entry.id                 = m_next_id++;
    entry.website            = website;
    entry.username           = username;
    entry.encrypted_password = Encryption::xor_encrypt(plain_password, m_master_key);

    m_entries.append(entry);
    save_data();
}

bool Password_Manager::delete_entry(int id) {
    int idx = find_index(id);
    if (idx == -1) return false;

    m_entries.remove(idx);
    save_data();
    return true;
}

QString Password_Manager::get_decrypted(int id) const {
    int idx = find_index(id);
    if (idx == -1 || !m_unlocked) return QString();

    return Encryption::xor_decrypt(m_entries[idx].encrypted_password, m_master_key);
}

const QVector<Password_Entry>& Password_Manager::get_entries() const {
    return m_entries;
}

bool Password_Manager::is_unlocked() const {
    return m_unlocked;
}

// ── private helpers ────────────────────────────────────────────────────────

int Password_Manager::find_index(int id) const {
    for (int i = 0; i < m_entries.size(); i++) {
        if (m_entries[i].id == id)
            return i;
    }
    return -1;
}

void Password_Manager::load_data() {
    m_entries.clear();
    m_next_id = 1;

    QVector<QStringList> rows = File_Handler::load_passwords();
    for (const QStringList &row : rows) {
        if (row.size() < 3) continue;

        Password_Entry e;
        e.id                 = m_next_id++;
        e.website            = row[0];
        e.username           = row[1];
        e.encrypted_password = row[2];
        m_entries.append(e);
    }
}

void Password_Manager::save_data() const {
    QVector<QStringList> rows;
    for (const Password_Entry &e : m_entries) {
        rows.append({ e.website, e.username, e.encrypted_password });
    }
    File_Handler::save_passwords(rows);
}
