#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>

#include "Twitterak_Class.hpp"

namespace Ui {
class signup;
}

class signup : public QMainWindow
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_signup_btn_clicked();

    void on_type_currentIndexChanged(const QString &arg1);

    void on_btn_back_clicked();

    void on_btn_select_clicked();

private:
    Ui::signup *ui;
    twitterak app;
};

#endif // SIGNUP_H
