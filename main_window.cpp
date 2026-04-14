/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: main_window.cpp
 * ============================================================
 */

#include "main_window.h"
#include "add_password_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QClipboard>
#include <QApplication>
#include <QFrame>
#include <QSet>
#include <QToolButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTimer>

Main_Window::Main_Window(Password_Manager *manager, QWidget *parent)
    : QMainWindow(parent), m_manager(manager)
{
    setWindowTitle("Haseeb Zahid Password Manager");
    setMinimumSize(880, 580);
    resize(1000, 640);

    build_ui();
    apply_styles();
    refresh_table();

    // Simple menu bar
    QMenu *file_menu = menuBar()->addMenu("File");
    QAction *lock_action = file_menu->addAction("Lock && Exit");
    connect(lock_action, &QAction::triggered, this, [this]() {
        m_manager->lock();
        close();
    });

    QMenu *help_menu = menuBar()->addMenu("Help");
    QAction *about_action = help_menu->addAction("About");
    connect(about_action, &QAction::triggered, this, &Main_Window::show_about);
}

void Main_Window::build_ui() {
    m_central = new QWidget();
    setCentralWidget(m_central);

    auto *root = new QVBoxLayout(m_central);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    // ── Top header bar ─────────────────────────────────────────────────────
    auto *header = new QWidget();
    header->setObjectName("header_bar");
    header->setFixedHeight(72);

    auto *header_layout = new QHBoxLayout(header);
    header_layout->setContentsMargins(24, 0, 24, 0);

    auto *app_title = new QLabel("🔐  Haseeb Zahid Password Manager");
    app_title->setObjectName("app_title");

    header_layout->addWidget(app_title);
    header_layout->addStretch();
    root->addWidget(header);

    // ── Toolbar row ────────────────────────────────────────────────────────
    auto *toolbar = new QWidget();
    toolbar->setObjectName("toolbar");
    toolbar->setFixedHeight(60);

    auto *toolbar_layout = new QHBoxLayout(toolbar);
    toolbar_layout->setContentsMargins(20, 10, 20, 10);
    toolbar_layout->setSpacing(10);

    m_add_btn = new QPushButton("＋  Add Password");
    m_add_btn->setObjectName("add_btn");
    m_add_btn->setFixedHeight(38);

    m_delete_btn = new QPushButton("🗑  Delete");
    m_delete_btn->setObjectName("delete_btn");
    m_delete_btn->setFixedHeight(38);

    m_search_field = new QLineEdit();
    m_search_field->setPlaceholderText("🔍  Search by website or username...");
    m_search_field->setFixedHeight(38);
    m_search_field->setMinimumWidth(280);

    m_count_label = new QLabel("0 entries");
    m_count_label->setObjectName("count_label");

    toolbar_layout->addWidget(m_add_btn);
    toolbar_layout->addWidget(m_delete_btn);
    toolbar_layout->addStretch();
    toolbar_layout->addWidget(m_count_label);
    toolbar_layout->addSpacing(12);
    toolbar_layout->addWidget(m_search_field);
    root->addWidget(toolbar);

    // Divider
    auto *divider = new QFrame();
    divider->setFrameShape(QFrame::HLine);
    divider->setObjectName("divider");
    root->addWidget(divider);

    // ── Table ──────────────────────────────────────────────────────────────
    build_table();
    root->addWidget(m_table);

    // ── Status bar ─────────────────────────────────────────────────────────
    auto *status_bar = new QWidget();
    status_bar->setObjectName("status_bar");
    status_bar->setFixedHeight(30);

    auto *status_layout = new QHBoxLayout(status_bar);
    status_layout->setContentsMargins(20, 0, 20, 0);

    auto *status_text = new QLabel("Vault is unlocked  •  Developed by Haseeb Zahid");
    status_text->setObjectName("status_text");
    status_layout->addWidget(status_text);
    status_layout->addStretch();

    root->addWidget(status_bar);

    connect(m_add_btn,    &QPushButton::clicked, this, &Main_Window::open_add_dialog);
    connect(m_delete_btn, &QPushButton::clicked, this, &Main_Window::delete_selected);
    connect(m_search_field, &QLineEdit::textChanged, this, &Main_Window::filter_entries);
}

void Main_Window::build_table() {
    m_table = new QTableWidget(0, 5);

    QStringList headers = { "  Website / App", "  Username / Email", "  Password", "  Actions", "  Copy" };
    m_table->setHorizontalHeaderLabels(headers);

    m_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    m_table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    m_table->setColumnWidth(3, 110);
    m_table->setColumnWidth(4, 80);

    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setAlternatingRowColors(true);
    m_table->verticalHeader()->setVisible(false);
    m_table->setShowGrid(false);
    m_table->setFocusPolicy(Qt::NoFocus);
    m_table->verticalHeader()->setDefaultSectionSize(48);
}

void Main_Window::refresh_table(const QString &filter) {
    m_revealed_rows.clear();
    m_table->setRowCount(0);

    const QVector<Password_Entry> &entries = m_manager->get_entries();
    QString query = filter.trimmed().toLower();

    int displayed = 0;
    for (const Password_Entry &entry : entries) {
        if (!query.isEmpty()) {
            bool match = entry.website.toLower().contains(query)
                      || entry.username.toLower().contains(query);
            if (!match) continue;
        }

        int row = m_table->rowCount();
        m_table->insertRow(row);

        // Store the entry id in the first column's data
        auto *website_item = new QTableWidgetItem("  " + entry.website);
        website_item->setData(Qt::UserRole, entry.id);
        m_table->setItem(row, 0, website_item);

        m_table->setItem(row, 1, new QTableWidgetItem("  " + entry.username));
        m_table->setItem(row, 2, new QTableWidgetItem("  ••••••••"));

        // Reveal/hide toggle button
        auto *reveal_btn = new QPushButton("👁  Reveal");
        reveal_btn->setObjectName("reveal_btn");
        int captured_row = row;
        connect(reveal_btn, &QPushButton::clicked, this, [this, captured_row]() {
            toggle_password_in_row(captured_row);
        });
        m_table->setCellWidget(row, 3, reveal_btn);

        // Copy button
        auto *copy_btn = new QPushButton("📋");
        copy_btn->setObjectName("copy_btn");
        copy_btn->setToolTip("Copy password to clipboard");
        int captured_row2 = row;
        connect(copy_btn, &QPushButton::clicked, this, [this, captured_row2]() {
            copy_password(captured_row2);
        });
        m_table->setCellWidget(row, 4, copy_btn);

        displayed++;
    }

    m_count_label->setText(QString::number(displayed) + " entr" + (displayed == 1 ? "y" : "ies"));
}

void Main_Window::toggle_password_in_row(int row) {
    auto *website_item = m_table->item(row, 0);
    if (!website_item) return;

    int entry_id = website_item->data(Qt::UserRole).toInt();

    if (m_revealed_rows.contains(row)) {
        // Hide it
        m_table->item(row, 2)->setText("  ••••••••");
        m_revealed_rows.remove(row);
        auto *btn = qobject_cast<QPushButton*>(m_table->cellWidget(row, 3));
        if (btn) btn->setText("👁  Reveal");
    } else {
        // Decrypt and show
        QString plain = m_manager->get_decrypted(entry_id);
        m_table->item(row, 2)->setText("  " + plain);
        m_revealed_rows.insert(row);
        auto *btn = qobject_cast<QPushButton*>(m_table->cellWidget(row, 3));
        if (btn) btn->setText("🙈  Hide");
    }
}

void Main_Window::copy_password(int row) {
    auto *website_item = m_table->item(row, 0);
    if (!website_item) return;

    int entry_id = website_item->data(Qt::UserRole).toInt();
    QString plain = m_manager->get_decrypted(entry_id);

    QApplication::clipboard()->setText(plain);

    // Brief visual feedback on the button
    auto *btn = qobject_cast<QPushButton*>(m_table->cellWidget(row, 4));
    if (btn) {
        btn->setText("✅");
        QTimer::singleShot(1500, btn, [btn]() { btn->setText("📋"); });
    }
}

void Main_Window::open_add_dialog() {
    Add_Password_Dialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    m_manager->add_entry(dialog.get_website(),
                         dialog.get_username(),
                         dialog.get_password());
    refresh_table(m_search_field->text());
}

void Main_Window::delete_selected() {
    int row = m_table->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "No Selection", "Please select an entry to delete.");
        return;
    }

    auto *website_item = m_table->item(row, 0);
    if (!website_item) return;

    QString site = website_item->text().trimmed();
    int entry_id = website_item->data(Qt::UserRole).toInt();

    QMessageBox confirm;
    confirm.setWindowTitle("Delete Entry");
    confirm.setText("Delete the entry for <b>" + site + "</b>?");
    confirm.setInformativeText("This action cannot be undone.");
    confirm.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    confirm.setDefaultButton(QMessageBox::Cancel);
    confirm.setStyleSheet("QLabel { color: white; } QMessageBox { background-color: #1e1e1e; }");

    if (confirm.exec() == QMessageBox::Yes) {
        m_manager->delete_entry(entry_id);
        refresh_table(m_search_field->text());
    }
}

void Main_Window::filter_entries(const QString &text) {
    refresh_table(text);
}

void Main_Window::show_about() {
    QMessageBox::about(this, "About",
        "<b>Haseeb Zahid Password Manager</b><br>"
        "Version 1.0<br><br>"
        "Developed by <b>Haseeb Zahid</b><br>"
        "Built with C++ and Qt Framework<br><br>"
        "A secure, local password vault with XOR encryption<br>"
        "and SHA-256 master password hashing."
    );
}

void Main_Window::apply_styles() {
    menuBar()->setStyleSheet(
        "QMenuBar { background-color: #0d0d0d; color: #888; border-bottom: 1px solid #1e1e1e; }"
        "QMenuBar::item:selected { background-color: #1e1e1e; color: white; }"
        "QMenu { background-color: #1a1a1a; color: white; border: 1px solid #2a2a2a; }"
        "QMenu::item:selected { background-color: #3d9be9; }"
    );

    m_central->setStyleSheet(R"(
        QWidget {
            background-color: #111111;
            font-family: "Segoe UI", sans-serif;
        }
        QWidget#header_bar {
            background-color: #0d0d0d;
            border-bottom: 1px solid #1e1e1e;
        }
        QLabel#app_title {
            font-size: 17px;
            font-weight: 700;
            color: #ffffff;
            letter-spacing: 0.5px;
        }
        QWidget#toolbar {
            background-color: #141414;
            border-bottom: 1px solid #1e1e1e;
        }
        QFrame#divider { color: #1e1e1e; }
        QPushButton#add_btn {
            background-color: #3d9be9;
            color: white;
            border: none;
            border-radius: 6px;
            font-size: 13px;
            font-weight: 600;
            padding: 0 16px;
        }
        QPushButton#add_btn:hover  { background-color: #5aaff0; }
        QPushButton#add_btn:pressed { background-color: #2a82d0; }
        QPushButton#delete_btn {
            background-color: #252525;
            color: #cc4444;
            border: 1px solid #333;
            border-radius: 6px;
            font-size: 13px;
            padding: 0 14px;
        }
        QPushButton#delete_btn:hover { background-color: #cc4444; color: white; border-color: #cc4444; }
        QLineEdit {
            background-color: #1e1e1e;
            border: 1px solid #2a2a2a;
            border-radius: 6px;
            padding: 0 10px;
            color: #cccccc;
            font-size: 13px;
        }
        QLineEdit:focus { border: 1px solid #3d9be9; color: white; }
        QLabel#count_label { color: #555555; font-size: 13px; }
        QTableWidget {
            background-color: #111111;
            alternate-background-color: #151515;
            border: none;
            color: #cccccc;
            font-size: 13px;
            selection-background-color: #1e3a5f;
            selection-color: #ffffff;
            outline: none;
        }
        QHeaderView::section {
            background-color: #0d0d0d;
            color: #555555;
            font-size: 11px;
            font-weight: 600;
            text-transform: uppercase;
            letter-spacing: 1px;
            border: none;
            border-bottom: 1px solid #1e1e1e;
            padding: 8px 0;
        }
        QPushButton#reveal_btn {
            background-color: transparent;
            color: #3d9be9;
            border: 1px solid #1e3a5f;
            border-radius: 4px;
            font-size: 12px;
            margin: 6px;
        }
        QPushButton#reveal_btn:hover { background-color: #1e3a5f; }
        QPushButton#copy_btn {
            background-color: transparent;
            color: #777777;
            border: 1px solid #252525;
            border-radius: 4px;
            font-size: 14px;
            margin: 6px;
        }
        QPushButton#copy_btn:hover { color: white; border-color: #444; }
        QWidget#status_bar { background-color: #0d0d0d; border-top: 1px solid #1e1e1e; }
        QLabel#status_text { color: #333333; font-size: 11px; }
    )");
}
