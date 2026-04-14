#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: login_dialog.h
 *  Description: Login screen — first-run setup or regular login
 * ============================================================
 */

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "password_manager.h"

class Login_Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Login_Dialog(Password_Manager *manager, QWidget *parent = nullptr);

private slots:
    void handle_submit();
    void toggle_password_visibility();

private:
    void build_ui_login();
    void build_ui_setup();
    void apply_styles();

    Password_Manager *m_manager;

    QLabel      *m_title_label;
    QLabel      *m_subtitle_label;
    QLineEdit   *m_password_field;
    QLineEdit   *m_confirm_field;   // only used during first-run setup
    QLabel      *m_confirm_label;
    QPushButton *m_submit_btn;
    QPushButton *m_toggle_btn;
    QLabel      *m_error_label;
    bool         m_is_setup_mode;
};

#endif // LOGIN_DIALOG_H
