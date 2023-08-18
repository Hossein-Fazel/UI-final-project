#ifndef OTHERS_PROFILE_H
#define OTHERS_PROFILE_H

#include <QMainWindow>

namespace Ui {
class others_profile;
}

class others_profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit others_profile(QWidget *parent = nullptr);
    ~others_profile();

private:
    Ui::others_profile *ui;
};

#endif // OTHERS_PROFILE_H
