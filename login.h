#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "Twitterak_Class.hpp"

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_login_btn_clicked();

    void on_btn_back_clicked();

private:
    Ui::login *ui;
    twitterak app;
};

#endif // LOGIN_H
