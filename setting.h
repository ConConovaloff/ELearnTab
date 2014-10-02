#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QSettings>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class GlobalSetting : public QSettings{
public:
    static GlobalSetting* getObj(); //Singleton
private:
    GlobalSetting(const QString &fileName, Format format, QObject *parent = 0);
    static GlobalSetting* m_instance;
};

extern GlobalSetting* appSetting;

//###################################
// setting QStackedWidget
//###################################

class QDoubleSpinBox;

class GeneralPage : public QWidget
{
public:
    GeneralPage(QWidget *parent = 0);
    void save();
private:
    QDoubleSpinBox *timingUpSpin;
    QDoubleSpinBox *timingDownSpin;
    QDoubleSpinBox *timingPauseSpin;
};

class DataBasePage : public QWidget
{
public:
    DataBasePage(QWidget *parent = 0);
    void save();
};

class SkinPage : public QWidget
{
public:
    SkinPage(QWidget *parent = 0);
    void save();
};

class LanguagePage : public QWidget
{
public:
    LanguagePage(QWidget *parent = 0);
    void save();
};

class ApiPage : public QWidget
{
public:
    ApiPage(QWidget *parent = 0);
    void save();
};

class HelpPage : public QWidget
{
public:
    HelpPage(QWidget *parent = 0);
    void save();
};


//###################################
//Setting window
//###################################

class SettingWin : public QDialog
{
    Q_OBJECT
public:
    explicit SettingWin(QDialog *parent = 0);

signals:

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void save();
private:
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

    SkinPage* skinPage ;
    DataBasePage* dataBasePage;
    GeneralPage* generalPage;
    LanguagePage* languagePage;
    ApiPage* apiPage;
    HelpPage* helpPage;
};


#endif // SETTING_H
