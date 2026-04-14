#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/*
 * ============================================================
 *  Haseeb Zahid Password Manager
 *  Developed by Haseeb Zahid
 *  File: main_window.h
 *  Description: Main vault dashboard — table + controls
 * ============================================================
 */

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "password_manager.h"

class Main_Window : public QMainWindow {
    Q_OBJECT

public:
    explicit Main_Window(Password_Manager *manager, QWidget *parent = nullptr);

private slots:
    void open_add_dialog();
    void delete_selected();
    void toggle_password_in_row(int row);
    void filter_entries(const QString &text);
    void copy_password(int row);
    void show_about();

private:
    void build_ui();
    void build_toolbar();
    void build_table();
    void refresh_table(const QString &filter = "");
    void apply_styles();

    Password_Manager *m_manager;

    QWidget      *m_central;
    QTableWidget *m_table;
    QLineEdit    *m_search_field;
    QLabel       *m_count_label;
    QPushButton  *m_add_btn;
    QPushButton  *m_delete_btn;

    // Track which rows have their passwords revealed
    QSet<int>     m_revealed_rows;
};

#endif // MAIN_WINDOW_H
