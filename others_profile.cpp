#include "others_profile.h"
#include "ui_others_profile.h"

others_profile::others_profile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::others_profile)
{
    ui->setupUi(this);
}

others_profile::~others_profile()
{
    delete ui;
}
