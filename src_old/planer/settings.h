#ifndef SETTINGS
#define SETTINGS

#include "database_v1.3.h"

class settings : public QObject
{
    Q_OBJECT
public:
    typedef struct
    {
        QString sysFilePath;
        QString pdfPath;
        int anzFelder;
        int krSpiele;
        QString startTurnier;
        int pauseVrZw;
        int pauseZwKr;
        int pauseKrPl;
        int satzVr;
        int minSatzVr;
        int pauseMinVr;
        int satzZw;
        int minSatzZw;
        int pauseMinZw;
        int satzKr;
        int minSatzKr;
        int pauseMinKr;
        int satzPl;
        int minSatzPl;
        int zeitFinale;
        int pausePlEhrung;
    } dataUi;
    
    settings(database *m_Db)
    {
        this->m_Db = m_Db;
    }

    // check double team names
    bool checkDoubleTeamNames(QSqlTableModel *model)
    {
        int count = 0;
        bool twoteams = false;
        QString team = "";

        for(int row = 0, col = 1; col < model->columnCount();)
        {
            team = model->index(row,col).data().toString();
            for(int i = 0; i < model->rowCount(); i++)
            {
                for(int j = 1; j < model->columnCount(); j++)
                {
                    if(team == model->index(i,j).data().toString() && team != "" )
                    {
                        count++;
                    }
                    if(count > 1)
                    {
                        twoteams = true;
                        break;
                    }
                }
            }
            count = 0;
            row++;
            if(row == model->rowCount())
            {
                col++;
                row = 0;
            }
        }

        if(!twoteams)
        {
            return true;
        }

        return false;
    }

    // get field names
    QStringList getFieldNames()
    {
        QList<QStringList> fieldNameList = m_Db->read("SELECT feldname FROM felder ORDER BY id ASC");
        QStringList fieldNames;

        foreach(QStringList fieldName, fieldNameList)
            fieldNames << fieldName.at(0);

        return fieldNames;
    }

    // get teams count
    int getTeamsCount(QSqlTableModel *model)
    {
        int msCount = 0;

        for(int i = 0; i < model->columnCount(); i++)
        {
            for(int x = 0; x < model->rowCount(); x++)
            {
                if(model->record(x).value(i).toString() != "")
                    msCount++;
            }
        }

        // mscount - 5 to remove id colums from count
        return msCount - 5;
    }

    // set fields table rows
    void setFieldsTableRows(int spinBoxCount)
    {
        int rowCount = m_Db->read("SELECT id FROM felder").count();

        if (rowCount < spinBoxCount)
        {
            for (int i = rowCount + 1; i <= spinBoxCount; i++)
                m_Db->write("INSERT INTO felder VALUES(" + QString::number(i) + ",'')");
        }
        else if(rowCount > spinBoxCount)
        {
            m_Db->write("DELETE FROM felder WHERE id > " + QString::number(spinBoxCount));
        }
    }

    // reset teams table
    void resetTeams()
    {
        QStringList insertRows;

        insertRows << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h) VALUES(0,'','','','','','')"
        << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h) VALUES(1,'','','','','','')"
        << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h) VALUES(2,'','','','','','')"
        << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h) VALUES(3,'','','','','','')"
        << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h) VALUES(4,'','','','','','')";

        m_Db->write("DELETE FROM mannschaften");

        foreach(QString insertRow, insertRows)
            m_Db->write(insertRow);
    }

    // set ui controls with values from vars
    void updateSettingsToUi()
    {
        // read config from database
        readConfig();

        // send data to mainform
        emit updateUi(m_DataSettings);
    }
    
    // reset configuration
    void resetConfig()
    {
        // reset config with default parameters
        writeConfig(4, 1, "10:00", 0, 0, 0, 1, 10, 0, 1, 10, 0, 1, 10, 0, 1, 10, 15, 30);
    }
    
public slots:
    // update configuration ui controls to vars and write to database
    void updateUiToSettings(dataUi m_DataSettings)
    {
        this->m_DataSettings = m_DataSettings;

        // write config to database
        writeConfig(m_DataSettings.anzFelder, m_DataSettings.krSpiele, m_DataSettings.startTurnier, m_DataSettings.pauseVrZw, 
            m_DataSettings.pauseZwKr, m_DataSettings.pauseKrPl, m_DataSettings.satzVr, m_DataSettings.minSatzVr, 
            m_DataSettings.pauseMinVr, m_DataSettings.satzZw, m_DataSettings.minSatzZw, m_DataSettings.pauseMinZw, 
            m_DataSettings.satzKr, m_DataSettings.minSatzKr, m_DataSettings.pauseMinKr, m_DataSettings.satzPl, 
            m_DataSettings.minSatzPl, m_DataSettings.zeitFinale, m_DataSettings.pausePlEhrung);
    }
    
signals:
    // send log msg
    void settingsLog(QString);

    // update ui
    void updateUi(dataUi);

private:
    // read configuration from database
    void readConfig()
    {
        m_Config = m_Db->createSqlQueryModel("select * from configuration");

        m_DataSettings.sysFilePath = m_Config->record(0).value("sysfilepath").toString();
        m_DataSettings.pdfPath = m_Config->record(0).value("pdfpath").toString();
        m_DataSettings.anzFelder = m_Config->record(0).value("anzfelder").toInt();
        m_DataSettings.krSpiele = m_Config->record(0).value("kreuzspiele").toInt();
        m_DataSettings.startTurnier = m_Config->record(0).value("startturnier").toString();
        m_DataSettings.pauseVrZw = m_Config->record(0).value("pausevrzw").toInt();
        m_DataSettings.pauseZwKr = m_Config->record(0).value("pausezwkr").toInt();
        m_DataSettings.pauseKrPl = m_Config->record(0).value("pausekrpl").toInt();
        m_DataSettings.satzVr = m_Config->record(0).value("satzvr").toInt();
        m_DataSettings.minSatzVr = m_Config->record(0).value("minsatzvr").toInt();
        m_DataSettings.pauseMinVr = m_Config->record(0).value("pauseminvr").toInt();
        m_DataSettings.satzZw = m_Config->record(0).value("satzzw").toInt();
        m_DataSettings.minSatzZw = m_Config->record(0).value("minsatzzw").toInt();
        m_DataSettings.pauseMinZw = m_Config->record(0).value("pauseminzw").toInt();
        m_DataSettings.satzKr = m_Config->record(0).value("satzkr").toInt();
        m_DataSettings.minSatzKr = m_Config->record(0).value("minsatzkr").toInt();
        m_DataSettings.pauseMinKr = m_Config->record(0).value("pauseminkr").toInt();
        m_DataSettings.satzPl = m_Config->record(0).value("satzpl").toInt();
        m_DataSettings.minSatzPl = m_Config->record(0).value("minsatzpl").toInt();
        m_DataSettings.zeitFinale = m_Config->record(0).value("zeitfinale").toInt();
        m_DataSettings.pausePlEhrung = m_Config->record(0).value("pauseplehrung").toInt();
    }

    // write configuration to database
    void writeConfig(int anzfelder, int kreuzspiele, QString startturnier, int pausevrzw, int pausezwkr, int pausekrpl, int satzvr, int minsatzvr, int pauseminvr, int satzzw, int minsatzzw, int pauseminzw, int satzkr, int minsatzkr, int pauseminkr, int satzpl, int minsatzpl, int zeitfinale, int pauseplehrung)
    {
        m_Db->write("UPDATE configuration SET anzfelder = " + QString::number(anzfelder)
                    + ", kreuzspiele = " + QString::number(kreuzspiele) + ", startturnier = '" + startturnier
                    + "', pausevrzw = " + QString::number(pausevrzw) + ", pausezwkr = " + QString::number(pausezwkr)
                    + ", pausekrpl = " + QString::number(pausekrpl) + ", satzvr = " + QString::number(satzvr)
                    + ", minsatzvr = " + QString::number(minsatzvr) + ", pauseminvr = " + QString::number(pauseminvr)
                    + ", satzzw = " + QString::number(satzzw) + ", minsatzzw = " + QString::number(minsatzzw)
                    + ", pauseminzw = " + QString::number(pauseminzw) + ", satzkr = " + QString::number(satzkr)
                    + ", minsatzkr = " + QString::number(minsatzkr) + ", pauseminkr = " + QString::number(pauseminkr)
                    + ", satzpl = " + QString::number(satzpl) + ", minsatzpl = " + QString::number(minsatzpl)
                    + ", zeitfinale = " + QString::number(zeitfinale) + ", pauseplehrung = " + QString::number(pauseplehrung) + " WHERE id = 1");
    }

    database *m_Db;

    QSqlTableModel *m_Teams, *m_Felder;
    QSqlQueryModel *m_Config;

    // data exchange for main form
    dataUi m_DataSettings;
    
    bool msChanged, configChanged, vrChange, zwChange, krChange, plChange;
    int anzFelder, krSpiele, pauseVrZw, pauseZwKr, pauseKrPl, satzVr, minSatzVr, pauseMinVr, satzZw, minSatzZw, pauseMinZw, satzKr, minSatzKr, pauseMinKr, satzPl, minSatzPl, zeitFinale, pausePlEhrung, spiel, runde;
    QString sysFilePath, pdfPath, startTurnier;
};

#endif // SETTINGS
