#ifndef ADD_PASSWORD_DIALOG_H
#define ADD_PASSWORD_DIALOG_H

/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: add_password_dialog.h
 *  Description: Dialog for adding a new password entry
 * ============================================================
 */

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class Add_Password_Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Add_Password_Dialog(QWidget *parent = nullptr);

    QString get_website()  const;
    QString get_username() const;
    QString get_password() const;

private slots:
    void toggle_password_visibility();
    void generate_password();
    void validate_and_accept();

private:
    void apply_styles();
    bool is_valid() const;

    QLineEdit   *m_website_field;
    QLineEdit   *m_username_field;
    QLineEdit   *m_password_field;
    QPushButton *m_toggle_btn;
    QPushButton *m_generate_btn;
    QPushButton *m_save_btn;
    QPushButton *m_cancel_btn;
    QLabel      *m_error_label;
};

#endif // ADD_PASSWORD_DIALOG_H
