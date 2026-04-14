#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: password_manager.h
 *  Description: Core logic — master auth & password vault
 * ============================================================
 */

#include <QString>
#include <QVector>

struct Password_Entry {
    int     id;
    QString website;
    QString username;
    QString encrypted_password; // stored encrypted; never plain
};

class Password_Manager {
public:
    Password_Manager();

    // Returns true if no master password has been set up yet
    bool is_first_run() const;

    // Create master password for the first time (returns false if mismatch)
    bool setup_master(const QString &password, const QString &confirm);

    // Verify password at login; stores key in memory on success
    bool verify_master(const QString &password);

    // Locks the vault (clears in-memory key)
    void lock();

    // Adds a new entry; encrypts the password before storing
    void add_entry(const QString &website,
                   const QString &username,
                   const QString &plain_password);

    // Removes entry by id; returns false if not found
    bool delete_entry(int id);

    // Returns decrypted password for the given entry id
    QString get_decrypted(int id) const;

    const QVector<Password_Entry>& get_entries() const;

    bool is_unlocked() const;

private:
    QVector<Password_Entry> m_entries;
    QString                 m_master_key;   // plain password in memory (never saved)
    QString                 m_master_hash;  // SHA-256 hash (saved to file)
    bool                    m_unlocked;
    int                     m_next_id;

    void load_data();
    void save_data() const;

    // Finds entry index by id (-1 if not found)
    int find_index(int id) const;
};

#endif // PASSWORD_MANAGER_H
