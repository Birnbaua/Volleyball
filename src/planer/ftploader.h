#ifndef FTPLOADER_H
#define FTPLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

class FTPLoader : public QObject 
{
	Q_OBJECT
public:
	explicit FTPLoader(QString fileName, QString ftpurl, QString ftpuser, QString ftppw);
	~FTPLoader();

public slots:
	void startUpload();
	void uploadFinished(QNetworkReply* reply);

signals:
    void logMessages(QString);

private:
	QNetworkAccessManager *nam;
	QFile *uploadFile;
	QString fileName, ftpurl, ftpuser, ftppw, uploadName;
};

#endif // FTPLOADER_H
