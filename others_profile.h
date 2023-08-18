#ifndef OTHERS_PROFILE_H
#define OTHERS_PROFILE_H

#include <QMainWindow>

#include "Base_User.hpp"

namespace Ui {
class others_profile;
}

class others_profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit others_profile(QWidget *parent = nullptr);
    ~others_profile();

    void fill_out(Base_User *user, std::string type);

private:
    Ui::others_profile *ui;
};

#endif // OTHERS_PROFILE_H
