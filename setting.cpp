#include "setting.h"
#include <QtGui>

//QString someValue = settings.value("some/config/key", "default value if unset").toString();

GlobalSetting* GlobalSetting::m_instance = 0;

GlobalSetting* GlobalSetting::getObj(){
    if(m_instance == 0){
        m_instance = new GlobalSetting("./config.ini", QSettings::IniFormat);
    }
    return m_instance;
}

GlobalSetting::GlobalSetting(const QString &fileName, Format format, QObject *parent) :
    QSettings(fileName, format, parent)
{

}

GlobalSetting* appSetting = GlobalSetting::getObj();

//#####################
// Visible window
//#####################

SettingWin::SettingWin(QDialog *parent) :
    QDialog(parent)
{
    setFixedSize(600, 300);
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::ListMode);
    contentsWidget->setIconSize(QSize(32, 32));
    contentsWidget->setFixedSize(150, 280);

    generalPage = new GeneralPage(); //TODO Объединить все в интерфейс
    dataBasePage = new DataBasePage();
    languagePage = new LanguagePage();
    skinPage = new SkinPage();
    apiPage = new ApiPage();
    helpPage = new HelpPage();

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(generalPage);
    pagesWidget->addWidget(dataBasePage);
    pagesWidget->addWidget(languagePage);
    pagesWidget->addWidget(skinPage);
    pagesWidget->addWidget(apiPage);
    pagesWidget->addWidget(helpPage);

    QPushButton *closeButton = new QPushButton(tr("Cancel"));
    QPushButton *saveButton = new QPushButton(tr("Save"));

    QListWidgetItem *configButton = new QListWidgetItem(QIcon("./style/default/general_settting.png"), tr("Configuration"), contentsWidget);
    QListWidgetItem *databaseButton = new QListWidgetItem(QIcon("./style/default/database_setting.png"), tr("Database"), contentsWidget);
    QListWidgetItem *languageButton = new QListWidgetItem(QIcon("./style/default/language_setting.png"), tr("Language"), contentsWidget);
    QListWidgetItem *skinButton = new QListWidgetItem(QIcon("./style/default/appearance_setting.png"), tr("Skin"), contentsWidget);
    QListWidgetItem *apiButton = new QListWidgetItem(QIcon("./style/default/api_setting.png"), tr("TranslateApi"), contentsWidget);
    QListWidgetItem *helpButton = new QListWidgetItem(QIcon("./style/default/help_setting.gif"), tr("Help"), contentsWidget);

    contentsWidget->setCurrentRow(0);

    connect(contentsWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
                      this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
    connect(closeButton, SIGNAL(clicked()),
                   this, SLOT(close()));
    connect(saveButton, SIGNAL(clicked()),
                  this, SLOT(save()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("settings"));
}

void SettingWin::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current){
        current = previous;
    }
    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void SettingWin::save(){
    generalPage->save();
    dataBasePage->save();
    skinPage->save();
    this->close();
}

//#####################
// Pages
//#####################

GeneralPage::GeneralPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *timingGroup = new QGroupBox(tr("Timing:"));

    QLabel *timingUpLabel = new QLabel(tr("show up word for seconds:"));
    QLabel *timingDownLabel = new QLabel(tr("show down word for seconds:"));
    QLabel *timingPauseLabel = new QLabel(tr("pause seconds:"));
    timingUpSpin = new QDoubleSpinBox();
    timingUpSpin->setValue(appSetting->value("window/timing/uptext", 0).toDouble());
    timingDownSpin = new QDoubleSpinBox();
    timingDownSpin->setValue(appSetting->value("window/timing/downtext", 5).toDouble());
    timingPauseSpin = new QDoubleSpinBox();
    timingPauseSpin->setValue(appSetting->value("window/timing/pause", 4).toDouble());

    QGridLayout *timingLayout = new QGridLayout;
    timingLayout->addWidget(timingUpLabel, 0, 0);
    timingLayout->addWidget(timingUpSpin, 0, 1);
    timingLayout->addWidget(timingDownLabel, 1, 0);
    timingLayout->addWidget(timingDownSpin, 1, 1);
    timingLayout->addWidget(timingPauseLabel, 2, 0);
    timingLayout->addWidget(timingPauseSpin, 2, 1);

    timingGroup->setLayout(timingLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(timingGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void GeneralPage::save(){
    appSetting->setValue("window/timing/uptext", timingUpSpin->value());
    appSetting->setValue("window/timing/downtext", timingDownSpin->value());
    appSetting->setValue("window/timing/pause", timingPauseSpin->value());
}

DataBasePage::DataBasePage(QWidget *parent)
    : QWidget(parent)
{
    QLabel* notReady = new QLabel(tr("will appear in the next version ELearnTab"));
    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(notReady);
    textLayout->addStretch(1);
    setLayout(textLayout);
}

void DataBasePage::save(){

}

SkinPage::SkinPage(QWidget *parent)
    : QWidget(parent)
{
    QLabel* notReady = new QLabel(tr("will appear in the next version ELearnTab"));
    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(notReady);
    textLayout->addStretch(1);
    setLayout(textLayout);
}

void SkinPage::save(){

}


LanguagePage::LanguagePage(QWidget *parent)
    : QWidget(parent)
{
    QLabel* notReady = new QLabel(tr("will appear in the next version ELearnTab"));
    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(notReady);
    textLayout->addStretch(1);
    setLayout(textLayout);
}


ApiPage::ApiPage(QWidget *parent)
    : QWidget(parent)
{
    QLabel* notReady = new QLabel(tr("will appear in the next version ELearnTab"));
    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(notReady);
    textLayout->addStretch(1);
    setLayout(textLayout);
}


HelpPage::HelpPage(QWidget *parent)
    : QWidget(parent)
{
    QLabel* helpDragDrop = new QLabel(tr("Drag and drop: \n  You can select a word in another application \n  and grasping, move it in ELearnTab to translate."));
    QLabel* helpMove = new QLabel(tr("Move application: \n  To move an application on the desktop, \n  just click on the app, hold and drag."));
    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(helpDragDrop);
    textLayout->addSpacing(10);
    textLayout->addWidget(helpMove);
    textLayout->addStretch(1);
    setLayout(textLayout);
}

