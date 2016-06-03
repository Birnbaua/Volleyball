#include "ftploader.h"

FTPLoader::FTPLoader(QString fileName, QString ftpurl, QString ftpuser, QString ftppw)
{
	this->fileName = fileName;
	this->ftpuser = ftpuser;
	this->ftppw = ftppw;
	this->ftpurl = ftpurl;

	uploadName = "./upload/data.db";

	nam = new QNetworkAccessManager(this);
	connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadFinished(QNetworkReply*)));
}

FTPLoader::~FTPLoader()
{

}

void FTPLoader::startUpload()
{
	QFile::remove(uploadName);
	QFile::copy(fileName, uploadName);
    uploadFile = new QFile(uploadName);
	
    if(uploadFile->open(QIODevice::ReadOnly))
	{
		emit logMessages("INFO: start uploading to " + ftpurl + ", " + ftpuser + ", " + ftppw);
		QUrl url(ftpurl);
		url.setUserName(ftpuser);
		url.setPassword(ftppw);

    	nam->put(QNetworkRequest(url), uploadFile);
	}
	else
	{
		emit logMessages("ERROR: could not open " + uploadName);
	}
}

void FTPLoader::uploadFinished(QNetworkReply* reply)
{
	if(reply->error())
		emit logMessages("ERROR: upload error " + reply->errorString());
	else
		emit logMessages("INFO: upload finished");

	uploadFile->close();
	reply->deleteLater();
}
