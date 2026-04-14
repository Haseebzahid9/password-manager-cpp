/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: main.cpp
 *  Description: Application entry point — boots the login flow
 *               then opens the main vault window.
 * ============================================================
 */

#include <QApplication>
#include <QStyleFactory>
#include <QPalette>

#include "login_dialog.h"
#include "main_window.h"
#include "password_manager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setApplicationName("Haseeb Zahid Password Manager");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Haseeb Zahid");

    // Use the Fusion style as a cross-platform base
    app.setStyle(QStyleFactory::create("Fusion"));

    // Dark palette for Qt dialogs / system widgets
    QPalette dark;
    dark.setColor(QPalette::Window,          QColor(17, 17, 17));
    dark.setColor(QPalette::WindowText,      QColor(200, 200, 200));
    dark.setColor(QPalette::Base,            QColor(14, 14, 14));
    dark.setColor(QPalette::AlternateBase,   QColor(21, 21, 21));
    dark.setColor(QPalette::ToolTipBase,     QColor(30, 30, 30));
    dark.setColor(QPalette::ToolTipText,     Qt::white);
    dark.setColor(QPalette::Text,            QColor(204, 204, 204));
    dark.setColor(QPalette::Button,          QColor(37, 37, 37));
    dark.setColor(QPalette::ButtonText,      Qt::white);
    dark.setColor(QPalette::BrightText,      Qt::red);
    dark.setColor(QPalette::Highlight,       QColor(61, 155, 233));
    dark.setColor(QPalette::HighlightedText, Qt::white);
    dark.setColor(QPalette::Disabled, QPalette::Text, QColor(80, 80, 80));
    app.setPalette(dark);

    // ── Boot sequence ──────────────────────────────────────────────────────
    Password_Manager manager;

    Login_Dialog login_dlg(&manager);
    if (login_dlg.exec() != QDialog::Accepted)
        return 0;   // user closed the login window

    Main_Window window(&manager);
    window.show();

    return app.exec();
}
