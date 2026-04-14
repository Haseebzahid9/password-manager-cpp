/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: add_password_dialog.cpp
 * ============================================================
 */

#include "add_password_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>

Add_Password_Dialog::Add_Password_Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Add New Password");
    setFixedSize(440, 440);
    setModal(true);

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(36, 36, 36, 36);
    root->setSpacing(0);

    // Title
    auto *heading = new QLabel("Add New Password");
    heading->setObjectName("heading");
    root->addWidget(heading);
    root->addSpacing(4);

    auto *sub = new QLabel("Fill in the details below to save your credentials.");
    sub->setObjectName("sub");
    sub->setWordWrap(true);
    root->addWidget(sub);
    root->addSpacing(28);

    // Website
    auto *web_label = new QLabel("Website / App Name");
    web_label->setObjectName("field_label");
    root->addWidget(web_label);
    root->addSpacing(6);

    m_website_field = new QLineEdit();
    m_website_field->setPlaceholderText("e.g. github.com");
    m_website_field->setFixedHeight(38);
    root->addWidget(m_website_field);
    root->addSpacing(16);

    // Username
    auto *user_label = new QLabel("Username / Email");
    user_label->setObjectName("field_label");
    root->addWidget(user_label);
    root->addSpacing(6);

    m_username_field = new QLineEdit();
    m_username_field->setPlaceholderText("e.g. haseeb@example.com");
    m_username_field->setFixedHeight(38);
    root->addWidget(m_username_field);
    root->addSpacing(16);

    // Password row
    auto *pwd_label = new QLabel("Password");
    pwd_label->setObjectName("field_label");
    root->addWidget(pwd_label);
    root->addSpacing(6);

    auto *pwd_row = new QHBoxLayout();
    m_password_field = new QLineEdit();
    m_password_field->setEchoMode(QLineEdit::Password);
    m_password_field->setPlaceholderText("Enter or generate password...");
    m_password_field->setFixedHeight(38);

    m_toggle_btn = new QPushButton("👁");
    m_toggle_btn->setFixedSize(38, 38);
    m_toggle_btn->setObjectName("icon_btn");
    m_toggle_btn->setToolTip("Show / Hide");

    m_generate_btn = new QPushButton("⚡");
    m_generate_btn->setFixedSize(38, 38);
    m_generate_btn->setObjectName("icon_btn");
    m_generate_btn->setToolTip("Generate strong password");

    pwd_row->addWidget(m_password_field);
    pwd_row->addWidget(m_toggle_btn);
    pwd_row->addWidget(m_generate_btn);
    root->addLayout(pwd_row);

    root->addSpacing(8);
    m_error_label = new QLabel();
    m_error_label->setObjectName("error_label");
    m_error_label->setWordWrap(true);
    m_error_label->hide();
    root->addWidget(m_error_label);

    root->addStretch();

    // Buttons
    auto *btn_row = new QHBoxLayout();
    m_cancel_btn = new QPushButton("Cancel");
    m_cancel_btn->setFixedHeight(40);
    m_cancel_btn->setObjectName("cancel_btn");

    m_save_btn = new QPushButton("Save Password");
    m_save_btn->setFixedHeight(40);
    m_save_btn->setObjectName("primary_btn");

    btn_row->addWidget(m_cancel_btn);
    btn_row->addSpacing(8);
    btn_row->addWidget(m_save_btn);
    root->addLayout(btn_row);

    connect(m_save_btn,     &QPushButton::clicked, this, &Add_Password_Dialog::validate_and_accept);
    connect(m_cancel_btn,   &QPushButton::clicked, this, &QDialog::reject);
    connect(m_toggle_btn,   &QPushButton::clicked, this, &Add_Password_Dialog::toggle_password_visibility);
    connect(m_generate_btn, &QPushButton::clicked, this, &Add_Password_Dialog::generate_password);

    apply_styles();
}

QString Add_Password_Dialog::get_website()  const { return m_website_field->text().trimmed(); }
QString Add_Password_Dialog::get_username() const { return m_username_field->text().trimmed(); }
QString Add_Password_Dialog::get_password() const { return m_password_field->text(); }

void Add_Password_Dialog::toggle_password_visibility() {
    bool hidden = (m_password_field->echoMode() == QLineEdit::Password);
    m_password_field->setEchoMode(hidden ? QLineEdit::Normal : QLineEdit::Password);
    m_toggle_btn->setText(hidden ? "🙈" : "👁");
}

void Add_Password_Dialog::generate_password() {
    const QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*";
    QString password;
    for (int i = 0; i < 16; i++) {
        int idx = QRandomGenerator::global()->bounded(chars.length());
        password += chars[idx];
    }
    m_password_field->setText(password);
    m_password_field->setEchoMode(QLineEdit::Normal);
    m_toggle_btn->setText("🙈");
}

void Add_Password_Dialog::validate_and_accept() {
    if (m_website_field->text().trimmed().isEmpty()) {
        m_error_label->setText("Website / App name cannot be empty.");
        m_error_label->show();
        return;
    }
    if (m_username_field->text().trimmed().isEmpty()) {
        m_error_label->setText("Username / Email cannot be empty.");
        m_error_label->show();
        return;
    }
    if (m_password_field->text().isEmpty()) {
        m_error_label->setText("Password cannot be empty.");
        m_error_label->show();
        return;
    }
    accept();
}

void Add_Password_Dialog::apply_styles() {
    setStyleSheet(R"(
        QDialog {
            background-color: #141414;
            border: 1px solid #2a2a2a;
            border-radius: 12px;
        }
        QLabel#heading {
            font-size: 18px;
            font-weight: 700;
            color: #ffffff;
            font-family: "Segoe UI", sans-serif;
        }
        QLabel#sub {
            font-size: 13px;
            color: #777777;
            font-family: "Segoe UI", sans-serif;
        }
        QLabel#field_label {
            font-size: 11px;
            font-weight: 600;
            color: #aaaaaa;
            font-family: "Segoe UI", sans-serif;
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        QLabel#error_label {
            color: #ff6b6b;
            font-size: 12px;
            font-family: "Segoe UI", sans-serif;
        }
        QLineEdit {
            background-color: #1e1e1e;
            border: 1px solid #2e2e2e;
            border-radius: 6px;
            padding: 0 10px;
            color: #ffffff;
            font-size: 13px;
            font-family: "Segoe UI", sans-serif;
        }
        QLineEdit:focus { border: 1px solid #3d9be9; }
        QPushButton#primary_btn {
            background-color: #3d9be9;
            color: #ffffff;
            border: none;
            border-radius: 6px;
            font-size: 13px;
            font-weight: 600;
            font-family: "Segoe UI", sans-serif;
        }
        QPushButton#primary_btn:hover  { background-color: #5aaff0; }
        QPushButton#primary_btn:pressed { background-color: #2a82d0; }
        QPushButton#cancel_btn {
            background-color: #252525;
            color: #aaaaaa;
            border: 1px solid #333333;
            border-radius: 6px;
            font-size: 13px;
            font-family: "Segoe UI", sans-serif;
        }
        QPushButton#cancel_btn:hover { background-color: #2e2e2e; color: #ffffff; }
        QPushButton#icon_btn {
            background-color: #1e1e1e;
            border: 1px solid #2e2e2e;
            border-radius: 6px;
            font-size: 15px;
        }
        QPushButton#icon_btn:hover { background-color: #2a2a2a; }
    )");
}
