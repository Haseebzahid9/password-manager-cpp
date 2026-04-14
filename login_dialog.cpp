/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: login_dialog.cpp
 * ============================================================
 */

#include "login_dialog.h"
#include <QHBoxLayout>
#include <QFrame>
#include <QPixmap>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

Login_Dialog::Login_Dialog(Password_Manager *manager, QWidget *parent)
    : QDialog(parent), m_manager(manager)
{
    m_is_setup_mode = manager->is_first_run();

    setWindowTitle("Haseeb Zahid Password Manager");
    setFixedSize(420, m_is_setup_mode ? 460 : 400);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    m_is_setup_mode ? build_ui_setup() : build_ui_login();
    apply_styles();
}

void Login_Dialog::build_ui_login() {
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(40, 40, 40, 40);
    root->setSpacing(0);

    // Header
    auto *icon_label = new QLabel("🔐");
    icon_label->setAlignment(Qt::AlignCenter);
    icon_label->setStyleSheet("font-size: 48px; margin-bottom: 8px;");

    m_title_label = new QLabel("Password Manager");
    m_title_label->setAlignment(Qt::AlignCenter);
    m_title_label->setObjectName("title");

    m_subtitle_label = new QLabel("Enter your master password to continue");
    m_subtitle_label->setAlignment(Qt::AlignCenter);
    m_subtitle_label->setObjectName("subtitle");

    root->addWidget(icon_label);
    root->addSpacing(4);
    root->addWidget(m_title_label);
    root->addSpacing(6);
    root->addWidget(m_subtitle_label);
    root->addSpacing(36);

    // Password field row
    auto *pass_label = new QLabel("Master Password");
    pass_label->setObjectName("field_label");
    root->addWidget(pass_label);
    root->addSpacing(6);

    auto *pass_row = new QHBoxLayout();
    m_password_field = new QLineEdit();
    m_password_field->setEchoMode(QLineEdit::Password);
    m_password_field->setPlaceholderText("Enter master password...");
    m_password_field->setFixedHeight(40);

    m_toggle_btn = new QPushButton("👁");
    m_toggle_btn->setFixedSize(40, 40);
    m_toggle_btn->setToolTip("Show / Hide password");
    m_toggle_btn->setObjectName("icon_btn");

    pass_row->addWidget(m_password_field);
    pass_row->addWidget(m_toggle_btn);
    root->addLayout(pass_row);
    root->addSpacing(10);

    m_error_label = new QLabel();
    m_error_label->setObjectName("error_label");
    m_error_label->setAlignment(Qt::AlignCenter);
    m_error_label->hide();
    root->addWidget(m_error_label);

    root->addSpacing(24);

    m_submit_btn = new QPushButton("Unlock Vault");
    m_submit_btn->setFixedHeight(44);
    m_submit_btn->setObjectName("primary_btn");
    root->addWidget(m_submit_btn);

    root->addStretch();

    auto *footer = new QLabel("Developed by Haseeb Zahid  •  v1.0");
    footer->setAlignment(Qt::AlignCenter);
    footer->setObjectName("footer");
    root->addWidget(footer);

    // Null-init unused pointers
    m_confirm_field = nullptr;
    m_confirm_label = nullptr;

    connect(m_submit_btn, &QPushButton::clicked, this, &Login_Dialog::handle_submit);
    connect(m_toggle_btn, &QPushButton::clicked, this, &Login_Dialog::toggle_password_visibility);
    connect(m_password_field, &QLineEdit::returnPressed, this, &Login_Dialog::handle_submit);
}

void Login_Dialog::build_ui_setup() {
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(40, 40, 40, 40);
    root->setSpacing(0);

    auto *icon_label = new QLabel("🔐");
    icon_label->setAlignment(Qt::AlignCenter);
    icon_label->setStyleSheet("font-size: 48px;");

    m_title_label = new QLabel("Welcome to Password Manager");
    m_title_label->setAlignment(Qt::AlignCenter);
    m_title_label->setObjectName("title");

    m_subtitle_label = new QLabel("Create a master password to secure your vault");
    m_subtitle_label->setAlignment(Qt::AlignCenter);
    m_subtitle_label->setWordWrap(true);
    m_subtitle_label->setObjectName("subtitle");

    root->addWidget(icon_label);
    root->addSpacing(4);
    root->addWidget(m_title_label);
    root->addSpacing(6);
    root->addWidget(m_subtitle_label);
    root->addSpacing(28);

    // Password
    auto *pass_label = new QLabel("Create Master Password");
    pass_label->setObjectName("field_label");
    root->addWidget(pass_label);
    root->addSpacing(6);

    auto *pass_row = new QHBoxLayout();
    m_password_field = new QLineEdit();
    m_password_field->setEchoMode(QLineEdit::Password);
    m_password_field->setPlaceholderText("Min. 6 characters...");
    m_password_field->setFixedHeight(40);

    m_toggle_btn = new QPushButton("👁");
    m_toggle_btn->setFixedSize(40, 40);
    m_toggle_btn->setObjectName("icon_btn");

    pass_row->addWidget(m_password_field);
    pass_row->addWidget(m_toggle_btn);
    root->addLayout(pass_row);
    root->addSpacing(14);

    // Confirm
    m_confirm_label = new QLabel("Confirm Master Password");
    m_confirm_label->setObjectName("field_label");
    root->addWidget(m_confirm_label);
    root->addSpacing(6);

    m_confirm_field = new QLineEdit();
    m_confirm_field->setEchoMode(QLineEdit::Password);
    m_confirm_field->setPlaceholderText("Re-enter password...");
    m_confirm_field->setFixedHeight(40);
    root->addWidget(m_confirm_field);

    root->addSpacing(10);
    m_error_label = new QLabel();
    m_error_label->setObjectName("error_label");
    m_error_label->setAlignment(Qt::AlignCenter);
    m_error_label->setWordWrap(true);
    m_error_label->hide();
    root->addWidget(m_error_label);

    root->addSpacing(20);
    m_submit_btn = new QPushButton("Create Vault");
    m_submit_btn->setFixedHeight(44);
    m_submit_btn->setObjectName("primary_btn");
    root->addWidget(m_submit_btn);

    root->addStretch();
    auto *footer = new QLabel("Developed by Haseeb Zahid  •  v1.0");
    footer->setAlignment(Qt::AlignCenter);
    footer->setObjectName("footer");
    root->addWidget(footer);

    connect(m_submit_btn, &QPushButton::clicked, this, &Login_Dialog::handle_submit);
    connect(m_toggle_btn, &QPushButton::clicked, this, &Login_Dialog::toggle_password_visibility);
    connect(m_confirm_field, &QLineEdit::returnPressed, this, &Login_Dialog::handle_submit);
}

void Login_Dialog::handle_submit() {
    QString pwd = m_password_field->text();

    if (m_is_setup_mode) {
        if (pwd.length() < 6) {
            m_error_label->setText("Password must be at least 6 characters.");
            m_error_label->show();
            return;
        }
        QString confirm = m_confirm_field->text();
        if (!m_manager->setup_master(pwd, confirm)) {
            m_error_label->setText("Passwords do not match. Please try again.");
            m_error_label->show();
            m_confirm_field->clear();
            m_confirm_field->setFocus();
            return;
        }
    } else {
        if (!m_manager->verify_master(pwd)) {
            m_error_label->setText("Incorrect password. Please try again.");
            m_error_label->show();
            m_password_field->clear();
            m_password_field->setFocus();
            return;
        }
    }

    accept();
}

void Login_Dialog::toggle_password_visibility() {
    bool hidden = (m_password_field->echoMode() == QLineEdit::Password);
    QLineEdit::EchoMode mode = hidden ? QLineEdit::Normal : QLineEdit::Password;
    m_password_field->setEchoMode(mode);
    if (m_confirm_field)
        m_confirm_field->setEchoMode(mode);
    m_toggle_btn->setText(hidden ? "🙈" : "👁");
}

void Login_Dialog::apply_styles() {
    setStyleSheet(R"(
        QDialog {
            background-color: #141414;
            border: 1px solid #2a2a2a;
            border-radius: 12px;
        }
        QLabel#title {
            font-size: 20px;
            font-weight: 700;
            color: #ffffff;
            font-family: "Segoe UI", sans-serif;
        }
        QLabel#subtitle {
            font-size: 13px;
            color: #888888;
            font-family: "Segoe UI", sans-serif;
        }
        QLabel#field_label {
            font-size: 12px;
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
        QLabel#footer {
            color: #444444;
            font-size: 11px;
            font-family: "Segoe UI", sans-serif;
        }
        QLineEdit {
            background-color: #1e1e1e;
            border: 1px solid #333333;
            border-radius: 6px;
            padding: 0px 12px;
            color: #ffffff;
            font-size: 14px;
            font-family: "Segoe UI", sans-serif;
        }
        QLineEdit:focus {
            border: 1px solid #3d9be9;
        }
        QPushButton#primary_btn {
            background-color: #3d9be9;
            color: #ffffff;
            border: none;
            border-radius: 6px;
            font-size: 14px;
            font-weight: 600;
            font-family: "Segoe UI", sans-serif;
        }
        QPushButton#primary_btn:hover {
            background-color: #5aaff0;
        }
        QPushButton#primary_btn:pressed {
            background-color: #2a82d0;
        }
        QPushButton#icon_btn {
            background-color: #1e1e1e;
            border: 1px solid #333333;
            border-radius: 6px;
            font-size: 16px;
        }
        QPushButton#icon_btn:hover {
            background-color: #2a2a2a;
        }
    )");
}
